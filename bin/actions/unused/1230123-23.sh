#!/bin/bash

#: ◣ + ◢ + I - Reverse selected text

clipboard=$( xsel -ob )

sleep 0.6
xdotool key Ctrl+z  # [5] keypress did unset selection: restore it
sleep 0.1
xdotool key Ctrl+c
sleep 0.1

clipboard=$(xsel -ob)
reverse=$(echo $clipboard | rev)
echo "$reverse" | xclip -in -selection clipboard
xdotool key Ctrl+v

echo "$clipboard" | xclip -in -selection clipboard
unset clipboard
unset reverse
