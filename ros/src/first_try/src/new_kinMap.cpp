// #include <mrpt/base.h>
// // #include <mrpt/core.h>
// #include "ros/ros.h"
// #include "sensor_msgs/Range.h"
// #include "tf/transform_listener.h"

// using  namespace mrpt::utils;
// using  namespace mrpt::poses;
// using  namespace mrpt::slam;
// using  namespace std;
// using namespace ros;
// using namespace tf;

// TransformListener *trans;
// int debug = 0;


// void update_map(float range, float x, float y, float yaw){
//     CObservationRange sonar = new 

// }

// void sonar1_callback(const sensor_msgs::Range::ConstPtr& msg){
//     cout << msg->range <<endl;
//     tf::StampedTransform t;
//     try{
//         trans->lookupTransform("/map", "/robot0_sonar_1", ros::Time(0), t);
//     }catch(tf::TransformException &ex){
//         cout<<"error: "<< &ex <<endl;
//     }
//     // cout<<"X :" <<t.getOrigin().x()<<endl;
//     // cout<<"Y :" <<t.getOrigin().y()<<endl;
//     double yaw, pitch, roll;
//     t.getBasis().getRPY(roll, pitch, yaw);
//     // cout<<"Angle: "<<yaw<<endl;

//     if(debug>10){
//         update_map(msg->range, t.getOrigin().x(), t.getOrigin().y(), yaw);
//     }
//     debug++;
// }

int main(int argc, char ** argv)
{
    // COccupancyGridMap2D occ_map;

    // ros::init(argc, argv, "new_kinMap");


    // ros::NodeHandle n;

    // TransformListener listener(ros::Duration(10));
    // trans = &listener;

    // // ros::Subscriber sub = n.subscribe("/robot0/laser_0", 1000, callback);
    // // Subscriber sub_sonar_0 = n.subscribe("/robot0/sonar_0", 1000, sonar0_callback);
    // Subscriber sub_sonar_1 = n.subscribe("/robot0/sonar_1", 1000, sonar1_callback);

    // ros::spin();

    return 0;
}