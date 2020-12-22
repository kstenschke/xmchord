#!/bin/bash

#: TL + D - If Chromium or Firefox has focus: Show Downloads

focusApplication=\
`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
    xdotool sleep 0.1
    xdotool key Ctrl+j
fi
