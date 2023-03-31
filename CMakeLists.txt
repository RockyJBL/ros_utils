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
  tf
)

find_package(Eigen3 REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES qr_mpc
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
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

add_executable(lala src/lala.cpp)
target_link_libraries(lala
  ${catkin_LIBRARIES}
  Eigen3::Eigen
)