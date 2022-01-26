#!/bin/bash

#: ◤ + Down - Decrease audio volume

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
me=$SUDO_USER

xdotool key XF86AudioLowerVolume

xdotool key Up

sleep 0.1
xdotool key Escape  # hide context menu popup

unset currentVolume
