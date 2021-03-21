#!/bin/bash

#: ◣ + , - Chromium or Firefox: Decrement numeric ending of current URL by one

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "chromium" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  # focus url, select and copy its ending
  # declare variable from clipboard, increment variable,
  # copy variable to clipboard,
  # paste clipboard over URL ending, press Enter: reload
  clipboard=$( xsel -ob )

  xdotool sleep 0.1
  xdotool key Ctrl+l
  xdotool key Ctrl+Right
  xdotool key Ctrl+Shift+Left
  xdotool key Ctrl+c
  xdotool sleep 0.1
  number=$(xsel -ob)
  ((number=number-1))
  echo $number | xsel -ib
  xdotool key Ctrl+v
  xdotool key Return

  echo "$clipboard" | xclip -in -selection clipboard
  unset clipboard
fi
