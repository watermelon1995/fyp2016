#include "ros/ros.h"
// #include "sensor_msgs/LaserScan.h"
#include <tf/transform_broadcaster.h>
#include <boost/thread/mutex.hpp>
#include <math.h>
// Include the library for creating obstacle
#include "interactive_markers/interactive_marker_server.h"

#include <boost/lexical_cast.hpp>



// int create_moving_square(double w1, double w2){
//
// }
//
// unsigned int num_readings = 360;
// double laser_frequency = 10;
// double ranges[num_readings];
// float minAngle = 0.0f;
// float maxAngle = 6.28318548203f;
// float minRange = 0.05999998658f;
// float maxRange = 5.0f;
//
//
// void real_laser_callback(const sensor_msgs::LaserScan& real_scan){
//   sensor_msgs::LaserScan scan_out;
//   float angle;
//   int distance;
//   int xMap, yMap;
//   int divisions = num_readings -1;
//
//   scan_out.angle_min = minAngle;
//   scan_out.angle_max = maxAngle;
//   scan_out.range_max = maxRange;
//   scan_out.range_min = minRange;
//   scan_out.angle_increment =
//     ( maxAngle - minAngle ) / divisions;
//
//
// }
static float RandomNumber(float Min, float Max)
{
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

static const float UPDATE_RATE = 1.0/10.0;

class MovingBox {
  struct BoxProperties
  {
    float inital_angle;
    float inital_speed;
    float last_x;
    float last_y;
    std::string frame_id;
    std::string name;
  };
  private:
    interactive_markers::InteractiveMarkerServer _server;
    std::vector<BoxProperties> box_props;
    int counter;
    ros::Timer loop_timer;
  public:
    MovingBox(ros::NodeHandle& nh,  float theta, float speed, int numbers):
    _server("Server_Moving_Box")
    {
      box_props.resize(numbers);
      for (int i = 0; i < numbers ; i++)
      {
        box_props[i].inital_angle = RandomNumber(0.0, 2*3.14);
        box_props[i].inital_speed = speed;
        // box_props[i].last_x = 0.0;
        // box_props[i].last_y = 0.0;
        box_props[i].last_x = RandomNumber(1.0, 7.75-1);
        box_props[i].last_y = RandomNumber(1.0, 7.46-2);
        std::string frame_prefix = "box_";
        frame_prefix += boost::lexical_cast<std::string>(i);
        std::string name_prefix = "HIHI_";
        name_prefix += boost::lexical_cast<std::string>(i);
        box_props[i].frame_id = frame_prefix;
        box_props[i].name = name_prefix;
        createBox(frame_prefix, name_prefix);
      }
      // createBox("base_link", "HIHI");
      loop_timer = nh.createTimer(ros::Duration(UPDATE_RATE), boost::bind(&MovingBox::updateBoxPoseCallback, this));
    }
    void createBox(std::string& frame_id, std::string& name){
      visualization_msgs::InteractiveMarker int_box;
      int_box.header.frame_id = frame_id;
      visualization_msgs::InteractiveMarkerControl box_control;
      box_control.always_visible = true;

      int_box.name = name;

      box_control.interaction_mode = visualization_msgs::InteractiveMarkerControl::NONE;
      box_control.orientation.w = 1;
      box_control.orientation.y = 1;

      visualization_msgs::Marker box;
      box.type = visualization_msgs::Marker::CUBE;
      box.scale.x = 0.3;
      box.scale.y = 0.3;
      box.scale.z = 0.3;

      box.color.r = 0.5;
      box.color.g = 0.5;
      box.color.b = 0.5;
      box.color.a = 1.0;

      box_control.markers.push_back(box);
      int_box.controls.push_back(box_control);
      _server.insert(int_box);
    }

    void resetPose(int id){
      if(id>=0 && id<box_props.size()){
        box_props[id].last_x = RandomNumber(1.0, 7.75-1);
        box_props[id].last_y = RandomNumber(1.0, 7.46-2);
        // box_props[id].inital_angle = 2*3.14 - box_props[id].inital_angle;
      }
    }

    void updateBoxPoseCallback(){

      geometry_msgs::Pose pose;
      for (int i = 0;i<box_props.size(); i++){
        if ( counter% 100 == 0 ){
          box_props[i].inital_angle = RandomNumber(0.0, 2*3.14);
          ROS_INFO("%d Changing direction: %f",i,box_props[i].inital_angle);
        }
        pose.position.x = box_props[i].last_x + box_props[i].inital_speed*cos(box_props[i].inital_angle);
        pose.position.y = box_props[i].last_y + box_props[i].inital_speed*sin(box_props[i].inital_angle);
        std::string frame_prefix = "box_";
        frame_prefix += boost::lexical_cast<std::string>(i);
        std::string name_prefix = "HIHI_";
        name_prefix += boost::lexical_cast<std::string>(i);
        _server.setPose(name_prefix , pose);
        box_props[i].last_x = pose.position.x;
        box_props[i].last_y = pose.position.y;
        if(box_props[i].last_x > 7.75 || box_props[i].last_x < 0.0 || box_props[i].last_y > 7.46 || box_props[i].last_y < 0.0){
          resetPose(i);
        }
        updateTransformCallback(box_props[i].last_x, box_props[i].last_y, frame_prefix);
        _server.applyChanges();
      }
      ++counter;
    }

    void updateTransformCallback(float x, float y, std::string frame_id){
      static tf::TransformBroadcaster br;
      tf::Transform transform;
      transform.setOrigin( tf::Vector3(x, y, 0.0) );
      tf::Quaternion q;
      q.setRPY(0, 0, 0);
      transform.setRotation(q);
      br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", frame_id));
    }

};

class Map_Moving {};

int main(int argc, char** argv){
  ros::init(argc, argv, "fake_laser_scan");
  ros::NodeHandle nh;

  // interactive_markers::InteractiveMarkerServer server("dynamic_box");
  MovingBox m_box(nh, M_PI/4, 0.03, 1);
  ros::spin();
  // ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("fake_scan", 50);

  // ros::Subscriber real_sub = n.subscribe("/robot0/laser_0", 1000, )

  // ros::spin();
  ROS_INFO("Exiting..");

  return 0;
}
