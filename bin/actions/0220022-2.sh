#!/bin/bash

#: ◣ + 1 - In Mattermost: Type ":+1:", other applications: move window to workspace 1

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if [[ "$focusApplication" =~ "mattermost-desk" ]]; then
  xdotool sleep 0.1
  xdotool type ":+1:"

  unset path_self
  unset focusApplication
  exit 0
fi

# all applications other than Mattermost: move window to workspace 1
wmctrl -r :ACTIVE: -t 1

