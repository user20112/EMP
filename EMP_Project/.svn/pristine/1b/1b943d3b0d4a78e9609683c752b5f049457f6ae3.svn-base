#!/bin/bash

if [ "$1" == "local" ]
then
	echo using local device setup
	exec 2>./error.log
	
else
	echo using service device setup
	
	exec 0</dev/tty9
	exec 1>/dev/tty9
	exec 2>./error.log
fi

echo check for gaserivce ... 
if [ $(ps -A | grep -c gaservice) = 0 ];
then
	cd config

	export IP_ADDR=`ip addr show usb0 | awk '/inet / {sub(/\/.*/, "", $2); print $2}'`
	echo use IP Address $IP_ADDR as interface for gamma
	#eth0
	
	cp config.template.xml config.xml
	sed -i "s/__IP__/$IP_ADDR/g" config.xml
	 
	/opt/gamma/bin/gaservice -c config.xml -p project.xml -l console &
	sleep 3
	cd ..
fi

echo set library path
export LD_LIBRARY_PATH=.:/usr/local/lib:/usr/lib:$LD_LIBRARY_PATH


echo start main application 
cd bin
./GaApp
cd ..

echo stop all services
pkill -x XiBase9
pkill -x gaservice
sleep 5
