#!/bin/bash

#: Right Shift + ◢ + Any of the top buttons -
#: Switch to previous workspace

me=$SUDO_USER

sudo -u "$me" dbus-send --dest=org.Cinnamon \
--print-reply /org/Cinnamon org.Cinnamon.switchWorkspaceLeft &> /dev/null
