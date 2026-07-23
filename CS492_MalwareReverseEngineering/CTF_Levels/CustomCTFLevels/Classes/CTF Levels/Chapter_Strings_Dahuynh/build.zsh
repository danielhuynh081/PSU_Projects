#!/bin/zsh

SALT=$(date)

if [[ $# -gt 0 ]]; then
  BINNAME=$(basename "$PWD")

  for USER in "$@"; do
    mkdir -p "obj/$USER"

    AA=$(echo "$USER $SALT $BINNAME" | shasum | base64 | head -1 | cut -c 1-8)

    echo "User: $USER | Password: $AA"

    sed "s/AAAAAA/$AA/" program.c.template | \
    clang -o "obj/$USER/$BINNAME" -x c -
  done

else
  echo "USAGE: build.zsh <user_email(s)>"
fi
