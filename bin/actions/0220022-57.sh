#!/bin/bash

#: ◣ + SPACE - in terminal - Type "yes"

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  xdotool type --delay 0 "yes"
  xdotool key Return
fi
