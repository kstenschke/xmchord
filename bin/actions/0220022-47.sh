#!/bin/bash

#: BR + V - Toggle active window "always on visible workspace" property

wmctrl -r :ACTIVE: -b toggle,sticky

activeWindowId=$(xdotool getactivewindow)
activeWindowProps=$(xprop -id ${activeWindowId} | grep _NET_WM_STATE)

me=$SUDO_USER

if [[ ${activeWindowProps} == *"_NET_WM_STATE_STICKY"* ]]; then
  #  notify-send "Always on visible workspace: On" -t 1
  echo "Always on visible workspace" | aosd_cat -R white -u 300 --y-offset=40 \
    -B green -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1
else
  #  notify-send "Always on visible workspace: Off" -t 1
  echo "Always on visible workspace" | aosd_cat -R white -u 300 --y-offset=40 \
  -B red -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1
fi
