#!/bin/bash

#: BR + U: Type current UNIX timestamp

sleep 0.1
xdotool key 0xff08

now=$(date +'%s')
xdotool type $now
