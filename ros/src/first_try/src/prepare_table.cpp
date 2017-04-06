#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "std_msgs/UInt8.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

tf::TransformListener *glob_trans;
ros::Publisher *glob_publish;
sql::PreparedStatement *pstmt;
#define lowerM1 64+40
#define upperM1 lowerM1+5
#define lowerM2 192+40
#define upperM2 lowerM2+5
using namespace std;

// sql::PreparedStatement *pstmt;

int glob_m1 = 0;
int glob_m2 = 0;

double last_x, last_y, last_r;

int running_test = -1;

#include "Robot.cpp"
Robot *glob_r;

void pose_callback(const geometry_msgs::PoseStamped::ConstPtr& pose_msg){
  tf::StampedTransform t;
  geometry_msgs::Twist compute_twist;
  try{
    glob_trans->lookupTransform("/map", "/scanmatcher_frame", ros::Time(0), t);
    glob_trans->lookupTwist("/scanmatcher_frame", "/map", ros::Time(0), ros::Duration(1.0), compute_twist);
    // glob_trans->lookupTwist("/scanmatcher_frame", "/map", "/scanmatcher_frame", tf:Point(0,0,0), "/scanmatcher_frame", ros::Time(0), ros::Duration(1.0), compute_twist);
    double yaw, pitch, roll;
    t.getBasis().getRPY(roll, pitch, yaw);

    if(running_test == 1){
      std::cout<<"Linear ["<<compute_twist.linear.x << ", " <<compute_twist.linear.y << ", " <<compute_twist.linear.z << " ]" <<std::endl;
      std::cout<<"Angular ["<<compute_twist.angular.x << ", " <<compute_twist.angular.y << ", " <<compute_twist.angular.z << " ]" <<std::endl;
      pstmt->setInt(1, glob_m1);
      pstmt->setInt(2, glob_m2);
      pstmt->setDouble(3, compute_twist.linear.x);
      pstmt->setDouble(4, compute_twist.linear.y);
      pstmt->setDouble(5, compute_twist.linear.z);
      pstmt->setDouble(6, compute_twist.angular.x);
      pstmt->setDouble(7, compute_twist.angular.y);
      pstmt->setDouble(8, compute_twist.angular.z);
      pstmt->executeUpdate();
    }
  }catch(tf::TransformException &ex){
      cout<<"error: "<< &ex <<endl;
  }
}

int main(int argc, char** argv){
  ros::init(argc, argv, "prepare_table");
  ros::NodeHandle nh;

  glob_r = new Robot(40.0, 40.0);

  tf::TransformListener listener(ros::Duration(10));
  glob_trans = &listener;

  glob_m1 = 0;
  glob_m2 = 0;
  ros::Publisher robot_control = nh.advertise<std_msgs::UInt8>("/robot_command", 1000);
  glob_publish = &robot_control;
  ros::Subscriber pose_sub = nh.subscribe("/slam_out_pose", 1000, pose_callback);


  try{
    sql::Driver *driver;
    sql::Connection *con;

    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "wutszkin28");
    con->setSchema("robot");

    pstmt = con->prepareStatement("INSERT INTO commands (motor1, motor2, linear_x, linear_y, linear_z, angular_x, angular_y, angular_z) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");

    glob_r->ros_send_movement(0, 0);
    int counter = 0;
    int rangeM1 = lowerM1;
    int rangeM2 = lowerM2;
    ros::Rate loop_rate(10);
    while (ros::ok()) {
      if(counter%40 == 0){
        if(running_test == 1){
          std::cout << "Test Finish" << std::endl;
          glob_r->ros_send_movement(0, 0);
          running_test = -1;
        }else if(running_test == -1){
          std::cout << "Setting Params" << std::endl;
          glob_m1 = rangeM1;
          glob_m2 = rangeM2;
          rangeM1++;
          rangeM2++;
          std::cout << "Test Start" << std::endl;
          std::cout << "Testing ["<<glob_m1 << ", " <<glob_m2 << " ]" << std::endl;
          glob_r->ros_send_movement(glob_m1, glob_m2);
          running_test = 1;
        }
      }

      if(rangeM1 > upperM1 || rangeM2 > upperM2){
        glob_r->ros_send_movement(0, 0);
        ros::shutdown();
      }

      ros::spinOnce();
      loop_rate.sleep();
      ++counter;
    }

    ROS_INFO("Exiting..");
    delete con;
    delete pstmt;

  }catch (sql::SQLException &e) {
    std::cout << "DIU" << std::endl;
  }


  return 0;
}
