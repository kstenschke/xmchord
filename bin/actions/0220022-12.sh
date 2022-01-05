#!/bin/bash

#: ◢ + ' - Output name of focused application

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

echo
echo "$focusApplication"
