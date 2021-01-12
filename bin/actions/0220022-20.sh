#!/bin/bash

#: ◢ + T - Toggle active window "always on top"

wmctrl -r :ACTIVE: -b toggle,above

activeWindowId=$(xdotool getactivewindow)
activeWindowProps=$(xprop -id "${activeWindowId}" | grep _NET_WM_STATE)

if [[ ${activeWindowProps} == *"_NET_WM_STATE_ABOVE"* ]]; then
#    notify-send "Always on top: On" -t 1
    echo "Always on top" | aosd_cat -R white -u 300 --y-offset=40 -B green \
    -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1
else
#    notify-send "Always on top: Off" -t 1
    echo "Always on top" | aosd_cat -R white -u 300 --y-offset=40 -B red \
    -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1
fi;
