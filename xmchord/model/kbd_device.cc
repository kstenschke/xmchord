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

namespace model {

KbdDevice::KbdDevice() {
  GetDevicePreference();
}

bool KbdDevice::GetDevicePreference() {
  if (!helper::File::FileExists(pathPreferences)) return false;

  device_name_preselect = helper::File::GetFileContents(pathPreferences);

  return true;
}

int KbdDevice::GetDeviceHandle() {
  auto *kbd_device = new KbdDevice();

  kbd_device->GetDevicesByPath("/dev/input/by-path", true);
  kbd_device->GetDevicesByPath("/dev/input/by-id");
  kbd_device->PrintDevicesList();

  int index_selected_device = kbd_device->ChoseDevice();
  kbd_device->SaveDevicePreference(index_selected_device);

  auto path_kbd_device =
      kbd_device->GetDevicePathByIndex(index_selected_device);

  if (path_kbd_device.empty()) {
    delete kbd_device;

    return -1;
  }

  int file_handle = open(path_kbd_device.c_str(), O_RDONLY);

  delete kbd_device;

  if (file_handle == -1)
    std::cerr << "Failed opening keyboard: " << path_kbd_device;
  else
    std::cout
      << helper::Textual::ANSI_BOLD
      << "\nChording observer started: "
      << helper::Textual::ANSI_RESET
      << "Mouse + " << path_kbd_device << "\n\n";

  return file_handle;
}

std::string KbdDevice::GetDevicePathByIndex(int index_device) {
  std::string command = "ls " + devices[index_device] + " | head -1";
  std::string kbd_path = helper::System::GetShellResponse(command.c_str());

  if (kbd_path.empty()
      || helper::Textual::Contains(kbd_path, "No such file or directory")
  ) {
    std::cerr
        << "Invalid Device path: "
        << devices[index_device] << "\n";

      return "";
  }

  return helper::Textual::GetSubStrBefore(kbd_path, "\n");
}

int KbdDevice::ChoseDevice() {
  std::cout << "\nNumber";

  if (-1 < device_index_preselect) {
    std::cout << " [" << device_index_preselect << "]";
  }

  std::cout << ": ";

  std::string choice;
  int n = 0;

  while (true) {
    getline(std::cin, choice);
    std::stringstream s(choice);

    if (s >> n) break;

    if (choice.empty()) {
      std::cout << device_index_preselect << "\n";

      return device_index_preselect - 1;
    }
  }

  return std::stoi(choice) - 1;
}

void KbdDevice::GetDevicesByPath(const std::string &device_path,
                                 bool set_amount_devices_in_path) {
  std::string device_paths = helper::System::GetShellResponse(
      ("find " + device_path + R"( -printf "%f\n")").c_str());

  auto devices_in_path = helper::Textual::Explode(device_paths, '\n');

  int index = 0;
  for (auto &device : devices_in_path) {
    ++index;

    if (index == 1) continue;  // skip 1st entry (is path itself)

    device.insert(0, device_path + "/");  // prefix device name w/ path
    devices.push_back(device);
  }

  if (set_amount_devices_in_path) SetAmountDevicesByPath(devices.size());
}

void KbdDevice::SetAmountDevicesByPath(int amount) {
  amount_devices_by_path = amount;
}

void KbdDevice::PrintDevicesList() {
  std::cout
    << helper::Textual::ANSI_BOLD
    << "\nSelect keyboard:\n\n"
    << helper::Textual::ANSI_RESET;

  bool do_preselect = !device_name_preselect.empty();

  int index = 1;
  for (auto &device_name : devices) {
    if (helper::Textual::StartsWith(device_name.c_str(), "by-")) continue;

    auto is_selected = do_preselect
        && device_name.find(device_name_preselect) != std::string::npos;

    if (is_selected) {
      device_index_preselect = index;
      std::cout << helper::Textual::ANSI_REVERSE;
    }

    std::cout << " " << index << " - " << device_name << " \n";

    if (is_selected) std::cout << helper::Textual::ANSI_RESET;

    if (index == amount_devices_by_path) std::cout << '\n';

    ++index;
  }
}

bool KbdDevice::SaveDevicePreference(int device_num) {
  if (helper::File::FileExists(pathPreferences))
    helper::File::Remove(pathPreferences);

  std::string device_identifier =
      helper::File::GetLastPathSegment(devices[device_num]);

  return helper::File::WriteToNewFile(pathPreferences, device_identifier);
}

}  // namespace model
