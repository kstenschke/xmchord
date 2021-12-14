#!/bin/bash

#: ◣ + R - Toggle active window roll-up state

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

wmctrl -b toggle,shaded -r :ACTIVE:

unset focusApplication
unset path_self
