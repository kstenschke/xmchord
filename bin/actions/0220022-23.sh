#!/bin/bash

#: ◢ + I - Display public and private IP Adress, copy public IP address

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"

"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

public_ip=$(curl -s ident.me)
private_ip=$(hostname -I | awk '{print $1}')

echo "$public_ip" | xclip -in -selection clipboard

(sleep 0.1; printf "Public IP: %s (Copied)\rPrivate IP: %s" \
"$private_ip" "$public_ip" | aosd_cat -R white -u 700 --y-offset=40 \
-B black -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1)

unset focusApplication
unset path_self
unset public_ip
unset private_ip
