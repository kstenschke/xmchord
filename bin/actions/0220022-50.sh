#!/bin/bash

#: ◢ + M - Launch or bring Claws Mail to front

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if pidof -s claws-mail > /dev/null; then
	wmctrl -a "Claws Mail"
else
    me=$SUDO_USER
    sudo -u "$me" nohup claws-mail > /dev/null &
    unset me
fi

xdotool key Escape

unset focusApplication
unset path_self
