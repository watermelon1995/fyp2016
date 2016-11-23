#include <ros.h>
#include <std_msgs/Float32.h>


ros::NodeHandle arduino_node;
float distance = 0.0;
ros::Publisher lidar("range_data", &distance);

void setup() {
  arduino_node.initNode();
  arduino_node.advertise(lidar);
}

void readCM(){
  
}

void loop() {
  

}
