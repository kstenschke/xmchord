#!/bin/bash

#: ◢ + N - Bring Nemo to front, launch if not yet running

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

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
