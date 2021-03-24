#!/bin/bash

# Remove typed character of chording combo
# in applications showing it undesiredly
# @param $1 identifier of focused application

if [[ "$1" =~ "geany" ]] \
  || [[ "$1" =~ "gnome-terminal" ]] \
  || [[ "$1" =~ "java" ]] \
  || [[ "$1" =~ "mattermost-desk" ]] \
  || [[ "$1" =~ soffice.bin ]] \
  || [[ "$1" =~ "xpad" ]] \
  || [[ "$1" =~ "yana" ]] \
  ; then
    xdotool key 0xff08  # Backspace
fi
