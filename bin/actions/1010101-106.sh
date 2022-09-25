#!/bin/bash

#: ◢ + Right - Within Gnome Terminal: Go Tab to right.
#: Within Chromium or Firefox: Go URL forward.

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  xdotool key Control_L+Page_Down
  exit 0
fi

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "chromium" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool keydown alt key Right
  xdotool sleep 0.5
  xdotool keyup alt
  exit 0
fi

if [[ "$focusApplication" =~ "xed" ]]; then
  xdotool key Alt_R+Control_L+Page_Up
  exit 0
fi