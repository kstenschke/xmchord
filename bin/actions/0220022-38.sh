#!/bin/bash

#: BR + L: Turn on keyboard backlight

echo '2' | sudo tee /sys/class/leds/tpacpi::kbd_backlight/brightness