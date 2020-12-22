#!/bin/bash

#: BL + V -
#: Paste (Fire CTRL+V).
#: When Gnome Screenshot active: export copied image to file, than open in
#: feh image viewer, set feh always-on-top and always-on-visible workspace

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

if [[ "$focusApplication" =~ "gnome-screensho" ]]; then  # gnome screenshot
  xdotool sleep 0.2
  xdotool click 1  # click, supposedly on [copy to clipboard] button under the mouse
  xdotool sleep 0.1
  xdotool key Escape  # close gnome screnshot window
  xdotool sleep 0.1
  xclip -selection clipboard -t image/png -o > /tmp/clipboard.png  # store image file
  me=$SUDO_USER
  xdotool sleep 0.1
  sudo -u $me nohup feh /tmp/clipboard.png > /dev/null & # open image file in viewer
  xdotool sleep 0.2
  wmctrl -r "clipboard.png" -b add,above  # Set feh always on top
  wmctrl -r "clipboard.png" -b add,sticky  # Set feh always on visible workspace
else  # fire regular paste
  xdotool sleep 0.1
  xdotool key ctrl+v
fi
