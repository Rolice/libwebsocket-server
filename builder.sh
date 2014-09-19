#!/bin/bash

STARTTIME=$(date +%s)
PROJECTDIR=`pwd`

g++ -g -o $PROJECTDIR/bin/wsconsumer                                      \
	$PROJECTDIR/*.cpp                                                     \
	                                                                      \
	-I../libwebsocket                                                     \
	-L../libwebsocket/bin                                                 \
	-lwebsocket

ENDTIME=$(date +%s)

printf "\n\nBuild Time: \033[32m$(($ENDTIME - $STARTTIME)) seconds\033[0m.\n\n"
