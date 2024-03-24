#!/bin/bash

FILESDIR=$1
SEARCHSTR=$2

# check for empty string
if [ -z $FILESDIR ]
then
	echo "ERROR: file directory input is empty"
	exit 1
fi

# check for valid file directory
if [ ! -d $FILESDIR ]
then
	echo "ERROR: file directory input is not a directory"
	exit 1
fi

# check for empty string
if [ -z $SEARCHSTR ]
then
	echo "ERROR: search string input is empty"
	exit 1
fi

# recursive search file directory and get the number of files
#
# https://stackoverflow.com/questions/9157138/recursively-counting-files-in-a-linux-directory
X=$( find $FILESDIR -type f | wc -l )

# https://unix.stackexchange.com/questions/6979/count-total-number-of-occurrences-using-grep
Y=$( grep -ro $SEARCHSTR $FILESDIR | wc -l)

echo "The number of files are $X and the number of matching lines are $Y"
