#!/bin/bash

#: Right Shift + BR + Any of the top buttons pressed together: Switch to previous workspace

me=$SUDO_USER
sudo -u $me dbus-send --dest=org.Cinnamon --print-reply /org/Cinnamon org.Cinnamon.switchWorkspaceLeft
