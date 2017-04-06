#include <vector>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Vector3.h"

using namespace std;



int prepare_message(int v1, int v2, geometry_msgs::Twist* data){

  //After Calculation , assign value for the message body
  data->linear.x = 0.5;
  data->linear.y = 0.0;
  data->linear.z = 0.0;

  data->angular.x = 0.0;
  data->angular.y = 0.0;
  data->angular.z = 0.0;

  return 0;
}

void dynamic_window_algorithm (
  geometry_msgs::Pose *robotPose,
  geometry_msgs::Pose2D *robotGoal,
  float robotWidth){

  std::vector<geometry_msgs::Vector3> allowable_v;
  std::vector<geometry_msgs::Vector3> allowable_w;

}


int main(int argc, char **argv){
  ros::init(argc, argv, "robot_movement_controller");
  ros::NodeHandle n;
  ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while(ros::ok())
  {
    geometry_msgs::Twist data;
    prepare_message(0.5, 0.5, &data);
    movement_pub.publish(data);
    cout<<"Message sent"<<endl;
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
