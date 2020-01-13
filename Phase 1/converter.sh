#!/bin/bash

function scan ()
{
	#display the local path
	path=$(cd "$(dirname "$0")"; pwd);
	echo path=$(cd "$(dirname "$0")"; pwd);

	#call the function convert
	convert;

	filelist=`ls`;
	for file in $filelist;
	do
		#recursive
		if [ -d $file ];
		then
			cd $file;
			scan;
			cd ..;
		fi
	done
}

function convert()
{
	for im in *.png;
	do
		echo "Converting: " $im;
		#convert png to ppm and rename
		ffmpeg -i $im $(basename $im png)ppm;
	done
	#delete the original function
        rm *.png;
}

scan

#Written in Shell language

#Function: Convert all documents including child documents png to ppm 

#Manual:
#1). install ffmpeg in a terminal
#2). move this file to your database of png documents or folders
#3). open the path in last step in a terminal
#4). run "chmod +x ./converter.sh"
#5). run "./converter.sh"
