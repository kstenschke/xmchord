#!/bin/bash

#: ◣ + ' - Output name of foccussed application

focusApplication=\
$(cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm)

echo
echo $focusApplication
