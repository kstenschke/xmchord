#!/bin/bash

#: ◢ + D -
#: If Chromium or Firefox active: Duplicate tab.
#: Else: Bring DataGrip window to front

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+l
  xdotool key Ctrl+c
  xdotool key Ctrl+t
  xdotool key Ctrl+v
  xdotool key Return
else
  # Bring DataGrip window to front
  if pidof -s datagrip.sh >/dev/null; then
    wmctrl -a datagrip
  else
    me=$SUDO_USER
    sudo -u "$me" nohup datagrip >/dev/null &
  fi
fi
