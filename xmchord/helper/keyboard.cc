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

#include <xmchord/helper/keyboard.h>

namespace helper {

int Keyboard::GetDeviceHandle() {
  // Detect keyboard
  std::string command = "ls /dev/input/by-path/*-event-kbd | head -1";
  std::string keyboardPath = helper::System::GetShellResponse(command.c_str());

  if (keyboardPath.empty()
        || helper::Textual::Contains(keyboardPath, "No such file or directory")
  ) {
      printf("Failed to detect keyboard.\n");

      return -1;
  }

  // Reduce to everything before 1st newline
  keyboardPath = helper::Textual::GetSubStrBefore(keyboardPath, "\n");

  const char *pDeviceKeyboard = keyboardPath.c_str();

  int file_handle = open(pDeviceKeyboard, O_RDONLY);

  if (file_handle == -1)
    printf(
        "ERROR opening keyboard %s, try running with sudo \n",
        pDeviceKeyboard);

  return file_handle;
}

}  // namespace helper
