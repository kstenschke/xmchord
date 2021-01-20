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

#ifndef XMCHORD_MODEL_ACTION_READER_H_
#define XMCHORD_MODEL_ACTION_READER_H_

#include <xmchord/helper/file.h>
#include <xmchord/helper/textual.h>
#include <dirent.h>
#include <cstdio>
#include <iostream>
#include <string>

namespace model {

class ActionReader {
 public:
  explicit ActionReader(const std::string &path = "actions");

  static std::string CollectActionFilenames(const std::string &path_actions);

  void PrintActionsWithComments();

 private:
  std::string path_actions_;
  DIR *dir_actions_;
  uint8_t len_longest_filename_;
  uint8_t amount_actions_ = 0;
  std::string output_;

  static void CollectActionsFilenames(std::string *filenames, DIR *dir_actions);

  void RenderActionsInfo();

  char *GetActionContent(const char *path_file);

  static std::string ExtractComments(const char *script);

  static char* ExtractSingleComment(const char *script,
                                    int offset_start_comment);

  std::string WrapOutputLine(const std::string &line);

  void AppendSegmentPreWrapped(const std::string &line,
                               size_t len_chording_identifier,
                               const std::string &segment,
                               uint16_t segment_len,
                               std::string *line_wrapped,
                               uint16_t *current_line_length);
};

}  // namespace model

#endif  // XMCHORD_MODEL_ACTION_READER_H_
