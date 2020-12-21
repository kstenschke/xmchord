/*
  Copyright (c) Kay Stenschke
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

#include <xmchord/model/action_reader.h>

namespace model {

std::string ActionReader::GetActionFiles(const std::string &path_actions) {
  DIR *dir;
  struct dirent *ent;

  if ((dir = opendir(path_actions.c_str())) == nullptr) {
    perror("Error: Failed opening actions directory.");

    return "";
  }

  std::string files = "\n";

  while ((ent = readdir(dir)) != nullptr) {
    std::string file = ent->d_name;

    if (ent->d_name[0] != '.'  // exclude hidden files
        && helper::Textual::EndsWith(ent->d_name, ".sh"))
      files = files.append(file).append("\n");
  }

  closedir(dir);

  return files;
}

// Iterate over actions/\*.sh ActionRunner files,
// output filenames followed by contained comments w/ prefix "#:"
void ActionReader::PrintListOfActionsWithComments() {
  DIR *dir;
  struct dirent *ent;

  if ((dir = opendir("actions")) == nullptr) {
    std::cerr << "Error: Failed opening actions directory";

    return;
  }

  std::string files;

  while ((ent = readdir(dir)) != nullptr) {
    if (ent->d_type != DT_REG) continue;

    char *file = ent->d_name;
    files = files.append(file).append("\n");

    std::string filename = "actions/";
    filename = filename.append(file);

    FILE *file_stream = fopen(filename.c_str(), "rb");

    if (!file_stream) {
      std::cout << "Failed opening " << filename << "\n";
      continue;
    }

    fseek(file_stream, 0, SEEK_END);
    auto length_file_content = ftell(file_stream);
    fseek(file_stream, 0, SEEK_SET);

    char *buffer =
        static_cast<char *>(malloc(static_cast<size_t>(length_file_content)));

    std::cout << file;

    if (buffer)
      fread(buffer, 1, static_cast<size_t>(length_file_content), file_stream);

    fclose(file_stream);

    if (buffer) {
      int offset_start_comment_line =
          helper::Textual::StrPos(buffer, const_cast<char *>("\n#:"), 0);

      if (offset_start_comment_line != -1) {
        char *comment_line =
            ExtractComment(buffer, offset_start_comment_line + 3);

        std::cout << "\t- " << comment_line << "\n";

        free(comment_line);
      } else {
        std::cout << "\t- No #:-comment line found\n";
      }
    }
  }

  closedir(dir);
}

char *ActionReader::ExtractComment(const char *buffer,
                                   int offset_start_comment) {
  int offset_endC_comment_line =
      helper::Textual::StrPos(
          const_cast<char *>(buffer),
          const_cast<char *>("\n"),
          offset_start_comment);

  int comment_line_length =
      offset_endC_comment_line - offset_start_comment;

  auto *comment_line =
      static_cast<char *>(malloc(comment_line_length + 1));

  strncpy(
      comment_line,
      buffer + offset_start_comment,
      comment_line_length);

  comment_line[comment_line_length] = '\0';

  return comment_line;
}
}  // namespace model
