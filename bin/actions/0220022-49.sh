#!/bin/bash

#: ◣ + N
#: Chromium: Move active tab into new window

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "chromium" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool key Control_L+l; xdotool sleep 0.1  # focus URL
  xdotool key Control_L+c; xdotool sleep 0.3  # copy URL
  xdotool key Control_L+w; xdotool sleep 0.3  # close tab
  xdotool key Control_L+n; xdotool sleep 0.5  # open new window
  xdotool key Control_L+v; xdotool sleep 0.1  # paste URL
  xdotool key Return  # load URL
fi

unset focusApplication
