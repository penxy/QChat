#!/bin/bash

# clear csv file without first line
dir="Data"
find $dir -type f -exec truncate -s 0 {} \;



