#!/bin/bash

#: ◣ + L
# In Terminal: Type and execute `rm -rf` shortcut to wipe configured cache directory
# Otherwise: Toggle keyboard backlight

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

# Terminal has focus: Type and execute command to `rm -rf` a configured path
if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  xdotool sleep 0.1
  xdotool type "rm -rf $XMCHORD_RM_FAVORITE"
  xdotool key Return

  unset focusApplication
  unset path_self
  exit 0
fi

if grep -Fxq "0" /sys/class/leds/tpacpi::kbd_backlight/brightness
then
  echo '2' | sudo tee /sys/class/leds/tpacpi::kbd_backlight/brightness
else
  echo '0' | sudo tee /sys/class/leds/tpacpi::kbd_backlight/brightness
fi

unset focusApplication
unset path_self
