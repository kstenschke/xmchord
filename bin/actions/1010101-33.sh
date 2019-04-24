#!/bin/bash

#: BL + F - If terminal has focus: Open search popup 

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`
if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
    # gnome terminal has focus
    xdotool key Control_L+Shift+f
fi
