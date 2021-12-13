#!/bin/bash

#: ◣ + ENTER
#: In browser: Browse for selected text in new tab
#: Global: Click left mouse button three times (select line).

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

#: In browser - Browse for selected text in new tab
if [[ "$focusApplication" =~ "chromium-browse" ]] \
    || [[ "$focusApplication" =~ "chromium" ]] \
    || [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool key Control_L+c; xdotool sleep 0.2  # copy selected text
  xdotool key Control_L+t; xdotool sleep 0.3  # open new tab
  xdotool key Control_L+v; xdotool sleep 0.1  # paste
  xdotool key Return                          # browse
  exit 0
fi

# Global: Click left mouse button three times (select line).
# Mouse+Key must be "hit": released immediately
sleep 0.5
xdotool click --repeat 3 1
