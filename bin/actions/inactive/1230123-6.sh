#!/bin/bash

#: ◣ + ◢ + 5 - Replace selected text by its MD5 hash

sleep 0.6
xdotool key Ctrl+z  # [5] keypress did unset selection: restore it
sleep 0.1
xdotool key Ctrl+c
sleep 0.1

clipboard=$(xsel -ob)
hash=$(echo $clipboard | md5sum | cut -d ' ' -f 1)
echo "$hash" | xclip -in -selection clipboard
xdotool key Ctrl+v

unset hash
