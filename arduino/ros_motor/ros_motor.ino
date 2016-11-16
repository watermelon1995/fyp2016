
#include <ros.h>
#include <std_msgs/UInt8.h>
#include <SoftwareSerial.h>

#define d_rx 6
#define d_tx 7

SoftwareSerial driver(d_rx, d_tx);

ros::NodeHandle nh;

void robot_command(const std_msgs::UInt8 &command){
  driver.write((byte)comend->data);
}

ros::Subscriber<std_msgs::UInt8> rob_sub("robot_command", &robot_command);



void setup(){
  driver.begin(9600);
  nh.initNode();
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
}
