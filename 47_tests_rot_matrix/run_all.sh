#!/bin/bash

testdir="/usr/local/intro_prog/rot_matrix"

run_test() {
    prog="$1"
    testfile="$2"
    IFS=$'\n'
    for line in `cat $testfile | sed 's/^$/ /'`
    do
	IFS=" " correct=`${testdir}/rotateMatrix $line 2>&1`
	IFS=" " broken=`$prog $line 2>&1`
	if [ "$broken" != "$correct" ]
	then
	    return 0
	fi
    done
    return 1
}

for i in ${testdir}/rotateMatrix*
do
    if [ "$i" != "${testdir}/rotateMatrix" ]
    then
	echo "Checking `basename $i`"
	run_test $i tests.txt
	x="$?"
	if [ "$x" != "0" ]
	then
	    echo "***Your tests failed to show that `basename $i` was broken!"
	fi
    fi
done
