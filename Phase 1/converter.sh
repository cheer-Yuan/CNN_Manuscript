#!/bin/bash

function scan ()
{
path=$(cd "$(dirname "$0")"; pwd);
echo path=$(cd "$(dirname "$0")"; pwd);
	convert;
	filelist=`ls`;
	for file in $filelist;
	do
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
		ffmpeg -i $im $(basename $im png)ppm;
	done
        rm *.png;
}

scan
#Before running the program use : chmod +x ./converter.sh

