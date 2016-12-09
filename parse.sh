#!/bin/bash -e

COMP=
LINK=

function parse() {
    cc=$1
    #exe=$(basename $cc)
    exe=clang-3.8
    SEARCH_CC="s/^.*$exe\"//p"
    SEARCH_LD="s/^.*$ld\"//p"
    echo cc = $cc
    echo exe = $exe
    echo search var = $SEARCH_CC
    shift
    ARGS="$@"
    echo ARGS = $ARGS
    #COMMAND_CC="$cc -### $ARGS 2>&1 > /dev/null | sed -n -e \"$SEARCH_CC\""
    #echo command =  "${COMMAND_CC}"
    #COMP=($($COMMAND_CC))
    COMP=$( $cc -### "$@" 2>&1 > /dev/null | sed -n -e "$SEARCH_CC" | sed 's/"//g' )
    #$cc -### "$@" 2>&1 > /dev/null | sed -n -e 's/^.*$clang"//p'
    #LINK=$(clang++ -### "$@" 2>&1 > /dev/null | sed -n -e 's/^.*ld"//p')
    LINK=$($cc -### "$@" 2>&1 > /dev/null | sed -n -e "$SEARCH_LD" | sed 's/"//g' )
}




parse "$@"

echo Command Line Args: "$@"

echo -e "\n\n"
for a in ${COMP[@]}
do
    COMPS+=$a
done

echo Compiler flags: ${COMP[@]}

echo -e "\n\n"

echo Linker flags ${LINK}
