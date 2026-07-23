#!/bin/bash

PROG=oll
POINTS=0
TOTAL_PONTS=75
CLEANUP=1
WARNINGS=0
DIFF_OPTIONS=""
BIG_TEST=0

SDIR=.
JDIR=~rchaney/Classes/cs201/Labs/Lab3

randTest() {
    LINES=$[ $RANDOM % 11000 + 15000 ]
    LEN=$[ $RANDOM % 200 + 700 ]
    ${JDIR}/gen_data -l ${LINES} -m ${LEN} > ip7.txt

    I=7
    ${SDIR}/${PROG} < ${SDIR}/ip${I}.txt > S-oll${I}.out
    ${JDIR}/${PROG} < ${SDIR}/ip${I}.txt > J-oll${I}.out

    diff ${DIFF_OPTIONS} S-oll${I}.out J-oll${I}.out > /dev/null
    if [ $? -eq 0 ]
    then
        ((POINTS+=9))
        echo "  +++ ${PROG} on test file ${PROG}-${I}.txt is good +++"
    else
        echo "  --- ${PROG} on test file ${PROG}-${I}.txt is sad  ---"
        CLEANUP=0
        echo "    try this: diff ${DIFF_OPTIONS} -y S-oll${I}.out J-oll${I}.out"
    fi
}

basicTests() {
    for I in `shuf -i 1-6 -n 6`
    do
        ${SDIR}/${PROG} < ${JDIR}/ip${I}.txt > S-oll${I}.out
        ${JDIR}/${PROG} < ${JDIR}/ip${I}.txt > J-oll${I}.out

        diff ${DIFF_OPTIONS} S-oll${I}.out J-oll${I}.out > /dev/null
        if [ $? -eq 0 ]
        then
            ((POINTS+=6))
            echo "  +++ ${PROG} on test file ${PROG}-${I}.txt is good +++"
        else
            echo "  --- ${PROG} on test file ${PROG}-${I}.txt is sad  ---"
            CLEANUP=0
            echo "    try this: diff ${DIFF_OPTIONS} -y S-oll${I}.out J-oll${I}.out"
        fi
    done
}

compileTest() {
    if [ ! -e ${PROG}.c ]
    then
        echo "No ${PROG}.c exists. Cannot continue."
        exit 1
    fi
    
    gcc -Wall -g -o ${PROG} ${PROG}.c 1> out.log 2> warn.log
    
    if [ $? -ne 0 ]
    then
        echo "compilation failed"
        echo "zero points"
        cat  out.log warn.log
        exit 1
    else
        NUM_BYTES=`wc -c < warn.log`
        if [ ${NUM_BYTES} -ne 0 ]
        then
            WARNINGS=1
            echo "  --- You have compiler warning messages. That is -20 percent!"
        else
            echo "  +++ You have no compiler warning messages. Good job."
           #((POINTS+=5))
        fi
    fi
}

valgrindTest() {
    cat ${JDIR}/ip1.txt ${JDIR}/ip2.txt ${JDIR}/ip3.txt | \
        valgrind ${SDIR}/${PROG} > vg.out 2> vg.err

    LEAKS=$(grep -c "All heap blocks were freed -- no leaks are possible" vg.err)
    if [ ${LEAKS} -eq 1 ]
    then
        echo "  EXCELLENT!!! You have no leaks!"
        ((POINTS+=30))
    else
        echo -e "\n*** Bummer. You have leaks. ***\n"
        #POINTS=$(echo ${POINTS}*.8 | bc)
        cat vg.err
    fi
}

while getopts "xCT" opt
do
    case $opt in
        x)
            # If you really, really, REALLY want to watch what is going on.
            echo "Hang on for a wild ride."
            set -x
            ;;
        C)
            # Skip removal of data files
            CLEANUP=0
            ;;
        \?)
            echo "Invalid option" >&2
            echo ""
            exit 1
            ;;
        :)
            echo "Option -$OPTARG requires an argument." >&2
            exit 1
            ;;
    esac
done

compileTest
basicTests
randTest
valgrindTest

echo "You have ${POINTS} points out of ${TOTAL_PONTS}"
if [ ${WARNINGS} -ne 0 ]
then
    POINTS=$(echo ${POINTS}*.8 | bc)
    echo "But, you have compiler warnings"
    echo "  So, you get this many points ${POINTS}"
fi

if [ ${CLEANUP} -eq 1 ]
then
    rm [JS]-oll[1-7].out out.log warn.log
    #rm ${PROG}
fi
