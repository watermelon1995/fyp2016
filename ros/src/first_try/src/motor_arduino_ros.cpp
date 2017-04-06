#include "ros/ros.h"
#include <signal.h>
#include "std_msgs/UInt8.h"
#include "SerialPort.cpp"

SerialPort* arduino_ptr = NULL;


void motorCallback(const std_msgs::UInt8::ConstPtr &command){
  arduino_ptr->write(command->data);
}

void shutDownHandler(int sig){
  if (arduino_ptr!=NULL){
    arduino_ptr->close();
    arduino_ptr = NULL;
  }
  ros::shutdown();
}

int main(int argc, char ** argv){
  SerialPort arduino = SerialPort("/dev/ttyUSB1");

  arduino_ptr = &arduino;
  arduino.open(57600);

  ros::init(argc, argv, "arduino_node");
  ros::NodeHandle nh;
  //Overwrite the default ros handler to close the serial port
  signal(SIGINT, shutDownHandler);

  ros::Subscriber motor_sub = nh.subscribe<std_msgs::UInt8>("robot_command", 1000, motorCallback);



  ros::spin();

  return 0;
}
