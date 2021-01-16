#!/bin/bash

#: ◢ + Up -
#: Jump-scroll to top- the invoked required key combo differs among programs,
#: some need "Home" others "Ctrl+Shift+Home" (gnome-terminal) or "Ctrl+Home"

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "gnome-terminal" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+Shift+Home
else
  if [[ "$focusApplication" =~ soffice.bin ]] \
  || [[ "$focusApplication" =~ "java" ]]; then
    xdotool sleep 0.1
    xdotool key Ctrl+Home
  else
    xdotool sleep 0.1
    xdotool key Home
  fi
fi
