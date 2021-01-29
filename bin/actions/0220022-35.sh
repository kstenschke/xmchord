#!/bin/bash

#: ◢ + H in browser - Toggle "view-source:" prefix of current URL.
#: In Claws-Mail - Toggle "hide read messages"
# (precondition: "thread view" option must be deactivated)

focusApplication=$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "claws-mail" ]]; then
  echo "Toggle hide read threads" | aosd_cat -R white -u 300 --y-offset=40 \
    -B black -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1

  xdotool key Alt+v                    # Expand "View" menu

  seq 6 | xargs -I -- xdotool key Down # Select "hide read messages" option

  xdotool key space # Toggle selected option
  xdotool sleep 0.1

  xdotool key Escape # Close menu
  xdotool sleep 0.1

  xdotool key Return # View 1st unread thread
else
  if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
    xdotool sleep 0.1
    xdotool key Control_L+d
  else
    if [[ "$focusApplication" =~ "chromium-browse" ]] \
    || [[ "$focusApplication" =~ "chromium" ]] \
    || [[ "$focusApplication" =~ "firefox" ]]; then
      clipboard=$( xsel -ob )

      xdotool sleep 0.1
      xdotool key Ctrl+l
      xdotool sleep 0.1
      xdotool key Ctrl+a
      xdotool key Ctrl+c
      xdotool key Home

      copied_url=$(xsel -ob)

      if [[ $copied_url == view-source* ]]; then
        seq 12 | xargs -I -- xdotool key Delete
      else
        xdotool type "view-source:"
        xdotool key End
      fi

      xdotool key Return

      echo "$clipboard" | xclip -in -selection clipboard
      unset clipboard
      unset copied_url
    fi
  fi
fi
