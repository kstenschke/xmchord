#!/bin/bash

#: ◢ + C - Launch or Bring Chromium window to front.
#: If Chromium or Firefox is focussed: Copy last segment of URL

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "chromium" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  #  Chromium or Firefox is focussed: Copy last segment of URL
  clipboard=$( xsel -ob )

  xdotool sleep 0.1
  xdotool key Ctrl+l
  xdotool key Right
  xdotool key shift+ctrl+Left
  xdotool key Ctrl+c
  copied_url=$(xsel -o)

  echo "Copied: $copied_url" | aosd_cat -R white -u 300 --y-offset=40 \
  -B black -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1

  echo "$clipboard" | xclip -in -selection clipboard
  unset clipboard
  unset copied_url
else
  if pidof -s chromium-browse >/dev/null; then
    wmctrl -a Chromium
  else
    if pidof -s chromium >/dev/null; then
      wmctrl -a Chromium
    else
      me=$SUDO_USER
  #    sudo -u "$me" nohup chromium-browser >/dev/null &
      sudo -u "$me" nohup chromium >/dev/null &
      unset me
    fi
  fi
fi

unset focusApplication
unset path_self
