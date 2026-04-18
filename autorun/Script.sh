#!/bin/bash
sudo systemctl stop pigpiod
sudo killall -9 RC_Vehicle_terminal pigpiod 2>/dev/null
sudo rm -f /var/run/pigpio.pid &&

cd RC_Vehicle_terminal &&
cd build &&
sudo ./RC_Vehicle_terminal > output.log






#