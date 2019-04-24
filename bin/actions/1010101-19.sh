#!/bin/bash

#: BL + R - In Evolution: Mark current mail as read. In Chromium: Reload.

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`
if [[ "$focusApplication" =~ "evolution" ]]; then
    xdotool sleep 0.1
    xdotool key Ctrl+k
    exit 0;
fi

if [[ "$focusApplication" =~ "chromium-browse" ]] || [[ "$focusApplication" =~ "firefox" ]]; then
    xdotool sleep 0.1
    xdotool key Ctrl+r
fi
