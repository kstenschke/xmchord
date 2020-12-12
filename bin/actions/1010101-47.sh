#!/bin/bash

#: BL + V - Paste (Fire CTRL+V), when gnome screenshot active: export copied image to file, than open in feh image viewer

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

if [[ "$focusApplication" =~ "gnome-screensho" ]]; then  # gnome screenshot
  xdotool sleep 0.2
  xdotool click 1  # click, supposedly on [copy to clipboard] button under the mouse
  xdotool sleep 0.1
  xdotool key Escape  # close gnome screnshot window
  xdotool sleep 0.1
  xclip -selection clipboard -t image/png -o > /tmp/clipboard.png  # store image file
  xdotool sleep 0.2
  feh /tmp/clipboard.png  # open image file in viewer
else  # fire regular paste
  xdotool sleep 0.1
  xdotool key ctrl+v
fi
