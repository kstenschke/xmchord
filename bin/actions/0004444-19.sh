#!/bin/bash

#: TL + R - Open Run dialog

me=$SUDO_USER
sudo -u $me bash -c "$(zenity --entry --title 'Enter a Command' --text '' --width 400)" > /dev/null &
rnohup nemo /home
