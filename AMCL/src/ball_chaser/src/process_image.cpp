#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <cmath>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    
    if (!client.call(srv))
        ROS_ERROR("Failed to call service");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    double part_of_image = round((img.step)/3);
    double row_length = 0;
    bool found= false;
    int compteur = 1;

    
    for (int i=0; i<img.height*img.step;i++) {
	if (img.data[i] == white_pixel) {

		if (i<(row_length+part_of_image)) {
		  drive_robot(0.2,0.2); //turn left
		  ROS_INFO("Left");
		  found = true;
		  break;
		} 

		else if ((row_length+part_of_image)<i && i<(row_length+2*part_of_image)) {
		  drive_robot(0.2,0.0); //straight
		  ROS_INFO("middle");
		  found = true;
		  break;
		} 

		else {
		  drive_robot(0.2,-0.2); //turn right
		  ROS_INFO("right");
		  found = true;
		  break;
		}	
	} 
	
	if (i>(img.step*compteur)) {
	   row_length = row_length + img.step; //to update our limits
           compteur++;	
	}
    }

   if (found==false){ // no white ball founded
	   drive_robot(0.0, 0.0); //Stop robot
	   ROS_INFO_STREAM("Robot stop"); 
	}

}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
