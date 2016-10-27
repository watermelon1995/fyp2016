
using namespace std;



class kalman_filter{
  private:
      double q; //process noise covariance
      double r; //measurement noise
      double x; //value
      double p; //estimation error covariance
      double k; //kalman gain
  public:
      void init_kalman(double t_q, double t_r, double t_p, double intial_value){
        q = t_q;
        r = t_r;
        p = t_p;
        x = intial_value;
      }

      void update_kalman(double measurement){
        //prediction update
        p = p + q;
        //measurement update
        k = p / (p+r);
        x = x + k * (measurement - x);
        p = (1 - k)*p;
      }

};
