#!/bin/bash

#: ◢ + M - Launch or bring Claws Mail to front

if pidof -s claws-mail > /dev/null; then
	wmctrl -a "Claws Mail"
else
    me=$SUDO_USER
    sudo -u "$me" nohup claws-mail > /dev/null &
fi

xdotool key Escape
