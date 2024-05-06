#!/bin/bash


[[ $# == 0 ]] && echo "arg error" && exit 1
cd DataBases;
db_name="mydb$1.db"
sqlite3 $db_name < ../ClearDB.sql
cd ..

#echo $PWD
