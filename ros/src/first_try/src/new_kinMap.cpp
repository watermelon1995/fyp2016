// #include <mrpt/base.h>
#include <mrpt/maps/COccupancyGridMap2D.h>
// #include <mrpt/utils/CMemoryStream.h>
#include <mrpt/utils/CImage.h>
// #include <mrpt/obs/CObservation2DRangeScan.h>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
// #include "geometry_msgs/Pose2D.h"
#include "new_kinGui.cpp"
#include "Mapping.cpp"
// #include "Robot.cpp"
#include <pthread.h>

// using  namespace mrpt::utils;
// using  namespace mrpt::poses;
// using  namespace mrpt::slam;
// using namespace mrpt::slam;



using namespace mrpt::maps;
using namespace mrpt::utils;
using namespace std;
using namespace ros;

// std::vector<float> *sensor_frame = NULL;
std::vector<float> best_particles_x;
std::vector<float> best_particles_y;
kinObserver k_observer;
Mapping *my_mapping;
CImagePtr glob_img;
Position *glob_pose;
kinGui *hi;
mrpt::opengl::CSetOfObjectsPtr  gl_gridmap_3d;
int counter = 0;







void laser_callback(const sensor_msgs::LaserScan::ConstPtr& scan_in){

  if(counter==0){
    my_mapping->setting_params(
      scan_in->angle_min,
      scan_in->angle_max,
      scan_in->angle_increment,
      scan_in->range_min,
      scan_in->range_max);
  }
  end_time = mrpt::system::now();
  time_diff = mrpt::system::timeDifference(begin_time, end_time);
  cout<<"Calculated : "<<time_diff <<endl;
  float offset = 4.0f;
  if(front==0){
    for(int i = 0;i<glob_particle.size();i++){
      glob_particle[i].update_particle(-0.33*time_diff*offset);
    }
  }else if (front==1){
    for(int i = 0;i<glob_particle.size();i++){
      glob_particle[i].update_particle(0.33*time_diff*offset);
    }
  }
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

  // cout<<"Greatest score: "<<max_score<<", i : "<<max_p<<endl;
  // glob_particle[max_p].print();
  best_particles_x.push_back(glob_particle[max_p].get_pose()->x);
  best_particles_x.push_back(glob_particle[max_p].get_pose()->y);
  my_mapping->update_map_xv11(scan_in->ranges, glob_particle[max_p].get_pose());

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
  //   cout<<"After Resampling"<<endl;
  //   for(int i = 0;i<glob_particle.size();i++){
  //       glob_particle[i].print();
  //   }
  //

  counter++;
  if(counter%10==0){
    // if(!gl_gridmap_3d){
    //   gl_gridmap_3d = CSetOfObjects::Create();
    // }
    // // gl_gridmap_3d->clear();
    // my_mapping->m_map->getAs3DObject(gl_gridmap_3d);
    // hi->update_gui(gl_gridmap_3d);

    my_mapping->m_map->getAsImage(*glob_img, false, true, false);
    // glob_img->triangle(glob_particle[max_p].get_pose()->x+312, glob_particle[max_p].get_pose()->y+297, 5,mrpt::utils::TColor::red, true, 3);
    hi->update_gui_2d(glob_img);

  }

}

void *start_gui(void *ptr){
  cout<<"fuck"<<endl;
  hi = new kinGui();
  hi->init(&k_observer);
  cout<<"fuck"<<endl;
}

void *start_robot_controll(void *ptr){

}


int main(int argc, char ** argv)
{

    glob_pose = new Position(0.0, 0.0, 0.0);
    my_mapping =  new Mapping(15.5, 14.92);
    k_observer.observeBegin(*(my_mapping->m_map));
    glob_img = mrpt::utils::CImage::Create();

    for(int i = 0;i < 10 ; i++){
      Particle *p = new Particle(0.0, 0.0, 0.0 , 0.1);
      glob_particle.push_back(*p);
    }

    hi = new kinGui();
    hi->init(&k_observer);

    // pthread_t gui_thread;
    // int ret;
    // ret = pthread_create(&gui_thread, NULL, &start_gui, NULL);
    // if(ret!=0){
    //   cout<<"DIU gui"<<endl;
    // }


    ros::init(argc, argv, "new_kinMap");


    ros::NodeHandle n;

    ros::Subscriber laser_sub = n.subscribe("/scan", 1000, laser_callback);

    ros::spin();

    // pthread_join(gui_thread, NULL);
    // cout<<"Exit...."<<endl;
    // exit(1);
    return 0;
}
