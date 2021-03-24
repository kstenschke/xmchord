#!/bin/bash

#: ◣ + U -
#: If terminal active: Type scp command to recursively upload directory
#: Else: Type current UNIX timestamp

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

# Type scp command to recursively download remote directory
if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  xdotool sleep 0.1
  xdotool type "scp -r $XMCHORD_SCP_LOCAL $XMCHORD_SCP_REMOTE"

  unset focusApplication
  unset path_self
  exit 0
fi

# Type current UNIX timestamp
sleep 0.1
xdotool key 0xff08  # Backspace

timestapm_now=$(date +'%s')
xdotool type "$timestapm_now"

unset timestapm_now
unset focusApplication
unset path_self
