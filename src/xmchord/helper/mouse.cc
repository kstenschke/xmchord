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

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>

//#include <zconf.h>
#include "vendor/zlib/zconf.h"

#include "mouse.h"

namespace helper {

int Mouse::GetDeviceHandle() {
  const char *pDeviceMice = "/dev/input/mice";
  int file_handle = open(pDeviceMice, O_RDONLY);

  if(file_handle == -1) {
    printf("ERROR Opening %s, try running with sudo \n", pDeviceMice);

    return -1;
  }

  return file_handle;
}

std::string Mouse::GetEventCode(const unsigned char *mouse_data) {
  // mouse_data[0]: buttons
  // mouse_data[1]: x movement
  // mouse_data[2]: y movement

  int mb_1 = mouse_data[0] & 0x1;	// left
  int mb_2 = mouse_data[0] & 0x2;	// right
  int mb_3 = mouse_data[0] & 0x3;
  int mb_4 = mouse_data[0] & 0x4;	// middle
  int mb_5 = mouse_data[0] & 0x5;
  int mb_6 = mouse_data[0] & 0x6;
  int mb_7 = mouse_data[0] & 0x7;

  // Get movement
  //signed char x, y;
  //x = mouse_data[1];
  //y = mouse_data[2];
  //printf("x=%d, y=%d\n", x, y);

  return helper::Mouse::JoinButtonBytes(mb_1, mb_2, mb_3, mb_4, mb_5, mb_6, mb_7);
}

std::string Mouse::JoinButtonBytes(int mb_1, int mb_2, int mb_3, int mb_4, int mb_5, int mb_6, int mb_7) {
  return
      std::to_string(mb_1)
          .append(std::to_string(mb_2))
          .append(std::to_string(mb_3)
                      .append(std::to_string(mb_4)
                                  .append(std::to_string(mb_5)
                                              .append(std::to_string(mb_6)
                                                          .append(std::to_string(mb_7)
                                                          )
                                              )
                                  )
                      )
          );
}

} // namespace helper
