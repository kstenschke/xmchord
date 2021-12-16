#!/bin/bash

#: ◤ + M - Bring Mattermost to front

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

#if pidof -s mattermost-desk > /dev/null; then
#  wmctrl -a mattermost-desk &> /dev/null
#else
    me=$SUDO_USER
    sudo -u "$me" nohup mattermost-desktop &> /dev/null
#fi

unset focusApplication
unset path_self
unset me
