#!/bin/bash

#: BR + F: Bring Firefox window to front

if pidof -s firefox > /dev/null; then
	wmctrl -a Firefox
else
    me=$SUDO_USER
    sudo -u $me nohup firefox > /dev/null &
fi
