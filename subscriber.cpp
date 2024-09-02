#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include "turtlesim/TeleportAbsolute.h"
#include "turtlesim/Kill.h"

//ros::Publisher pub;
ros::Publisher velocity_pub;

//void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
//{
	//ROS_INFO("Turtle subscriber@[%f, %f, %f]",
	//msg->x, msg->y, msg->theta);
	//geometry_msgs::Twist my_vel;
	//my_vel.linear.x = 1.0;
	//my_vel.angular.z = 1.0;
	// pub.publish(my_vel); 
//}

int main(int argc, char **argv)
{
    // Initialize the node, setup the NodeHandle for handling the communication with the ROS system
    ros::init(argc, argv, "turtlebot_subscriber");
    ros::NodeHandle nh;

    // Kill the default turtle
    ros::ServiceClient kill_client = nh.serviceClient<turtlesim::Kill>("/kill");
    turtlesim::Kill kill_srv;
    kill_srv.request.name = "turtle1"; 
    kill_client.call(kill_srv);
    
    // Spawn a new turtle at the center
    ros::ServiceClient spawn_client = nh.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn spawn_srv;
    spawn_srv.request.x = 5.5;
    spawn_srv.request.y = 5.5;
    spawn_srv.request.theta = 0.0;
    spawn_srv.request.name = "turtle_Bauyrzhan";
    spawn_client.call(spawn_srv);

    // Teleport to the first corner
    ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle_Bauyrzhan/teleport_absolute");
    turtlesim::TeleportAbsolute teleport_srv;
    teleport_srv.request.x = 4.5;
    teleport_srv.request.y = 4.5;
    teleport_srv.request.theta = 0.0;
    teleport_client.call(teleport_srv);

    // Initialize publisher for the turtle velocity
    velocity_pub = nh.advertise<geometry_msgs::Twist>("/turtle_Bauyrzhan/cmd_vel", 10);
    geometry_msgs::Twist vel_msg;
    ros::Rate rate(1);

    // Square movement
    for (int i = 0; i < 4; ++i)
    {
    	// Turn 90 degrees
        vel_msg.linear.x = 0.0;
        vel_msg.angular.z = -1.57;  // -90 degrees in radians
        velocity_pub.publish(vel_msg);
        ros::Duration(1.0).sleep(); // Turn for 1 second 
        
        // Move forward
        vel_msg.linear.x = 2.0;
        vel_msg.angular.z = 0.0;
        velocity_pub.publish(vel_msg);
        ros::Duration(2.0).sleep(); // Move for 2 seconds

    }

    // Triangular movement
    for (int i = 0; i < 3; ++i)
    {	
    	
	if (i != 2) {
		// Turn 90 degrees
		vel_msg.linear.x = 0.0;
		vel_msg.angular.z = -1.57;  // -90 degrees in radians
		velocity_pub.publish(vel_msg);
		ros::Duration(1.0).sleep(); // Turn for 1 second
		// Move forward
        	vel_msg.linear.x = 2.0;
        	vel_msg.angular.z = 0.0;
        	velocity_pub.publish(vel_msg);
        	ros::Duration(2.0).sleep(); // Move for 2 seconds
		
	} else {
		vel_msg.linear.x = 0.0;
		vel_msg.angular.z = -1.57/2-1.57;  // -135 degrees in radians
		velocity_pub.publish(vel_msg);
		ros::Duration(1.0).sleep(); // Turn for 1 second
		
		vel_msg.linear.x = 2.0*1.41;
        	vel_msg.angular.z = 0.0;
        	velocity_pub.publish(vel_msg);
        	ros::Duration(2.0).sleep(); // Move for 2 seconds
		
	}
        
    }

    return 0;
}
