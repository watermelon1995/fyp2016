// #include <wx/wx.h>
// #include <wx/slider.h>
// #include "SerialPort.cpp"
// #include <iostream>
// #include <string>     // std::string, std::stoi
// #include <mrpt/maps/COccupancyGridMap2D.h>
// #include <mrpt/gui/CMyGLCanvasBase.h>
// #include <mrpt/gui/WxUtils.h>
// // #include <mrpt/utils/CMemoryStream.h>
// #include <mrpt/utils/CImage.h>
// #include <mrpt/obs/CObservation2DRangeScan.h>
// #include "ros/ros.h"
// #include "sensor_msgs/LaserScan.h"
// // #include "tf/transform_listener.h"
// #include "geometry_msgs/Pose2D.h"
// #include "new_kinGui.cpp"
// #include <pthread.h>
//
// using namespace std;
// using namespace mrpt::maps;
// using namespace mrpt::gui;
// using namespace mrpt::utils;
// using namespace ros;
//
// #define angle_min -3.1415
// #define angle_max 3.1415
// #define resolution 0.02
// #define max_range 4.09
//
// // pthread_mutex_t mutex;
//
//
// class MyApp: public wxApp
// {
// public:
//     virtual bool OnInit();
//     // virtual int OnRun();
// };
//
// class MyFrame: public wxFrame
// {
// public:
//     MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
//     wxSlider *m1_slider;
//     wxSlider *m2_slider;
//     wxTextCtrl *duration_input;
//     wxTextCtrl *serial_input;
//     // wxBitmap *map_img;
//     // wxTimer *timer_1;
//     // wxChoice *duration_selector;
//     unsigned char m1_motor;
//     unsigned char m2_motor;
// private:
//     void OnHello(wxCommandEvent& event);
//     void OnExit(wxCommandEvent& event);
//     void OnAbout(wxCommandEvent& event);
//     // void OnScroll(wxScrollEvent& event);
//     void OnCommandSend(wxCommandEvent& event);
//     // void OnPaintMap(wxPaintEvent& event);
//     // void OnPaintMap2(wxCommandEvent& event);
//     // void Render(wxDC& dc);
//     // void Render_MRPT(wxDC& dc);
//     // void OnTimerInterrupt(wxTimerEvent& event);
//     // void OnPaint(wxPaintEvent& event);
//     wxDECLARE_EVENT_TABLE();
// };
//
// const int ID_Hello    = wxNewId();
// const int ID_SLIDER_1 = wxNewId();
// const int ID_SLIDER_2 = wxNewId();
// const int ID_PANEL_1  = wxNewId();
// const int ID_DURATION_INPUT = wxNewId();
// const int ID_SEND_COMMAND_BUTTON = wxNewId();
// const int ID_SERIAL_PORT = wxNewId();
// const int ID_TIMER_1 = wxNewId();
//
// wxDEFINE_EVENT(MY_NEW_TYPE, wxCommandEvent);
//
// wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
//     EVT_MENU(ID_Hello,   MyFrame::OnHello)
//     EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
//     EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
//     EVT_BUTTON(ID_SEND_COMMAND_BUTTON, MyFrame::OnCommandSend)
// wxEND_EVENT_TABLE()
//
// // EVT_PAINT(MyFrame::OnPaintMap)
// // EVT_COMMAND(wxID_ANY, MY_NEW_TYPE, MyFrame::OnPaintMap2)
// // EVT_TIMER(ID_TIMER_1,MyFrame::OnTimerInterrupt)
//
// wxIMPLEMENT_APP(MyApp);
// //Thread
// // pthread_t laser_thread;
// //
// COccupancyGridMap2D *grid_map;
// // CMyGLCanvasBase *canvas;
// CImagePtr c_img_ptr;
// CDisplayWindowPtr gui_2d;
// CImage c_img;
// wxBitmap *gl_img;
// int debug = 0;
// // MyFrame* gl_frame;
// //
// //
// void update_grid(int x, int y, float v){
//     // if(grid_map!=NULL){
//         if(v<0.5){
//             grid_map->updateCell(x-1, y-1, v);
//             grid_map->updateCell(x-1, y, v);
//             grid_map->updateCell(x-1, y+1, v);
//             grid_map->updateCell(x, y-1, v);
//             grid_map->updateCell(x, y, v);
//             grid_map->updateCell(x, y+1, v);
//             grid_map->updateCell(x+1, y-1, v);
//             grid_map->updateCell(x+1, y, v);
//             grid_map->updateCell(x+1, y+1, v);
//         }else{
//             grid_map->updateCell(x, y, v);
//         }
//     // }
// }
//
// float distance(int x0, int x1, int y0, int y1){
//     int distance_x = (x1-x0)*(x1-x0);
//     int distance_y = (y1-y0)*(y1-y0);
//     return sqrt(distance_x+distance_y);
// }
//
// void update_line(int x1, int y1, int x2, int y2) {
//     int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
//     dx = x2 - x1;
//     dy = y2 - y1;
//     dx1 = fabs(dx);
//     dy1 = fabs(dy);
//     px = 2 * dy1 - dx1;
//     py = 2 * dx1 - dy1;
//     if (dy1 <= dx1) {
//         if (dx >= 0) {
//             x = x1;
//             y = y1;
//             xe = x2;
//         } else {
//             x = x2;
//             y = y2;
//             xe = x1;
//         }
//         //   update_grid(x, y, 0.4);
//         //   putpixel(x,y,c);
//         for (i = 0; x < xe; i++) {
//             x = x + 1;
//             if (px < 0) {
//                 px = px + 2 * dy1;
//             } else {
//                 if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
//                     y = y + 1;
//                 } else {
//                     y = y - 1;
//                 }
//                 px = px + 2 * (dy1 - dx1);
//             }
//             update_grid(x, y, 0.6);
//         }
//     } else {
//         if (dy >= 0) {
//             x = x1;
//             y = y1;
//             ye = y2;
//         } else {
//             x = x2;
//             y = y2;
//             ye = y1;
//         }
//         //   update_grid(x, y, 0.4);
//         for (i = 0; y < ye; i++) {
//             y = y + 1;
//             if (py <= 0) {
//                 py = py + 2 * dx1;
//             } else {
//                 if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
//                     x = x + 1;
//                 } else {
//                     x = x - 1;
//                 }
//                 py = py + 2 * (dx1 - dy1);
//             }
//
//             update_grid(x, y, 0.6);
//         }
//     }
// }
//
// void update_map(vector<float> ranges, float x, float y, float yaw){
//     int i;
//     float angle = yaw+angle_min;
//     float angle_interval = (angle_max*2)/ranges.size();
//     int start_x = grid_map->x2idx(x);
//     int start_y = grid_map->y2idx(y);
//     int end_x;
//     int end_y;
//     cout<<"Update_map"<<endl;
//     for(i = 0;i<ranges.size();i++){
//         if(!isinf(ranges[i])){
//             end_x = grid_map->x2idx(x+ranges[i]*cos(angle));
//             end_y = grid_map->y2idx(y+ranges[i]*sin(angle));
//             update_grid(end_x, end_y, 0.4);
//             update_line(start_x, start_y, end_x, end_y);
//         }else{
//             end_x = grid_map->x2idx(x+max_range*cos(angle));
//             end_y = grid_map->y2idx(y+max_range*sin(angle));
//             update_line(start_x, start_y, end_x, end_y);
//         }
//         if(i<336){
//             angle = yaw-(336-i)*angle_interval;
//         }else if(i>=336){
//             angle = yaw+(i-336)*angle_interval;
//         }
//     }
// }
//
// void laser_callback(const sensor_msgs::LaserScan::ConstPtr& scan_in){
//     // pthread_mutex_lock(&mutex);
//     cout<<"Callback"<<endl;
//
//     debug++;
//     // if(debug>10){
//       // cout<<"0";
//       update_map(scan_in->ranges, 15.5/2, 14.92/2, 0);
//       grid_map->getAsImage(c_img, false, false, false);
//       // gui_2d->showImage(&c_img);
//       // cout<<"1";
//       // gl_img = MRPTImage2wxBitmap(&c_img);
//       if(debug%50==0){
//
//         cout<<"map_saved"<<endl;
//
//         if(!grid_map->saveAsBitmapFile("/home/kin/Desktop/new_kin.bmp")){
//           cout<<"Error in Saving to Bitmap"<<endl;
//         }
//
//
//       }
//       // gl_img = MRPTImage2wxBitmap(*c_img_ptr);
//
//       // wxCommandEvent event(MY_NEW_TYPE);
//       // event.SetString("This is the data");
//       // wxPostEvent(gl_frame->OnPaintMap2, event);
//       // cout<<"2";
//     // }
//     // pthread_mutex_unlock(&mutex);
// }
//
//
//
// struct MOVEMENT{
//   unsigned char m1_command;
//   unsigned char m2_command;
//   unsigned int duration;
// } __attribute__((__packed__));
//
// MOVEMENT robot_move;
//
//
//
// //Implement general function
// bool send_movement(MOVEMENT m, const char* portName){
//
//   // MOVEMENT *ptr;
//   // ptr = &m;
//   unsigned char buf[sizeof(MOVEMENT)];
//   memcpy(buf, &m, sizeof(MOVEMENT));
//
//   SerialPort hi = SerialPort(portName);
//
//
//
//   if(hi.open(115200)){
//       cout<<"Port opened successfully"<<endl;
//       // hi.write(103);
//       for(int j = 0;j<10;j++){
//         for(int i = 0;i<sizeof(MOVEMENT);i++){
//           cout<<i<<": " <<(int)buf[i]<<endl;
//           hi.write(buf[i]);
//         }
//       }
//
//       // for(int i = 0;i<sizeof(MOVEMENT);i++){
//       //   cout<<i<<": " <<(int)buf[i]<<endl;
//       //   hi.write(buf[i]);
//       // }
//       // for(int i = 0;i<sizeof(MOVEMENT);i++){
//       //   cout<<i<<": " <<(int)buf[i]<<endl;
//       //   hi.write(buf[i]);
//       // }
//       // for(int i = 0;i<sizeof(MOVEMENT);i++){
//       //   cout<<i<<": " <<(int)buf[i]<<endl;
//       //   hi.write(buf[i]);
//       // }
//       // for(int i = 0;i<sizeof(MOVEMENT);i++){
//       //   cout<<i<<": " <<(int)buf[i]<<endl;
//       //   hi.write(buf[i]);
//       // }
//       cout<<"Write to serial Done!"<<endl;
//   }else{
//       cout<<"Port opened Failed"<<endl;
//       return false;
//   }
//   // hi.close();
//   return true;
// }
//
// void map_get_img(){
//
// }
//
// void *start_laser_thread(void *ptr){
//     c_img =  mrpt::utils::CImage();
//     //
//     COccupancyGridMap2D temp = COccupancyGridMap2D(0.0, 15.5, 0.0, 14.92, 0.02);
//     grid_map  = &temp;
//
//     // gui_2d = CDisplayWindow::Create("kinMap_2D", 1024, 768);
//     // gui_2d->setPos(500, 10);
//     int argc = 1;
//     char  *argv[]={"/home/kin/fyp2016/ros/devel/lib/first_try/controller", NULL};
//     cout<<"Initalizing ROS"<<endl;
//     ros::init(argc, argv, "new_kinMap");
//     ros::NodeHandle n;
//     ros::Subscriber laser_sub = n.subscribe("/scan", 1000, laser_callback);
//     ros::spin();
//     // gui_2d->waitForKey();
// }
// //
// //
// // void *start_gui_thread(void *ptr){
// //     MyFrame *frame = new MyFrame( "Autonomous Robot Controller", wxPoint(50, 50), wxSize(1280, 960) );
// //     // gl_frame = frame;
// //     frame->Show( true );
// //     //
// //     gl_img = frame->map_img;
// // }
// //Implement myapp function
// bool MyApp::OnInit()
// {
//     // wxInitAllImageHandlers();
//     // c_img_ptr = mrpt::utils::CImage::Create();
//
//
//     //
//     // int argc = 1;
//     // char  *argv[]={"/home/kin/fyp2016/ros/devel/lib/first_try/controller", NULL};
//     // cout<<"Initalizing ROS"<<endl;
//     // ros::init(argc, argv, "new_kinMap");
//
//     // ros::spin();
//
//
//     MyFrame *frame = new MyFrame( "Autonomous Robot Controller", wxPoint(50, 50), wxSize(1000, 600) );
//     // gl_frame = frame;
//     frame->Show( true );
//     // //
//     // gl_img = frame->map_img;
//     // pthread_t gui_thread;
//     // int ret;
//     // ret =  pthread_create(&gui_thread, NULL, &start_gui_thread, NULL);
//     // if(ret!=0){
//     //   cout<<"Error: Failed to create thread for gui"<<endl;
//     // }
//
//     // pthread_t laser_thread;
//     // int ret;
//     // ret =  pthread_create(&laser_thread, NULL, &start_laser_thread, NULL);
//     // if(ret!=0){
//     //   cout<<"Error: Failed to create thread for laser"<<endl;
//     // }
//
//     // int argc = 1;
//     // char  *argv[]={"/home/kin/fyp2016/ros/devel/lib/first_try/controller", NULL};
//     // cout<<"Initalizing ROS"<<endl;
//     // ros::init(argc, argv, "new_kinMap");
//     // ros::NodeHandle n;
//     // ros::Subscriber laser_sub = n.subscribe("/scan", 1000, laser_callback);
//     // // Subscriber sub_sonar_0 = n.subscribe("/robot0/sonar_0", 1000, sonar0_callback);
//     // // Subscriber sub_sonar_1 = n.subscribe("/robot0/sonar_1", 1000, sonar1_callback);
//     // ros::spin();
//
//     cout<<"MyApp Init Done!"<<endl;
//
//     return true;
// }
//
// // int  MyApp::OnRun(){
// //   ros::NodeHandle n;
// //
// //   // TransformListener listener(ros::Duration(5));
// //   // trans = &listener;
// //   // cout<<"de";
// //   ros::Subscriber laser_sub = n.subscribe("/scan", 1000, laser_callback);
// //   // ros::spinOnce();
// //   return wxApp::OnRun();
// // }
// //Implement myframe function
//
//
//
// MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
//         : wxFrame(NULL, wxID_ANY, title, pos, size)
// {
//
//     // wxFrame *frame = new wxFrame(this, wxID_ANY, wxT("Hello wxDC"), wxPoint(50,50), wxSize(800,600));
//
//
//     wxPanel *panel = new wxPanel(this, ID_PANEL_1);
//     // map_img = MRPTImage2wxBitmap(*c_img_ptr);
//     // grid_map->getAsImage(*c_img_ptr, false, false, false);
//     //
//     //
//     // map_img = new wxBitmap();
//
//     // map_img->LoadFile("/home/kin/Desktop/debug.bmp", wxBITMAP_DEFAULT_TYPE );
//
//     // timer_1 = new wxTimer(this, ID_TIMER_1);
//     // timer_1->Start(2000);
//
//     // canvas = new CMyGLCanvasBase( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize );
//
//     // canvas->m_openGLScene->insert( mrpt::opengl::CGridPlaneXY::Create(-100,100,-100,100,0,5) );
//
//     wxButton *sendCommand = new wxButton(this, ID_SEND_COMMAND_BUTTON, "Send MOVEMENT Comand", wxPoint(700, 100));
//
//     // wxButton *stopCommand = new wxButton(this, ID_SEND_COMMAND_BUTTON, "Send STOP Comand", wxPoint(700, 100));
//
//     m1_slider = new wxSlider(this, ID_SLIDER_1, 64 , 1, 127, wxPoint(100, 100), wxSize(500, 100), wxSL_HORIZONTAL|wxSL_VALUE_LABEL);
//
//     m2_slider = new wxSlider(this, ID_SLIDER_2, 192 , 128, 255, wxPoint(100, 200), wxSize(500, 100), wxSL_HORIZONTAL|wxSL_VALUE_LABEL);
//
//     duration_input = new  wxTextCtrl(this, ID_DURATION_INPUT,"",wxPoint(700, 200), wxDefaultSize);
//     serial_input = new  wxTextCtrl(this, ID_SERIAL_PORT,"",wxPoint(700, 300), wxDefaultSize);
//     serial_input->AppendText("/dev/ttyUSB1");
//     //Button Event
//     // Connect(ID_SEND_COMMAND_BUTTON, )
//
//
//
//     //Slider Event
//     // Connect(ID_SLIDER_1, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(MyFrame::OnScroll));
//     // Connect(ID_SLIDER_2, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(MyFrame::OnScroll));
//
//     // wxFlexGridSizer* FlexGridSizer5;
//
//     // FlexGridSizer5 = new wxFlexGridSizer(2, 2, 0, 0);
//     wxMenu *menuFile = new wxMenu;
//     menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
//                      "Help string shown in status bar for this menu item");
//     menuFile->AppendSeparator();
//     menuFile->Append(wxID_EXIT);
//     wxMenu *menuHelp = new wxMenu;
//     menuHelp->Append(wxID_ABOUT);
//     wxMenuBar *menuBar = new wxMenuBar;
//     menuBar->Append( menuFile, "&File" );
//     menuBar->Append( menuHelp, "&Help" );
//     SetMenuBar( menuBar );
//     CreateStatusBar();
//     SetStatusText( "Welcome to wxWidgets!" );
// }
// void MyFrame::OnExit(wxCommandEvent& event)
// {
//     Close( true );
// }
// void MyFrame::OnAbout(wxCommandEvent& event)
// {
//     wxMessageBox( "This is a wxWidgets' Hello world sample",
//                   "About Hello World", wxOK | wxICON_INFORMATION );
// }
// void MyFrame::OnHello(wxCommandEvent& event)
// {
//     SerialPort hi = SerialPort("/dev/ttyUSB0");
//     if(hi.open(115200)){
//       wxLogMessage("Port opened successfully");
//       while(1){
//           hi.write(12);
//           sleep(1);
//       }
//     }
//     else{
//       wxLogMessage("Failed to open port!");
//
//     }
//     // wxLogMessage("Hello world from wxWidgets!");
//     hi.close();
// }
//
// // void MyFrame::OnScroll(wxScrollEvent& event){
// //   m1_motor = (unsigned char)m1_slider->GetValue();
// //   m2_motor = (unsigned char)m2_slider->GetValue();
// //   // cout<<"M1_motor: " <<(int)m1_motor<<endl;
// //   // cout<<"M2_motor: " <<(int)m2_motor<<endl;
// // }
//
// void MyFrame::OnCommandSend(wxCommandEvent& event){
//   robot_move.m1_command = (unsigned char)m1_slider->GetValue();
//   robot_move.m2_command = (unsigned char)m2_slider->GetValue();
//   long temp;
//   duration_input->GetValue().ToLong(&temp, 10);
//   robot_move.duration = (unsigned int)temp;
//   // cout<<"M1_motor: " <<(int)robot_move.m1_command<<endl;
//   // cout<<"M2_motor: " <<(int)robot_move.m2_command<<endl;
//   // cout<<"Duration: " <<robot_move.duration<<endl;
//   // SerialPort hi = SerialPort("/dev/ttyUSB0");
//   // if(hi.open(9600)){
//
//   // }
//   send_movement(robot_move, serial_input->GetValue());
//   // hi.close();
// }
//
//
// // void MyFrame::OnPaintMap(wxPaintEvent& event){
// //   // cout<<"Paint event recieved"<<endl;
// //   wxPaintDC dc(this);
// //   MyFrame::Render(dc);
// // }
// //
// // void MyFrame::Render(wxDC&  dc){
// //   // grid_map->getAsImage(*c_img_ptr, false, false, false);
// //   // map_img = MRPTImage2wxBitmap(*c_img_ptr);
// //   dc.DrawBitmap(*map_img, 0, 0, false);
// // }
// //
// // void MyFrame::OnPaintMap2(wxCommandEvent& event){
// //   wxPaintDC dc(this);
// //   MyFrame::Render_MRPT(dc);
// // }
// //
// //
// // void MyFrame::Render_MRPT(wxDC&  dc){
// //   // pthread_mutex_lock(&mutex);
// //   //
// //   // grid_map->getAsImage(c_img, false, false, false);
// //   // c_img.saveToFile("/home/kin/Desktop/123.bmp");
// //   // cout<<"here?1";
// //   // map_img = MRPTImage2wxBitmap(&c_img);
// //   // cout<<"here?2";
// //   // dc.DrawBitmap(*map_img, 0, 0, false);
// //   // pthread_mutex_unlock(&mutex);
// // }
// //
// // void MyFrame::OnTimerInterrupt(wxTimerEvent& event){
// //   // cout<<"ROS Spin"<<endl;
// //   // ros::spinOnce();
// //
// //   // pthread_mutex_lock(&mutex);
// //   // cout<<"GUI timer interrupt"<<endl;
// //   // if(grid_map!=NULL&&debug>20){
// //   //   wxPaintDC dc(this);
// //   //   MyFrame::Render_MRPT(dc);
// //   // }
// //   // pthread_mutex_unlock(&mutex);
// // }
// // void MyFrame::OnPaint(wxPaintEvent& event){
// //
// // }
