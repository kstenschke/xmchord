#!/bin/bash

#: BL + V - Paste (Fire CTRL+V), when gnome screenshot active: export clipboard to image file and open it in XViewer

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

if [[ "$focusApplication" =~ "gnome-screensho" ]]; then  # gnome screenshot
  xdotool sleep 0.2
  xdotool click 1  # click, supposedly on [copy to clipboard] button under the mouse
  xdotool sleep 0.1
  xdotool key Escape  # close gnome screnshot window
  xdotool sleep 0.1
  xclip -selection clipboard -t image/png -o > /tmp/clipboard.png  # store image file
  xdotool sleep 0.2
  xviewer /tmp/clipboard.png  # open image file in viewer
else  # fire regular paste
  xdotool sleep 0.1
  xdotool key ctrl+v
fi



