#!/bin/bash

#: BR + Up: Jump-scroll to top- the required key combo differs among programs, some need "Home" others "Ctrl+Home"

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`
if [[ "$focusApplication" =~ "soffice.bin" ]]; then
    #: LibreOffice
    xdotool sleep 0.1
    xdotool key Ctrl+Home
else
    xdotool sleep 0.1
    xdotool key Home
fi
