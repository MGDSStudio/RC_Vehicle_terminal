#!/bin/bash

sudo systemctl stop pigpiod

sudo killall -9 RC_Vehicle_terminal pigpiod 2>/dev/null

sudo rm -f /var/run/pigpio.pid &&

sleep 15 &&

cd RC_Vehicle_terminal &&

git pull &&

cd build &&

cmake -DCMAKE_BUILD_TYPE=Release .. &&

cmake --build . -j 1 &&

sudo ./RC_Vehicle_terminal





#