#!/bin/bash

#: BL + R - In Chromium and Firefox: Reload.

focusApplication=\
$(cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+r
fi
