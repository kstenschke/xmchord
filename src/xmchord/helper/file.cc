/*
  Copyright (c) 2019, Kay Stenschke
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of  nor the names of its contributors may be used to
     endorse or promote products derived from this software without specific
     prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include <string>
#include <fstream>
#include <vector>
#include <zconf.h>
#include <dirent.h>
#include <cstring>
#include <iostream>

#include "file.h"
#include "textual.h"

namespace helper {

bool File::FileExists(const std::string &name) {
  return access(name.c_str(), F_OK) != -1;
}

std::string File::GetActionFiles(std::string path_actions) {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(path_actions.c_str())) == nullptr) {
	perror("Error: Failed opening actions directory.");
	return "";
  }
  std::string files;
  while ((ent = readdir(dir)) != nullptr) {
	std::string file = ent->d_name;
	if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
	  // @todo filter for files ending w/ ".sh"
	  files = files.append( file ).append("\n");
	}
  }
  closedir(dir);
  return files;
}

// Iterate over actions/\*.sh ActionRunner files, output filenames followed by contained comments w/ prefix "#:"
void File::TraceActions() {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir("actions")) == nullptr) {
	perror("Error: Failed opening directory");
	return;
  }
  std::string files;
  while ((ent = readdir(dir)) != nullptr) {
	char *file = ent->d_name;
	if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
	  files = files.append(file).append("\n");

	  char * buffer = nullptr;
	  long length;
	  if (strlen(file) - 3 ==helper::Textual::StrPos(file, const_cast<char *>(".sh"), 0)) {
		std::string filename = "actions/";
		filename = filename.append(file);
		FILE *f = fopen(filename.c_str(), "rb");
		if (f) {
		  fseek(f, 0, SEEK_END);
		  length = ftell(f);
		  fseek(f, 0, SEEK_SET);
		  buffer = static_cast<char *>(malloc(static_cast<size_t>(length)));

		  std::cout << file;

		  if (buffer) {
			fread(buffer, 1, static_cast<size_t>(length), f);
		  }
		  fclose(f);
		} else {
		  std::cout << "Failed opening " << filename << "\n";
		}

		if (buffer) {
		  int offsetStartCommentLine = helper::Textual::StrPos(buffer, const_cast<char *>("\n#:"), 0);
		  if (offsetStartCommentLine != -1) {
			offsetStartCommentLine += 3;
			int offsetEndCommentLine = helper::Textual::StrPos(buffer, const_cast<char *>("\n"), offsetStartCommentLine);
			int commentLineLength = offsetEndCommentLine - offsetStartCommentLine;

			auto *commentLine = static_cast<char *>(malloc(commentLineLength + 1));
			strncpy(commentLine, buffer + offsetStartCommentLine, commentLineLength);
			commentLine[commentLineLength] = '\0';

			std::cout << "\t- " << commentLine << "\n";
			free(commentLine);
		  } else {
			std::cout << "\t- No #:-comment line found\n";
		  }
		}
	  }
	}
  }
  closedir(dir);
}

} // namespace helper
