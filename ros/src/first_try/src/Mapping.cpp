#include <mrpt/maps/COccupancyGridMap2D.h>


using namespace mrpt::maps;

class Mapping{
  private:
     float laser_angle_min;
     float laser_angle_max;
     float laser_angle_increment;
     float laser_range_min;
     float laser_range_max;
     float p_obj;
     float p_free;
     float max_range;

  public:
    COccupancyGridMap2DPtr m_map;
    Mapping(float map_x, float map_y){
      laser_angle_min = -3.1415;
      laser_angle_max = -3.1415;
      p_obj = 0.4;
      p_free = 0.6;
      max_range = 4.09;
      m_map = COccupancyGridMap2D::Create();
      m_map->setSize(-map_x, map_x, -map_y, map_y, 0.02);
    }
    void setting_params(float angle_min, float angle_max, float angle_interval, float range_min, float range_max){
      laser_angle_min = angle_min;
      laser_angle_max = angle_max;
      laser_angle_increment = angle_interval;
      laser_range_min = range_min;
      laser_range_max = range_max;
    }

    void update_grid(int x, int y, float prob){
        if(prob<0.5){
          // m_map->updateCell(x-1, y-1, prob);
          m_map->updateCell(x-1, y, prob);
          // m_map->updateCell(x-1, y+1, prob);
          m_map->updateCell(x, y-1, prob);
          m_map->updateCell(x, y, prob);
          m_map->updateCell(x, y+1, prob);
          // m_map->updateCell(x+1, y-1, prob);
          m_map->updateCell(x+1, y, prob);
          // m_map->updateCell(x+1, y+1, prob);
        }else{
          m_map->updateCell(x, y, prob);
        }
    }

    void update_line_free(int x1, int y1, int x2, int y2){
      int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
      dx = x2 - x1;
      dy = y2 - y1;
      dx1 = fabs(dx);
      dy1 = fabs(dy);
      px = 2 * dy1 - dx1;
      py = 2 * dx1 - dy1;
      if (dy1 <= dx1) {
          if (dx >= 0) {
              x = x1;
              y = y1;
              xe = x2;
          } else {
              x = x2;
              y = y2;
              xe = x1;
          }
          //   update_grid(x, y, 0.4);
          //   putpixel(x,y,c);
          for (i = 0; x < xe; i++) {
              x = x + 1;
              if (px < 0) {
                  px = px + 2 * dy1;
              } else {
                  if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                      y = y + 1;
                  } else {
                      y = y - 1;
                  }
                  px = px + 2 * (dy1 - dx1);
              }
              update_grid(x, y, p_free);
          }
      } else {
          if (dy >= 0) {
              x = x1;
              y = y1;
              ye = y2;
          } else {
              x = x2;
              y = y2;
              ye = y1;
          }
          //   update_grid(x, y, 0.4);
          for (i = 0; y < ye; i++) {
              y = y + 1;
              if (py <= 0) {
                  py = py + 2 * dx1;
              } else {
                  if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                      x = x + 1;
                  } else {
                      x = x - 1;
                  }
                  py = py + 2 * (dx1 - dy1);
              }

              update_grid(x, y, p_free);
          }
      }

    }

    void update_map_xv11(vector<float> laser_obs, Position *p){
      float angle = p->r + laser_angle_min;
      int start_x = m_map->x2idx(p->x);
      int start_y = m_map->y2idx(p->y);
      int end_x;
      int end_y;

      for(int i = 0; i<laser_obs.size(); i++){
        if(!isinf(laser_obs[i])){
          if(laser_obs[i]!=0.0f){
            end_x = m_map->x2idx(p->x+laser_obs[i]*cos(angle));
            end_y = m_map->x2idx(p->y+laser_obs[i]*sin(angle));
            update_grid(end_x, end_y, p_obj);
            update_line_free(start_x, start_y, end_x, end_y);
          }else{
            //Is Zero (treat as infinity)
            end_x = m_map->x2idx(p->x+laser_range_max*cos(angle));
            end_y = m_map->y2idx(p->y+laser_range_max*sin(angle));
            update_line_free(start_x, start_y, end_x, end_y);
          }
        }else{
          //Is infinity
          end_x = m_map->x2idx(p->x+laser_range_max*cos(angle));
          end_y = m_map->y2idx(p->y+laser_range_max*sin(angle));
          update_line_free(start_x, start_y, end_x, end_y);
        }

        angle = p->r+i*laser_angle_increment;
      }
    }

    void update_map(vector<float> laser_obs, Position *p){
      float angle = p->r + laser_angle_min;
      float angle_interval = (laser_angle_max*2)/laser_obs.size();
      int start_x = m_map->x2idx(p->x);
      int start_y = m_map->y2idx(p->y);
      int end_x;
      int end_y;



      for(int i = 0; i < laser_obs.size() ; i++){
        if(!isinf(laser_obs[i])){
          if(laser_obs[i]!=0.0){
            end_x = m_map->x2idx(p->x+laser_obs[i]*cos(angle));
            end_y = m_map->y2idx(p->y+laser_obs[i]*sin(angle));
            update_grid(end_x, end_y, p_obj);
            update_line_free(start_x, start_y, end_x, end_y);
          }
        }else{
          end_x = m_map->x2idx(p->x+max_range*cos(angle));
          end_y = m_map->y2idx(p->y+max_range*sin(angle));
          // update_grid(end_x, end_y, 0.4);
          update_line_free(start_x, start_y, end_x, end_y);
        }

        if(i<336){
            angle = p->r-(336-i)*angle_interval;
        }else if(i>=336){
            angle = p->r+(i-336)*angle_interval;
        }
      }
    }

    int compute_scan_matching_line(int x1, int y1, int x2, int y2){
      int line_matching_score = 0;
      int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
      dx = x2 - x1;
      dy = y2 - y1;
      dx1 = fabs(dx);
      dy1 = fabs(dy);
      px = 2 * dy1 - dx1;
      py = 2 * dx1 - dy1;
      if (dy1 <= dx1) {
          if (dx >= 0) {
              x = x1;
              y = y1;
              xe = x2;
          } else {
              x = x2;
              y = y2;
              xe = x1;
          }
          //   update_grid(x, y, 0.4);
          //   putpixel(x,y,c);
          for (i = 0; x < xe; i++) {
              x = x + 1;
              if (px < 0) {
                  px = px + 2 * dy1;
              } else {
                  if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                      y = y + 1;
                  } else {
                      y = y - 1;
                  }
                  px = px + 2 * (dy1 - dx1);
              }
              if(m_map->getCell(x,y)<0.5f){
                line_matching_score +=1;
              }
          }
      } else {
          if (dy >= 0) {
              x = x1;
              y = y1;
              ye = y2;
          } else {
              x = x2;
              y = y2;
              ye = y1;
          }
          //   update_grid(x, y, 0.4);
          for (i = 0; y < ye; i++) {
              y = y + 1;
              if (py <= 0) {
                  py = py + 2 * dx1;
              } else {
                  if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                      x = x + 1;
                  } else {
                      x = x - 1;
                  }
                  py = py + 2 * (dx1 - dy1);
              }

              if(m_map->getCell(x,y)<0.5f){
                line_matching_score +=1;
              }
          }
      }
      return line_matching_score;
    }

    int compute_scan_matching(vector<float> laser_obs, Particle *par){
      Position* par_position = par->get_pose();
      int matching_score = 0;
      float angle = par_position->r +laser_angle_min;
      int start_x = m_map->x2idx(par_position->x);
      int start_y = m_map->y2idx(par_position->y);
      int end_x;
      int end_y;

      for(int i = 0; i<laser_obs.size();i++){
        if(!isinf(laser_obs[i])){
          if(laser_obs[i]!=0.0f){
            end_x = m_map->x2idx(par_position->x+laser_obs[i]*cos(angle));
            end_y = m_map->x2idx(par_position->y+laser_obs[i]*sin(angle));
            // cout<<m_map->getCell(end_x, end_y)<<endl;
            if(m_map->getCell(end_x, end_y)>0.5f){
              // cout<<"Match"<<endl;
              matching_score +=10;
            }else{
              // matching_score -=5;
            }
            matching_score += compute_scan_matching_line(start_x, start_y, end_x, end_y);
          }else{
            //Is Zero (treat as infinity)
            end_x = m_map->x2idx(par_position->x+laser_range_max*cos(angle));
            end_y = m_map->y2idx(par_position->y+laser_range_max*sin(angle));

            matching_score += compute_scan_matching_line(start_x, start_y, end_x, end_y);
          }
        }else{
          //Is infinity
          end_x = m_map->x2idx(par_position->x+laser_range_max*cos(angle));
          end_y = m_map->y2idx(par_position->y+laser_range_max*sin(angle));

          matching_score += compute_scan_matching_line(start_x, start_y, end_x, end_y);
        }
        angle = par_position->r+i*laser_angle_increment;
      }
      par->update_particle_weight(matching_score);
      return matching_score;
    }
    // COccupancyGridMap2DPtr get_map(){
    //   return m_map;
    // }
};
