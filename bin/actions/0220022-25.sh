#!/bin/bash

#: BR + P -
#: Launch Pidgin if not yet running, or bring Pidgin window to front.
#: Open new message popup

if pidof -s nemo > /dev/null; then
    pidginsPid=`pidof pidgin | cut -d " " -f 2`
    windowTitle=`wmctrl -l -p | grep $pidginsPid | grep @ | cut -d " " -f 8-`
    wmctrl -a $windowTitle
else
    me=$SUDO_USER
    sudo -u $me nohup pidgin > /dev/null &
fi

xdotool sleep 0.2
xdotool key Ctrl+m
