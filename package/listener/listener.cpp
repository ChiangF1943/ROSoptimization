#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>

void ChatterCallback1(const std_msgs::String::ConstPtr& msg)
{
    std::cout << "CB1, listener heard: " << msg->data.c_str() << std::endl;
}

void ChatterCallback2(const std_msgs::String::ConstPtr& msg)
{
    std::cout << "CB2, listener heard: " << msg->data.c_str() << std::endl;
}

void ChatterCallback3(const std_msgs::String::ConstPtr& msg)
{
    std::cout << "CB3, listener heard: " << msg->data.c_str() << std::endl;
}

int main(int argc, char **argv)
{
    std::cout << "This is a listener!" << std::endl;
    ros::init(argc, argv, "listener");
    // create roscpp interfaces for publishers, subscribers, service clients, etc
	ros::NodeHandle n; 
	// will call function subscribe(topic, queue_size, void(*fp), TransportHints()) which is define in node_handle.h
	// and the function will call subscribe(ops) in node_handle.cpp
    ros::Subscriber chatter_pub1 = n.subscribe("chatter", 1000, ChatterCallback1);
    ros::Subscriber chatter_pub2 = n.subscribe("chatter2", 1000, ChatterCallback2);
    ros::Subscriber chatter_pub3 = n.subscribe("chatter3", 1000, ChatterCallback3);

    ros::spin();
    /* 在spin()之后进行函数回调，具体过程是：
    * 1. 进入ros::spin()函数，新建一个SingleThreadedSpinner类对象s，执行类中的函数SingleThreadedSpinner::spin(CallbackQueue* queue = 0);
    * 2. queue为默认赋值参数0，所以被赋值getGlobalCallbackQueue()，即queue = g_global_queue，是一个CallbackQueue类的共享指针；
    * 3. 只要ros::ok()为真，就一直循环调用queue->callAvailable(timeout)，所以实际进行函数回调是在callAvailable中，位于callback_queue.cpp
    * 4. 每次使用callOneCB()调用一个回调函数执行，其中回调callback为 cb = *tls->cb_it.callback，执行为result = cb->call()语句，即应该调用CallbackInterface::call()方法；
    * 5. 但CallbackInterface::call()为虚函数，实际上cb为CallbackQueue类对象，实际调用的是SubscriptionQueue::call(),位于subscription_queue.cpp；//这里调用SubscriptionQueue类方法的原理还没搞懂
    * 6. 在call()里，执行"	Event event(params.event, create_);	callback_(ParameterAdapter<P>::getParameter(event));"两句代码，完成。
    * 回调函数队列被运行
    * */
	return 0;
}
