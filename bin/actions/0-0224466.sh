#!/bin/bash

#: BR + Any of the top buttons together: Switch to next workspace

me=$SUDO_USER
sudo -u $me dbus-send --dest=org.Cinnamon --print-reply /org/Cinnamon org.Cinnamon.switchWorkspaceRight &> /dev/null
