#!/bin/bash

#: BR + C -
#: Launch or Bring Chromium window to front.
#: If Chromium or Firefox is focussed: Copy last segment of URL

focusApplication=\
$(cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  #  Chromium or Firefox is focussed: Copy last segment of URL
  xdotool sleep 0.1
  xdotool key Ctrl+l
  xdotool key Right
  xdotool key shift+ctrl+Left
  xdotool key Ctrl+c
#  notify-send "Copied trailing URL segement" -t 1
  copied=$(xsel -o)

  echo "Copied: $copied" | aosd_cat -R white -u 300 --y-offset=40 \
  -B black -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1
else
  if pidof -s chromium-browse >/dev/null; then
    wmctrl -a Chromium  # Activate Chromium window
  else
    me=$SUDO_USER
    sudo -u $me nohup chromium-browser >/dev/null &  # Launch Chromium
  fi
fi
