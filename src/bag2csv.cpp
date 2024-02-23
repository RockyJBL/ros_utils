#include <ros/ros.h>
#include <tf/tf.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <eigen3/Eigen/Dense>

std::vector<double> row_to_write;
std::vector<std::string> column_headers;
std::string log_path;

void sync_cb(const geometry_msgs::PoseStampedConstPtr& pose_msg,const geometry_msgs::TwistStampedConstPtr& twist_msg,const geometry_msgs::TwistStampedConstPtr& accel_msg, const geometry_msgs::TwistStampedConstPtr& wheel_speed_msg){
    row_to_write.clear();
    // row_to_write.resize(column_headers.size());
    row_to_write.push_back(pose_msg->header.stamp.toSec());
    row_to_write.push_back(pose_msg->pose.position.x);
    row_to_write.push_back(pose_msg->pose.position.y);
    tf::Quaternion tf_quaternion;
    Eigen::Vector3d euler;
    tf::quaternionMsgToTF(pose_msg->pose.orientation,tf_quaternion);
    tf::Matrix3x3(tf_quaternion).getRPY(euler.x(), euler.y(), euler.z());
    row_to_write.push_back(euler.z());
    row_to_write.push_back(twist_msg->twist.linear.x);
    row_to_write.push_back(twist_msg->twist.linear.y);
    row_to_write.push_back(twist_msg->twist.angular.z);
    row_to_write.push_back(accel_msg->twist.linear.x);
    row_to_write.push_back(accel_msg->twist.linear.y);
    row_to_write.push_back(accel_msg->twist.angular.z);
    row_to_write.push_back(wheel_speed_msg->twist.angular.y);

    // Write the data to the CSV file
    std::ofstream out_file;
    out_file.open(log_path,std::ios::app);
    if (out_file.is_open()) {
        for (size_t i = 0; i < row_to_write.size(); ++i){
            out_file << row_to_write[i];
            if (i < row_to_write.size() -1){
                out_file << ",";
            }
        }
        out_file << "\n";
        // Close the file
        out_file.close();
    }
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"bag2csv_node");
    ros::NodeHandle nh;

    message_filters::Subscriber<geometry_msgs::PoseStamped> pose_sub(nh,"/vrpn_client_node/gh034_drift_car/pose",1);
    message_filters::Subscriber<geometry_msgs::TwistStamped> twist_sub(nh,"/vrpn_client_node/gh034_drift_car/twist",1);
    message_filters::Subscriber<geometry_msgs::TwistStamped> accel_sub(nh,"/vrpn_client_node/gh034_drift_car/accel",1);
    message_filters::Subscriber<geometry_msgs::TwistStamped> wheel_speed_sub(nh,"/wheel_speed",1);
    typedef message_filters::sync_policies::ApproximateTime<geometry_msgs::PoseStamped, geometry_msgs::TwistStamped, geometry_msgs::TwistStamped, geometry_msgs::TwistStamped> my_sync_policy;
    message_filters::Synchronizer<my_sync_policy> sync(my_sync_policy(10), pose_sub,twist_sub,accel_sub,wheel_speed_sub);
    sync.registerCallback(boost::bind(&sync_cb,_1,_2,_3,_4));

    column_headers = {"time","x","y","yaw","vx","vy","r","ax","ay","r_dot","wheel_speed"};
    // Get the current time
    std::time_t now = std::time(nullptr);
    std::tm tm = *std::localtime(&now);
    // Format the time as "yyyy-mm-dd-hh-mm"
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y_%m_%d_%H_%M");
    std::string time_stamp = oss.str();

    // Construct the full file path
    log_path = "/root/results/" + time_stamp + ".csv";

    // Open the file for writing
    std::ofstream out_file(log_path);

    // Check if the file was successfully opened
    if (out_file.is_open()) {
        // Write column headers as the first row
        for (size_t i = 0; i < column_headers.size(); ++i) {
            out_file << column_headers[i];
            if (i < column_headers.size() - 1) {
                out_file << ",";
            }
        }
        out_file << "\n";
        // Close the file
        out_file.close();
    } else {
        ROS_ERROR_STREAM("Failed to open the file for writing: " << log_path);
    }

    ros::spin();

    return 0;
}
