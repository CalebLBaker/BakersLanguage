#!/bin/bash

# Parse command line arguments
o_flag=false
outfile="out.elf"
infile=""
for var in $@
	do
		if [ "$o_flag" = true ] ; then
			outfile=$var
			o_flag=false
		elif [ "$var" = "-o" ] ; then
			o_flag=true
		else
			infile=$var
		fi
	done

# Check to make sure an input file was specified
if [ "$infile" = "" ] ; then
	echo "No input file specified"
	exit -1
fi

# Compile
blc $infile -o tmpfile.s
nasm tmpfile.s -f Elf64 -o tmpfile.o
ld tmpfile.o -o $outfile

# Delete temporary file
rm tmpfile.s
rm tmpfile.o

exit 0

