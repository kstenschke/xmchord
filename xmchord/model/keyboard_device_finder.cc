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

#include <xmchord/model/keyboard_device_finder.h>

namespace model {

KeyboardDeviceFinder::KeyboardDeviceFinder(const std::string& device_path) {
  if (!device_path.empty()) {
    // Preselect keyboard device from given shell argument "-k=..."
    device_name_selected_ = device_path;
  } else {
    // Preselect keyboard from /var/tmp/xmchord.pref, if it exists
    SetDeviceNameSelectedFromPreference();
  }
}

bool KeyboardDeviceFinder::SetDeviceNameSelectedFromPreference() {
  if (!helper::File::FileExists(kPathPreferences)) return false;

  device_name_selected_ = helper::File::GetFileContents(kPathPreferences);

  return true;
}

int KeyboardDeviceFinder::GetDeviceHandle(const std::string& device_path,
                                          bool list_devices) {
  auto *kbd_finder = new KeyboardDeviceFinder(device_path);

  // Collect available device's paths
  kbd_finder->GetDevicesByPath("/dev/input/by-path", true);
  kbd_finder->GetDevicesByPath("/dev/input/by-id");

  // Identify+select keyboard by matching substring, output list if not found
  if (!kbd_finder->SelectKeyboardFromAvailableDevices(list_devices)) {
    delete kbd_finder;
    return -1;
  }

  kbd_finder->SaveDevicePreference();  // Remember preference for 30 days

  auto path_kbd_device = kbd_finder->GetDevicePathBySelectedIndex();

  if (path_kbd_device.empty()) {
    delete kbd_finder;
    return -1;
  }

  int file_handle = open(path_kbd_device.c_str(), O_RDONLY);

  delete kbd_finder;

  if (file_handle == -1)
    std::cerr << "Failed opening keyboard: " << path_kbd_device;
  else
    std::cout
      << helper::Textual::ANSI_BOLD
      << "Chording observer started: "
      << helper::Textual::ANSI_RESET
      << "Mouse + " << path_kbd_device << "\n\n";

  return file_handle;
}

std::string KeyboardDeviceFinder::GetDevicePathBySelectedIndex() {
  std::string command = "ls " + devices_[device_index_selected_] + " | head -1";
  std::string kbd_path = helper::System::GetShellResponse(command.c_str());

  if (kbd_path.empty()
      || helper::Textual::Contains(kbd_path, "No such file or directory")
  ) {
    std::cerr
        << "Invalid Device path: "
        << devices_[device_index_selected_] << "\n";

      return "";
  }

  return helper::Textual::GetSubStrBefore(kbd_path, "\n");
}

void KeyboardDeviceFinder::GetDevicesByPath(const std::string &device_path,
                                            bool set_amount_devices_in_path) {
  std::string device_paths = helper::System::GetShellResponse(
      ("find " + device_path + R"( -printf "%f\n")").c_str());

  auto devices_in_path = helper::Textual::Explode(device_paths, '\n');

  int index = 0;
  for (auto &device : devices_in_path) {
    ++index;

    if (index == 1) continue;  // skip 1st entry (is path itself)

    device.insert(0, device_path + "/");  // prefix device name w/ path
    devices_.push_back(device);
  }

  if (set_amount_devices_in_path) SetAmountDevicesByPath(devices_.size());
}

void KeyboardDeviceFinder::SetAmountDevicesByPath(int amount) {
  amount_devices_by_path_ = amount;
}

// If preference or -k (or --keyboard) argument given: Use matching device
// If no preference and no -k (and no --keyboard) argument given:
// Use internal keyboard
// If no device matches or list_devices == true: list available devices and exit
//
// Device argument can be given as any substring of the device identifier
// Device preference is stored w/o the path, to handle change of devices order
bool KeyboardDeviceFinder::SelectKeyboardFromAvailableDevices(
    bool list_devices) {
  std::string devices_list;

  bool hasKeyboardPreference = !device_name_selected_.empty();

  if (hasKeyboardPreference) {
    std::cout << "Keyboard preference (/var/tmp/xmchord.pref) found: "
              << device_name_selected_ << "\n";
  } else {
    if (list_devices)
      std::cout << "No keyboard preference (/var/tmp/xmchord.pref) given.\n";
    else
      std::cout << "No keyboard preference (/var/tmp/xmchord.pref) given: "
                   "Use default device and store as preference.\n";
  }

  bool has_preselection = list_devices || hasKeyboardPreference;
  bool has_rendered_selected = false;  // stop upon 1st matching device

  int index = 0;
  for (auto &device_name : devices_) {
    if (helper::Textual::StartsWith(device_name.c_str(), "by-")) continue;

    bool is_selected = false;

    if (!has_rendered_selected) {
      is_selected =
          has_preselection
            ? device_name.find(device_name_selected_) != std::string::npos
            : !list_devices && device_name.find("-kbd") != std::string::npos;
    }

    if (is_selected) {
      device_index_selected_ = index;
      has_rendered_selected = true;

      devices_list += helper::Textual::ANSI_REVERSE;
    }

    devices_list += "  " + device_name + " \n";

    if (is_selected) devices_list += helper::Textual::ANSI_RESET;

    if (index == amount_devices_by_path_) devices_list += '\n';

    ++index;
  }

  if (list_devices) {
    std::cout << "\nAvailable devices:\n" << devices_list << "\n";
    exit(0);
  }

  if (-1 !=  device_index_selected_) return true;

  std::cerr
      << "No keyboard device selected. "
      << "Specify preference via argument -k=<DEVICE>\n"
      << "Available devices:\n" << devices_list << "\n";

  exit(127);
//  return false;  TODO(kay): implement return bool here and exit in main
}

// Store selected keyboard device to /var/tmp/xmchord.pref, kept for 30 days
bool KeyboardDeviceFinder::SaveDevicePreference() {
  ResetDevicePreference();

  std::string device_identifier =
      helper::File::GetLastPathSegment(devices_[device_index_selected_]);

  return helper::File::OverwriteFile(kPathPreferences, device_identifier);
}

void KeyboardDeviceFinder::ResetDevicePreference(bool notify) {
  helper::File::OverwriteFile(kPathPreferences, "");

  if (notify)
    std::cout
      << "Reset keyboard device preference: "
      << kPathPreferences << "\n\n";
}
}  // namespace model
