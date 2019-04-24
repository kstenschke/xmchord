#!/bin/bash

#: BR + T: Toggle active window "always on top"

wmctrl -r :ACTIVE: -b toggle,above
