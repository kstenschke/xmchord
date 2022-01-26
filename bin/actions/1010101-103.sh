#!/bin/bash

#: ◢ + Up - Increase audio volume

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
me=$SUDO_USER

xdotool key XF86AudioRaiseVolume

xdotool key Down

sleep 0.1
xdotool key Escape  # hide context menu popup

unset currentVolume
