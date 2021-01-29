#!/bin/bash

#: Right-CTRL + ◢ + Right - Chromium/Firefox: Focus next tab, than reload it

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "chromium" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool key ctrl+Tab
  xdotool sleep 0.1
  xdotool key ctrl+F5
fi

