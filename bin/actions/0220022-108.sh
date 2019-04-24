#!/bin/bash

#: BR + Down: Jump-scroll to bottom- the required key combo differs among programs, some need "End" others "Ctrl+End"

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`
if [[ "$focusApplication" =~ "soffice.bin" ]]; then
    #: LibreOffice
    xdotool sleep 0.1
    xdotool key Ctrl+End
else
    xdotool sleep 0.1
    xdotool key End
fi
