#!/bin/bash

#: ◢ + U - Type current UNIX timestamp

sleep 0.1
xdotool key 0xff08  # Backspace

timestapm_now=$(date +'%s')
xdotool type "$timestapm_now"

unset timestapm_now
