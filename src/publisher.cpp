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

int main(int argc, char **argv)
{
    ros::init(argc, argv, "publisher");
    ros::NodeHandle nh;
    ros::Rate loop_rate(20);

    ros::Publisher test_ref_pub;
    geometry_msgs::Pose dummy_pose;

    test_ref_pub = nh.advertise<ros_utils::test>("/lala/test_ref",20);

    while(ros::ok()){
        test_ref.header.stamp = ros::Time::now();
        test_ref.is_preview = true;
        test_ref.ref_pose.resize(5);
        test_ref.ref_twist.resize(5);

        test_ref.ref_pose[0].position.x = 1;

        // for(unsigned int i = 0; i <= 9; i++){
        //     dummy_pose.position.x = i+1;
        //     test_ref.ref_pose.push_back(dummy_pose);
        // }

        test_ref_pub.publish(test_ref);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
