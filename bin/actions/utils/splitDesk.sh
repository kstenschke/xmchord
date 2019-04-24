#!/bin/bash

# original script copied from Steve Simpson's gist: https://gist.github.com/culyun/a7347a58168a75ba8c06f1ddd67cf06d

## get screens from left to right
## get screens x-origin
#SCREEN1_X0=$(wmctrl -lG | grep Schreibtisch | awk 'NR==1{print $3;}')
#SCREEN2_X0=$(wmctrl -lG | grep Schreibtisch | awk 'NR==2{print $3;}')
#SCREEN3_X0=$(wmctrl -lG | grep Schreibtisch | awk 'NR==3{print $3;}')
#
## get screens y-origin
#SCREEN1_Y0=$(wmctrl -lG | grep Schreibtisch | awk 'NR==1{print $4;}')
#SCREEN2_Y0=$(wmctrl -lG | grep Schreibtisch | awk 'NR==2{print $4;}')
#SCREEN3_Y0=$(wmctrl -lG | grep Schreibtisch | awk 'NR==3{print $4;}')
#
## get screens x-max
#SCREEN1_X1=$(wmctrl -lG | grep Schreibtisch | awk 'NR==1{print $5;}')
#SCREEN2_X1=$(wmctrl -lG | grep Schreibtisch | awk 'NR==2{print $5;}')
#SCREEN3_X1=$(wmctrl -lG | grep Schreibtisch | awk 'NR==3{print $5;}')
#
## get screens y-max
#SCREEN1_Y1=$(wmctrl -lG | grep Schreibtisch | awk 'NR==1{print $6;}')
#SCREEN2_Y1=$(wmctrl -lG | grep Schreibtisch | awk 'NR==2{print $6;}')
#SCREEN3_Y1=$(wmctrl -lG | grep Schreibtisch | awk 'NR==3{print $6;}')
#
#echo "screen 1: $SCREEN1_X0, $SCREEN1_Y0 to $SCREEN1_X1, $SCREEN1_Y1";
#echo "screen 2: $SCREEN2_X0, $SCREEN2_Y0 to $SCREEN2_X1, $SCREEN2_Y1";
#echo "screen 3: $SCREEN3_X0, $SCREEN3_Y0 to $SCREEN3_X1, $SCREEN3_Y1";

ICON=0
GapX=1
GapY=0
TOP_MARGIN=0
BOTTOM_MARGIN=46
LEFT_MARGIN=0
RIGHT_MARGIN=$ICON

# Max Resolution X and Y
# xrandr has got cleverer.  It knows about monitors.  The --q1 dumbs things down.. needs to be fixed
MAX_X=`xrandr --q1 | grep "*" | awk '{print $2}'`
MAX_Y=`xrandr --q1 | grep "*" | awk '{print $4}'`
#Y=`xrandr --q1 | grep "*" | awk '{print $1}' | awk -F "x" '{print $2}'`

# Working area
WX=$((($MAX_X)-$ICON))
WY=$((($MAX_Y)-$BOTTOM_MARGIN))

# X Coordinates
X1=$((($WX/2)))
X2=$((($WX/2)+$GapX))

# Y Coordinates
Y1=$((($WY/2)))
Y2=$((($WY/2)+$GapY))

# echo Screen Resolution X x Y = $MAX_X x $MAX_Y
# echo Working area resolution X x Y = $WX x $WY
# echo X1 = $X1, X2 = $X2
# echo Y1 = $Y1, Y2 = $Y2

wmctrl -r :ACTIVE: -b remove,maximized_vert,maximized_horz

case "$1" in
  'left') wmctrl -r :ACTIVE: -e "1,0,0,$X1,$WY" ;;
  'right') wmctrl -r :ACTIVE: -e "1,$X2,0,$X2,$WY" ;;
  'top') wmctrl -r :ACTIVE: -e "1,0,0,$WX,$Y1" ;;
  'bottom') wmctrl -r :ACTIVE: -e "1,0,$Y1,$WX,$Y1" ;;
  'top-left') wmctrl -r :ACTIVE: -e "1,0,0,$X1,$Y1" ;;
  'top-right') wmctrl -r :ACTIVE: -e "1,$X2,0,$X2,$Y1" ;;
  'bottom-left') wmctrl -r :ACTIVE: -e "1,0,$Y2,$X1,$Y1" ;;
  'bottom-right') wmctrl -r :ACTIVE: -e "1,$X2,$Y2,$X1,$Y1" ;;
  'full') wmctrl -r :ACTIVE: -e "1,0,0,$WX,$WY" ;;
  *) echo "Usage: $0 {left|right|top|bot|top-right|top-left|bottom-right|bottom-left}"; exit 1;;
esac