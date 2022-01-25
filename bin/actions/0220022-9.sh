#!/bin/bash

#: ◣ + 8 - Move caret eight times to the right (e.g. to crop git hashes quickly)

focusApplication=$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$(
  cd "$(dirname "$0")" >/dev/null 2>&1 || exit
  pwd -P
)"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

xdotool sleep 0.1

for i in {1..8}; do
  xdotool key Right
done
