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

#include <xmchord/helper/system.h>

namespace helper {

// Get absolute path to application executable
// TODO(kay): can use getenv("PWD") instead?
std::string System::GetBinaryPath(char **argv, size_t strLenExecutableName) {
  char *path_relative = argv[0];
  char absolute_path[255];
  char *ptr;

  ptr = realpath(path_relative, absolute_path);

  auto len_without_binary = std::strlen(absolute_path) - strLenExecutableName;

  return std::string(ptr).substr(0, len_without_binary);
}

void System::RunShellCommand(const char *command) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
  system(command);
#pragma clang diagnostic pop
}

std::string System::GetShellResponse(const char *command) {
  FILE *fp;
  char path[1035];

  // Open the command for reading
  fp = popen(command, "r");

  if (fp ==nullptr)
    return "Failed to run command";

  // Read the output one line at a time
  std::string result;

  while (fgets(path, sizeof(path), fp) !=nullptr) result += path;

  pclose(fp);

  return result;
}

}  // namespace helper

