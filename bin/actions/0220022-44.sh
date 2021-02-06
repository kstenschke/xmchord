#!/bin/bash

#: ◢ + Y - Bring Yana to front, launch if not yet running

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if pidof -s yana > /dev/null; then
  wmctrl -a Yana &> /dev/null
else
    me=$SUDO_USER
    sudo -u "$me" nohup yana &> /dev/null
fi

unset path_self
