#!/bin/bash

#: BR + C: Bring Chromium window to front

if pidof -s chromium-browse > /dev/null; then
	wmctrl -a Chromium
else
    me=$SUDO_USER
    sudo -u $me nohup chromium-browser > /dev/null &
fi
