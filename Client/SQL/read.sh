#!/bin/bash



cd SQL/DataBases;

[[ $# < 1 ]] && echo "arg error" && exit 1

myid=$1
python3 ../read.py $myid


cd ../..




# clear db after read
cd SQL;
./ClearDB.sh $1
cd ..