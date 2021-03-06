#!/bin/bash

#: ◣ + S -
#: In terminal: Type and execute command to connect to preferred SSH host
#: Else: Toggle clicked window's (custom) "roll-sideways" state

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

# Type and execute command to connect to preferred SSH host
if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  xdotool sleep 0.1
  xdotool type "ssh $XMCHORD_SSH_REMOTE"
  xdotool key Return

  if [[ $XMCHORD_SSH_REMOTE_NEEDS_CONFIRMATION = "1" ]]; then
    sleep 0.3
    xdotool type "yes"
    xdotool key Return
  fi

  sleep 0.3
  xdotool type "cd $XMCHORD_SSH_REMOTE_PATH_INITIAL"
  xdotool key Return

  unset focusApplication
  unset path_self
  exit 0
fi

# Toggle clicked window's (custom) "roll-sideways" state
activeWindowId=$(xdotool getactivewindow)

# Get active window's width and height (excludes window decoration)
unset w
unset h

eval "$(xwininfo -id "$(xdotool getactivewindow)" |
  sed -n -e "s/^ \+Width: \+\([0-9]\+\).*/w=\1/p" \
         -e "s/^ \+Height: \+\([0-9]\+\).*/h=\1/p" )"

if [ "$w" -ne "30" ]; then
  # Window is NOT rolled-down sideways

  # Store width to file, to later be able to restore it
  mkdir -p ./tmp
  echo "$w" > "./tmp/window-width_$activeWindowId.txt"

  # Unmaximize window
  if xwininfo -all -id "$activeWindowId"|grep "Maximized Horz"; then
    wmctrl -r :ACTIVE: -b toggle,maximized_horz
    xdotool sleep 0.1
  fi
  if xwininfo -all -id "$activeWindowId"|grep "Maximized Vert"; then
    wmctrl -r :ACTIVE: -b toggle,maximized_vert
    xdotool sleep 0.1
  fi

  # Retain maximized dimension
  xdotool windowsize "$activeWindowId" "$w" ""
  xdotool sleep 0.1

  # Roll-down sideways
  xdotool windowsize "$activeWindowId" 30 ""
else
  # Window is rolled-down sideways, restore it's previous size
  w=$(cat ./tmp/window-width_"$activeWindowId".txt)
  xdotool windowsize "$activeWindowId" "$w" ""

  rm ./tmp/window-width_"$activeWindowId".txt
fi

unset focusApplication
unset path_self
unset w
unset h
