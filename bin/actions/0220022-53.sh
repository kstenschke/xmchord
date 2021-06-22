#!/bin/bash

#: ◣ + [-] in browser - Toggle URL part
# for setup, two URL sub-strings parts must be defined as env-vars:
# `XMCHORD_URL_SUBSTR_1` and `XMCHORD_URL_SUBSTR_2`.
# This action replaces each of these within the active browser's URL by the
# other one and re/loads the URL after.

xdotool sleep 0.1

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

if [[ "$focusApplication" =~ "chromium-browse" ]] \
|| [[ "$focusApplication" =~ "chromium" ]] \
|| [[ "$focusApplication" =~ "firefox" ]]; then
  xdotool sleep 0.1
  xdotool key Ctrl+l  # focus URL
  xdotool sleep 0.1
  xdotool key Ctrl+x  # cut
  sleep 0.1
  TOGGLE_URL=$(xclip -o)  # put into variable

  if [[ $TOGGLE_URL == *"$XMCHORD_URL_SUBSTR_2"* ]]; then
    # URL does contain env var $URL_SUBSTR_2
    # replace $URL_SUBSTR_2 within URL by $URL_SUBSTR_1
    TOGGLE_URL="${TOGGLE_URL/$XMCHORD_URL_SUBSTR_2/$XMCHORD_URL_SUBSTR_1}"
  else
    # replace $URL_SUBSTR_1 within URL by $URL_SUBSTR_2
    TOGGLE_URL="${TOGGLE_URL/$XMCHORD_URL_SUBSTR_1/$XMCHORD_URL_SUBSTR_2}"
  fi;

  echo "$TOGGLE_URL" | xclip -in -selection clipboard  # put URL into clipboard

  sleep 0.1
  xdotool key Ctrl+v  # paste modified URL
  sleep 0.1
  xdotool key Return
fi

unset focusApplication
