struct motor_command{
  int m1_command;
  int m2_command;
};


class Motor{
  public:
    float speed[256];
    Motor(){
      //Initalize speed
      for(int i = 0; i<256;i++){
        speed[i]=0;
      }
      //M1 Backward
      speed[1]=  -34.247;
      speed[5]=  -32.725;
      speed[9]=  -30.521;
      speed[13]= -28.218;
      speed[17]= -25.892;
      speed[21]= -23.633;
      speed[25]= -21.246;
      speed[28]= -19.393;
      speed[32]= -16.975;
      speed[36]= -14.455;
      speed[40]= -12.071;
      speed[44]= -9.737;
      speed[48]= -7.317;
      speed[52]= -4.861;
      speed[56]= -2.438;
      //M1 Forward
      speed[72]=   3.044;
      speed[76]=   5.283;
      speed[78]=   6.569;
      speed[80]=   7.613;
      speed[82]=   8.845;
      speed[84]=   9.904;
      speed[86]=   10.960;
      speed[88]=   12.145;
      speed[90]=   13.222;
      speed[92]=   14.455;
      speed[94]=   15.430;
      speed[96]=   16.711;
      speed[98]=   17.584;
      speed[100]=  18.880;
      speed[102]=  19.734;
      speed[104]=  21.037;
      speed[106]=  21.776;
      speed[108]=  23.191;
      speed[110]=  23.921;
      speed[112]=  25.281;
      speed[115]=  27.145;
      speed[118]=  28.595;
      speed[120]=  29.526;
      speed[122]=  31.209;
      speed[124]=  31.797;
      speed[127]=  33.000;

      //M2 Backward
      speed[128]= -31.291;
      speed[132]= -30.325;
      speed[136]= -28.560;
      speed[140]= -26.504;
      speed[144]= -24.266;
      speed[148]= -21.616;
      speed[152]= -19.489;
      speed[156]= -17.389;
      speed[160]= -15.501;
      speed[164]= -13.297;
      speed[168]= -11.125;
      speed[172]= -8.921;
      speed[176]= -6.694;
      speed[180]= -4.479;
      //M2 Forward
      speed[204]= 6.026;
      speed[206]= 8.201;
      speed[208]= 9.269;
      speed[210]= 10.398;
      speed[212]= 11.493;
      speed[214]= 12.533;
      speed[216]= 13.699;
      speed[220]= 14.772;
      speed[222]= 15.813;
      speed[224]= 16.988;
      speed[226]= 17.986;
      speed[228]= 19.156;
      speed[230]= 20.225;
      speed[232]= 21.323;
      speed[234]= 22.334;
      speed[236]= 23.491;
      speed[238]= 24.595;
      speed[240]= 25.611;
      speed[242]= 26.775;
      speed[244]= 27.687;
      speed[246]= 28.910;
      speed[248]= 30.285;
      speed[250]= 31.003;
      speed[252]= 31.840;
      speed[255]= 32.724;

      float lower_bound;
      float upper_bound;
      int start;
      int end;
      int range = 0;
      for(int i= 0; i<256;i++){
        if(i!=0 && i!= 64 && i!=192){
          if(speed[i]==0){
            start = i;
            range = 1;
            for(int j = start+1;j<256;j++){
              range++;
              if(speed[j]==0 && j!=0 && j!= 64 && j!=192){

              }else{
                upper_bound = speed[j];
                end = j-1;
                break;
              }
            }

            speed[i] = (upper_bound - lower_bound) / range + lower_bound;
            lower_bound = speed[i];
            // for(int k = start;k<=end;k++){
            //   speed[k] = (upper_bound - lower_bound) / range + lower_bound*
            // }

            // range +=-1;
          }else{
            // range = 0;
            lower_bound = speed[i];
          }
        }
      }
      // for(int i= 0;i<256;i++){
      //   std::cout<<"i: "<< i <<" speed: "<<speed[i]<<std::endl;
      // }
    }

    void apply_ratio(float ratio){
      for(int i =0;i<256;i++){
        speed[i] = speed[i]*ratio;
      }
    }


    motor_command look_up_command(float m1_speed, float m2_speed){
      motor_command m;
      if(m1_speed<0){
        for(int i = 1;i<63;i++){
          if(m1_speed >= speed[i] && m1_speed <= speed[i+1]){
            if(speed[i] - m1_speed > speed[i+1] - m1_speed){
              m.m1_command = i;
              break;
            }else{
              m.m1_command = i+1;
              break;
            }
          }
        }
      }else if(m1_speed>0){
        for(int i = 65;i<126;i++){
          if(m1_speed >= speed[i] && m1_speed <= speed[i+1]){
            if(speed[i] - m1_speed > speed[i+1] - m1_speed){
              m.m1_command = i;
              break;
            }else{
              m.m1_command = i+1;
              break;
            }
          }
        }
      }else{
        m.m1_command = 64;
      }

      if(m2_speed<0){
        for(int i = 128;i<191;i++){
          if(m2_speed >= speed[i] && m2_speed <= speed[i+1]){
            if(speed[i] - m2_speed > speed[i+1] - m2_speed){
              m.m2_command = i;
              break;
            }else{
              m.m2_command = i+1;
              break;
            }
          }
        }
      }else if(m2_speed>0){
        for(int i = 193;i<254;i++){
          if(m2_speed >= speed[i] && m2_speed <= speed[i+1]){
            if(speed[i] - m2_speed > speed[i+1] - m2_speed){
              m.m2_command = i;
              break;
            }else{
              m.m2_command = i+1;
              break;
            }
          }
        }
      }else{
        m.m2_command = 192;
      }
      std::cout<<"M1 : "<<m.m1_command<<" M2: "<<m.m2_command<<std::endl;
      return m;
    }
};
