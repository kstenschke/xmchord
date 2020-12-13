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

#ifndef XMCHORD_MODEL_KBD_DEVICE_H_
#define XMCHORD_MODEL_KBD_DEVICE_H_

#include <xmchord/helper/system.h>
#include <xmchord/helper/textual.h>
#include <xmchord/helper/file.h>

#include <fcntl.h>
#include <iostream>
#include <string>
#include <vector>

namespace model {
class KbdDevice {
 public:
  KbdDevice();

  static int GetDeviceHandle();
  void SetAmountDevicesByPath(int amount);

 private:
  static const std::string kPathPref;
  std::string device_name_preselect;
  int device_index_preselect = -1;
  std::vector<std::string> devices;
  int amount_devices_by_path{};

  bool GetDevicePreference();

  void GetDevicesByPath(const std::string &device_path,
                        bool set_amount_devices_in_path = false);

  void PrintDevicesList();

  int ChoseDevice();

  bool SaveDevicePreference(int device_num);

  std::string GetDevicePathByIndex(int index_device);
};  // class Keyboard
}  // namespace model

#endif  // XMCHORD_MODEL_KBD_DEVICE_H_
