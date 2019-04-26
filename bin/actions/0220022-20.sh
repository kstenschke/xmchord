#!/bin/bash

#: BR + T: Toggle active window "always on top"

wmctrl -r :ACTIVE: -b toggle,above

activeWindowId=`xdotool getactivewindow`
activeWindowProps=`xprop -id ${activeWindowId} | grep _NET_WM_STATE`

me=$SUDO_USER

if [[ ${activeWindowProps} == *"_NET_WM_STATE_ABOVE"* ]]; then
    sudo -u $me echo "Always on top: On" | osd_cat -A right -p top -f -*-*-bold-*-*-*-36-120-*-*-*-*-*-* -cgray -d 1
else
    sudo -u $me echo "Always on top: Off" | osd_cat -A right -p top -f -*-*-bold-*-*-*-36-120-*-*-*-*-*-* -cgray -d 1
fi;