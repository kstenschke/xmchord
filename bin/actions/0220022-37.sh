#!/bin/bash

#: ◢ + K - Bring Kitematic window to front

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"

"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if pidof -s firefox > /dev/null; then
	wmctrl -a Kitematic
else
    me=$SUDO_USER
    sudo -u "$me" nohup kitematic > /dev/null &
    unset me
fi

unset focusApplication
unset path_self
