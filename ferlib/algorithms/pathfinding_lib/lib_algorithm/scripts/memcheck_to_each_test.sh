#!/bin/bash

#!\file valgrind_to_each_test.sh

##------------------------------------------------------------------------------

VALGRIND_OPTIONS="--leak-check=full --leak-resolution=high --partial-loads-ok=yes --track-origins=yes --undef-value-errors=yes"
#--show-leak-kinds=all"

START_DATE=$(date) # just to check the total execution time

WORK_DIR=$PWD
TEST_DIR="$WORK_DIR/../test/test_generating_lib/"


##------------------------------------------------------------------------------

exec_memcheck()
{
  exec_tests
  bring_results
}


##------------------------------------------------------------------------------

exec_tests()
{
    cd $TEST_DIR


#make run.concrete_singledist_test
#echo $PWD
    for test in $(ls *_test.cc | sed 's/.cc//g')
    do
	echo Executing: valgrind $test

	LOCAL_VALGRIND_OPTIONS="$VALGRIND_OPTIONS --log-file=vgrind.$test.out"
#  echo LOCAL_VALGRIND_OPTIONS : $LOCAL_VALGRIND_OPTIONS

#    RUN_COMMAND="make runtest"
	RUN_COMMAND="make run.$test"
#    echo RUN_COMMAND : $RUN_COMMAND 
        
	valgrind $LOCAL_VALGRIND_OPTIONS $RUN_COMMAND

    done 
}

##------------------------------------------------------------------------------

bring_results()
{
    mv $TEST_DIR/*.out $WORK_DIR
    cd $WORK_DIR

# echo
# echo
# echo --- TEST_DIR ---
#   pwd
#   echo $TEST_DIR
#   ls $TEST_DIR
# echo
# echo --- WORK_DIR ---
#   echo $WORK_DIR
#   ls $WORK_DIR
# echo
#   exit 44
  
}

##------------------------------------------------------------------------------

show_results()
{
cd $WORK_DIR

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

}

##==============================================================================

exec_memcheck
show_results

##==============================================================================
