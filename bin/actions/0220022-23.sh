#!/bin/bash

#: ◣ + I - Display public and private IP and Wifi MAC adress,
#: copy public IP address

focusApplication=\
$(cat /proc/"$(xdotool getwindowpid "$(xdotool getwindowfocus)")"/comm)

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 || exit ; pwd -P )"
"$path_self"/utils/remove_unwanted_output.sh "$focusApplication"

public_ip=$(curl -s ident.me)
private_ip=$(hostname -I | awk '{print $1}')

wifi_mac=$(ip addr show \
"$(awk 'NR==3{print $1}' /proc/net/wireless | tr -d :)" \
| awk '/ether/{print $2}')

echo "$public_ip" | xclip -in -selection clipboard

(sleep 0.1; printf "Public IP: %s (Copied)\rPrivate IP: %s\rWifi MAC: %s" \
"$private_ip" "$public_ip" "$wifi_mac" \
| aosd_cat -R white -u 3000 --y-offset=40 \
-B black -b 240 --padding=24 -x 5 -n "Ubuntu 20" -p 1)

unset focusApplication
unset path_self
unset public_ip
unset private_ip
unset wifi_mac
