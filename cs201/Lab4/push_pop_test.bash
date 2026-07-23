#!/bin/bash

Build()
{
    echo "Building ..."
    make -s clean push_pop all > /dev/null 2>&1
    if [ ! -x ${SPROG} ]
    then
        echo "No executable: 0 points"
        exit
    fi
    echo -e "\tbuilt"
}

TestFile()
{
    #IFILE=${JDIR}/$1
    FN=$1
    IFILE=${JDIR}/push_pop_${FN}.txt
    echo "Testing with input: push_pop_${FN}.txt"

    ${JPROG} < ${IFILE} \
             > j${FN}1s_out.txt 2> j${FN}1s_err.txt
    ${JPROG} -i ${IFILE} \
             -o j${FN}1i_out.txt 2> j${FN}1i_err.txt

    timeout ${TO} ${SPROG} < ${IFILE} \
             > s${FN}1s_out.txt 2> s${FN}1s_err.txt
    timeout ${TO} ${SPROG} -i ${IFILE} \
             -o s${FN}1i_out.txt 2> s${FN}1i_err.txt

    ${DIFF} -q j${FN}1s_out.txt s${FN}1s_out.txt > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        ((P2_POINTS+=4))
        echo "    Pass 1 of push_pop_${FN}.txt compared the same. Excellent!"
    else
        echo "*** j${FN}1s_out.txt s${FN}1s_out.txt differ"
        echo "*** try 'diff -y s${FN}1s_out.txt j${FN}1s_out.txt' "
        CLEANUP=0
    fi
    ${DIFF} -q j${FN}1i_out.txt s${FN}1i_out.txt > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        ((P2_POINTS+=4))
    else
        echo "*** j${FN}1i_out.txt s${FN}1i_out.txt differ"
    fi

    
    BOT="-b 0x8140"
    RSP="-s 0x8130"
    ${JPROG} ${RSP} ${BOT} < ${IFILE} \
             > j${FN}2s_out.txt 2> j${FN}2s_err.txt
    ${JPROG} ${BOT} ${RSP} -i ${IFILE} \
             -o j${FN}2i_out.txt 2> j${FN}2i_err.txt

    timeout ${TO} ${SPROG} ${RSP} ${BOT} < ${IFILE} \
             > s${FN}2s_out.txt 2> s${FN}2s_err.txt
    timeout ${TO} ${SPROG} ${BOT} ${RSP} -i ${IFILE} \
             -o s${FN}2i_out.txt 2> s${FN}2i_err.txt

    ${DIFF} -q j${FN}2s_out.txt s${FN}2s_out.txt > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        ((P2_POINTS+=4))
        echo "    Pass 2 of push_pop_${FN}.txt compared the same. Excellent!"
    else
        echo "*** j${FN}2s_out.txt s${FN}2s_out.txt differ"
        echo "*** try 'diff -y s${FN}2s_out.txt j${FN}2s_out.txt' "
        CLEANUP=0
    fi
    ${DIFF} -q j${FN}2i_out.txt s${FN}2i_out.txt > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        ((P2_POINTS+=4))
    else
        echo "*** j${FN}2i_out.txt s${FN}2i_out.txt differ"
    fi


    LIM="-l 0x2000"
    RSP="-s 0x7530"
    ${JPROG} ${RSP} ${LIM} ${BOT} < ${IFILE} \
             > j${FN}3s_out.txt 2> j${FN}3s_err.txt
    ${JPROG} ${RSP} -i ${IFILE} ${BOT} ${LIM} \
             -o j${FN}3i_out.txt 2> j${FN}3i_err.txt

    timeout ${TO} ${SPROG} ${RSP} ${LIM} ${BOT} < ${IFILE} \
             > s${FN}3s_out.txt 2> s${FN}3s_err.txt
    timeout ${TO} ${SPROG} ${RSP} -i ${IFILE} ${BOT} ${LIM} \
             -o s${FN}3i_out.txt 2> s${FN}3i_err.txt

    ${DIFF} -q j${FN}3s_out.txt s${FN}3s_out.txt > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        ((P2_POINTS+=4))
        echo "    Pass 3 of push_pop_${FN}.txt compared the same. Excellent!"
    else
        echo "*** j${FN}3s_out.txt s${FN}3s_out.txt differ"
        echo "*** try 'diff -y s${FN}3s_out.txt j${FN}3s_out.txt' "
        CLEANUP=0
    fi
    ${DIFF} -q j${FN}3i_out.txt s${FN}3i_out.txt > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        ((P2_POINTS+=4))
    else
        echo "*** j${FN}3i_out.txt s${FN}3i_out.txt differ"
    fi


    # VOPTS="--show-leak-kinds=all --show-reachable=yes --track-origins=yes"
    timeout ${TO} valgrind ${SPROG} ${RSP} ${LIM} ${BOT} < ${IFILE} \
             -o s${FN}4s_out.txt 2> s${FN}4s_err.txt
    CLEAN=`tail -n 4 s${FN}4s_err.txt \
        | head -1 \
        | grep -c "All heap blocks were freed -- no leaks are possible"`
    if [ ${CLEAN} -eq 1 ]
    then
        echo -e "    Pass 4 - first valgrind is good"
        ((P2_POINTS+=4))
    else
        echo -e "\t*** first valgrind found leaks"
    fi


    timeout ${TO} valgrind ${SPROG} ${RSP} -i ${IFILE} ${LIM} ${BOT} \
             > s${FN}5s_out.txt 2> s${FN}5s_err.txt
    CLEAN=`tail -n 4 s${FN}5s_err.txt \
        | head -1 \
        | grep -c "All heap blocks were freed -- no leaks are possible"`
    if [ ${CLEAN} -eq 1 ]
    then
        echo -e "    Pass 5 - second valgrind is good"
        ((P2_POINTS+=4))
    else
        echo -e "\t*** second valgrind found leaks"
    fi
   
    echo -e "    Points so far on part 2: ${P2_POINTS}\n"
}

CLEANUP=1
LAB=Lab4
JDIR=~rchaney/Classes/cs201/Labs/${LAB}/
JPROG=${JDIR}/push_pop
SPROG=./push_pop
P2_POINTS=0
TO="5s"
DIFF="diff -w"

while getopts "xC" opt
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
        echo "disable cleaning up output files"
	    ;;
	\?)
	    echo "Invalid option" >&2
	    echo ""
	    #showHelp
	    exit 1
	    ;;
	:)
	    echo "Option -$OPTARG requires an argument." >&2
	    exit 1
	    ;;
    esac
done


Build

((P2_POINTS+=8))

TestFile 1
TestFile 2 
TestFile 3 
TestFile 4 
TestFile 5
TestFile 6

# needs more testing
#for FILE in `shuf -i 1-6 -n 6`
#do
#    TestFile ${FILE}
#done

echo -e "Points on part 2: ${P2_POINTS}\n"

if [ ${CLEANUP} -eq 1 ]
then
    echo "cleaning up output files"
    # a wee bit of a gnarly regex
    rm [js][1-7][1-6][is]_{out,err}.txt
fi
