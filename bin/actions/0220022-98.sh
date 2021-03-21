#!/bin/bash

#: ◣ + Numpad [/] -
#: In Gnome Terminal: Insert 40 empty lines (helpful to separate sections of
#: output)

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  xdotool key 0xff08  # backspace
  seq 8 | xargs -I -- xdotool key Return
fi
