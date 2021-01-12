#!/bin/bash

#: ◣ + C - Copy (Fire CTRL+C)

xdotool sleep 0.1
xdotool key ctrl+c

copied=$(xsel -o)

xdotool click 2  # Close context popup

echo "Copied: $copied" | aosd_cat -R white -u 300 --y-offset=40 \
-B black -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1
