#!/bin/bash

#: ◢ + L - Toggle keyboard backlight

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

if grep -Fxq "0" /sys/class/leds/tpacpi::kbd_backlight/brightness
then
  echo '2' | sudo tee /sys/class/leds/tpacpi::kbd_backlight/brightness
else
  echo '0' | sudo tee /sys/class/leds/tpacpi::kbd_backlight/brightness
fi

unset focusApplication
unset path_self
