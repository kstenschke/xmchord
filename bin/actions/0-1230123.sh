#!/bin/bash

#: ◣ + ◢ -
#: Touch active corner (bottom-right) w/ mouse pointer,
#: than return to original mouse location

# Remember current mouse position (variables: $X, $Y)
eval "$(xdotool getmouselocation --shell)"

# Get coordinates of bottom-right corner
x=$(xdpyinfo | grep dimensions | sed -r 's/^[^0-9]*([0-9]+).*$/\1/')
y=$(xdpyinfo | grep dimensions | grep -Po '((?<=x)([0-9]+)(?= pixels))')

xdotool mousemove "$x" "$y"  # Move mouse to hit "active corner"
xdotool sleep 0.3
xdotool mousemove "$X" "$Y"  # Restore original mouse position
