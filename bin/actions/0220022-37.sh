#!/bin/bash

#: BR + K: Bring Kitematic window to front

if pidof -s firefox > /dev/null; then
	wmctrl -a Kitematic
else
    me=$SUDO_USER
    sudo -u $me nohup kitematic > /dev/null &
fi
