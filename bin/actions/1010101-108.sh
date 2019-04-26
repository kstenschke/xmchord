#!/bin/bash

#: BL + Down - Decrease audio volume

amixer -D pulse sset Master 5%- &> /dev/null

me=$SUDO_USER
currentVolume=`amixer -D pulse sget Master | grep 'Front Left: Playback' | grep -oE "[0-9]{1,3}%"`
sudo -u $me echo "Volume lower ($currentVolume)" | osd_cat -A right -p top -f -*-*-bold-*-*-*-36-120-*-*-*-*-*-* -cgray -d 1
