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
    ros::init(argc, argv, "rpy2q");
    ros::NodeHandle nh;
    ros::Rate loop_rate(20);
    # define M_PI		3.14159265358979323846	/* pi */

    double phi,theta,psi;

    phi = 0.0;
    theta = 0.0;
    psi = M_PI/4;

    geometry_msgs::Quaternion quaternion = tf::createQuaternionMsgFromRollPitchYaw(phi,theta,psi);

    std::cout<<quaternion.w<<std::endl;
    std::cout<<quaternion.x<<std::endl;
    std::cout<<quaternion.y<<std::endl;
    std::cout<<quaternion.z<<std::endl;

    tf::Quaternion tf_quaternion;
    tf::quaternionMsgToTF(quaternion,tf_quaternion);
    tf::Matrix3x3(tf_quaternion).getRPY(phi, theta, psi);

    return 0;
}
