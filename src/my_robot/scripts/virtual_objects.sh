#!/bin/sh
xterm -e "source ../../../../devel/setup.bash ; roslaunch my_robot world.launch" &
sleep 2
xterm -e "source ../../../../devel/setup.bash ; roslaunch my_robot amcl.launch" &
sleep 2
xterm -e "source ../../../../devel/setup.bash ; rosrun my_robot add_markers" &
sleep 2
