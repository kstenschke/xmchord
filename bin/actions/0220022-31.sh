#!/bin/bash

#: BR + S: "Roll" clicked window sideways (scale-down horizontally)

activeWindowId=`xdotool getactivewindow`

# Get active window's width and height (excludes window decoration)
unset w
eval $(xwininfo -id $(xdotool getactivewindow) |
  sed -n -e "s/^ \+Width: \+\([0-9]\+\).*/w=\1/p" \
         -e "s/^ \+Height: \+\([0-9]\+\).*/h=\1/p" )

if [ "$w" -ne "30" ]; then
  # Window is NOT rolled-down sideways

  # Store width to file, to later be able to restore it
  mkdir -p ./tmp
  echo "$w" > "./tmp/window-width_$activeWindowId.txt"

  # Unmaximize window
  if xwininfo -all -id $activeWindowId|grep "Maximized Horz"; then
    wmctrl -r :ACTIVE: -b toggle,maximized_horz
    xdotool sleep 0.1
  fi
  if xwininfo -all -id $activeWindowId|grep "Maximized Vert"; then
    wmctrl -r :ACTIVE: -b toggle,maximized_vert
    xdotool sleep 0.1
  fi

  # Retain maximized dimension
  xdotool windowsize $activeWindowId $w $h
  xdotool sleep 0.1

  # Roll-down sideways
  xdotool windowsize $activeWindowId 30 $h
else
  # Window is rolled-down sideways, restore it's previous size
  w=`cat ./tmp/window-width_$activeWindowId.txt`
  xdotool windowsize $activeWindowId $w $h

  rm ./tmp/window-width_$activeWindowId.txt
fi
