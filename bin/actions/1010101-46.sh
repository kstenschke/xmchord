#!/bin/bash

#: ◣ + C - Copy (Fire CTRL+C)

xdotool sleep 0.1
xdotool key ctrl+c
sleep 0.1
xdotool key Escape  # hide context menu popup

copied=$(xsel -o)

echo "Copied: $copied" | aosd_cat -R white -u 500 --y-offset=40 \
-B black -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1

unset copied