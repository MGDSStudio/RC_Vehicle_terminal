#!/bin/bash
sleep 5
export DISPLAY=:0
#export SDL_VIDEODRIVER=dummy  #
#export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
systemctl stop pigpiod
killall -9 RC_Vehicle_terminal pigpiod 2>/dev/null
rm -f /var/run/pigpio.pid
cd /home/mgdsstudio/RC_Vehicle_terminal/build/bin || exit
./RC_Vehicle_terminal > /home/mgdsstudio/RC_Vehicle_terminal/output.log 2>&1

#crontab -e
#@reboot sudo /bin/bash /home/mgdsstudio/RC_Vehicle_terminal/autorun/Script.sh > /home/mgdsstudio/RC_Vehicle_terminal/cron_log.log 2>&1




#