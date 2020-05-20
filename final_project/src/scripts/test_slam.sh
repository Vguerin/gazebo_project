#!/bin/sh
xterm -e "roslaunch my_robot world.launch" &
#xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "roslaunch my_robot teleop.launch" 

