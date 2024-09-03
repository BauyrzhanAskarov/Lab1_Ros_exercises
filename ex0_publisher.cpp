#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <vector>
#include <string>
#include <cctype>

std::vector<int> extractDigits(const std::string& str) {
    std::vector<int> result;
    for (const auto& ch : str) {
        if (std::isdigit(ch)) {
            result.push_back(ch - '0');
        }
    }
    return result;
}

void publishDigits(const std::vector<int>& digits, ros::Publisher& publisher, ros::Rate& rate, const std::string& rate_label) {
    for (const auto& digit : digits) {
        std_msgs::Int32 message;
        message.data = digit;

        ROS_INFO("Publishing at %s: %d", rate_label.c_str(), message.data);
        publisher.publish(message);

        ros::spinOnce();
        rate.sleep();
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "ros_topic_publisher_alternative");
    ros::NodeHandle node_handle;
    ros::Publisher publisher = node_handle.advertise<std_msgs::Int32>("Bauyrzhan", 10);

    std::string nu_id = "201940321";
    std::vector<int> nu_id_digits = extractDigits(nu_id);

    ros::Rate rate_slow(1);  // 1 Hz
    ros::Rate rate_fast(50);  // 50 Hz

    while (ros::ok()) {
        // Publish digits at 1 Hz
        publishDigits(nu_id_digits, publisher, rate_slow, "1Hz");

        // Publish digits at 50 Hz
        publishDigits(nu_id_digits, publisher, rate_fast, "50Hz");
    }

    return 0;
}

