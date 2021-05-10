#!/bin/bash

#: ◣ + R
#: Within Thunderbird: Mark message read
#: Else: Toggle active window roll-up state

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "thunderbird" ]]; then
  xdotool sleep 0.1
  xdotool key Alt+m
  xdotool sleep 0.1
  xdotool key k
  xdotool sleep 0.1
  xdotool key r
  xdotool sleep 0.3
  xdotool key Escape
  xdotool key Escape

  unset focusApplication
  exit 0
fi

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

wmctrl -b toggle,shaded -r :ACTIVE:

unset focusApplication
unset path_self
