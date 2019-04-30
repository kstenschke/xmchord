#!/bin/bash

#: BL + A - Global: Fire CTRL+A / Evolution: switch to "all messages" filter

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

if [[ "$focusApplication" =~ "evolution" ]]; then
    # Evolution has focus: Activate "All Messages" filter
    xdotool sleep 0.1

    xdotool keydown alt key Left
    xdotool key w
    xdotool keyup alt
    xdotool sleep 0.1
    xdotool key space
    xdotool sleep 0.1
    xdotool key Home
    xdotool key space

    exit 0;
fi

echo 'select all'
xdotool sleep 0.1
xdotool key ctrl+a
