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

#Before running the program use : chmod +x ./converter.sh

