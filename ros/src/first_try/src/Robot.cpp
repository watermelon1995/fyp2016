#include "SerialPort.cpp"

using namespace std;

class Position {
  public:
    float x;
    float y;
    float r;
    Position(float t_x, float t_y, float t_r){
      x = t_x;
      y = t_y;
      r = t_r;
    }
    void print(){
      cout<<"X: "<<x<<" Y: "<<y<<" R: "<<r<<endl;
    }
    // void print_to_file(ofstream ss){
    //     ss<<"X: "<<x<<" Y: "<<y<<" R: "<<r<<endl;
    // }
};


struct MOVEMENT{
  unsigned char m1_command;
  unsigned char m2_command;
  unsigned int duration;
} __attribute__((__packed__));

// MOVEMENT robot_move;


class Particle{
private:
  Position *p_position;
  float p_weight;
public:
  Particle(float x, float y, float r, float weight){
    p_position = new Position(x, y, r);
    p_weight = weight;
  }

  Position* get_pose(){
    return p_position;
  }

  void update_pose(float x, float y, float r){
    p_position->x += x + random_float(-0.02, 0.02);
    p_position->y += y + random_float(-0.02, 0.02);
    p_position->r += r + random_float(-0.02, 0.02);
  }


  float get_weight(){
    return p_weight;
  }


  void set_weight(float new_weight){
    p_weight = new_weight;
  }



  float random_float(float min, float max){
      // this  function assumes max > min, you may want
      // more robust error checking for a non-debug build
      assert(max > min);
      float random = ((float) rand()) / (float) RAND_MAX;

      // generate (in your case) a float between 0 and (4.5-.78)
      // then add .78, giving you a float between .78 and 4.5
      float range = max - min;
      return (random*range) + min;
  }
  void update_particle_yaw(float r){
    p_position->r = r;
  }


  void update_particle(float distance){
    p_position->y += (distance)+ random_float(-0.005, 0.005);
  }

  void update_particle_weight(int scan_matching_score){
    p_weight = (float)p_weight * (float) scan_matching_score;
  }

  void print(){
    cout<<"X: "<<p_position->x<<", Y: "<<p_position->y<<", R: "<<p_position->r<<endl;
    cout<<"Weight: "<<p_weight<<endl;
  }
};

vector<Particle> glob_particle;

class Robot{
  private:
    float r_length;
    float r_width;
    Position *r_position;

    int isListening;
  public:
    SerialPort *hihi;
    Robot(float length, float width){
      r_length = length;
      r_width = width;
      r_position = new Position(0.0,0.0, 0.0);
      hihi = new SerialPort("/dev/ttyUSB1");
      isListening = 0;
    }

    void set_yaw(float r){
      r_position->r = r;
    }

    void set_pose(float x, float y, float r){
      r_position->x = x;
      r_position->y = y;
      r_position->r = r;
    }

    Position* get_pose(){
      return r_position;
    }

    // void random_walk(){
    //
    // }

    void  ros_send_movement(int m1, int m2){
      // if(1<=m1<=127 && 128<=m2<=255){
        std_msgs::UInt8 robot_move_msg;
        robot_move_msg.data = (unsigned char)m1;
        glob_publish->publish(robot_move_msg);
        robot_move_msg.data = (unsigned char)m2;
        glob_publish->publish(robot_move_msg);
        cout<<"Done"<<endl;
      // }else{

      // }
    }

    void turn_anticlock(){
      MOVEMENT m;
      m.m1_command = (unsigned char)127;
      m.m2_command = (unsigned char)128;
      m.duration = (unsigned int)1000;
      unsigned char buf[sizeof(MOVEMENT)];
      memcpy(buf, &m, sizeof(MOVEMENT));
      if(hihi->open(115200)){
        for(int i = 0; i<sizeof(MOVEMENT);i++){
          cout<<i<<": "<<(int)buf[i]<<endl;
          hihi->write(buf[i]);
        }

      }else{
        cout<<"error"<<endl;
      }
    }

    void turn_clock(){
      MOVEMENT m;
      m.m1_command = (unsigned char)1;
      m.m2_command = (unsigned char)255;
      m.duration = (unsigned int)1000;
      unsigned char buf[sizeof(MOVEMENT)];
      memcpy(buf, &m, sizeof(MOVEMENT));
      // SerialPort hihi = SerialPort("/dev/ttyUSB1");
      if(hihi->open(115200)){
        for(int i = 0; i<sizeof(MOVEMENT);i++){
          cout<<i<<": "<<(int)buf[i]<<endl;
          hihi->write(buf[i]);
        }

      }else{
        cout<<"error"<<endl;
      }
    }

    void stop(){
      MOVEMENT m;
      m.m1_command = (unsigned char)0;
      m.m2_command = (unsigned char)0;
      m.duration = (unsigned int)1000;
      unsigned char buf[sizeof(MOVEMENT)];
      memcpy(buf, &m, sizeof(MOVEMENT));
      // SerialPort hihi = SerialPort("/dev/ttyUSB1");
      if(hihi->open(115200)){
        for(int i = 0; i<sizeof(MOVEMENT);i++){
          cout<<i<<": "<<(int)buf[i]<<endl;
          hihi->write(buf[i]);
        }

      }else{
        cout<<"error"<<endl;
      }
    }

    void go_back(){
      MOVEMENT m;
      m.m1_command = (unsigned char)1;
      m.m2_command = (unsigned char)128;
      m.duration = (unsigned int)1000;
      unsigned char buf[sizeof(MOVEMENT)];
      memcpy(buf, &m, sizeof(MOVEMENT));
      // SerialPort hihi = SerialPort("/dev/ttyUSB1");
      if(hihi->open(115200)){
        for(int i = 0; i<sizeof(MOVEMENT);i++){
          cout<<i<<": "<<(int)buf[i]<<endl;
          hihi->write(buf[i]);
        }

      }else{
        cout<<"error"<<endl;
      }
    }

    void go_straight(){
      MOVEMENT m;
      m.m1_command = (unsigned char)127;
      m.m2_command = (unsigned char)255;
      m.duration = (unsigned int)1000;
      unsigned char buf[sizeof(MOVEMENT)];
      memcpy(buf, &m, sizeof(MOVEMENT));
      // SerialPort hihi = SerialPort("/dev/ttyUSB1");
      // if(hihi.open(115200)){
      if(hihi->available()){
        for(int i = 0; i<sizeof(MOVEMENT);i++){
          cout<<i<<": "<<(int)buf[i]<<endl;
          hihi->write(buf[i]);
        }
      }else{
        cout<<"error sending"<<endl;
      }


      // }else{
        // cout<<"error"<<endl;
      // }
    }

    void listen_to_driver(){
      if(hihi->open(115200)){
        while(true){

          if(hihi->available()){
            cout<<(char)hihi->read();
          }
        }
      }else{
        cout<<"error"<<endl;
      }

    }
};
