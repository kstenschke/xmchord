#!/bin/bash

# @author steve_simpson     Copied from gist: https://gist.github.com/culyun/a7347a58168a75ba8c06f1ddd67cf06d
# @author kay_stenschke     Added multi-screen offset detection for xmchord

# define $x, $y, $w, $y from active window position and dimension
unset x y w h
eval $(xwininfo -id $(xdotool getactivewindow) |
sed -n -e "s/^ \+Absolute upper-left X: \+\([0-9]\+\).*/x=\1/p" \
       -e "s/^ \+Absolute upper-left Y: \+\([0-9]\+\).*/y=\1/p" \
       -e "s/^ \+Width: \+\([0-9]\+\).*/w=\1/p" \
       -e "s/^ \+Height: \+\([0-9]\+\).*/h=\1/p" )

# get screens absolute horizontal offset
# @todo make this language independent or localize "Schreibtisch"
SCREEN0_X0=$(wmctrl -lG | grep Schreibtisch | awk 'NR==1{print $3;}')
# subtract 1 so detection using greater-than works
SCREEN0_X0=$((SCREEN0_X0 / 2 - 1))

SCREEN1_X0=$(wmctrl -lG | grep Schreibtisch | awk 'NR==2{print $3;}')
SCREEN1_X0=$((SCREEN1_X0 / 2 - 1))

SCREEN2_X0=$(wmctrl -lG | grep Schreibtisch | awk 'NR==3{print $3;}')
SCREEN2_X0=$((SCREEN2_X0 / 2 - 1))

# detect offsets by which screen the active window is on
SCREEN_LEFT=0;
if [ ${x} -gt ${SCREEN0_X0} ] && [ ${x} -lt ${SCREEN1_X0} ]; then
    SCREEN_LEFT=${SCREEN0_X0};
else
    if [ ${x} -gt ${SCREEN1_X0} ] && [ ${x} -lt ${SCREEN2_X0} ]; then
        SCREEN_LEFT=${SCREEN1_X0};
    else
        if [ ${x} -gt ${SCREEN2_X0} ]; then
            SCREEN_LEFT=${SCREEN2_X0};
        fi;
    fi;
fi;

ICON=0
GapX=1
GapY=0
TOP_MARGIN=0
BOTTOM_MARGIN=46
LEFT_MARGIN=0
RIGHT_MARGIN=$ICON

# Max Resolution X and Y
MAX_X=`xrandr --q1 | grep "*" | awk '{print $2}'`
MAX_Y=`xrandr --q1 | grep "*" | awk '{print $4}'`

# Working area
WX=$((($MAX_X)-$ICON))
WY=$((($MAX_Y)-$BOTTOM_MARGIN))

# X Coordinates
X1=$((($WX/2)))
X2=$((($WX/2)+$GapX))

# Y Coordinates
Y1=$((($WY/2)))
Y2=$((($WY/2)+$GapY))

wmctrl -r :ACTIVE: -b remove,maximized_vert,maximized_horz

case "$1" in
  'left') wmctrl -r :ACTIVE: -e "1,$SCREEN_LEFT,0,$X1,$WY" ;;
  'right')
    LEFT=$((X2 + SCREEN_LEFT));
    wmctrl -r :ACTIVE: -e "1,$LEFT,0,$X2,$WY" ;;
  'top') wmctrl -r :ACTIVE: -e "1,$SCREEN_LEFT,0,$WX,$Y1" ;;
  'bottom') wmctrl -r :ACTIVE: -e "1,$SCREEN_LEFT,$Y1,$WX,$Y1" ;;
  'top-left') wmctrl -r :ACTIVE: -e "1,$SCREEN_LEFT,0,$X1,$Y1" ;;
  'top-right')
    LEFT=$((X2 + SCREEN_LEFT));
    wmctrl -r :ACTIVE: -e "1,$LEFT,0,$X2,$Y1" ;;
  'bottom-left') wmctrl -r :ACTIVE: -e "1,$SCREEN_LEFT,$Y2,$X1,$Y1" ;;
  'bottom-right')
    X2=$((X2 + SCREEN_LEFT));
    wmctrl -r :ACTIVE: -e "1,$X2,$Y2,$X1,$Y1" ;;
  'full') wmctrl -r :ACTIVE: -e "1,$SCREEN_LEFT,0,$WX,$WY" ;;
  *) echo "Usage: $0 {left|right|top|bot|top-right|top-left|bottom-right|bottom-left}"; exit 1;;
esac
