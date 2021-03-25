#!/bin/bash

#: ◣ + . -
#: Chromium or Firefox: Increment numeric ending of current URL by one
#: Mattermost desktop client: Next unread channel

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "chromium" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  # focus URL, select and copy its ending
  # declare variable from clipboard, increment variable, copy variable to clipboard
  # paste clipboard over URL ending, press Enter: reload
  clipboard=$( xsel -ob )

  xdotool sleep 0.1
  xdotool key Ctrl+l
  xdotool key Ctrl+Right
  xdotool key Ctrl+Shift+Left
  xdotool key Ctrl+c
  xdotool sleep 0.1
  number=$(xsel -ob)
  ((number=number+1))
  echo $number | xsel -ib
  xdotool key Ctrl+v
  xdotool key Return

  echo "$clipboard" | xclip -in -selection clipboard
  unset clipboard
  unset path_self
  unset focusApplication
  exit 0
fi

if [[ "$focusApplication" =~ "mattermost-desk" ]]; then
  xdotool sleep 0.1
  xdotool key Alt+Shift+Down

  unset path_self
  unset focusApplication
  exit 0
fi
