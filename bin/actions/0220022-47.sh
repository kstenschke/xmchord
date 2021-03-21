#!/bin/bash

#: ◣ + V - Toggle active window "always on visible workspace" property

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

wmctrl -r :ACTIVE: -b toggle,sticky

activeWindowId=$(xdotool getactivewindow)
activeWindowProps=$(xprop -id "${activeWindowId}" | grep _NET_WM_STATE)

if [[ ${activeWindowProps} == *"_NET_WM_STATE_STICKY"* ]]; then
  #  notify-send "Always on visible workspace: On" -t 1
  echo "Always on visible workspace" | aosd_cat -R white -u 300 --y-offset=40 \
    -B green -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1
else
  #  notify-send "Always on visible workspace: Off" -t 1
  echo "Always on visible workspace" | aosd_cat -R white -u 300 --y-offset=40 \
  -B red -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1
fi

unset focusApplication
unset path_self
unset activeWindowId
unset activeWindowProps
