
#include <mrpt/gui/CDisplayWindow3D.h>
#include <mrpt/opengl/CGridPlaneXY.h>
#include <mrpt/system/threads.h>
#include <mrpt/utils/CObserver.h>

using namespace mrpt;
using namespace mrpt::utils;
using namespace mrpt::opengl;
using namespace mrpt::gui;
using namespace std;


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
        }
        else{
          cout << "[MyObserver] Event received: Another mrptEvent \n";
        }
    }
};

class kinGui{
  public:
    CDisplayWindow3DPtr gui;
    COpenGLScenePtr scene;

    void init(kinObserver *k_observer){
      cout << "Setting up gui windows..."<<endl;

      gui = CDisplayWindow3D::Create("kinMap GUI", 1024, 768);
      {
        scene = gui->get3DSceneAndLock();
        scene->insert( mrpt::opengl::CGridPlaneXY::Create() );
        gui->unlockAccess3DScene();
        gui->repaint();
      }

      k_observer->observeBegin(*gui);

      cout << "Setting up gui windows... Done!" <<endl;

      gui->waitForKey();

      // while(gui->isOpen()){
      //   mrpt::system::sleep(100);
      // }
    }

    // CDisplayWindow3D getWindows(){
    //   return (CDisplayWindow3D)gui;
    // }

    // void bindObserver(){
    //   k_observer->observeBegin(*gui);
    // }

    void update_gui(mrpt::opengl::CSetOfObjectsPtr obj){
      scene->clear();
      scene->insert(obj);
      gui->repaint();
      // obj.clear();
    }
};
