#!/bin/bash

#: BR + L - Toggle keyboard backlight

if grep -Fxq "0" /sys/class/leds/tpacpi::kbd_backlight/brightness
then
  echo '2' | sudo tee /sys/class/leds/tpacpi::kbd_backlight/brightness
else
  echo '0' | sudo tee /sys/class/leds/tpacpi::kbd_backlight/brightness
fi
