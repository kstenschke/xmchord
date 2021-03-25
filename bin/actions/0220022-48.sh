#!/bin/bash

#: ◣ + B
#: Within Thunderbird: Open address book
#: Else: Open new bash (terminal)

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

# Thunderbird: open address book
if [[ "$focusApplication" =~ "thunderbird" ]]; then
  xdotool sleep 0.1
  xdotool key Down
  xdotool key Ctrl+Shift+b

  unset focusApplication
  unset path_self
  exit 0
fi

# Else: open terminal
me=$SUDO_USER
sudo -u "$me" nohup gnome-terminal &> /dev/null
