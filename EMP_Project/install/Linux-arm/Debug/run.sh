#!/bin/bash

echo check for gaserivce ... 
if [ $(ps -A | grep -c gaservice) = 0 ];
then
	cd config

	export IP_ADDR=`ip addr show eth0 | awk '/inet / {sub(/\/.*/, "", $2); print $2}'`
	echo use IP Address $IP_ADDR as interface for gamma
	
	cp config.template.xml config.xml
	sed -i "s/__IP__/$IP_ADDR/g" config.xml
	 
	/opt/gamma/bin/gaservice -c config.xml -p project.xml -l console &
	sleep 3
	cd ..
fi

echo set library path
export LD_LIBRARY_PATH=.:/usr/local/lib:/usr/lib:/opt/gamma/lib:$LD_LIBRARY_PATH

cd bin

echo Load Basetec cape.
/usr/local/bin/BASETEC_800479115.sh

 
echo start main application
./GaApp

echo stop gaservice ...
pkill -x gaservice
sleep 5
