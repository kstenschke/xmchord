#!/bin/bash

#: BR + Up -
#: Jump-scroll to top- the required key combo differs among programs, some need
#: "Home" others "Ctrl+Shift+Home" (gnome-terminal) or "Ctrl+Home" (LibreOffice)

focusApplication=$(cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm)

if [[ "$focusApplication" =~ "gnome-terminal" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+Shift+Home
else
  if [[ "$focusApplication" =~ "soffice.bin" ]]; then  # LibreOffice
    xdotool sleep 0.1
    xdotool key Ctrl+Home
  else
    xdotool sleep 0.1
    xdotool key Home
  fi
fi
