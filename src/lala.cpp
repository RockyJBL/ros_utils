#include <ros/ros.h>
#include <tf/tf.h>
#include <Eigen/Dense>
#include <geometry_msgs/PoseStamped.h>

Eigen::Vector3d point1(0,1,1);
Eigen::Vector3d point2(0,0,0);
Eigen::Vector3d distance;

int main(int argc, char **argv){
    ros::init(argc, argv, "vicon_correction");

    distance = point1-point2;
    std::cout<<distance.norm()<<std::endl;

}
