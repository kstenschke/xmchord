#!/bin/bash

#: BR + T: Toggle active window "always on top"

wmctrl -r :ACTIVE: -b toggle,above

me=$SUDO_USER
#sudo -u $me notify-send "Toggled always on top (above)"
sudo -u $me echo "Always on top" | osd_cat -A right -p top -f -*-*-bold-*-*-*-36-120-*-*-*-*-*-* -cgray -d 1