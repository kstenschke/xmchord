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

ActionReader::ActionReader(const std::string &path) {
  path_actions_ = path;
  dir_actions_ =  opendir(path_actions_.c_str());

  if (nullptr != dir_actions_)
    len_longest_filename_ = helper::File::GeLongestFilenameLength(dir_actions_);
}

std::string ActionReader::CollectActionFilenames(
    const std::string &path_actions) {
  auto dir_actions =  opendir(path_actions.c_str());

  if (dir_actions == nullptr) {
    perror("Error: Failed opening actions directory.");

    return "";
  }

  std::string files = "\n";
  CollectActionsFilenames(&files, dir_actions);

  return files;
}

// Iterate over "actions" directory at same path as xmchord binary,
// output file path + name and their contained comments (having "#:" prefix)
void ActionReader::PrintActionsWithComments() {
  if (dir_actions_ == nullptr) {
    std::cerr << "Error: Failed opening actions directory";

    return;
  }

  RenderActionsInfo();
  closedir(dir_actions_);

  std::cout << "\n" << (unsigned int)amount_actions_
            << " xmchord actions found:\n\n" << output_ << "\n";
}

void ActionReader::RenderActionsInfo() {
  struct dirent *ent;

  while ((ent = readdir(dir_actions_)) != nullptr) {
    if (ent->d_type != DT_REG) continue;  // Skip everything but regular files

    char *filename = ent->d_name;
    output_ += filename;
    ++amount_actions_;

    auto *action_content = GetActionContent(filename);

    if (nullptr == action_content) return;

    auto len_filename = strlen(filename);
    if (len_filename < len_longest_filename_)
      output_ +=
          helper::Textual::Repeat(" ", len_longest_filename_ - len_filename);

    output_ += " = ";

    auto comment = ExtractComments(action_content);
    output_ += comment;

    auto offset_last_line = output_.find_last_of('\n');

    if (std::string::npos != offset_last_line) {
      auto last_line = output_.substr(offset_last_line);

      if (last_line.length() >  130)
        output_ = output_.substr(0, offset_last_line).append(
            WrapOutputLine(last_line));
    }

    output_ += '\n';
  }
}

void ActionReader::CollectActionsFilenames(std::string *filenames,
                                           DIR *dir_actions) {
  struct dirent *ent;

  while ((ent = readdir(dir_actions)) != nullptr) {
    if (ent->d_name[0] != '.'  // exclude hidden files
        && helper::Textual::EndsWith(ent->d_name, ".sh"))
      *filenames = (*filenames).append(ent->d_name).append("\n");
  }

  closedir(dir_actions);
}

char *ActionReader::GetActionContent(const char *path_file) {
  std::string filename = std::string(path_actions_) + "/" + path_file;
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

std::string ActionReader::ExtractComments(const char *script) {
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

char* ActionReader::ExtractSingleComment(const char *script,
                                         int offset_start_comment) {
  int offset_end_comment_line = helper::Textual::StrPos(
      const_cast<char *>(script),
      const_cast<char *>("\n"),
      offset_start_comment);

  int comment_line_length =
      offset_end_comment_line - offset_start_comment;

  auto *comment_line = static_cast<char *>(malloc(comment_line_length + 1));

  strncpy(comment_line, script + offset_start_comment, comment_line_length);
  comment_line[comment_line_length] = '\0';

  return comment_line;
}

std::string ActionReader::WrapOutputLine(const std::string &line) {
  auto segments = helper::Textual::Explode(line, ' ');

  std::string last_line_wrapped;
  size_t len_chording_identifier = 0;
  uint16_t current_line_length = 0;

  for (const auto& segment : segments) {
    auto segment_len = segment.length();

    if (current_line_length + segment_len > 80) {
      AppendSegmentPreWrapped(line,
                              len_chording_identifier,
                              segment,
                              segment_len,
                              &last_line_wrapped,
                              &current_line_length);
    } else {
      last_line_wrapped += " " + segment;
      current_line_length += segment_len + 1;
    }
  }
  return last_line_wrapped;
}

void ActionReader::AppendSegmentPreWrapped(
    const std::string &line, size_t len_chording_identifier,
    const std::string &segment, uint16_t segment_len,
    std::string *line_wrapped, uint16_t *current_line_length) {
  if (len_chording_identifier == 0) {
    len_chording_identifier = line.find(" -");

    if (len_chording_identifier == std::string::npos)
      len_chording_identifier = len_longest_filename_ + 3;
  }

  *line_wrapped +=
      "\n" + helper::Textual::Repeat(" ", len_chording_identifier)
      + segment;

  *current_line_length = segment_len;
}
}  // namespace model
