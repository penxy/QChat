#!/bin/bash




dir="Log"

find "$dir" -type f -exec truncate -s 0 {} \;

#make clean

echo "" > log.txt
make
./bin/Server


find "$dir" -type f -exec cat -n {} \;

