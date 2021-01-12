#!/bin/bash

#: ◤ + U -
#: Within Chromium and Firefox: focus URL

focusApplication=\
$(cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+l
  exit 0
fi
