#!/bin/bash

#: BR + V - Toggle active window "always on visible workspace" property

wmctrl -r :ACTIVE: -b toggle,sticky
