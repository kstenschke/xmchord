#!/bin/bash

#: ◢ + P -
#: Launch Pidgin if not yet running, or bring Pidgin window to front.
#: Open new message popup

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if pidof -s nemo > /dev/null; then
    pidginsPid=$(pidof pidgin | cut -d " " -f 2)
    windowTitle=$(wmctrl -l -p | grep "$pidginsPid" | grep @ | cut -d " " -f 8-)
    wmctrl -a "$windowTitle"

    unset pidginsPid
    unset windowTitle
else
    me=$SUDO_USER
    sudo -u "$me" nohup pidgin > /dev/null &
    unset me
fi

xdotool sleep 0.2
xdotool key Ctrl+m

unset focusApplication
unset path_self
