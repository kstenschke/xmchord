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

#include <xmchord/helper/textual.h>
#include <dirent.h>
#include <cstdio>
#include <iostream>
#include <string>

namespace model {

class ActionReader {
 public:
  static std::string GetActionFiles(const std::string& path_actions);

  static void PrintActionsWithComments();
 private:
  static void PrintActionsInPathWithComments(std::string *output,
                                             std::string *files,
                                             DIR *path_actions,
                                             const std::string &path,
                                             bool check_unique = false);

  static void GetActionsInPath(std::string *files, DIR *dir_stream);

  static char *GetActionContent(const std::string &path, const char *file);

  static std::string ExtractCommentLines(const char *script);

  static char* ExtractSingleComment(const char *buffer,
                                    int offset_start_comment);

  static std::string WrapOutputLine(uint8_t len_file_path,
                                    const std::string &last_line);
};

}  // namespace model

#endif  // XMCHORD_MODEL_ACTION_READER_H_
