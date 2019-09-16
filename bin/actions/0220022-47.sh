#!/bin/bash

#: BR + V - Toggle active window "always on visible workspace" property

wmctrl -r :ACTIVE: -b toggle,sticky

activeWindowId=`xdotool getactivewindow`
activeWindowProps=`xprop -id ${activeWindowId} | grep _NET_WM_STATE`

me=$SUDO_USER

if [[ ${activeWindowProps} == *"_NET_WM_STATE_STICKY"* ]]; then
#    sudo -u $me echo "Always on visible workspace: On" | osd_cat -A right -p top -f -*-*-bold-*-*-*-36-120-*-*-*-*-*-* -cgray -d 1
  notify-send "Always on visible workspace: On" -t 1
else
#    sudo -u $me echo "Always on visible workspace: Off" | osd_cat -A right -p top -f -*-*-bold-*-*-*-36-120-*-*-*-*-*-* -cgray -d 1
   notify-send "Always on visible workspace: Off" -t 1
fi;

