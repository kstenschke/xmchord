#!/bin/bash

#: BL + TL: If Chromium has focus: close current tab

focusApplication=$(cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] || [[ "$focusApplication" =~ "firefox" ]]; then
  ./actions/utils/chromium-close-active-tab.sh
fi
