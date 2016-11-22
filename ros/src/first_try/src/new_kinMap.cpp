// #include <mrpt/base.h>
#include <pthread.h>

// pthread_mutex_t mutex;

#include <mrpt/maps/COccupancyGridMap2D.h>
// #include <mrpt/utils/CMemoryStream.h>
#include <mrpt/utils/CImage.h>
// #include <mrpt/obs/CObservation2DRangeScan.h>
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/UInt8.h"
#include "geometry_msgs/PoseStamped.h"
#include "tf/transform_listener.h"

// #include "geometry_msgs/Pose2D.h"
ros::Publisher *glob_publish;


#include "new_kinGui.cpp"
#include "Mapping.cpp"
// #include "Robot.cpp"
#include <iostream>
#include <fstream>

#define number_of_particles 10

// using  namespace mrpt::utils;
// using  namespace mrpt::poses;
// using  namespace mrpt::slam;
// using namespace mrpt::slam;



using namespace mrpt::maps;
using namespace mrpt::utils;
using namespace std;
using namespace ros;
using namespace tf;

// std::vector<float> *sensor_frame = NULL;
std::vector<float> best_particles_x;
std::vector<float> best_particles_y;
std::vector<float> best_particles_r;
// std::vector<float> time_count;
kinObserver k_observer;
Mapping *my_mapping;
TransformListener *glob_trans;
// Mapping *my_mapping_2;
CImagePtr glob_img;
// CImagePtr glob_img_obs;


Position *glob_pose;
kinGui *hi;
mrpt::opengl::CSetOfObjectsPtr  gl_gridmap_3d;

ofstream *debug_file;

int counter = 0;

float glob_random_float(float min, float max){
    // this  function assumes max > min, you may want
    // more robust error checking for a non-debug build
    assert(max > min);
    float random = ((float) rand()) / (float) RAND_MAX;

    // generate (in your case) a float between 0 and (4.5-.78)
    // then add .78, giving you a float between .78 and 4.5
    float range = max - min;
    return (random*range) + min;
}

float glob_correct_random(float max){
  float random = ((float) rand()) /(float) RAND_MAX;
  return random*max;
}


void pose_callback(const geometry_msgs::PoseStamped::ConstPtr& pose_msg){
  tf::StampedTransform t;
  try{
    glob_trans->lookupTransform("/map", "/scanmatcher_frame", ros::Time(0), t);
  }catch(tf::TransformException &ex){
      cout<<"error: "<< &ex <<endl;
  }
  double yaw, pitch, roll;
  t.getBasis().getRPY(roll, pitch, yaw);
  //  t.getOrigin().x(), t.getOrigin().y(), yaw)
  glob_pose->x =  t.getOrigin().x();
  glob_pose->y =  t.getOrigin().y();
  glob_pose->r = yaw;
  glob_pose->print();
  cout<<"frame_angle: "<<yaw<<" D: "<<yaw*180/(M_PI)<<endl;
  if(debug_file->is_open()){
    *(debug_file)<< "X: "<<glob_pose->x ;
    *(debug_file)<< " ,Y: "<<glob_pose->y ;
    *(debug_file)<< " ,R: "<<glob_pose->r<<"\n" ;
  }
  for(int i = 0;i<glob_particle.size();i++){
    glob_particle[i].update_pose(glob_pose->x, glob_pose->y, glob_pose->r);
  }
}


void compass_callback(const std_msgs::Float32::ConstPtr& compass_msg){
  // glob_r->set_yaw(compass_msg->data);
  // float reflected_angle = atan(-sin(compass_msg->data)/-cos(compass_msg->data));
  // cout<<"reflected_angle: "<<reflected_angle<<" D: "<<reflected_angle*180/(M_PI)<<endl;
  cout<<"original_angle: "<<compass_msg->data<<" D: "<<compass_msg->data*180/(M_PI)<<endl;
  if(abs(glob_goal->x-glob_pose->x)>0.1 || abs(glob_goal->y-glob_pose->y)>0.1 ){
    float angle_diff = atan((glob_goal->y - glob_pose->y)/(glob_goal->x - glob_pose->x));
    if(angle_diff>=glob_pose->r){
      glob_r->ros_send_movement(86, 170);
    }else{
      glob_r->ros_send_movement(43, 212);
    }
  }
  // glob_pose->r = compass_msg->data;
  // best_particles_r.push_back(compass_msg->data);
  // // time_count.push_back((float)counter/0.1);
  // for(int i = 0;i<glob_particle.size();i++){
  //   glob_particle[i].update_particle_yaw(compass_msg->data);
  // }
}

void laser_callback(const sensor_msgs::LaserScan::ConstPtr& scan_in){

  if(counter==0){
    my_mapping->setting_params(
      scan_in->angle_min,
      scan_in->angle_max,
      scan_in->angle_increment,
      scan_in->range_min,
      scan_in->range_max);
      if(glob_pose->r!=0.1){
        my_mapping->update_map_xv11(scan_in->ranges, glob_pose);
        counter++;
      }
  }else{
    if(front!=-1){
      end_time = mrpt::system::now();
      time_diff = mrpt::system::timeDifference(begin_time, end_time);
    }
    cout<<"Calculated : "<<time_diff <<endl;
    float offset = 1.0f;
    // if(front==0){
    //   for(int i = 0;i<glob_particle.size();i++){
    //     glob_particle[i].update_particle((-0.109)*time_diff);
    //   }
    //   // glob_pose->y += 0.20*time_diff;
    // }else if (front==1){
    //   for(int i = 0;i<glob_particle.size();i++){
    //     glob_particle[i].update_particle(0.02*time_diff);
    //   }
    //   // glob_pose->y += -0.20*time_diff;
    // }
    begin_time = end_time;
    // for (int i = 0;i<glob_particle.size();i++){
    //   glob_particle[i].update_particle(0.0);
    // }
    int max_score = 0;
    int score = 0;
    int max_p = 0;
    for (int i = 0;i<glob_particle.size();i++){
      score = my_mapping->compute_scan_matching(scan_in->ranges, &glob_particle[i]);
      if(score>=max_score){
        max_score = score;
        max_p = i;
      }
    }

    // my_mapping_2->m_map->clear();

    cout<<"Greatest score: "<<max_score<<", i : "<<max_p<<endl;
    // glob_particle[max_p].print();
    // best_particles_x.push_back(((glob_particle[max_p].get_pose()->x)/0.05)+200);
    // best_particles_y.push_back(-((glob_particle[max_p].get_pose()->y)/0.05)+200);
    float best_x = glob_particle[max_p].get_pose()->x;
    float best_y = glob_particle[max_p].get_pose()->y;
    float best_r = glob_particle[max_p].get_pose()->r;

    // hi->update_plot_vector(best_particles_x, best_particles_y);
    hi->update_plot_vector(best_particles_r, best_particles_r);
    // my_mapping->update_map_xv11(scan_in->ranges, glob_particle[max_p].get_pose());
    my_mapping->update_map_xv11(scan_in->ranges, glob_pose);
    // my_mapping_2->insertObservation()
    // my_mapping_2->update_map_xv11(scan_in->ranges, glob_particle[max_p].get_pose());



    float max_weight = glob_particle[max_p].get_weight();

    std::vector<Particle> new_particles;
    float beta = 0.0;
    int index = 0;
    for(int i = 0;i<number_of_particles;i++){
      beta = beta + glob_correct_random(max_weight);
      while (glob_particle[index].get_weight()<beta) {
        beta = beta - glob_particle[index].get_weight();
        index++;
        index = index % number_of_particles;
      }
      new_particles.push_back(glob_particle[index]);
    }
    glob_particle = new_particles;

    float total_weight = 0.0;
    for (int i = 0;i<glob_particle.size();i++){
      total_weight += glob_particle[i].get_weight();
    }
    //Normalized Weight
    for (int i = 0;i<glob_particle.size();i++){
      float new_weight = glob_particle[i].get_weight()/total_weight;
      glob_particle[i].set_weight(new_weight);
      // cout<<"Weight: "<<new_weight<<", i: "<<i<<endl;
    }
    //
    // cout<<"Before Resampling"<<endl;
    // for(int i = 0;i<glob_particle.size();i++){
    //     glob_particle[i].print();
    // }
    //
    //   //Resampling Weight
    //   std::vector<Particle> new_particles;
    //   for(int i=0;i<glob_particle.size();i++){
    //     int choice = rand()*total_weight;
    //     int index = -1;
    //     do {
    //       index++;
    //       choice -= glob_particle[index].get_weight();
    //     } while(choice>0);
    //     new_particles.push_back(glob_particle[index]);
    //   }
    //   glob_particle = new_particles;
    //
      // cout<<"After Resampling"<<endl;
      // for(int i = 0;i<glob_particle.size();i++){
      //     glob_particle[i].print();
      // }
    //

    counter++;
    // if(counter%10==0){
      // if(!gl_gridmap_3d){
      //   gl_gridmap_3d = CSetOfObjects::Create();
      // }
      // // gl_gridmap_3d->clear();
      // my_mapping->m_map->getAs3DObject(gl_gridmap_3d);
      // hi->update_gui(gl_gridmap_3d);

      my_mapping->m_map->getAsImage(*glob_img, false, true, false);
      glob_img->triangle(((glob_pose->x)/0.02)+500, -((glob_pose->y)/0.02)+500,5,mrpt::utils::TColor::green, true, 2);
      glob_img->triangle(((glob_goal->x)/0.02)+500, -((glob_goal->y)/0.02)+500,5,mrpt::utils::TColor::blue, true, 2);
      hi->update_gui_2d(glob_img, best_particles_x, best_particles_y);

      // getchar();
      // my_mapping_2->m_map->getAsImage(*glob_img_obs, false, true, false);

      // hi->show_observation(glob_img_obs);

    // }DA
    if(abs(glob_goal->x-glob_pose->x)>0.1 || abs(glob_goal->y-glob_pose->y)>0.1 ){
      glob_r->ros_send_movement(86,213);
      // float angle_diff = atan((glob_goal->y - glob_pose->y)/(glob_goal->x - glob_pose->x));
      // if(angle_diff>=glob_pose->r){
      //   glob_r->ros_send_movement(86, 170);
      // }else{
      //   glob_r->ros_send_movement(43, 212);
      // }
    }else{
      glob_r->ros_send_movement(0,0);
    }



  }

}

void *start_gui(void *ptr){
  cout<<"fuck"<<endl;
  hi = new kinGui();
  hi->init(&k_observer);
  cout<<"fuck"<<endl;
}

// void *start_robot_controll(void *ptr){
//   while(true){
//     pthread_mutex_lock(&mutex);
//     if(glob_r->hihi->available()){
//       cout<<(char)glob_r->hihi->read();
//     }
//
//     pthread_mutex_unlock(&mutex);
//
//   }
// }



int main(int argc, char ** argv)
{

    glob_pose = new Position(0.0, 0.0, 0.0);
    my_mapping =  new Mapping(10.0, 10.0);
    // my_mapping_2 = new Mapping(10.0, 10.0);
    // k_observer.observeBegin(*(my_mapping_2->m_map));
    k_observer.observeBegin(*(my_mapping->m_map));
    glob_img = mrpt::utils::CImage::Create();
    // glob_img_obs = mrpt::utils::CImage::Create();

    for(int i = 0;i < number_of_particles ; i++){
      Particle *p = new Particle(glob_random_float(-0.5, 0.5), glob_random_float(-0.5, 0.5), 0.0 , 0.1);
      glob_particle.push_back(*p);
    }

    hi = new kinGui();
    hi->init(&k_observer);

    glob_r = new Robot(40.0, 40.0);

    debug_file = new ofstream("/home/kin/Desktop/correct.txt");

    // glob_r->listen_to_driver();
    // glob_r->go_straight();
    // cout<<"GOGOGO"<<endl;
    // pthread_mutex_init(&mutex, NULL);
    //
    //
    // pthread_t control_thread;
    // int ret;
    // ret = pthread_create(&control_thread, NULL, &start_robot_controll, NULL);


    // pthread_t gui_thread;
    // int ret;
    // ret = pthread_create(&gui_thread, NULL, &start_gui, NULL);
    // if(ret!=0){
    //   cout<<"DIU gui"<<endl;
    // }


    ros::init(argc, argv, "new_kinMap");

    TransformListener listener(ros::Duration(10));
    glob_trans = &listener;

    ros::NodeHandle n;
    ros::Publisher robot_control = n.advertise<std_msgs::UInt8>("/robot_command", 1000);
    glob_publish = &robot_control;
    glob_r->ros_send_movement(0,0);
    ros::Subscriber pose_sub = n.subscribe("/slam_out_pose", 1000, pose_callback);
    ros::Subscriber laser_sub = n.subscribe("/scan", 1000, laser_callback);
    ros::Subscriber compass_sub = n.subscribe("/robot_compass", 1000, compass_callback);

    ros::spin();

    debug_file->close();
    // glob_r->listen_to_driver();

    // pthread_join(gui_thread, NULL);
    // cout<<"Exit...."<<endl;
    // exit(1);
    return 0;
}
