#include "ros/ros.h"
#include "std_msgs/String.h"
#include <boost/thread.hpp>
#include <sstream>
#include <iostream>

int main(int argc, char **argv)
{
	std::cout << "Welcome to QnxRos`s Virtual World!" << std::endl;
	ros::init(argc, argv, "talker");
	ros::NodeHandle n; 
	// will call function subscribe(topic, queue_size, void(*fp), TransportHints()) which is define in node_handle.h
	// and the function will call subscribe(ops) in node_handle.cpp
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(0.5);
	int count = 0;

	while (ros::ok())
    {
        std_msgs::String msg;
        std::stringstream ss;
        ss <<  count;
        msg.data = ss.str();
        ROS_INFO("talker says: %s", msg.data.c_str());

        chatter_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
        ++count;
	}


	return 0;
}
