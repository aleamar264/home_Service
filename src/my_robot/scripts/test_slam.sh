#!/bin/sh
xterm -e "source ../../../devel/setup.bash ; roslaunch my_robot world.launch" &
sleep 2
xterm -e "source ../../../devel/setup.bash ; roslaunch my_robot map_slam.launch" &
sleep 2
xterm -e "source ../../../devel/setup.bash ; rosrun teleop_twist_keyboard teleop_twist_keyboard.py " &
sleep 2