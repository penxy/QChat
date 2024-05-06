#!/bin/bash


# it will ignore the first line


# clear db
cd SQL;
./ClearDB.sh $1
cd ..


cd SQL/DataBases;

[[ $# < 1 ]] && echo "arg error" && exit 1
myid=$1
python3 ../write.py $myid



cd ../..

# clear csv file

cd SQL;
./ClearCSV.sh
cd ..


