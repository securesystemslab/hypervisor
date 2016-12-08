#!/bin/bash -e

COMP=
LINK=

function parse() {
    COMP=($(clang++ -### "$@" 2>&1 > /dev/null | sed -n -e 's/^.*clang"//p'))
    LINK=$(clang++ -### "$@" 2>&1 > /dev/null | sed -n -e 's/^.*ld"//p')
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
