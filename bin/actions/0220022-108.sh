#!/bin/bash

#: ◣ + Down -
#: Jump-scroll to bottom- the invoked required key combo differs among programs,
#: some need "End" others "Ctrl+End" (e.g. LibreOffice)

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ soffice.bin ]] \
|| [[ "$focusApplication" =~ "java" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+End
else  # Default
  xdotool sleep 0.1
  xdotool key End
fi
