#!/bin/bash

#: BL + U - Chromium: focus URL, Evolution: activate "unread" filter

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`
if [[ "$focusApplication" =~ "chromium-browse" ]] || [[ "$focusApplication" =~ "firefox" ]]; then
    xdotool sleep 0.1
    xdotool key Ctrl+l
    exit 0;
fi

if [[ "$focusApplication" =~ "evolution" ]]; then
    xdotool sleep 0.1
    xdotool keydown alt key Left
    xdotool key w
    xdotool keyup alt
    xdotool sleep 0.1
    xdotool key space
    xdotool sleep 0.1
    xdotool key Down
    xdotool key space
fi
