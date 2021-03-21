#!/bin/bash

#: ◣ + $ - Convert selected text to all upper-/lower-case
#: Mouse+Key must be "hit": released immediately

sleep 0.6
xdotool key Ctrl+z  # [$] keypress did unset selection: restore it
sleep 0.1
xdotool key Ctrl+c
sleep 0.1

clipboard=$( xsel -ob )

copied_text=$(xsel -ob)
upper=${copied_text^^}

if [[ "$copied_text" == "$upper" ]]; then
  echo "${copied_text,,}" | xclip -in -selection copied_text # Copy all lower
else
  echo "$upper" | xclip -in -selection copied_text # Copy all upper
fi

xdotool key Ctrl+v

echo "$clipboard" | xclip -in -selection clipboard
unset clipboard
unset copied_text
unset upper
