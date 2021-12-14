#!/bin/bash

#: ◣ + G - In Gnome Screenshot: Left click, close popup, focus gimp, paste as new image

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "gnome-screensho" ]]; then
  xdotool sleep 0.2
  xdotool click 1

  xdotool sleep 0.1
  xdotool key Escape
  xdotool sleep 0.1

  if pidof -s gimp-2.10 > /dev/null; then
    # bring gimp (version is always <MAJOR>.<MINOR>) to front
    gimpPid=$(pidof gimp-2.10)
    windowTitle=$(wmctrl -l -p | grep "$gimpPid" | cut -d " " -f 8-)
    wmctrl -a "$windowTitle"
    xdotool sleep 0.2
    xdotool keyup Shift+Super+Left key Ctrl+Shift+v  # paste as new image
    else
      echo "Launching Gimp..." | aosd_cat -R white -u 500 --y-offset=40 \
      -B black -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1

      me=$SUDO_USER
      sudo -u "$me" nohup gimp > /dev/null &
  fi
fi
