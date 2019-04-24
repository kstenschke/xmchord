#!/bin/bash

#: BR + E: Open Nemo

me=$SUDO_USER
sudo -u $me nohup nemo /home > /dev/null &
