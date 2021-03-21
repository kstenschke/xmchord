#!/bin/bash

#: ◣ + F -
#  Bring Firefox window to front
#: Within Claws Mail: Open "Search Folder" popup
#: Within Gnome Terminal: Open "find" popup

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if [[ "$focusApplication" =~ "claws-mail" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+Shift+f
else
  if [[ "$focusApplication" =~ "gnome-terminal" ]]; then
    xdotool key Ctrl+Shift+f
  else
    if pidof -s firefox >/dev/null; then
      wmctrl -a Firefox
    else
      me=$SUDO_USER
      sudo -u "$me" nohup firefox >/dev/null &
      unset me
    fi
  fi
fi

unset focusApplication
unser path_self
