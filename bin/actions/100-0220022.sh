#!/bin/bash

#: AltGr + BR: If Gnome Screenshot popup has focus: Fire left click, than close current window

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

if [[ "$focusApplication" =~ "gnome-screensho" ]]; then
  xdotool sleep 0.2
  xdotool click 1

  xdotool sleep 0.1
  xdotool key Escape
fi
