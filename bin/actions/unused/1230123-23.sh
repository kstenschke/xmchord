#!/bin/bash

#: ◣ + ◢ + I - Replace selected text by itself backwards (inverse)

sleep 0.6
xdotool key Ctrl+z  # [5] keypress did unset selection: restore it
sleep 0.1
xdotool key Ctrl+c
sleep 0.1

clipboard=$(xsel -ob)
reverse=$(echo $clipboard | rev)
echo "$reverse" | xclip -in -selection clipboard
xdotool key Ctrl+v

unset reverse
