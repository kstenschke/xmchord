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

#include <xmchord/model/action_runner.h>

#include <xmchord/helper/file.h>
#include <xmchord/helper/system.h>

#include <string>
#include <iostream>
#include <utility>

namespace model {

// Constructor
ActionRunner::ActionRunner(
    bool debug,
    std::string path_actions,
    std::string action_files)
    : path_actions(std::move(path_actions)),
      debug(debug),
      action_files(std::move(action_files)) {
}

// Triggered after button- or key-code changed:
// look for and evoke related shell-script
void ActionRunner::EvokeAction(
    bool clickWasFirst,
    const std::string &buttons_code,
    int kbd_code) {
  std::string filename_action;

  filename_action =
      clickWasFirst
        // Filename built like: <mouse_code>-<kbd_code>.sh
        ? filename_action.append(buttons_code).append("-").append(
            std::to_string(kbd_code)).append(".sh")
        // Filename built like: <kbd_code>-<mouse_code>.sh
        : filename_action.append(std::to_string(kbd_code)).append(
            "-").append(buttons_code).append(".sh");

  if (debug)
    std::cout << "Event code: "
              << filename_action.substr(0, filename_action.length() - 3)
              << "\n";

  std::string path_action_file = path_actions;

  if (clickWasFirst) {
    // Filename built like: <mouse_code>-<kbd_code>.sh
    path_action_file.append(buttons_code).append("-").append(
        std::to_string(kbd_code)).append(".sh");
  } else {
    // Filename built like: <kbd_code>-<mouse_code>.sh
    path_action_file.append(std::to_string(kbd_code)).append("-").append(
        buttons_code).append(".sh");
  }

  if (debug) {
    // Debug mode: ActionRunner files can be added while xmchord already runs
    if (helper::File::FileExists(path_action_file))
      helper::System::RunShellCommand(path_action_file.c_str());
    else
      std::cout << "Action file not found: " << path_action_file << "\n";
  } else if (action_files.find(filename_action) != std::string::npos) {
    // Regular mode: ActionRunner files are cached on start of xmchord,
    // when adding actions xmchord must be restarted
    helper::System::RunShellCommand(path_action_file.c_str());
  }
}

}  // namespace model
