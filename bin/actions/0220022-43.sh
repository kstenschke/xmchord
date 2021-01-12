#!/bin/bash

#: ◢ + $ - Convert selected text to all upper-/lower-case
# Mouse+Key must be "hit": released immediately

sleep 0.6
xdotool key Ctrl+z  # [$] keypress did unset selection: restore it
sleep 0.1
xdotool key Ctrl+c
sleep 0.1

clipboard=$(xsel -ob)
upper=${clipboard^^}

if [[ "$clipboard" == "$upper" ]]; then
  echo "${clipboard,,}" | xclip -in -selection clipboard # Copy all lower
else
  echo "$upper" | xclip -in -selection clipboard # Copy all upper
fi

xdotool key Ctrl+v

unset upper
