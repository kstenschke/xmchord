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

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/input.h>
#include <sys/types.h>
#include <pthread.h>

#include <xmchord/models/action_runner.h>
#include <xmchord/helper/system.h>
#include <xmchord/helper/mouse.h>
#include <xmchord/helper/keyboard.h>
#include <xmchord/helper/file.h>
#include <xmchord/config.h>

#include <iostream>
#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

std::string path_actions;
std::string action_files;  // Newline separated list of existing action files
std::string path_action_file;

bool debug;

std::string buttons_code;
int kbd_code = 0;

models::ActionRunner *action_runner = nullptr;

/**
 * Keyboard watcher (to run within thread)
 *
 * @param x_void_ptr
 * @return
 * @todo movie into KeyObserver model
 */
void *KbdWatcher(void *x_void_ptr) {
  int device_handle_keyboard = helper::Keyboard::GetDeviceHandle();

  if (device_handle_keyboard == -1) {
    std::cout << "Error: Failed opening keyboard device handle\n";

    return nullptr;
  }

  struct input_event kbd_event{};

  while (1) {
    read(device_handle_keyboard, &kbd_event, sizeof(struct input_event));

    switch (kbd_event.value) {
      case 1:
        // Key newly pressed
        if (kbd_event.code != 0) {
          kbd_code = kbd_event.code;

          if (std::strcmp(buttons_code.c_str(), helper::Mouse::CODE_NOOP) != 0)
            action_runner->EvokeAction(true, buttons_code, kbd_code);
        }

        break;
      case 2:
        // Key still being pressed
        break;
      case 0:
        // Key released
        if (kbd_event.code != 0) kbd_code = 0;

        break;
      default: break;
    }
  }
}

/**
 * Main application:
 * init: cache available action shell script files
 * optional: trace actions (if argument given)
 * launch key watcher thread
 * endlessly run mouse watcher
 *
 * @param argc Amount of arguments received
 * @param argv Array of arguments received, argv[0] is name and path of executable
 */
int main(int argc, char **argv) {
  if (argc > 1) {
    if (strcmp(argv[1], "actions") == 0 || strcmp(argv[1], "a") == 0) {
      // List action files and their 1st inline comment line starting with "#:"
      helper::File::TraceActions();

      return 0;
    }

    if (strcmp(argv[1], "debug") == 0 || strcmp(argv[1], "d") == 0) {
      debug = true;
    } else if (strcmp(argv[1], "version") == 0 || strcmp(argv[1], "v") == 0) {
      std::cout
          << "xmchord version " << XMCHORD_VERSION_MAJOR << "."
          << XMCHORD_VERSION_MINOR << "."
          << XMCHORD_VERSION_PATCH << "\n"
          "Copyright (c) 2019-2020 Kay Stenschke\n\n";
    } else {
      std::cout << "Argument unknown: " << argv[1] << "\n";

      return 0;
    }
  }

  std::string path_binary = helper::System::GetBinaryPath(
      argv,
      std::strlen(XMCHORD_EXECUTABLE_NAME));

  path_actions = path_binary + "/actions/";
  action_files = helper::File::GetActionFiles(path_actions);

  if (action_files.length() == 0) {
    std::cout << "No action files found in: " << path_actions << "\n";

    return 1;
  }

  unsigned char mouse_data[3];

  int device_handle_mouse = helper::Mouse::GetDeviceHandle();

  if (device_handle_mouse == -1) return -1;

  action_runner = new models::ActionRunner(debug, path_actions, action_files);

  // Launch key watcher thread
  pthread_t kbd_watcher_thread;

  int k = 0;

  if (pthread_create(&kbd_watcher_thread, nullptr, KbdWatcher, &k)) {
    fprintf(stderr, "Error: Failed creating key watcher thread\n");

    return 1;
  }

  // Infinite loop: mouse watcher
  // @todo move into MouseObserver model
  while (1) {
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

#pragma clang diagnostic pop
