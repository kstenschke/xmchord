#!/bin/bash

#: BR + G: If Gnome Screenshot popup has focus: Fire left click, close popup, focus gimp, paste as new image

focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

if [[ "$focusApplication" =~ "gnome-screensho" ]]; then
  xdotool sleep 0.2
  xdotool click 1

  xdotool sleep 0.1
  xdotool key Escape
  xdotool sleep 0.1

  if pidof -s gimp-2.8 > /dev/null; then  # bring gimp to front
    gimpPid=`pidof gimp-2.8`
    windowTitle=` wmctrl -l -p | grep $gimpPid | cut -d " " -f 8-`
    wmctrl -a $windowTitle
    xdotool sleep 0.2
    xdotool keyup Shift+Super+Left key Ctrl+Shift+v  # paste as new image
#    else
#      me=$SUDO_USER
#      sudo -u $me nohup gimp > /dev/null &
  fi
fi
