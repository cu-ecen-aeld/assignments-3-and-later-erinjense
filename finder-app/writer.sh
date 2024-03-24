#!/bin/bash

WRITEFILE=$1
WRITESTR=$2

# check for empty string
if [ -z $WRITEFILE ]
then
	echo "ERROR: file input is empty"
	exit 1
fi

# check for empty string
if [ -z $WRITESTR ]
then
	echo "ERROR: search string input is empty"
	exit 1
fi

# make just the parent directory
mkdir -p $( dirname $WRITEFILE )

# create the file in parent directory
touch $WRITEFILE

# overwrite with write str
echo $WRITESTR > $WRITEFILE
