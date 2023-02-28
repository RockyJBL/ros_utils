#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/ActuatorControl.h>
#include <mavros_msgs/OverrideRCIn.h>

#include <iostream>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

Eigen::Quaterniond local_quatern;
Eigen::Vector3d eigen_euler;
Eigen::Vector3d barbara_euler;

tf::Quaternion tf_q;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rc_override");
    ros::NodeHandle nh;
    ros::Rate loop_rate(20);

    ros::Publisher actuator_pub, override_pub;
    mavros_msgs::ActuatorControl actuator_control;
    mavros_msgs::OverrideRCIn override_rc_in;

    // ROS Publisher
    // actuator_pub = nh.advertise<mavros_msgs::ActuatorControl>("/mavros/actuator_control",20);
    override_pub = nh.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override",20);

    // override_rc_in.channels[1] = 0;
    // override_rc_in.channels[2] = 0;
    override_rc_in.channels[3] = 1875;
    override_rc_in.channels[4] = 1576;
    override_rc_in.channels[5] = 1577;
    // override_rc_in.channels[6] = 0;
    // override_rc_in.channels[7] = 0;
    // override_rc_in.channels[8] = 0;
    // override_rc_in.channels[9] = 0;
    // override_rc_in.channels[10] = 0;
    // override_rc_in.channels[11] = 0;
    // override_rc_in.channels[12] = 0;
    // override_rc_in.channels[13] = 0;
    // override_rc_in.channels[14] = 0;

    

    // actuator_control.group_mix = 0;
    // actuator_control.controls[0] = 1;
    // actuator_control.controls[1] = 1;
    // actuator_control.controls[2] = 1;
    // actuator_control.controls[3] = 1;
    // actuator_control.controls[4] = 1;
    // actuator_control.controls[5] = 1;
    // actuator_control.controls[6] = 1;
    // actuator_control.controls[7] = 1;

    while(ros::ok()){
        // actuator_pub.publish(actuator_control);
        override_pub.publish(override_rc_in);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
