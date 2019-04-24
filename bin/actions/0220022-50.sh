#!/bin/bash

#: BR + M: Bring Evolution mail client window to front

if pidof -s evolution > /dev/null; then
	wmctrl -a Evolution
else
    me=$SUDO_USER
    sudo -u $me nohup evolution > /dev/null &
fi
