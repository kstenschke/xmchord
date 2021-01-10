#!/bin/bash

#: Top-any: If terminal window has focus - close current tab.
#: BR+H in browser: Toggle "view-source:" prefix of current URL

focusApplication=$(cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm)

if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  xdotool sleep 0.1
  xdotool key Control_L+d
else
  if [[ "$focusApplication" =~ "chromium-browse" ]] ||
    [[ "$focusApplication" =~ "firefox" ]]; then
    xdotool sleep 0.1
    xdotool key Ctrl+l
    xdotool sleep 0.1
    xdotool key Ctrl+a
    xdotool key Ctrl+c
    xdotool key Home

    clipboard=`xsel -ob`

    if [[ $clipboard == view-source* ]]; then
      for i in {1..12}; do
        xdotool key Delete
      done
    else
      xdotool type "view-source:"
      xdotool key End
    fi

    xdotool key Return
  fi
fi
