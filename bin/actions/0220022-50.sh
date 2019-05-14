#!/bin/bash

#: BR + M: Bring Thunderbird mail client window to front

if pidof -s thunderbird > /dev/null; then
	wmctrl -a Thunderbird
else
    me=$SUDO_USER
    sudo -u $me nohup thunderbird > /dev/null &
fi

xdotool key Escape

#if pidof -s evolution > /dev/null; then
#	wmctrl -a Evolution
#else
#    me=$SUDO_USER
#    sudo -u $me nohup evolution > /dev/null &
#fi
