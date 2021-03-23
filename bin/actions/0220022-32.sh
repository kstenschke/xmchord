#!/bin/bash

#: ◣ + D -
#: If Chromium or Firefox active: Duplicate tab.
#: If terminal active: Type scp command to recursively download remote directory
#: Else: Bring DataGrip window to front

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "chromium" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  clipboard=$( xsel -ob )

  xdotool sleep 0.1
  xdotool key Ctrl+l
  xdotool key Ctrl+c
  xdotool key Ctrl+t
  xdotool key Ctrl+v
  xdotool key Return

  echo "$clipboard" | xclip -in -selection clipboard

  unset clipboard
  unset focusApplication
  unset path_self
  exit 0
fi

# Type scp command to recursively download remote directory
if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  xdotool sleep 0.1
  xdotool type "scp -r "
  xdotool type $XMCHORD_SCP_REMOTE
  xdotool type " "
  xdotool type $XMCHORD_SCP_LOCAL

  unset focusApplication
  unset path_self
  exit 0
fi

# Bring DataGrip window to front
if pidof -s datagrip.sh >/dev/null; then
  wmctrl -a datagrip
else
  me=$SUDO_USER
  sudo -u "$me" nohup datagrip >/dev/null &
  unset me
fi

unset focusApplication
unset path_self
