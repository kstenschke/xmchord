#!/bin/bash

#: BL + right - Gnome Terminal: Go Tab to right. Chromium: Go URL forward.

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

#if [[ "$focusApplication" =~ "evolution" ]]; then
#    #@todo implement
#fi
    
if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
    # In Gnome terminal: Go to next tab
    xdotool key Control_L+Page_Down
    exit 0;
fi

if [[ "$focusApplication" =~ "chromium-browse" ]] || [[ "$focusApplication" =~ "firefox" ]]; then
    # In Chromium: Go URL forward
    xdotool sleep 0.1
    xdotool keydown alt key Right
    xdotool sleep 0.5
    xdotool keyup alt
fi
