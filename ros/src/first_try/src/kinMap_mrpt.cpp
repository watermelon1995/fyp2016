#include "ros/ros.h"
// #include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/Range.h"
#include "tf/transform_listener.h"
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>
#include "bitmap_image.hpp"

#include <boost/unordered_set.hpp>

using boost::unordered_set;
using std::pair;




#define _USE_MATH_DEFINES

using namespace std;
using namespace ros;
using namespace tf;

const int map_width = 1550;
const int map_length = 1492;
const int map_ratio = 100;
float occ_map [map_length][map_width];
TransformListener *trans;

// //ultrasonic scan data;
// /*
//     Header header;
//     uint8 radiation_type;
//     float field_of_view;
//     float min_range;
//     float max_range;
//     float range;
// */

float cone = 0.87; //angle of the cone area for the sonar sensor




struct Grid{
    unsigned int obs_count;
    unsigned int free_count;
    float i;
};

Grid **log_map;

void init_log_on(){
    log_map = new Grid*[map_length];
    for(int i = 0 ;i<map_length;i++){
        log_map[i] = new Grid[map_width];
    }
    for(int y = 0;y< map_length;y++){
        for(int x = 0;x<map_width;x++){
            log_map[y][x].obs_count = 0;
            log_map[y][x].free_count = 0;
            log_map[y][x].i = 0.0;
        }
    }
}




void init_map(){
    for(int i = 0; i<map_length;i++){
        for (int j = 0; j<map_width;j++){
            occ_map [i][j] = 0.5;
        }
    }
}

void print_map(){
    //Debug to file
    ofstream debug_file;
    debug_file.open("/home/kin/Desktop/debug.txt", ios::trunc);
    debug_file.setf(ios::fixed);
    for(int i =map_length-1 ;i>=0;i--){
        for(int j = 0;j<map_width;j++){
            // if(occ_map[i][j]>0.9){
            //     debug_file<<".";
            // }else if(occ_map[i][j]>0.8){
            //     debug_file<<"!";
            // }else if(occ_map[i][j]>0.6){
            //     debug_file<<"?";
            // }else{
            //     debug_file<<" ";
            // }
            if(occ_map[i][j]==0.5){
                debug_file<<",,,,,";
            }else{
                debug_file << setprecision(3)<<occ_map[i][j] << ",";
            }
        }
        debug_file<<endl;
    }
    debug_file.close();
}

void print_bmp(){
  bitmap_image image(map_length, map_width);
  int colour_ratio  = 0;
  image_drawer draw(image);
  draw.pen_width(1);
  for(int i = 0;i<map_length;i++){
    for(int j = 0;j<map_width;j++){
        colour_ratio = (int)(occ_map[i][j] * 10);
        draw.pen_color(255-25*colour_ratio, 255-25*colour_ratio, 255-25*colour_ratio);
        draw.plot_pen_pixel(j,map_length-i);
    }
  }
  image.save_image("/home/kin/Desktop/debug.bmp");
}

void print_json (){
  ofstream debug_json;
  debug_json.open("/home/kin/Desktop/debug.json", ios::trunc);
  debug_json.setf(ios::fixed);
  debug_json<<"[ ";
  for(int i = map_length-1;i>=0;i--){
    debug_json<<"[ ";
    for(int j = map_width-1;j>=0;j--){
      if(j!=0){
        debug_json<<"{ x: " <<j<<", ";
        debug_json<<" y: "<< i << ", ";
        debug_json<< "p: " <<setprecision(2)<<occ_map[i][j]<<"},";
      }else{
        debug_json<<"{ x: " <<j<<", ";
        debug_json<<" y: "<< i << ", ";
        debug_json<< "p: " <<setprecision(2)<<occ_map[i][j]<<"}";
      }
    }

    if(i!=0){
      debug_json<<"],";
    }else{
      debug_json<<"]";
    }
  }
  debug_json.close();
}

float normal_PFD (float sample, float mean, float variance){
    return pow(sqrt(2*variance*M_PI), -1)*exp((-1)*((sample-mean)*(sample-mean))/(2*variance));
}

float distance (int x1, int y1, int x2, int y2 ){
    return sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
}


bool check_grid (int x, int y){
    if((x>=0 && x<map_width) && (y>=0 && y<map_length)){
        return true;
    }else{
        return false;
    }
}

void update_grid (int x, int y, float p){
    if(check_grid(x,y)){
        float new_p = log(occ_map[y][x]) - log(1-occ_map[y][x]) + log(p) - log(1-p);
        if(occ_map[y][x]!=0.5){
            // For unexplored map
            new_p = 1.0 - (1.0/exp(new_p));
        }else{
            // For refunded map
            new_p = 1.0 - (1.0/exp(new_p));
        }
        
        occ_map[y][x] = new_p;
        
        // cout<<"new_p :" <<new_p<<endl;
            if(new_p>1){
                occ_map[y][x] = 0.99;
            }else if(new_p<0){
                occ_map[y][x] = 0.01;
            }else{
                occ_map[y][x] = new_p;
            }
    }else{
        // cout<<"Out of bound"<<endl;
    }


    // occ_map[ (map_width/2) + x ] [ (map_length) +y] = p;
}


void update_line(int x0, int x1, int y0, int y1){
    int temp_x0 = x0;
    int temp_x1 = x1;
    int temp_y0 = y0;
    int temp_y1 = y1;
    float p;
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    
    if(steep){
        temp_x0 = y0;
        temp_x1 = y1;
    }
    if(temp_x0 > temp_x1){
        temp_x0 = temp_x1;
        temp_y0 = temp_y1;
    }

    int delta_x = temp_x1 - temp_x0;
    int delta_y = abs(temp_y1 - temp_y0);
    int error = delta_x /2;
    int y_step;
    int x_step;
    if(temp_x0<temp_x1){
        x_step = 1;
    }else{
        x_step = -1;
    }
    int y = temp_y0;
    if(temp_y0 < temp_y1 ){
        y_step = 1;
    }else{
        y_step = -1;
    }
    int x = temp_x0;
    while(x!=temp_x1){
        // p = distance(x0, y0, x, y)/distance(x0,y0, x1, y1);
        p = 0.9;
        if(steep){    
            
            update_grid(y, x, p);
        }else{
            
            update_grid(x, y, p);
        }
        error = error - delta_y;
        if(error<0){
            y = y+y_step;
            error = error+delta_x;
        }
        x = x + x_step;
    }
}

void update_log_on_grid(int y, int x, float p){
    if(check_grid(x, y)){

    }else{
        // cout<<"Out of Range"<<endl;
    }
}



void update_map(float range , double x, double y, double yaw){
    int start_x  = (int)floor(x * map_ratio);
    int start_y  = (int)floor(y * map_ratio);
    int end_x, end_y ;
    int curl_x, curl_y;
    float p ;

    unordered_set<int> grids;

    if(!isinf(range)){
        for(float cone_angle = yaw-(cone/2);cone_angle<yaw+(cone/2);cone_angle= cone_angle+0.001){
           for(float r = (range) ; r>0 ; r-=0.01){
            
            //   cout<<"Angle: "<<cone_angle<<endl;
              
              end_x = (int)floor(x*map_ratio + (cos(cone_angle)*r*map_ratio));
              end_y = (int)floor(y*map_ratio + (sin(cone_angle)*r*map_ratio));

              if(grids.find(((end_x + end_y)*(end_x + end_y + 1)/2) + end_y) == grids.end() ){
                p = 0.1;
                
                if(r > (range-range*0.02)){
                    p = (r/range);
                    // p = p * ((abs((cone/2)-(cone_angle-yaw)))/(cone/4));
                } else{
                   
                }
                    update_grid(end_x, end_y, p);
                
                 grids.insert(((end_x + end_y)*(end_x + end_y + 1)/2) + end_y);
                // p = (r/range)*
                
                // cout<<"update"<<endl;
                

              }
              


            //   update_line(start_x, end_x, start_y, end_y);
            //   curl_x = (int)floor(x*map_ratio + (cos(cone_angle) * r * map_ratio));
            //   curl_y = (int)floor(y*map_ratio + (sin(cone_angle) * r * map_ratio));

            //   if(r<(range+range*0.1) && r>(range-range*0.1)) {
            //     p = (r/range)*0.9;
            //   }else{
            //     p = 0.1;
            //   }


            //   update_grid(curl_x, curl_y, p);
           }
        }
    }else{
      range = 3.0;
      for(float r = range; r>0; r -= 0.01){
        for(float cone_angle = yaw-(cone/2);cone_angle<yaw+(cone/2);cone_angle = cone_angle + 0.001){
          curl_x = (int)floor(x*map_ratio + (cos(cone_angle) * r * map_ratio));
          curl_y = (int)floor(y*map_ratio + (sin(cone_angle) * r * map_ratio));
          update_grid(curl_x, curl_y , 0.1);
        }
      }
    }


        //
        // print_map();
        // cout<<"Done! open debug.txt"<<endl;
        // getchar();


    //     while( (curl_x !=end_x) && (curl_y !=end_y)){
    //         cout<<"Current x:"<<curl_x<<endl;
    //         cout<<"Current y:"<<curl_y<<endl;
    //         // cout<<"End x: "<<end_x<<endl;
    //         // cout<<"End y: "<<end_y<<endl;
    //         cout<<"Distance to end: "<<distance(curl_x, curl_y, end_x, end_y)<<endl;
    //         p = normal_PFD(distance(curl_x, curl_y, end_x, end_y), range, 10.0);
    //         update_grid(curl_x, curl_y, p);
    //         if(p!=0){
    //             cout<<"Current x:"<<curl_x<<endl;
    //             cout<<"Current y:"<<curl_y<<endl;
    //         }

    //         if(curl_x > end_x){
    //             curl_x -=1;
    //         }else if(curl_x < end_x){
    //             curl_x +=1;
    //         }

    //         if(curl_y > end_y){
    //             curl_y -=1;
    //         }else if(curl_y < end_y){
    //             curl_y +=1;
    //         }
    //     }

    // }

}

int debug = 0;
int debug_2 = 0;
int debug_0 = 0;




void sonar1_callback(const sensor_msgs::Range::ConstPtr& msg){
    cout << msg->range <<endl;
    tf::StampedTransform t;
    try{
        trans->lookupTransform("/map", "/robot0_sonar_1", ros::Time(0), t);
    }catch(tf::TransformException &ex){
        cout<<"error: "<< &ex <<endl;
    }
    // cout<<"X :" <<t.getOrigin().x()<<endl;
    // cout<<"Y :" <<t.getOrigin().y()<<endl;
    double yaw, pitch, roll;
    t.getBasis().getRPY(roll, pitch, yaw);
    // cout<<"Angle: "<<yaw<<endl;

    debug++;
    cout<<debug<<endl;
    if(debug>1000){
                print_map();
                print_bmp();

        cin >> debug;
    }
    if(debug>50){
        update_map(msg->range, t.getOrigin().x(), t.getOrigin().y(), yaw);

    }
}

void sonar2_callback(const sensor_msgs::Range::ConstPtr& msg){
    cout << msg->range <<endl;
    tf::StampedTransform t;
    try{
        trans->lookupTransform("/map", "/robot0_sonar_2", ros::Time(0), t);
    }catch(tf::TransformException &ex){
        cout<<"error: "<< &ex <<endl;
    }
    // cout<<"2_X :" <<t.getOrigin().x()<<endl;
    // cout<<"2_Y :" <<t.getOrigin().y()<<endl;
    double yaw, pitch, roll;
    t.getBasis().getRPY(roll, pitch, yaw);
    // cout<<"2_Angle: "<<yaw<<endl;

    debug_2++;
    cout<<debug_2<<endl;
    if(debug_2>1000){
                print_map();
                print_bmp();

        cin >> debug;
    }
    if(debug_2>50){
        update_map(msg->range, t.getOrigin().x(), t.getOrigin().y(), yaw);

    }
}

void sonar0_callback(const sensor_msgs::Range::ConstPtr& msg){
    cout << msg->range <<endl;
    tf::StampedTransform t;
    try{
        trans->lookupTransform("/map", "/robot0_sonar_0", ros::Time(0), t);
    }catch(tf::TransformException &ex){
        cout<<"error: "<< &ex <<endl;
    }
    // cout<<"2_X :" <<t.getOrigin().x()<<endl;
    // cout<<"2_Y :" <<t.getOrigin().y()<<endl;
    double yaw, pitch, roll;
    t.getBasis().getRPY(roll, pitch, yaw);
    // cout<<"2_Angle: "<<yaw<<endl;

    debug_0++;
    cout<<debug_0<<endl;
    if(debug_0>500){
                print_map();
                print_bmp();

        cin >> debug;
    }
    if(debug_0>50){
        update_map(msg->range, t.getOrigin().x(), t.getOrigin().y(), yaw);

    }
}


int main(int argc, char ** argv){
    ros::init(argc, argv, "listener");

    init_map();


    ros::NodeHandle n;

    TransformListener listener(ros::Duration(10));
    trans = &listener;

    Subscriber sub = n.subscribe("/robot0/laser_0", 1000, callback);
    // Subscriber sub_sonar_0 = n.subscribe("/robot0/sonar_0", 1000, sonar0_callback);
    // Subscriber sub_sonar_1 = n.subscribe("/robot0/sonar_1", 1000, sonar1_callback);
    // Subscriber sub_sonar_2 = n.subscribe("/robot0/sonar_2", 1000, sonar2_callback);

    ros::spin();

    return 0;
}
