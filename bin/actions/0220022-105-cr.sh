#!/bin/bash

#: Right-CTRL + ◢ + Left - Chromium/Firefox: Focus previous tab, than reload it

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool key shift+ctrl+Tab
  xdotool sleep 0.1
  xdotool key ctrl+F5
fi
