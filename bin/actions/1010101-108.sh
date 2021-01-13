#!/bin/bash

#: ◣ + Down - Decrease audio volume

amixer -D pulse sset Master 5%- &> /dev/null

#currentVolume=`amixer -D pulse sget Master | \
#grep 'Front Left: Playback' | \
#grep -oE "[0-9]{1,3}%"`
#notify-send "Volume lower ($currentVolume)" -t 1

echo "Volume--" | aosd_cat -R white -u 300 --y-offset=40 -B black -b 240 \
--padding=24 -x 5 -n "Ubuntu 20" -p 1

xdotool key Up

sleep 0.1
xdotool key Escape  # hide context menu popup
