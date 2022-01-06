#!/bin/bash

#: ◤ + W - Summon default web browser (same as browser-key)

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

xdotool key XF86WWW

unset focusApplication
unset path_self
sleep 0.1
