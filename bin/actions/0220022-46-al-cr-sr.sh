#!/bin/bash

# workaround while "◢ + C" emits event code w/ trailing modifiers "al-cr-sr"

path_self="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
"$path_self"/0220022-46.sh
unset path_self
