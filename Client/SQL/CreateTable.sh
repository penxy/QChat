#!/bin/bash



cd SQL/DataBases;
[ $# -eq 0 ] && echo "arg error" && exit 1
myid=$1
python3 ../CreateTable.py $myid
cd ../..
