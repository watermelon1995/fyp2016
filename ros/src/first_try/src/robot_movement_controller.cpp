#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

int prepare_message(int v1, int v2, geometry_msgs::Twist &data){

  //After Calculation , assign value for the message body
  data->linear->x;
  data->linear->x;
  data->linear->x;

  data->angular->x;
  data->angular->x;
  data->angular->x;

  return 0;
}


int main(int argc, char **argv){
  ros::init(argc, argv, "robot_movement_controller");
  ros::NodeHandle n;
  ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while(ros::ok()){
    geometry_msgs::Twist t;
    t.
    loop_rate.sleep();

  }
  return 0;
}
