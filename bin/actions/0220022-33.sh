#!/bin/bash

#: BR + F:
#  Bring Firefox window to front
#: Within Claws Mail: Open "Search Folder" popup
#: Within Gnome Terminal: Open "find" popup

focusApplication=\
$(cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm)

if [[ "$focusApplication" =~ "claws-mail" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+Shift+f
else
  if [[ "$focusApplication" =~ "gnome-terminal" ]]; then
    xdotool sleep 0.1
    xdotool key 0xff08  # Backspace
    xdotool key Ctrl+Shift+f
  else
    if pidof -s firefox >/dev/null; then
      wmctrl -a Firefox
    else
      me=$SUDO_USER
      sudo -u $me nohup firefox >/dev/null &
    fi
  fi
fi
