#!/bin/bash

#: BL + Up - Increase audio volume

amixer -D pulse sset Master 5%+

me=$SUDO_USER
#sudo -u $me notify-send "🔊++"
sudo -u $me echo "🔊++" | osd_cat -A right -p top -f -*-*-bold-*-*-*-36-120-*-*-*-*-*-* -cgray -d 1
