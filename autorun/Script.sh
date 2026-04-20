#!/bin/bash
sleep 5
export DISPLAY=:0
#export SDL_VIDEODRIVER=dummy  #
#export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
systemctl stop pigpiod
killall -9 RC_Vehicle_terminal pigpiod 2>/dev/null
rm -f /var/run/pigpio.pid
cd /home/pi/RC_Vehicle_terminal/build || exit
./RC_Vehicle_terminal > /home/pi/output.log 2>&1

#crontab -e
#@reboot /bin/bash /home/pi/start_vehicle.sh > /home/pi/cron_log.log 2>&1




#