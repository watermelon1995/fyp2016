
#include <mrpt/gui/CDisplayWindow3D.h>
#include <mrpt/gui/CDisplayWindow.h>
#include <mrpt/opengl/CGridPlaneXY.h>
#include <mrpt/system/threads.h>
#include <mrpt/utils/CObserver.h>
#include <mrpt/gui/CDisplayWindowPlots.h>
#include "Robot.cpp"
#include <time.h>
#include <mrpt/system/datetime.h>

using namespace mrpt;
using namespace mrpt::utils;
using namespace mrpt::opengl;
using namespace mrpt::gui;
using namespace std;

mrpt::system::TTimeStamp begin_time;
mrpt::system::TTimeStamp end_time;
int front = 0;
double time_diff;

class kinObserver: public mrpt::utils::CObserver{
  protected:
    void OnEvent(const mrptEvent &e){
      if (e.isOfType<mrptEventOnDestroy>())
          cout << "[MyObserver] Event received: mrptEventOnDestroy\n";
        else if (e.isOfType<mrptEventWindowResize>())
        {
          const mrptEventWindowResize &ee = static_cast<const mrptEventWindowResize &>(e);
          cout << "[MyObserver] Resize event received from: " << ee.source_object <<", new size: " << ee.new_width << " x " << ee.new_height << "\n";
        }
        else if (e.isOfType<mrptEventWindowChar>())
        {
          const mrptEventWindowChar &ee = static_cast<const mrptEventWindowChar &>(e);
          cout << "[MyObserver] Char event received from: " << ee.source_object<< ". Char code: " <<  ee.char_code << " modif: " << ee.key_modifiers << "\n";
          switch (ee.char_code) {
            case 81:
              // Q
              begin_time = mrpt::system::now();
              front= 2;
              Robot::turn_anticlock();
              break;
            case 69:
              // E
              begin_time = mrpt::system::now();
              front= 2;
              Robot::turn_clock();
              break;
            case 87:
              // W
              begin_time = mrpt::system::now();
              cout<<"begin : "<<begin_time<<endl;
              front = 1;
              Robot::go_straight();

              // for(int i = 0;i<glob_particle.size();i++){
              //   glob_particle[i].update_particle(0.3);
              // }
              break;
            case 83:
              // S
              begin_time = mrpt::system::now();
              cout<<begin_time<<endl;
              front = 0;
              Robot::go_back();
              break;
            case 32:
              // Space
              front = -1;
              Robot::stop();

              // end_time = mrpt::system::now();
              // time_diff = mrpt::system::timeDifference(begin_time, end_time);
              // cout<<"Calculated : "<<time_diff <<endl;
              // if(front==0){
              //   for(int i = 0;i<glob_particle.size();i++){
              //     glob_particle[i].update_particle(-0.33*time_diff);
              //   }
              // }else if (front==1){
              //   for(int i = 0;i<glob_particle.size();i++){
              //     glob_particle[i].update_particle(0.33*time_diff);
              //   }
              // }



              break;
            default:
              break;
          }
        }
        else if (e.isOfType<mrptEventWindowClosed>())
        {
          const mrptEventWindowClosed &ee = static_cast<const mrptEventWindowClosed &>(e);
          cout << "[MyObserver] Window closed event received from: " << ee.source_object<< "\n";
        }
        else if (e.isOfType<mrptEventMouseDown>())
        {
          const mrptEventMouseDown &ee = static_cast<const mrptEventMouseDown&>(e);
          cout << "[MyObserver] Mouse down event received from: " << ee.source_object<< "pt: " <<ee.coords.x << "," << ee.coords.y << "\n";
          // Robot::go_straight();
          // for (int i = 0;i<glob_particle.size();i++){
          //   glob_particle[i].update_particle(-0.03);
          // }
        }
        else{
          cout << "[MyObserver] Event received: Another mrptEvent \n";
        }
    }
};

class kinGui{
  public:
    // CDisplayWindow3DPtr gui_3d;
    CDisplayWindowPtr gui_2d;
    // CDisplayWindowPlotsPtr plot;
    // COpenGLScenePtr scene;

    void init(kinObserver *k_observer){
      cout << "Setting up gui_3d windows..."<<endl;

      // gui_3d = CDisplayWindow3D::Create("kinMap GUI", 1024, 768);
      // {
      //   scene = gui_3d->get3DSceneAndLock();
      //   scene->insert( mrpt::opengl::CGridPlaneXY::Create() );
      //   gui_3d->unlockAccess3DScene();
      //   gui_3d->repaint();
      // }

      gui_2d = CDisplayWindow::Create("kinMap_2D", 1024, 768);
      // plot = CDisplayWindowPlots::Create("Debug Pose", 1024, 768);

      // gui_3d->setPos(10,10);

      gui_2d->setPos(500, 10);
      // plot->setPos(10, 10);


      // k_observer->observeBegin(*gui_3d);
      k_observer->observeBegin(*gui_2d);
      // k_observer->observeBegin(*plot);

      cout << "Setting up gui_3d windows... Done!" <<endl;

      // gui_3d->waitForKey();
      gui_2d->waitForKey();
      // plot->waitForKey();

      // while(gui->isOpen()){
      //   mrpt::system::sleep(100);
      // }
    }


    void update_gui_2d(mrpt::utils::CImagePtr img){
      gui_2d->showImage(*img);
    }

    // CDisplayWindow3D getWindows(){
    //   return (CDisplayWindow3D)gui;
    // }

    // void bindObserver(){
    //   k_observer->observeBegin(*gui);
    // }

    // void update_gui(mrpt::opengl::CSetOfObjectsPtr obj){
    //   scene->clear();
    //   scene->insert(obj);
    //   gui_3d->repaint();
    //   // obj.clear();
    // }
};
