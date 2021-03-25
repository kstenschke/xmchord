#!/bin/bash

#: ◣ + F -
#  Bring Firefox window to front
#: Within Claws Mail: Open "Search Folder" popup
#: Within Gnome Terminal: Open "find" popup
#: Within Thunderbird: Open "Search Messages" popup

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if [[ "$focusApplication" =~ "claws-mail" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+Shift+f

  unset focusApplication
  unset path_self
  exit 0
fi

if [[ "$focusApplication" =~ "thunderbird" ]]; then
  xdotool sleep 0.1
  xdotool key Up
  xdotool key Ctrl+Shift+f

  unset focusApplication
  unset path_self
  exit 0
fi

if [[ "$focusApplication" =~ "gnome-terminal" ]]; then
  xdotool key Ctrl+Shift+f
  sleep 0.1
  wmctrl -r :ACTIVE: -b toggle,above
else
  if pidof -s firefox >/dev/null; then
    wmctrl -a Firefox
  else
    me=$SUDO_USER
    sudo -u "$me" nohup firefox >/dev/null &
    unset me
  fi
fi

unset focusApplication
unset path_self
