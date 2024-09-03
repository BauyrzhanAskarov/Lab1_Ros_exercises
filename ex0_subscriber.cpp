
#include "ros/ros.h"
#include "std_msgs/Int32.h"


void numberCallback(const std_msgs::Int32::ConstPtr& msg) {
    ROS_INFO("Received: %d", msg->data);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "ros_topic_subscriber");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("Bauyrzhan", 10, numberCallback);
    ros::spin(); 

    return 0;
}
