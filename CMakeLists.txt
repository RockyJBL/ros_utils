cmake_minimum_required(VERSION 3.0.2)
project(ros_utils)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslaunch
  geometry_msgs
  mavros_msgs
  message_generation
  tf
)

find_package(Eigen3 REQUIRED)

add_message_files(
  FILES
  test.msg
)

generate_messages(DEPENDENCIES geometry_msgs ros_utils)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES ros_utils
 CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(camera_synchronizer src/camera_synchronizer.cpp)
target_link_libraries(camera_synchronizer
  ${catkin_LIBRARIES}
)

add_executable(rc_override src/rc_override.cpp)
target_link_libraries(rc_override
  ${catkin_LIBRARIES}
)

add_executable(vicon_correction src/vicon_correction.cpp)
target_link_libraries(vicon_correction
  ${catkin_LIBRARIES}
  Eigen3::Eigen
)

add_executable(subscriber src/subscriber.cpp)
target_link_libraries(subscriber
  ${catkin_LIBRARIES}
  Eigen3::Eigen
)

add_executable(publisher src/publisher.cpp)
target_link_libraries(publisher
  ${catkin_LIBRARIES}
  Eigen3::Eigen
)

add_executable(rpy2q src/rpy2q.cpp)
target_link_libraries(rpy2q
  ${catkin_LIBRARIES}
  Eigen3::Eigen
)

add_executable(bag2csv src/bag2csv.cpp)
target_link_libraries(bag2csv
  ${catkin_LIBRARIES}
  Eigen3::Eigen
)