// #include <mrpt/base.h>
// #include <boost/thread/locks.hpp>
// #include <boost/thread/shared_mutex.hpp>
//
// typedef boost::shared_mutex Lock;
// typedef boost::unique_lock< Lock > WriteLock;
// typedef boost::shared_lock< Lock > ReadLock;
//
// Lock myLock;


// pthread_mutex_t mutex;
// #include <mrpt_bridge/laser_scan.h>
#include <mrpt/maps/COccupancyGridMap2D.h>
#include <mrpt/obs/CObservation2DRangeScan.h>
// #include <mrpt/slam/CObservation2DRangeScan.h>
#include <mrpt/math/matrix_adaptors.h>
#include <mrpt/maps/CSimplePointsMap.h>
#include <mrpt/slam/CICP.h>
#include <mrpt/poses/CPose2D.h>
#include <mrpt/poses/CPosePDF.h>
#include <mrpt/poses/CPosePDFGaussian.h>
// #include <mrpt/utils/CMemoryStream.h>
#include <mrpt/utils/CImage.h>
// #include <mrpt/obs/CObservation2DRangeScan.h>
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/UInt8.h"
#include "geometry_msgs/PoseStamped.h"
#include "tf/transform_listener.h"
#include "nav_msgs/OccupancyGrid.h"

#include "geometry_msgs/Pose.h"
#include "mrpt_bridge/time.h"
#include "mrpt_bridge/pose.h"

// #include "geometry_msgs/Pose2D.h"
ros::Publisher *glob_publish;
ros::Publisher *glob_map_publish;
#include "Motor.cpp"

Motor *glob_motor;

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
using namespace mrpt::slam;
using namespace mrpt::obs;
using namespace mrpt::math;
using namespace mrpt::poses;
using namespace mrpt::utils;
using namespace std;
using namespace ros;
using namespace tf;

// std::vector<float> *sensor_frame = NULL;
std::vector<float> best_particles_x;
std::vector<float> best_particles_y;
std::vector<float> best_particles_r;
// std::vector<float> time_count;
float last_yaw;
float last_yaw2;
kinObserver k_observer;
Mapping *my_mapping;
TransformListener *glob_trans;
// Mapping *my_mapping_2;
CImagePtr glob_img;
// CImagePtr glob_img_obs;


Position *glob_pose;
kinGui *hi;
mrpt::opengl::CSetOfObjectsPtr  gl_gridmap_3d;

ofstream *estimate_file;
ofstream *debug_file;

int counter = 0;

int  ICP_method = (int) icpClassic;

CObservation2DRangeScan mrpt_last_scan;
mrpt::poses::CPose3D mrpt_ref_pose;
mrpt::poses::CPose3D mrpt_static_pose;




// bool self_map_convert(    const COccupancyGridMap2D &src, nav_msgs::OccupancyGrid &des)
// {
//    //printf("--------mrpt2ros:  %f, %f, %f, %f, r:%f\n",src.getXMin(), src.getXMax(), src.getYMin(), src.getYMax(), src.getResolution());
//    des.info.width = src.getSizeX();
//    des.info.height = src.getSizeY();
//    des.info.resolution = src.getResolution ();
//
//    des.info.origin.position.x = src.getXMin();
//    des.info.origin.position.y = src.getYMin();
//    des.info.origin.position.z = 0;
//
//    des.info.origin.orientation.x = 0;
//    des.info.origin.orientation.y = 0;
//    des.info.origin.orientation.z = 0;
//    des.info.origin.orientation.w = 1;
//
//    des.data.resize ( des.info.width*des.info.height );
//      for ( int h = 0; h < des.info.height; h++ ) {
//                const COccupancyGridMap2D::cellType *pSrc = src.getRow (h);
//       int8_t *pDes = &des.data[h * des.info.width];
//        for ( int w = 0; w < des.info.width; w++ ) {
//            *pDes++ = MapHdl::instance()->cellMrpt2Ros(*pSrc++);
//        }
//    }
//    return true;
// }

bool self_convert(const sensor_msgs::LaserScan &_msg, const mrpt::poses::CPose3D &_pose, CObservation2DRangeScan  &_obj)
{
	mrpt_bridge::convert(_msg.header.stamp, _obj.timestamp);
	_obj.rightToLeft = true;
	_obj.sensorLabel = _msg.header.frame_id;
	_obj.aperture = _msg.angle_max - _msg.angle_min;
	_obj.maxRange = _msg.range_max;
	_obj.sensorPose =  _pose;

	ASSERT_(_msg.ranges.size()>1);

	const size_t N = _msg.ranges.size();
	const double ang_step = _obj.aperture/(N-1);
	const double fov05 = 0.5*_obj.aperture;
	const double inv_ang_step = (N-1)/_obj.aperture;

	_obj.scan.resize(N);
	_obj.validRange.resize(N);
	for(std::size_t i_mrpt = 0; i_mrpt < N; i_mrpt++)
	{

		// ROS indices go from _msg.angle_min to _msg.angle_max, while
		// in MRPT they go from -FOV/2 to +FOV/2.
		int i_ros = inv_ang_step*( -fov05-_msg.angle_min+ang_step*i_mrpt);
		if (i_ros<0) i_ros+=N; else if (i_ros>=(int)N) i_ros-=N;  // wrap around 2PI...

		// set the scan
		const float r = _msg.ranges[i_ros];
		_obj.scan[i_mrpt] = r;

		// set the validity of the scan
		const bool r_valid = ((_obj.scan[i_mrpt] < (_msg.range_max*0.95)) && (_obj.scan[i_mrpt] > _msg.range_min));
		_obj.validRange[i_mrpt] = r_valid;
	}

	return true;
}


void ICP_scan_matching(const sensor_msgs::LaserScan& ros_scan){
  CSimplePointsMap		m1,m2;
  float					runningTime;
  CICP::TReturnInfo		info;
  CICP					ICP;

  CObservation2DRangeScan this_scan;
  // bool convert_success = mrpt_bridge::convert(ros_scan, mrpt_ref_pose, this_scan);
  bool convert_success = self_convert(ros_scan, mrpt_ref_pose, this_scan);
  if(convert_success){
    //Sucuss
    m2.insertObservation(&this_scan);

    m1.insertObservation(&mrpt_last_scan);
  	// ICP.options.ICP_algorithm = icpLevenbergMarquardt;
  	ICP.options.ICP_algorithm = icpClassic;
  	// ICP.options.ICP_algorithm = (TICPAlgorithm)ICP_method;

      // configuration options for the icp algorithm
  	ICP.options.maxIterations			= 100;
  	ICP.options.thresholdAng			= DEG2RAD(10.0f);
  	ICP.options.thresholdDist			= 0.75f;
  	ICP.options.ALFA					= 0.5f;
  	ICP.options.smallestThresholdDist	= 0.05f;
  	ICP.options.doRANSAC = false;

  	// ICP.options.dumpToConsole();

    CPose2D	initialPose(0.0f,0.0f,(float)DEG2RAD(0.0f));
    CPosePDFPtr pdf = ICP.Align(
      &m1,
      &m2,
      initialPose,
      &runningTime,
      (void*)&info);

    // printf("ICP run in %.02fms, %d iterations (%.02fms/iter), %.01f%% goodness\n -> ",
    //     runningTime*1000,
    //     info.nIterations,
    //     runningTime*1000.0f/info.nIterations,
    //     info.goodness*100 );

    // cout << "Mean of estimation: " << pdf->getMeanVal() << endl<< endl;

    CPosePDFGaussian  gPdf;
    gPdf.copyFrom(*pdf);

    // cout << "Covariance of estimation: " << endl << gPdf.cov << endl;

    // cout << " std(x): " << sqrt( gPdf.cov(0,0) ) << endl;
    // cout << " std(y): " << sqrt( gPdf.cov(1,1) ) << endl;
    // cout << " std(phi): " << RAD2DEG(sqrt( gPdf.cov(2,2) )) << " (deg)" << endl;


    CPose2D est;
    // gPdf.drawSingleSample(est);

    // CPosePDF inin;


    est = pdf->getMeanVal();
    // cout<<" X: "<<est.m_coords[0]<<endl;
    // cout<<" R: "<<est.phi()<<endl;
    // cout<<" Y: "<<est.m_coords[1]<<endl;

    float x2, y2, r2;
    x2 = est.m_coords[0];
    y2 = est.m_coords[1];
    r2 = est.phi();
    float theta = est.phi();


    mrpt::math::CMatrixDouble44 trans_matrix;
    est.getHomogeneousMatrix(trans_matrix);
    // cout<<"Matrix :\n"<<trans_matrix<<endl;
    // glob_pose->x = est.m_coords[0];
    // glob_pose->y = est.m_coords[1];
    // glob_pose->r = est.phi();
    // ReadLock r_lock(myLock);
    CPose2D original_pose(glob_pose->x, glob_pose->y, glob_pose->r);
    // original_pose.x = glob_pose->x;
    // original_pose.y = glob_pose->y;
    // original_pose.phi = glob_pose->r;

    original_pose = original_pose + est;

    // CMatrix original_matrix = CMatrix(4, 1);
    //
    // CMatrixColumnAccessor<float> helper(original_matrix, 0);
    // helper[0] = glob_pose->x;
    // helper[1] = glob_pose->y;
    // helper[2] = glob_pose->r;
    // helper[3] = 1;
    //
    // // CMatrix original_matrix = CMatrix(original_pose);
    // original_matrix = original_matrix * trans_matrix;
    // float error = glob_pose->r - original_pose.phi();
    // WriteLock w_lock(myLock);
    glob_pose->x = original_pose.m_coords[0];
    glob_pose->y = original_pose.m_coords[1];
    glob_pose->r = original_pose.phi();

    // last_yaw2 = original_pose.phi();

    // glob_pose->r += (theta);
    //
    //
    // float trans = sqrt(x2*x2 + y2*y2);
    // float rot1 = atan2(y2,x2) - glob_pose->r;
    // float rot2 = glob_pose->r - rot1;
    // cout<<"distance: "<<trans<<endl;
    //
    // glob_pose->x += (trans)*(cos((glob_pose->r) + rot1));
    // glob_pose->y += (trans)*(sin((glob_pose->r) + rot1));

    // glob_pose->x = glob_pose->x * ()
    // glob_pose->x = (sqrt( gPdf.cov(0,0) ));
    // glob_pose->y = sqrt( gPdf.cov(1,1) );
    // glob_pose->r = sqrt( gPdf.cov(2,2) ) ;



    // cout << "-> Saving reference map as scan1.txt" << endl;
    // m1.save2D_to_text_file("scan1.txt");
    //
    // cout << "-> Saving map to align as scan2.txt" << endl;
    // m2.save2D_to_text_file("scan2.txt");
    //
    // cout << "-> Saving transformed map to align as scan2_trans.txt" << endl;
    // CSimplePointsMap m2_trans = m2;
    // m2_trans.changeCoordinatesReference( gPdf.mean );
    // m2_trans.save2D_to_text_file("scan2_trans.txt");



  }else{
    //Fail
  }

}


double randn (double mu, double sigma){
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;

  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }

  do
    {
      U1 = -1 + ((double) rand () / RAND_MAX) * 2;
      U2 = -1 + ((double) rand () / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }
  while (W >= 1 || W == 0);

  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;

  call = !call;

  return (mu + sigma * (double) X1);
}

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

  // float error = glob_pose->r - yaw;
  // WriteLock w_lock(myLock);
  // cout<<"Yaw: "<<yaw<<endl;
  // glob_pose->r = yaw;
  // last_yaw  = glob_pose->r;
  //  t.getOrigin().x(), t.getOrigin().y(), yaw)

  // mrpt_bridge::convert(pose_msg->pose, mrpt_ref_pose);
  // glob_pose->x =  t.getOrigin().x();
  // glob_pose->y =  t.getOrigin().y();
  // glob_pose->r = yaw;
  // glob_pose->print();
  // glob_pose->print();
  // cout<<"frame_angle: "<<yaw<<" D: "<<yaw*180/(M_PI)<<endl;
  // if(debug_file->is_open()){
  //   *(debug_file)<< "X: "<<glob_pose->x ;
  //   *(debug_file)<< " ,Y: "<<glob_pose->y ;
  //   *(debug_file)<< " ,R: "<<glob_pose->r<<"\n" ;
  // }

  // for(int i = 0;i<glob_particle.size();i++){
  //   glob_particle[i].update_pose(glob_pose->x, glob_pose->y, glob_pose->r);
  // }
}


void compass_callback(const std_msgs::Float32::ConstPtr& compass_msg){
  // glob_r->set_yaw(compass_msg->data);
  // float reflected_angle = atan(-sin(compass_msg->data)/-cos(compass_msg->data));
  // cout<<"reflected_angle: "<<reflected_angle<<" D: "<<reflected_angle*180/(M_PI)<<endl;
  cout<<"original_angle: "<<compass_msg->data<<" D: "<<compass_msg->data*180/(M_PI)<<endl;

  // glob_pose->r = M_PI - compass_msg->data ;
  // glob_pose->r = 2*M_PI - compass_msg->data;

  // float theta = compass_msg->data;

  // if(front!=-1){
  //   end_time = mrpt::system::now();
  //   time_diff = mrpt::system::timeDifference(begin_time, end_time);
  // }
  // begin_time = end_time;
  // //
  // float vl, vr, R, W;
  // float l = 0.44;
  // //
  // if(front==2){
  //   for(int i = 0;i<glob_particle.size();i++){
  //
  //     vl = randn(0.05, 1);
  //     vr = randn(0.1, 1);
  //     R = (l/2)* (vl+vr) / (vr-vl);
  //     W = (vr-vl) / l;
  //     Position *p = glob_particle[i].get_pose();
  //     p->x = cos(W * time_diff) * R * sin(compass_msg->data) - sin(W * time_diff) * -(R) * cos(compass_msg->data) + (p->x - R * sin(compass_msg->data));
  //     p->y = sin(W * time_diff) * R * sin(compass_msg->data) + cos(W * time_diff) * -(R) * cos(compass_msg->data) + (p->y + R * cos(compass_msg->data));
  //     p->r = compass_msg->data + W * time_diff;
  //     if(estimate_file->is_open()){
  //       *(estimate_file)<< "X: "<<p->x ;
  //       *(estimate_file)<< " ,Y: "<<p->y ;
  //       *(estimate_file)<< " ,R: "<<p->r<<"\n" ;
  //     }
  //   }
  //   if(estimate_file->is_open()){
  //     *(estimate_file)<<"----------------------------------------------\n";
  //   }
  //   cout<<"UPDATE PARTICLE"<<endl;
  // }else if(front==0){
  //
  // }
  //



  // if(abs(glob_goal->x-glob_pose->x)>0.1 || abs(glob_goal->y-glob_pose->y)>0.1 ){
  //   float angle_diff = atan((glob_goal->y - glob_pose->y)/(glob_goal->x - glob_pose->x));
  //   if(angle_diff>=glob_pose->r){
  //     glob_r->ros_send_movement(86, 170);
  //   }else{
  //     glob_r->ros_send_movement(43, 212);
  //   }
  // }
  // glob_pose->r = compass_msg->data;
  // best_particles_r.push_back(compass_msg->data);
  // // time_count.push_back((float)counter/0.1);
  // for(int i = 0;i<glob_particle.size();i++){
  //   glob_particle[i].update_particle_yaw(compass_msg->data);
  // }
}

// void laser_callback(const sensor_msgs::LaserScan& scan_in){
//
//   if(counter==0){
//     my_mapping->setting_params(
//       scan_in.angle_min,
//       scan_in.angle_max,
//       scan_in.angle_increment,
//       scan_in.range_min,
//       scan_in.range_max);
//       if(glob_pose->r!=0.1){
//         my_mapping->update_map_xv11(scan_in.ranges, glob_pose);
//         counter++;
//       }
//       // bool convert_success = mrpt_bridge::convert(scan_in, mrpt_ref_pose, mrpt_last_scan);
//       bool convert_success = self_convert(scan_in, mrpt_ref_pose, mrpt_last_scan);
//       if(!convert_success){
//         cout<<"Error ros bridge"<<endl;
//       }
//   }else{
//     ICP_scan_matching(scan_in);
//     // bool convert_success_2 = mrpt_bridge::convert(scan_in, mrpt_ref_pose, mrpt_last_scan);
//     bool convert_success_2 = self_convert(scan_in, mrpt_ref_pose, mrpt_last_scan);
//     if(!convert_success_2){
//       cout<<"Error ros bridge"<<endl;
//     }
//
//
//     // if(front!=-1){
//     //   end_time = mrpt::system::now();
//     //   time_diff = mrpt::system::timeDifference(begin_time, end_time);
//     // }
//     // cout<<"Calculated : "<<time_diff <<endl;
//     // float offset = 1.0f;
//     // if(front==0){
//     //   for(int i = 0;i<glob_particle.size();i++){
//     //     glob_particle[i].update_particle((-0.109)*time_diff);
//     //   }
//     //   // glob_pose->y += 0.20*time_diff;
//     // }else if (front==1){
//     //   for(int i = 0;i<glob_particle.size();i++){
//     //     glob_particle[i].update_particle(0.02*time_diff);
//     //   }
//     //   // glob_pose->y += -0.20*time_diff;
//     // }200
//     // begin_time = end_time;
//     // for (int i = 0;i<glob_particle.size();i++){
//     //   glob_particle[i].update_particle(0.0);
//     // }
//     int max_score = 0;
//     int score = 0;
//     int max_p = 0;
//     for (int i = 0;i<glob_particle.size();i++){
//       score = my_mapping->compute_scan_matching(scan_in.ranges, &glob_particle[i]);
//       if(score>=max_score){
//         max_score = score;
//         max_p = i;
//       }
//     }
//
//     // my_mapping_2->m_map->clear();
//
//     cout<<"Greatest score: "<<max_score<<", i : "<<max_p<<endl;
//     // glob_particle[max_p].print();
//     // best_particles_x.push_back(((glob_particle[max_p].get_pose()->x)/0.02)+500);
//     // best_particles_y.push_back(-((glob_particle[max_p].get_pose()->y)/0.02)+500);
//     // float best_y = glob_particle[max_p].get_pose()->y;
//     // float best_x = glob_particle[max_p].get_pose()->x;
//     // float best_r = glob_particle[max_p].get_pose()->r;
//
//     // hi->update_plot_vector(best_particles_x, best_particles_y);
//     // hi->update_plot_vector(best_particles_r, best_particles_r);
//     // my_mapping->update_map_xv11(scan_in.ranges, glob_particle[max_p].get_pose());
//     my_mapping->update_map_xv11(scan_in.ranges, glob_pose);
//     // my_mapping_2->insertObservation()
//     // my_mapping_2->update_map_xv11(scan_in.ranges, glob_particle[max_p].get_pose());
//
//
//
//     float max_weight = glob_particle[max_p].get_weight();
//
//     std::vector<Particle> new_particles;
//     float beta = 0.0;
//     int index = 0;
//     for(int i = 0;i<number_of_particles;i++){
//       beta = beta + glob_correct_random(max_weight);
//       while (glob_particle[index].get_weight()<beta) {
//         beta = beta - glob_particle[index].get_weight();
//         index++;
//         index = index % number_of_particles;
//       }
//       new_particles.push_back(glob_particle[index]);
//     }
//     glob_particle = new_particles;
//
//     float total_weight = 0.0;
//     for (int i = 0;i<glob_particle.size();i++){
//       total_weight += glob_particle[i].get_weight();
//     }
//     //Normalized Weight
//     for (int i = 0;i<glob_particle.size();i++){
//       float new_weight = glob_particle[i].get_weight()/total_weight;
//       glob_particle[i].set_weight(new_weight);
//       // cout<<"Weight: "<<new_weight<<", i: "<<i<<endl;
//     }
//     //
//     // cout<<"Before Resampling"<<endl;
//     // for(int i = 0;i<glob_particle.size();i++){
//     //     glob_particle[i].print();
//     // }
//     //
//     //   //Resampling Weight
//     //   std::vector<Particle> new_particles;
//     //   for(int i=0;i<glob_particle.size();i++){
//     //     int choice = rand()*total_weight;
//     //     int index = -1;
//     //     do {
//     //       index++;
//     //       choice -= glob_particle[index].get_weight();
//     //     } while(choice>0);
//     //     new_particles.push_back(glob_particle[index]);
//     //   }
//     //   glob_particle = new_particles;
//     //
//       // cout<<"After Resampling"<<endl;
//       // for(int i = 0;i<glob_particle.size();i++){
//       //     glob_particle[i].print();
//       // }
//     //
//
//     counter++;
//     // if(counter%10==0){
//       // if(!gl_gridmap_3d){
//       //   gl_gridmap_3d = CSetOfObjects::Create();
//       // }
//       // // gl_gridmap_3d->clear();
//       // my_mapping->m_map->getAs3DObject(gl_gridmap_3d);
//       // hi->update_gui(gl_gridmap_3d);
//
//       my_mapping->m_map->getAsImage(*glob_img, false, true, false);
//       glob_img->triangle(((glob_pose->x)/0.02)+500, -((glob_pose->y)/0.02)+500,5,mrpt::utils::TColor::green, true, 2);
//       glob_img->triangle(((glob_goal->x)/0.02)+500, -((glob_goal->y)/0.02)+500,5,mrpt::utils::TColor::blue, true, 2);
//       hi->update_gui_2d(glob_img, best_particles_x, best_particles_y);
//
//       // getchar();
//       // my_mapping_2->m_map->getAsImage(*glob_img_obs, false, true, false);
//
//       // hi->show_observation(glob_img_obs);
//
//     // }DA
//     // if(abs(glob_goal->x-glob_pose->x)>0.1 || abs(glob_goal->y-glob_pose->y)>0.1 ){
//     //   glob_r->ros_send_movement(86,213);
//     //   // float angle_diff = atan((glob_goal->y - glob_pose->y)/(glob_goal->x - glob_pose->x));
//     //   // if(angle_diff>=glob_pose->r){
//     //   //   glob_r->ros_send_movement(86, 170);
//     //   // }else{
//     //   //   glob_r->ros_send_movement(43, 212);
//     //   // }
//     // }else{
//     //   glob_r->ros_send_movement(0,0);
//     // }
//
//
//
//   }
//
// }

void laser_callback(const sensor_msgs::LaserScan& scan_in){

  if(counter==0){
    my_mapping->setting_params(
      scan_in.angle_min,
      scan_in.angle_max,
      scan_in.angle_increment,
      scan_in.range_min,
      scan_in.range_max);
      if(glob_pose->r!=0.1){
        my_mapping->update_map_xv11(scan_in.ranges, glob_pose);
        counter++;
      }
      // bool convert_success = mrpt_bridge::convert(scan_in, mrpt_ref_pose, mrpt_last_scan);
      bool convert_success = self_convert(scan_in, mrpt_ref_pose, mrpt_last_scan);
      if(!convert_success){
        cout<<"Error ros bridge"<<endl;
      }
  }else{
    //
    // tf::StampedTransform t;
    // try{
    //   glob_trans->lookupTransform("/map", "/robot0", ros::Time(0), t);
    // }catch(tf::TransformException &ex){
    //     cout<<"error: "<< &ex <<endl;
    // }
    // double yaw, pitch, roll;
    // t.getBasis().getRPY(roll, pitch, yaw);
    //
    // // float error = glob_pose->r - yaw;
    // // WriteLock w_lock(myLock);
    // // cout<<"Yaw: "<<yaw<<endl;
    // // glob_pose->r = yaw;
    // // last_yaw  = glob_pose->r;
    // //  t.getOrigin().x(), t.getOrigin().y(), yaw)
    //
    // // mrpt_bridge::convert(pose_msg->pose, mrpt_ref_pose);
    // // glob_pose->x =  t.getOrigin().x();
    // // glob_pose->y =  t.getOrigin().y();
    // glob_pose->r = yaw;
    // glob_pose->print();

    ICP_scan_matching(scan_in);
    // bool convert_success_2 = mrpt_bridge::convert(scan_in, mrpt_ref_pose, mrpt_last_scan);

      bool convert_success_2 = self_convert(scan_in, mrpt_static_pose, mrpt_last_scan);
      if(!convert_success_2){
        cout<<"Error ros bridge"<<endl;
      }


    // mrpt_ref_pose.setFromValues(glob_pose->x, glob_pose->y , 0, glob_pose->r , 0, 0);

    // if(mrpt_ref_pose)
      mrpt_ref_pose.setFromValues(0, 0 , 0, 0 , 0, 0);
      mrpt_static_pose.setFromValues(0, 0 , 0, 0 , 0, 0);



    // if(front!=-1){
    //   end_time = mrpt::system::now();
    //   time_diff = mrpt::system::timeDifference(begin_time, end_time);
    // }
    // cout<<"Calculated : "<<time_diff <<endl;
    // float offset = 1.0f;
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
    // }200
    // begin_time = end_time;
    // for (int i = 0;i<glob_particle.size();i++){
    //   glob_particle[i].update_particle(0.0);
    // }
    // int max_score = 0;
    // int score = 0;
    // int max_p = 0;
    // for (int i = 0;i<glob_particle.size();i++){
    //   score = my_mapping->compute_scan_matching(scan_in.ranges, &glob_particle[i]);
    //   if(score>=max_score){
    //     max_score = score;
    //     max_p = i;
    //   }
    // }
    //
    // // my_mapping_2->m_map->clear();
    //
    // cout<<"Greatest score: "<<max_score<<", i : "<<max_p<<endl;
    // // glob_particle[max_p].print();
    best_particles_x.push_back(((glob_pose->x)/0.02)+500);
    best_particles_y.push_back(-((glob_pose->y)/0.02)+500);
    // // float best_y = glob_particle[max_p].get_pose()->y;
    // // float best_x = glob_particle[max_p].get_pose()->x;
    // // float best_r = glob_particle[max_p].get_pose()->r;
    //
    // // hi->update_plot_vector(best_particles_x, best_particles_y);
    // // hi->update_plot_vector(best_particles_r, best_particles_r);
    // // my_mapping->update_map_xv11(scan_in.ranges, glob_particle[max_p].get_pose());
    glob_pose->print();
    my_mapping->update_map_xv11(scan_in.ranges, glob_pose);
    // // my_mapping_2->insertObservation()
    // // my_mapping_2->update_map_xv11(scan_in.ranges, glob_particle[max_p].get_pose());
    //
    //
    //
    // float max_weight = glob_particle[max_p].get_weight();
    //
    // std::vector<Particle> new_particles;
    // float beta = 0.0;
    // int index = 0;
    // for(int i = 0;i<number_of_particles;i++){
    //   beta = beta + glob_correct_random(max_weight);
    //   while (glob_particle[index].get_weight()<beta) {
    //     beta = beta - glob_particle[index].get_weight();
    //     index++;
    //     index = index % number_of_particles;
    //   }
    //   new_particles.push_back(glob_particle[index]);
    // }
    // glob_particle = new_particles;
    //
    // float total_weight = 0.0;
    // for (int i = 0;i<glob_particle.size();i++){
    //   total_weight += glob_particle[i].get_weight();
    // }
    // //Normalized Weight
    // for (int i = 0;i<glob_particle.size();i++){
    //   float new_weight = glob_particle[i].get_weight()/total_weight;
    //   glob_particle[i].set_weight(new_weight);
    //   // cout<<"Weight: "<<new_weight<<", i: "<<i<<endl;
    // }
    // //
    // // cout<<"Before Resampling"<<endl;
    // // for(int i = 0;i<glob_particle.size();i++){
    // //     glob_particle[i].print();
    // // }
    // //
    // //   //Resampling Weight
    // //   std::vector<Particle> new_particles;
    // //   for(int i=0;i<glob_particle.size();i++){
    // //     int choice = rand()*total_weight;
    // //     int index = -1;
    // //     do {
    // //       index++;
    // //       choice -= glob_particle[index].get_weight();
    // //     } while(choice>0);
    // //     new_particles.push_back(glob_particle[index]);
    // //   }
    // //   glob_particle = new_particles;
    // //
    //   // cout<<"After Resampling"<<endl;
    //   // for(int i = 0;i<glob_particle.size();i++){
    //   //     glob_particle[i].print();
    //   // }
    // //
    //
    counter++;
    // // if(counter%10==0){
    //   // if(!gl_gridmap_3d){
    //   //   gl_gridmap_3d = CSetOfObjects::Create();
    //   // }
    //   // // gl_gridmap_3d->clear();
    //   // my_mapping->m_map->getAs3DObject(gl_gridmap_3d);
    //   // hi->update_gui(gl_gridmap_3d);
    //
      my_mapping->m_map->getAsImage(*glob_img, false, true, false);
      glob_img->triangle(((glob_pose->x)/0.02)+500, -((glob_pose->y)/0.02)+500,5,mrpt::utils::TColor::green, true, 2);
      glob_img->saveToFile("/home/kin/Desktop/dilidili.jpg");
    //   glob_img->triangle(((glob_goal->x)/0.02)+500, -((glob_goal->y)/0.02)+500,5,mrpt::utils::TColor::blue, true, 2);
      hi->update_gui_2d(glob_img, best_particles_x, best_particles_y);



      // nav_msgs::OccupancyGrid on99;
      // mrpt_bridge_map::convert(*(my_mapping->m_map), on99);
      // glob_map_publish->publish(on99);


    //
    //   // getchar();
      // my_mapping_2->m_map->getAsImage(*glob_img_obs, false, true, false);

      // hi->show_observation(glob_img_obs);

    // }DA
    // if(abs(glob_goal->x-glob_pose->x)>0.1 || abs(glob_goal->y-glob_pose->y)>0.1 ){
    //   glob_r->ros_send_movement(86,213);
    //   // float angle_diff = atan((glob_goal->y - glob_pose->y)/(glob_goal->x - glob_pose->x));
    //   // if(angle_diff>=glob_pose->r){
    //   //   glob_r->ros_send_movement(86, 170);
    //   // }else{
    //   //   glob_r->ros_send_movement(43, 212);
    //   // }
    // }else{
    //   glob_r->ros_send_movement(0,0);
    // }



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
      Particle *p = new Particle(randn(-0.3, 0.3), glob_random_float(-0.3, 0.3), 0.0 , 0.1);
      glob_particle.push_back(*p);
    }
    glob_motor = new Motor();

    glob_r = new Robot(40.0, 40.0);


    hi = new kinGui();
    hi->init(&k_observer);




    debug_file = new ofstream("/home/kin/Desktop/correct.txt");
    estimate_file = new ofstream("/home/kin/Desktop/est.txt");

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
    ros::Publisher output_map = n.advertise<nav_msgs::OccupancyGrid>("/kin_map", 2000);
    glob_map_publish = &output_map;
    glob_r->ros_send_movement(0,0);

    // ros::MultiThreadedSpinner spinner(4);

    ros::Subscriber pose_sub = n.subscribe("/slam_out_pose", 1000, pose_callback);
    ros::Subscriber laser_sub = n.subscribe("/scan", 1000, laser_callback);
    ros::Subscriber compass_sub = n.subscribe("/robot_compass", 1000, compass_callback);

    ros::spin();

    debug_file->close();
    estimate_file->close();
    // glob_r->listen_to_driver();

    // pthread_join(gui_thread, NULL);
    // cout<<"Exit...."<<endl;
    // exit(1);
    return 0;
}
