#!/bin/bash

#!\file valgrind_to_each_test.sh

##------------------------------------------------------------------------------

VALGRIND_OPTIONS="--leak-check=full --leak-resolution=high --partial-loads-ok=yes --track-origins=yes --undef-value-errors=yes"
#--show-leak-kinds=all"

START_DATE=$(date) # just to check the total execution time

##------------------------------------------------------------------------------

# for test in $(grep BOOST_AUTO_TEST_CASE ../test/test.cc \
#    | sed 's/\/\/.*//g' \
#    | sed 's/.*(//g' \
#    | sed 's/)//g')
# do

#make run.concrete_singledist_test
#echo $PWD
for test in $(ls *_test.cc | sed 's/.cc//g')
do
   echo Executing: valgrind $test

   LOCAL_VALGRIND_OPTIONS="$VALGRIND_OPTIONS --log-file=vgrind.$test.out"
#    echo LOCAL_VALGRIND_OPTIONS : $LOCAL_VALGRIND_OPTIONS

#    RUN_COMMAND="make runtest"
     RUN_COMMAND="make run.$test"
#    echo RUN_COMMAND : $RUN_COMMAND 
        
   valgrind $LOCAL_VALGRIND_OPTIONS $RUN_COMMAND

done 

##------------------------------------------------------------------------------

echo
echo
echo Start time...
echo $START_DATE
echo
echo End time...
date
echo 

# Example brief error info
echo
echo Memory errors:
grep -L "ERROR SUMMARY: 0" *.out
echo
echo Memory leaks:
grep -L "definitely lost: 0" *.out
echo
