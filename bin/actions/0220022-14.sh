#!/usr/bin/env bash

#: BL + Backspace - If Chromium or Firefox window has focus: Remove trailing segment from current URL
focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`
if [[ "$focusApplication" =~ "chromium-browse" ]] || [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+l
  xdotool key Right
  xdotool key shift+ctrl+Left
  xdotool key 0xff08  # Backspace
  xdotool key Return
fi
