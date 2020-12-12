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

#include <xmchord/helper/file.h>

namespace helper {

bool File::FileExists(const std::string &name) {
  return access(name.c_str(), F_OK) != -1;
}

bool File::Remove(const char *file_path) {
  return remove(file_path) == 0;
}

std::string File::GetLastPathSegment(std::string path) {
  if (path.find('/') == std::string::npos) return path;

  std::vector<std::string> parts = helper::Textual::Explode(path, '/');

  return parts[parts.size() - 1];
}

std::string File::GetActionFiles(const std::string &path_actions) {
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

    if (strcmp(ent->d_name, ".") != 0 &&
        strcmp(ent->d_name, "..") != 0
        ) {
      files = files.append(file).append("\n");

      if (strlen(file) - 3 == helper::Textual::StrPos(
          file,
          const_cast<char *>(".sh"),
          0)) {
        std::string filename = "actions/";
        filename = filename.append(file);
        FILE *f = fopen(filename.c_str(), "rb");

        char *buffer = nullptr;

        if (f) {
          fseek(f, 0, SEEK_END);
          auto length_file_content = ftell(f);
          fseek(f, 0, SEEK_SET);

          buffer = static_cast<char *>(malloc(
              static_cast<size_t>(length_file_content)));

          std::cout << file;

          if (buffer)
            fread(buffer, 1, static_cast<size_t>(length_file_content), f);

          fclose(f);
        } else {
          std::cout << "Failed opening " << filename << "\n";
        }

        if (buffer) {
          int offset_start_comment_line =
              helper::Textual::StrPos(buffer, const_cast<char *>("\n#:"), 0);

          if (offset_start_comment_line != -1) {
            offset_start_comment_line += 3;

            int offset_endC_comment_line =
                helper::Textual::StrPos(
                    buffer,
                    const_cast<char *>("\n"),
                    offset_start_comment_line);

            int comment_line_length =
                offset_endC_comment_line - offset_start_comment_line;

            auto *comment_line =
                static_cast<char *>(malloc(comment_line_length + 1));

            strncpy(
                comment_line,
                buffer + offset_start_comment_line,
                comment_line_length);

            comment_line[comment_line_length] = '\0';

            std::cout << "\t- " << comment_line << "\n";

            free(comment_line);
          } else {
            std::cout << "\t- No #:-comment line found\n";
          }
        }
      }
    }
  }

  closedir(dir);
}

std::string File::GetFileContents(const std::string &filename) {
  std::ifstream file(filename);

  return GetFileContents(file);
}

std::string File::GetFileContents(std::ifstream &file) {
  // Get file size
  file.seekg(0, std::ios::end);
  std::streampos length = file.tellg();
  file.seekg(0, std::ios::beg);

  // Read the whole file into the buffer
  std::vector<char> buffer(static_cast<uint64_t>(length));
  file.read(&buffer[0], length);

  std::string str(buffer.begin(), buffer.end());

  return str;
}

bool File::WriteToNewFile(const std::string &filename,
                          const std::string &content) {
  std::ofstream out_file(filename);
  out_file << content;
  out_file.close();

  return File::FileExists(filename);
}

}  // namespace helper
