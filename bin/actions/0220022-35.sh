#!/bin/bash

#: BR + G -
#: If Claws Mail has focus: Toggle "Hide read threads"

focusApplication=\
`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

if [[ "$focusApplication" =~ "claws-mail" ]]; then
  echo "Toggle hide read threads" | aosd_cat -R white -u 300 --y-offset=40 \
  -B black -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1

  xdotool key Alt+v  # Expand "View" menu

  for i in {1..8}  # Select "hide read threads" option
  do
    xdotool key Down
  done

  xdotool key space  # Toggle selected option
  xdotool sleep 0.1

  xdotool key Escape  # Close menu
  xdotool sleep 0.1

  xdotool key Return  # View 1st unread thread
fi
