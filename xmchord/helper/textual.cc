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

#include <xmchord/helper/textual.h>

namespace helper {

int Textual::StrPos(char *hay, char *needle, int offset) {
  // TODO(kay): do not use variable length array
  char haystack[strlen(hay)];  // NOLINT [build/c++11]

  strncpy(haystack, hay + offset, strlen(hay) - offset);

  char *p = strstr(haystack, needle);

  return p ? (int)(p - haystack + offset) : -1;
}

bool Textual::Contains(const std::string &haystack, const char *needle) {
  return std::string::npos != haystack.find(needle);
}

std::string Textual::GetSubStrBefore(
    const std::string &haystack,
    const char *needle,
    uint32_t pos) {
  size_t offsetStart = haystack.find(needle, pos);

  return std::string::npos != offsetStart
         ? haystack.substr(0, offsetStart)
         : haystack;
}

// Split given string by given character delimiter into vector of strings
std::vector<std::string> Textual::Explode(std::string const &str,
                                          char delimiter) {
  std::vector<std::string> result;
  std::istringstream iss(str);

  for (std::string token; std::getline(iss, token, delimiter);)
    result.push_back(std::move(token));

  return result;
}

// Check whether given string starts w/ given prefix
bool Textual::StartsWith(const char *str, const char *prefix) {
  return 0 == strncmp(str, prefix, strlen(prefix));
}

// Check whether given string ends w/ given string
bool Textual::EndsWith(std::string const &str, std::string const &ending) {
  return ending.empty()
      || (ending.size() <= str.size()
          && std::equal(ending.rbegin(), ending.rend(), str.rbegin()));
}

int Textual::SubstrCount(const std::string &haystack,
                         const std::string &needle) {
  if (needle.length() == 0) return 0;

  int count = 0;

  for (size_t offset = haystack.find(needle);
       offset != std::string::npos;
       offset = haystack.find(needle, offset + needle.length())) {
    ++count;
  }

  return count;
}

std::string Textual::Repeat(const std::string& str, u_int64_t amount) {
  std::string out;

  for (u_int64_t i = 0; i < amount; i++) out+= str;

  return out;
}

}  // namespace helper
