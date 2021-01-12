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

// Build reference of given global and local action shell script files
std::string ActionReader::GetActionFiles(
    const std::string &path_actions) {
  DIR *dir_actions =  opendir(path_actions.c_str());
  bool has_actions = dir_actions != nullptr;

  if (!has_actions) {
    perror("Error: Failed opening actions directory.");

    return "";
  }

  std::string files = "\n";

  return GetActionsInPath(files, dir_actions);
}

std::string &ActionReader::GetActionsInPath(std::string &files,
                                            DIR *p_dirstream) {
  struct dirent *ent;

  while ((ent = readdir(p_dirstream)) != nullptr) {
    if (ent->d_name[0] != '.'  // exclude hidden files
        && helper::Textual::EndsWith(ent->d_name, ".sh"))
      files = files.append(ent->d_name).append("\n");
  }

  closedir(p_dirstream);

  return files;
}

// Iterate over "actions" directory at same path as xmchord binary,
// output file path + name and their contained comments (having "#:" prefix)
void ActionReader::PrintActionsWithComments() {
  std::string path_actions = "actions";
  DIR *dir_actions = opendir(path_actions.c_str());
  auto has_actions = dir_actions != nullptr;

  if (!has_actions) {
    std::cerr << "Error: Failed opening actions directory";

    return;
  }

  std::string files, output;

  PrintActionsInDirectoryWithComments(output, files, dir_actions, path_actions);
  closedir(dir_actions);

  std::cout << "\n" << helper::Textual::SubstrCount(output, "\n")
            << " xmchord actions found:\n\n"
            << output << "\n";
}

void ActionReader::PrintActionsInDirectoryWithComments(std::string &output,
                                                       std::string &files,
                                                       DIR *path_actions,
                                                       std::string &path,
                                                       bool check_unique) {
  struct dirent *ent;

  while ((ent = readdir(path_actions)) != nullptr) {
    if (ent->d_type != DT_REG  // Skip everything but regular files
        // Skip already listed files (local actions precede)
        || (check_unique && helper::Textual::Contains(files, ent->d_name))
    ) continue;

    char *file = ent->d_name;
    files = files.append(file).append("\n");

    output += path + "/" + file;

    auto *action_content = GetActionContent(path, file);

    if (nullptr == action_content) return;

    auto len_file_path = path.length() + strlen(file) + 1;
    output += "\t = ";

    auto comment = ExtractCommentLines(action_content);;
    output += comment;

    auto offset_last_line = output.find_last_of('\n');

    if (std::string::npos != offset_last_line) {
      auto last_line = output.substr(offset_last_line);

      if (last_line.length() >  130)
        output = output.substr(0, offset_last_line)
            .append(WrapOutputLine(len_file_path, last_line));
    }

    output += '\n';
  }
}

std::string ActionReader::WrapOutputLine(
    unsigned long len_file_path,
    const std::string &last_line) {
  auto segments = helper::Textual::Explode(last_line, ' ');

  std::string last_line_wrapped;
  uint16_t current_line_length = 0;

  for (const auto& segment : segments) {
    auto segment_len = segment.length();

    if (current_line_length + segment_len > 80) {
      last_line_wrapped += "\n" + helper::Textual::Repeat(" ", len_file_path)
          + "\t\t" + segment;

      current_line_length = segment_len;
    } else {
      last_line_wrapped += " " + segment;
      current_line_length += segment_len + 1;
    }
  }
  return last_line_wrapped;
}

char *ActionReader::GetActionContent(const std::string &path,
                                     const char *file) {
  std::string filename = std::string(path) + "/" + file;
  FILE *file_stream = fopen(filename.c_str(), "rb");

  if (!file_stream) {
    std::cout << "Failed opening " << filename << "\n";

    return nullptr;
  }

  fseek(file_stream, 0, SEEK_END);
  auto length_file_content = ftell(file_stream);
  fseek(file_stream, 0, SEEK_SET);

  if (length_file_content == 0) {
    fclose(file_stream);
    std::cout << "File is empty: " << filename << "\n";

    return nullptr;
  }

  char *content =
      static_cast<char *>(malloc(static_cast<size_t>(length_file_content)));

  fread(content, 1, static_cast<size_t>(length_file_content), file_stream);
  fclose(file_stream);

  return content;
}

std::string ActionReader::ExtractCommentLines(const char *script) {
  uint16_t script_len = strlen(script);
  uint16_t offset_start = 0;
  std::string comment;

  do {
    int offset_start_comment_line = helper::Textual::StrPos(
        const_cast<char *>(script),
        const_cast<char *>("\n#:"),
        offset_start);

    if (offset_start_comment_line != -1
        && offset_start_comment_line < script_len) {
      char *comment_line =
          ExtractSingleComment(script, offset_start_comment_line + 3);

      comment += comment_line;

      offset_start += offset_start_comment_line + 4;

      free(comment_line);
    } else {
      if (offset_start == 0) comment += "\t- No #:-comment line found\n";

      break;
    }
  } while (true);

  return comment;
}

char* ActionReader::ExtractSingleComment(const char *buffer,
                                         int offset_start_comment) {
  int offset_end_comment_line = helper::Textual::StrPos(
      const_cast<char *>(buffer),
      const_cast<char *>("\n"),
      offset_start_comment);

  int comment_line_length =
      offset_end_comment_line - offset_start_comment;

  auto *comment_line = static_cast<char *>(malloc(comment_line_length + 1));

  strncpy(comment_line, buffer + offset_start_comment, comment_line_length);
  comment_line[comment_line_length] = '\0';

  return comment_line;
}
}  // namespace model
