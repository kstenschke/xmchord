#!/bin/bash

#: BR + N - Bring Nemo to front, launch if not yet running

if pidof -s nemo > /dev/null; then
    nemosPid=`pidof nemo`
    windowTitle=` wmctrl -l -p | grep $nemosPid | cut -d " " -f 8-`
	wmctrl -a $windowTitle
else
    me=$SUDO_USER
    sudo -u $me nohup nemo > /dev/null &
fi
