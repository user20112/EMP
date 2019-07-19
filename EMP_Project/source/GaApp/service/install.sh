
systemctl stop GaApp.service
echo wait until serive is stopped ...
sleep 5
cp -u GaApp.service /etc/systemd/system/
systemctl enable /etc/systemd/system/GaApp.service
systemctl start GaApp.service
echo wait until serive is started ...
sleep 10
systemctl status GaApp.service
