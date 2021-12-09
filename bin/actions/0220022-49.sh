#!/bin/bash

#: ◣ + N
#: Chromium: Move active tab into new window
#: Global: Bring Nemo to front, launch if not yet running

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "chromium" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool key Control_L+l; xdotool sleep 0.1  # focus URL
  xdotool key Control_L+c; xdotool sleep 0.3  # copy URL
  xdotool key Control_L+w; xdotool sleep 0.3  # close tab
  xdotool key Control_L+n; xdotool sleep 0.5  # open new window
  xdotool key Control_L+v; xdotool sleep 0.1  # paste URL
  xdotool key Return  # load URL
  exit 0
fi

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if pidof -s nemo > /dev/null; then
    nemosPid=$(pidof nemo)
    windowTitle=$(wmctrl -l -p | grep "$nemosPid" | cut -d " " -f 8-)
	wmctrl -a "$windowTitle"
else
    me=$SUDO_USER
    sudo -u "$me" nohup nemo > /dev/null &
    unset me
fi

unset focusApplication
unset path_self
