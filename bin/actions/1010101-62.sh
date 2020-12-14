#!/usr/bin/env bash

#: BL + F4 - If Chromium or Firefox window has focus: Close active tab
focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`
if [[ "$focusApplication" =~ "chromium-browse" ]] || [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+w
fi
