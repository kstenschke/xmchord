#!/bin/bash

#: BR + D: Bring DataGrip window to front

# Bring DataGrip window to front
if pidof -s datagrip.sh > /dev/null; then
    wmctrl -a datagrip
else
    me=$SUDO_USER
    sudo -u $me nohup datagrip > /dev/null &
fi
