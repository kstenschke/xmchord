#!/bin/bash

#: ◢ + Up - Increase audio volume

amixer -D pulse sset Master 5%+ &> /dev/null

currentVolume=$(amixer -D pulse sget Master | \
grep "Front Left: Playback" | \
grep -oE "[0-9]{1,3}%")

echo "Volume++ ($currentVolume)" | \
aosd_cat -R white -u 300 --y-offset=40 -B black -b 240 \
--padding=24 -x 5 -n "Ubuntu 20" -p 1

xdotool key Down

sleep 0.1
xdotool key Escape  # hide context menu popup

unset currentVolume
