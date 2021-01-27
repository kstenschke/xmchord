#!/bin/bash

# Remove typed character of chording combo
# in applications showing it undesiredly
# @param $1 identifier of focused application

if [[ "$1" =~ soffice.bin ]] \
  || [[ "$1" =~ "java" ]] \
  || [[ "$1" =~ "gnome-terminal" ]]; then
    xdotool key 0xff08  # Backspace
fi
