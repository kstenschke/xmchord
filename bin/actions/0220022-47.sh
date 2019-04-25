#!/bin/bash

#: BR + V - Toggle active window "always on visible workspace" property

wmctrl -r :ACTIVE: -b toggle,sticky

me=$SUDO_USER
#sudo -u $me notify-send "Toggled always on visible workspace (sticky)"
sudo -u $me echo "Always on visible workspace" | osd_cat -A right -p top -f -*-*-bold-*-*-*-36-120-*-*-*-*-*-* -cgray -d 1
