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
#xterm -e "rosrun teleop_twist_keyboard teleop_twist_keyboard.py" &
xterm -e "rosrun add_markers add_markers_node"  &
sleep 5
xterm -e "rosrun pick_objects pick_objects_node"
