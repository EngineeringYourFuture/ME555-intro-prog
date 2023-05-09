#!/bin/bash

testdir="/usr/local/intro_prog/power"

run_test(){
    i="$1"
    test=`basename $i | sed 's/power//' | sed 's/.o//'`
    if [ "$test"  == "" ]
    then
	echo "**Testing correct implementation**"
    else
	echo "**Testing broken implementation ${test}**"
    fi
    echo "-------------------------------------"
    echo ""
    gcc -o test-power test-power.c $i
    if [ "$?" != "0" ]
    then
	echo "Could not compile test-power.c with $i" > /dev/stderr
	exit 1
    fi
    ./test-power
    if [ "$?" != 0 ]
    then
	if [ "$test" == "" ]
	then
	    echo "Your test program falsely failed the correct implementation!" > /dev/stderr
	    exit 1
	fi
    else
	if [ "$test" != "" ]
	then
	    echo "Your test program did not identify $i as broken!" > /dev/stderr
	    exit 1
	fi
    fi
    echo ""
}

# do correct impl first
run_test ${testdir}/power.o

# do broken impls
for i in ${testdir}/power?*.o
do
    run_test $i
done
