#!/bin/bash

#: ◣ + Numpad 5 - Maximize active window

wmctrl -r :ACTIVE: -b toggle,maximized_vert,maximized_horz
