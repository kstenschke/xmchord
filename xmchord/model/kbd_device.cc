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

#include <xmchord/model/kbd_device.h>
#include <iostream>

namespace model {

int KbdDevice::GetDeviceHandle() {
  std::cout << "Select keyboard device\n";
  std::cout << "----------------------\n\n";

  std::vector<std::string> devices;
  getDevicesByPath(&devices, "/dev/input/by-path");
  int amount_devices_by_path = devices.size();
  getDevicesByPath(&devices, "/dev/input/by-id");

  PrintDevicesList(devices, amount_devices_by_path);
  int device_num = ChoseDevice();

  std::string command = "ls " + devices[device_num] + " | head -1";
  std::string kbd_path = helper::System::GetShellResponse(command.c_str());

  if (kbd_path.empty()
        || helper::Textual::Contains(kbd_path, "No such file or directory")
  ) {
      printf("Failed to detect keyboard.\n");

      return -1;
  }

  kbd_path = helper::Textual::GetSubStrBefore(kbd_path, "\n");
  const char *pDeviceKeyboard = kbd_path.c_str();

  int file_handle = open(pDeviceKeyboard, O_RDONLY);

  if (file_handle == -1)
    printf(
        "ERROR opening keyboard %s, try running with sudo \n",
        pDeviceKeyboard);

  return file_handle;
}

int KbdDevice::ChoseDevice() {
  std::cout << "\nNumber: ";
  std::string choice;
  std::cin >> choice;

  return std::stoi(choice) - 1;
}

void KbdDevice::getDevicesByPath(
    std::vector<std::string> *devices,
    const std::string &device_path) {
  std::string device_paths = helper::System::GetShellResponse(
      ("find " + device_path + R"( -printf "%f\n")").c_str());

  auto found_devices = helper::Textual::Explode(device_paths, '\n');

  int index = 0;
  for (auto &device : found_devices) {
    ++index;

    if (index == 1) continue;  // skip 1st entry (is path itself)

    device.insert(0, device_path + "/");  // prefix device name w/ path
    devices->push_back(device);
  }
}

void KbdDevice::PrintDevicesList(const std::vector<std::string> &devices,
                                int amount_devices_by_path) {
  int num = 1;
  for (auto &device : devices) {
    if (helper::Textual::StartsWith(device.c_str(), "by-")) continue;

    std::cout << num << " - " << device << '\n';

    if (num == amount_devices_by_path) std::cout << '\n';

    ++num;
  }
}

}  // namespace model
