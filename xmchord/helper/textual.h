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

#ifndef XMCHORD_HELPER_TEXTUAL_H_
#define XMCHORD_HELPER_TEXTUAL_H_

#include <cstring>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace helper {
namespace Textual {

const char ANSI_BOLD[] = "\033[1m";
const char ANSI_REVERSE[] = "\033[7m";
const char ANSI_RESET[] = "\033[0m";

int StrPos(char *hay, char *needle, int offset);

bool Contains(const std::string &haystack, const char *needle);

std::string GetSubStrBefore(
    const std::string &haystack,
    const char *needle,
    uint32_t pos = 0);

std::vector<std::string> Explode(std::string const &str, char delimiter);

bool StartsWith(const char *str, const char *prefix);
bool EndsWith(std::string const &str, std::string const &ending);

int SubstrCount(const std::string& haystack, const std::string& needle);

std::string Repeat(const std::string& str, u_int16_t amount);

}  // namespace Textual
}  // namespace helper

#endif  // XMCHORD_HELPER_TEXTUAL_H_
