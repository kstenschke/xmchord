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

#include <xmchord/xmchord.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

typedef struct thread_arguments_kbd {
  std::string device_path = "";
} thargs_t;

/**
 * Main application:
 * init: cache available action shell script files
 * optional: trace actions (if argument given)
 * launch key watcher thread
 * endlessly run mouse watcher
 *
 * @param argc Amount of arguments received
 * @param argv Array: arguments received, argv[0] is name and path of executable
 */
int main(int argc, char **argv) {
  bool run = true;
  bool debug = false;

  std::string kbd_device_path;
  int exit_code = InitArgs(argc, argv, &kbd_device_path, &debug, &run);

  if (!run) return exit_code;

  std::string path_binary = helper::System::GetBinaryPath(
      argv, std::strlen(XMCHORD_EXECUTABLE_NAME));

  std::string path_actions = path_binary + "/actions/";
  std::string action_files = model::ActionReader::GetActionFiles(path_actions);

  if (action_files.length() == 0) {
    std::cerr << "No action files found in: " << path_actions << "\n";

    return 126;  // 126 = Command invoked cannot execute
  }

  unsigned char mouse_data[3];
  int device_handle_mouse = helper::Mouse::GetDeviceHandle();

  if (device_handle_mouse == -1) {
    std::cerr << "Failed to initialize mouse watcher.\n";

    return 126;
  }

  action_runner = new model::ActionRunner(debug, path_actions, action_files);

  // Launch keyboard watcher thread
  pthread_t thread_kbd_watcher;
  thargs_t thread_args;
  thread_args.device_path = kbd_device_path;

  if (pthread_create(&thread_kbd_watcher, nullptr, KbdWatcher, &thread_args)) {
    std::cerr << "Failed to initialize keyboard watcher.\n";

    delete action_runner;
    return 126;
  }

  // Infinite loop: mouse watcher
  while (true) {  // TODO(kay): move into MouseObserver model
    if (read(device_handle_mouse, mouse_data, sizeof(mouse_data)) > 0) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
      buttons_code = helper::Mouse::GetEventCode(mouse_data);
#pragma clang diagnostic pop

      // Find and invoke associated action shell script
      if (std::strcmp(buttons_code.c_str(), helper::Mouse::CODE_NOOP) != 0)
        action_runner->EvokeAction(false, buttons_code, kbd_code);
    }
  }
}

int InitArgs(int argc,
             char *const *argv,
             std::string *kbd_device_path,
             bool *debug,
             bool *run) {
  if (argc <= 1) return 0;  // No arguments given

  if (strcmp(argv[1], "a") == 0 || strcmp(argv[1], "actions") == 0) {
    model::ActionReader::PrintActionsWithComments();
    *run = false;
    return 0;
  }

  if (strcmp(argv[1], "d") == 0 || strcmp(argv[1], "debug") == 0) {
    *debug = true;
    return 0;
  }

  if (strcmp(argv[1], "h") == 0 || strcmp(argv[1], "help") == 0
      || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    *run = false;

    PrintVersionInfo();
    PrintHelp();

    return 0;
  }

  if (helper::Textual::StartsWith(argv[1], "-k=")) {
    *kbd_device_path = std::string(argv[1]).substr(3);
    return 0;
  }

  if (helper::Textual::StartsWith(argv[1], "--keyboard=")) {
    *kbd_device_path = std::string(argv[1]).substr(11);
    return 0;
  }

  if (strcmp(argv[1], "l") == 0 || strcmp(argv[1], "listDevices") == 0) {
    *run = false;
    model::KeyboardDeviceFinder::GetDeviceHandle("", true);

    return 0;
  }

  if (strcmp(argv[1], "r") == 0 || strcmp(argv[1], "reset") == 0) {
    *run = false;
    auto *kbd_device_finder = new model::KeyboardDeviceFinder("");
    kbd_device_finder->ResetDevicePreference(true);

    delete kbd_device_finder;
    return 0;
  }

  if (strcmp(argv[1], "version") == 0 || strcmp(argv[1], "v") == 0) {
    PrintVersionInfo();
    *run =  false;
    return 0;
  }

  std::cerr << "Argument unknown: " << argv[1] << "\n";
  return 127;
}

void PrintVersionInfo() {
  std::cout
      << "\nxmchord version " << XMCHORD_VERSION_MAJOR << "."
      << XMCHORD_VERSION_MINOR << "."
      << XMCHORD_VERSION_PATCH << "\n"
      "Released under the BSD-3-Clause License.\n"
      "Copyright (c) Kay Stenschke\n\n";
}

void PrintHelp() {
  std::cout <<
    "Usage: xmchord [OPTION]\n"
    "Available commands:\n"
    "  actions\t\tList available action script files including their "
    "inlined #: comment(s).\n"
    "  a\t\t\tShorthand for \"actions\" command.\n\n"

    "  debug\t\t\tRun in debug mode: event codes are printed as they occur,"
    " script files can be added at run-time.\"a\"\n"
    "  d\t\t\tShorthand for \"debug\" command.\n\n"

    "  help\t\t\tOutput version number and this help text.\n"
    "  h\t\t\tShorthand for \"help\" command.\n\n"

    "  --keyboard=[path]\tSet path of non-default keyboard device to be used. "
    "The preference is persisted also after restart, until reset or changed.\n"
    "  -k=\t\t\tShorthand for \"--keyboard\" option.\n\n"

    "  listDevices\t\tOutput paths of available devices (helpful when setting "
    "up -k option).\n"
    "  l\t\t\tShorthand for \"listDevices\" command.\n\n"

    "  reset\t\t\tReset preferences.\n"
    "  r=\t\t\tShorthand for \"reset\" command,\n\n"

    "  version\t\tOutput version number.\n"
    "  h\t\t\tShorthand for \"version\" command,\n\n";
}

// Keyboard watcher (running within thread)
void *KbdWatcher(void *thread_args) {
  std::string device_path =
      reinterpret_cast<thargs_t*>(thread_args)->device_path;

  int device_handle_keyboard =
      model::KeyboardDeviceFinder::GetDeviceHandle(device_path);

  if (device_handle_keyboard == -1) return nullptr;

  struct input_event kbd_event{};

  while (true) {
    read(device_handle_keyboard, &kbd_event, sizeof(struct input_event));

    switch (kbd_event.value) {
      case 0:  // Key released
        if (kbd_event.code != 0) kbd_code = 0;

        break;
      case 1:  // Key newly pressed
        if (kbd_event.code != 0) {
          kbd_code = kbd_event.code;

          if (std::strcmp(buttons_code.c_str(), helper::Mouse::CODE_NOOP) != 0)
            action_runner->EvokeAction(true, buttons_code, kbd_code);
        }

        break;
      case 2:  // Key still being pressed
        break;
      default: break;
    }
  }
}

#pragma clang diagnostic pop
