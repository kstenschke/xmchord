#!/bin/bash

#: BL + R - If evolution has focus: Mark selected mail read

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`
if [[ "$focusApplication" =~ "evolution" ]]; then
    # evolution focus
    xdotool key Menu
    xdotool sleep 0.1
    xdotool key k
fi
