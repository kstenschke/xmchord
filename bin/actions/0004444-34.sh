#!/bin/bash

#: ◤ + G - Summon default mail client (same as mail-key)

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

xdotool key XF86Mail

unset focusApplication
unset path_self
sleep 0.1