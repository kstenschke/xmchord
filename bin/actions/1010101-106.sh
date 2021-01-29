#!/bin/bash

#: ◣ + Right - Within Gnome Terminal: Go Tab to right.
#: Within Chromium or Firefox: Go URL forward.

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  # Terminal: Go to next tab
  xdotool key Control_L+Page_Down
  exit 0
else
  if [[ "$focusApplication" =~ "chromium-browse" ]] \
  || [[ "$focusApplication" =~ "chromium" ]] \
  || [[ "$focusApplication" =~ "firefox" ]]; then
    # Chromium or Firefox: Go URL forward
    xdotool sleep 0.1
    xdotool keydown alt key Right
    xdotool sleep 0.5
    xdotool keyup alt
  fi
fi
