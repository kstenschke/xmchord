#!/bin/bash

#: ◣ + W - Hit CTRL+W (close window)
#: In Mattermost: Type ":wave:"

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if [[ "$focusApplication" =~ "mattermost-desk" ]]; then
  xdotool sleep 0.1
  xdotool type ":wave:"

  unset path_self
  unset focusApplication
  exit 0
fi

xdotool sleep 0.3
xdotool key Control_L+w
