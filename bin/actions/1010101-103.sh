#!/bin/bash

#: BL + Up - Increase audio volume

amixer -D pulse sset Master 5%+

me=$SUDO_USER
currentVolume=`amixer -D pulse sget Master | grep 'Front Left: Playback' | grep -oE "[0-9]{1,3}%"`
sudo -u $me echo "Volume louder ($currentVolume)" | osd_cat -A right -p top -f -*-*-bold-*-*-*-36-120-*-*-*-*-*-* -cgray -d 1
