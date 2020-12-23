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

#ifndef XMCHORD_XMCHORD_H_
#define XMCHORD_XMCHORD_H_

#include <xmchord/model/action_reader.h>
#include <xmchord/model/action_runner.h>
#include <xmchord/helper/system.h>
#include <xmchord/helper/mouse.h>
#include <xmchord/model/keyboard_device_finder.h>
#include <xmchord/helper/file.h>
#include <xmchord/config.h>
#include <linux/input.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

// TODO(kay): store within model instead of using a global string variable
std::string buttons_code;  // NOLINT [build/c++11]

int kbd_code = 0;

model::ActionRunner *action_runner = nullptr;

int InitArgs(int argc,
             char *const *argv,
             std::string *kbd_device_path,
             bool *debug,
             bool *run);

void PrintVersionInfo();
void PrintHelp();

void *KbdWatcher(void *x_void_ptr);

#endif  // XMCHORD_XMCHORD_H_
