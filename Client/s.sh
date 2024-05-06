#!/bin/bash

  



./Shell/up.sh
dir="Log"

find "$dir" -type f -exec truncate -s 0 {} \;

#make clean
make
./bin/main

find "$dir" -type f -exec cat -n {} \;
