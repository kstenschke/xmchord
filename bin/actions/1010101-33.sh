#!/bin/bash

#: ◣ + F - Global / if terminal has focus: Open search popup

focusApplication=\
$(cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm)

if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  # gnome terminal has focus
  xdotool key Control_L+Shift+f
  exit 0
fi

xdotool sleep 0.1
xdotool key ctrl+f
