#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace ros;

sensor_msgs::LaserScan *ls = NULL;

void callback(const sensor_msgs::LaserScan::ConstPtr& msg){
    //ranges are vector<float>
    vector<float> scan_data;  
    scan_data = msg->ranges; 
    for(int i = 0;i<scan_data.size();i++){
        std::cout << i << ": "; 
        std::cout << scan_data[i]<<std::endl;
    }
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "listener");

    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/robot0/laser_0", 1000, callback);

    ros::spin();

    return 0;
}