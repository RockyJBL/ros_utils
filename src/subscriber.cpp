#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/ActuatorControl.h>
#include <mavros_msgs/OverrideRCIn.h>
#include "ros_utils/test.h"
#include "ros_utils/lala.h"

#include <iostream>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

ros_utils::test test_ref;
bool bool_flag = false;

void test_ref_cb(const ros_utils::test::ConstPtr& msg){
    test_ref = *msg;
    bool_flag = true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "subscriber");
    ros::NodeHandle nh;

    ros::Subscriber test_ref_sub = nh.subscribe<ros_utils::test>("/lala/test_ref",20,test_ref_cb);

    while(ros::ok()){
        ros::spinOnce();
        if(bool_flag) break;
    }

    for (int i = 0; i < 5; ++i){
        std::cout<<"++i"<<std::endl;
        std::cout<<i<<std::endl;
    }

    return 0;
}
