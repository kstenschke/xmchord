#!/bin/bash

#: ◣ + O - Open generic URL
# the URL is built from env-var `XMCHORD_GENERIC_URL` with its sub-string
# `SELECTED_TEXT` replaced by the given text-selection

xdotool sleep 0.1

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

xdotool key Ctrl+z  # [$] keypress did remove selection: restore it
sleep 0.1

xdotool key Control_L+c  # copy selected text
sleep 0.1

SELECTED_TEXT=$(xclip -o)  # put into variable

# replace "SELECTED_TEXT" within URL preset from ENV var
GENERIC_URL="${XMCHORD_GENERIC_URL/SELECTED_TEXT/$SELECTED_TEXT}"

echo "$GENERIC_URL" | xclip -in -selection clipboard  # put URL into clipboard

# focus or launch chromium
if pidof -s chromium-browse >/dev/xnull; then
  wmctrl -a Chromium
else
  me=$SUDO_USER
  #    sudo -u "$me" nohup chromium-browser >/dev/null &
  sudo -u "$me" nohup chromium >/dev/null &
  unset me
fi

sleep 0.5

xdotool key Control_L+l  # focus location field
sleep 0.1
xdotool key Control_L+v  # paste
sleep 0.1
xdotool key Return  # load
