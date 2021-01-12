#!/bin/bash

#: ◢ + Esc - Bring System Monitor to front, launch if not yet running

if pidof -s gnome-system-monitor > /dev/null; then
    systemMonitorPid=`pidof nemo`
    windowTitle=` wmctrl -l -p | grep $systemMonitorPid | cut -d " " -f 8-`
	wmctrl -a $windowTitle &> /dev/null
else
    me=$SUDO_USER
    sudo -u $me nohup gnome-system-monitor &> /dev/null
fi
