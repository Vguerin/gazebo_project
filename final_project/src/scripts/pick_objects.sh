#!/bin/sh
xterm -e "roscore" &
sleep 5
xterm -e "roslaunch my_robot world.launch" &
#xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e "roslaunch my_robot amcl.launch" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "rosrun pick_objects pick_objects_node" 

