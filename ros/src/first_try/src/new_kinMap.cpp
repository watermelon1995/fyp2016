// #include <mrpt/base.h>
#include <mrpt/maps/COccupancyGridMap2D.h>
// #include <mrpt/utils/CMemoryStream.h>
#include <mrpt/utils/CImage.h>
#include <mrpt/obs/CObservation2DRangeScan.h>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "tf/transform_listener.h"
#include "geometry_msgs/Pose2D.h"
#include "new_kinGui.cpp"
#include <pthread.h>

// using  namespace mrpt::utils;
// using  namespace mrpt::poses;
// using  namespace mrpt::slam;
// using namespace mrpt::slam;

using namespace mrpt::maps;
using namespace mrpt::utils;
using namespace std;
using namespace ros;
using namespace tf;

#define number_of_ray 667
#define angle_min -2.0944
#define angle_max 2.0944
#define resolution 0.02
#define max_range 4.09

TransformListener *trans;
int debug = 0;
COccupancyGridMap2D *map_ptr = NULL;


void update_grid(int x, int y, float v){
    if(map_ptr!=NULL){
        if(v<0.5){
            map_ptr->updateCell(x-1, y-1, v);
            map_ptr->updateCell(x-1, y, v);
            map_ptr->updateCell(x-1, y+1, v);
            map_ptr->updateCell(x, y-1, v);
            map_ptr->updateCell(x, y, v);
            map_ptr->updateCell(x, y+1, v);
            map_ptr->updateCell(x+1, y-1, v);
            map_ptr->updateCell(x+1, y, v);
            map_ptr->updateCell(x+1, y+1, v);
        }else{
            map_ptr->updateCell(x, y, v);
        }
    }
}

float distance(int x0, int x1, int y0, int y1){
    int distance_x = (x1-x0)*(x1-x0);
    int distance_y = (y1-y0)*(y1-y0);
    return sqrt(distance_x+distance_y);
}

void bhm_line(int x1,int y1,int x2,int y2){
 int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
 dx=x2-x1;
 dy=y2-y1;
 dx1=fabs(dx);
 dy1=fabs(dy);
 px=2*dy1-dx1;
 py=2*dx1-dy1;
 if(dy1<=dx1)
 {
  if(dx>=0)
  {
   x=x1;
   y=y1;
   xe=x2;
  }
  else
  {
   x=x2;
   y=y2;
   xe=x1;
  }
//   update_grid(x, y, 0.4);
//   putpixel(x,y,c);
  for(i=0;x<xe;i++)
  {
   x=x+1;
   if(px<0)
   {
    px=px+2*dy1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     y=y+1;
    }
    else
    {
     y=y-1;
    }
    px=px+2*(dy1-dx1);
   }
//    delay(0);
   update_grid(x, y, 0.6);
  }
 }
 else
 {
  if(dy>=0)
  {
   x=x1;
   y=y1;
   ye=y2;
  }
  else
  {
   x=x2;
   y=y2;
   ye=y1;
  }
//   update_grid(x, y, 0.4);
  for(i=0;y<ye;i++)
  {
   y=y+1;
   if(py<=0)
   {
    py=py+2*dx1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     x=x+1;
    }
    else
    {
     x=x-1;
    }
    py=py+2*(dx1-dy1);
   }

   update_grid(x, y, 0.6);
  }
 }
}


void update_map(vector<float> ranges, float x, float y, float yaw){
    int i;
    float angle = yaw+angle_min;
    float angle_interval = (angle_max*2)/ranges.size();
    int start_x = map_ptr->x2idx(x);
    int start_y = map_ptr->y2idx(y);
    int end_x;
    int end_y;

    for(i = 0;i<ranges.size();i++){
        // cout<<"i: "<<i<<endl;
        // cout<<"r: "<<ranges[i]<<endl;
        // cout<<"a: "<<angle<<endl;
        if(!isinf(ranges[i])){
            end_x = map_ptr->x2idx(x+ranges[i]*cos(angle));
            end_y = map_ptr->y2idx(y+ranges[i]*sin(angle));
            // cout<<"start_x"<<start_x<<endl;
            // cout<<"start_y"<<start_y<<endl;
            // cout<<"end_x: "<<end_x<<endl;
            // cout<<"end_y: "<<end_y<<endl;
            update_grid(end_x, end_y, 0.4);
            bhm_line(start_x, start_y, end_x, end_y);
            // update_line(start_x, end_x, start_y, end_y, false);

            // sleep(1);
            // cout<<"line"<<endl;
        }else{
            // end_x = map_ptr->x2idx(x+max_range*cos(angle));
            // end_y = map_ptr->y2idx(y+max_range*sin(angle));
            // update_grid(end_x, end_y, 0.4);
            // bhm_line(start_x, start_y, end_x, end_y);
            // update_line(start_x, end_x, start_y, end_y, true);
        }

        if(i<336){
            angle = yaw-(336-i)*angle_interval;
        }else if(i>=336){
            angle = yaw+(i-336)*angle_interval;
        }
    }
}

kinObserver k_observer;
CImagePtr glob_img;
kinGui *hi;
mrpt::opengl::CSetOfObjectsPtr glObj;

void laser_callback(const sensor_msgs::LaserScan::ConstPtr& scan_in){
    tf::StampedTransform t;
    try{
        trans->lookupTransform("/map", "/robot0", ros::Time(0), t);
    }catch(tf::TransformException &ex){
        ROS_ERROR("%s",ex.what());
        cout<<"Error: "<<&ex<<endl;
    }
    cout<<"X :" <<t.getOrigin().x()<<endl;
    cout<<"Y :" <<t.getOrigin().y()<<endl;
    cout<<"Z :" <<t.getOrigin().z()<<endl;
    double yaw, pitch, roll;
    t.getBasis().getRPY(roll, pitch, yaw);
    cout<<"Angle: "<<yaw<<endl;

    // if(debug>1000){
    //     cout<<"Done!"<<endl;
    //     map_ptr->saveAsBitmapFile("/home/kin/Desktop/new_kin.bmp");
    //     sleep(5);
    //
    //     exit(0);
    // }

    if(debug>10){
        // geometry_msgs::Pose2D hihi= new Pose2D(t.getOrigin().x(), t.getOrigin().y(), yaw);
        // update_map_observation(scan_in);
        update_map(scan_in->ranges, t.getOrigin().x(), t.getOrigin().y(), yaw);
        if(debug%5 == 0){
          // glObj.clear_unique();
          // map_ptr->getAs3DObject(glObj);
          // hi->update_gui(glObj);

          map_ptr->getAsImage(*glob_img, false, false, false);
          hi->update_gui_2d(glob_img);

        }

    }
    debug++;
}

int *argc_global;
char **argv_global;



void *start_gui(void *ptr){
  cout<<"fuck"<<endl;

  hi = new kinGui();

  hi->init(&k_observer);
  cout<<"fuck"<<endl;


  // getchar();
}



void *start_ros(void *ptr){

}


int main(int argc, char ** argv)
{
  // argc_global = &argc;
  // argv_global = argv;
    // cout<<argc<<endl;
    // cout<<*argv<<endl;
    // glObj = mrpt::opengl::CSetOfObjects::Create();
    glob_img = mrpt::utils::CImage::Create();

    pthread_t gui_thread;
    int ret;
    ret = pthread_create(&gui_thread, NULL, &start_gui, NULL);
    if(ret!=0){
      cout<<"DIU gui"<<endl;
    }
    // cout<<"size_x:" <<occ_map.getSizeX()<<endl;
    // cout<<"size_y:" <<occ_map.getSizeY()<<endl;

    COccupancyGridMap2D occ_map = COccupancyGridMap2D(0.0, 15.5, 0.0, 14.92, 0.02);
    k_observer.observeBegin(occ_map);
    map_ptr = &occ_map;


    ros::init(argc, argv, "new_kinMap");


    ros::NodeHandle n;

    TransformListener listener(ros::Duration(5));
    trans = &listener;
    // cout<<"de";
    ros::Subscriber laser_sub = n.subscribe("/robot0/laser_0", 1000, laser_callback);
    // Subscriber sub_sonar_0 = n.subscribe("/robot0/sonar_0", 1000, sonar0_callback);
    // Subscriber sub_sonar_1 = n.subscribe("/robot0/sonar_1", 1000, sonar1_callback);

    ros::spin();



    //
    //
    // ret = pthread_create(&ros_thread, NULL, &start_ros, NULL);
    // if(ret!=0){
    //   cout<<"DIU ros"<<endl;
    // }
    // ret = pthread_create(&gui_thread, NULL, &start_gui, NULL);
    // if(ret!=0){
    //   cout<<"DIU gui"<<endl;
    // }
    pthread_join(gui_thread, NULL);
    cout<<"Exit...."<<endl;
    exit(1);
    // pthread_join(ros_thread, NULL);
    // while(1);
    // cout<<"end"<<endl;
    return 0;
}
