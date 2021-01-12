#!/bin/bash

#: ◢ + Left - Switch to previous tab (global, Chromium DevTools)

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  # gnome terminal has focus
  xdotool key Control_L+Page_Up
  exit 0
fi

activeWindowTitle=$(xdotool getactivewindow getwindowname)
if [[ $activeWindowTitle == "DevTools"* ]]; then
  # Chromium DevTools: focus next tab (CTRL+])
  xdotool key Control_L+bracketleft
  exit 0
fi

# default key combo
xdotool key shift+ctrl+Tab
