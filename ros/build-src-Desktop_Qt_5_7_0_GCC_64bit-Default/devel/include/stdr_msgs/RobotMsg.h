// Generated by gencpp from file stdr_msgs/RobotMsg.msg
// DO NOT EDIT!


#ifndef STDR_MSGS_MESSAGE_ROBOTMSG_H
#define STDR_MSGS_MESSAGE_ROBOTMSG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose2D.h>
#include <stdr_msgs/FootprintMsg.h>
#include <stdr_msgs/LaserSensorMsg.h>
#include <stdr_msgs/SonarSensorMsg.h>
#include <stdr_msgs/RfidSensorMsg.h>
#include <stdr_msgs/CO2SensorMsg.h>
#include <stdr_msgs/SoundSensorMsg.h>
#include <stdr_msgs/ThermalSensorMsg.h>
#include <stdr_msgs/KinematicMsg.h>

namespace stdr_msgs
{
template <class ContainerAllocator>
struct RobotMsg_
{
  typedef RobotMsg_<ContainerAllocator> Type;

  RobotMsg_()
    : initialPose()
    , footprint()
    , laserSensors()
    , sonarSensors()
    , rfidSensors()
    , co2Sensors()
    , soundSensors()
    , thermalSensors()
    , kinematicModel()  {
    }
  RobotMsg_(const ContainerAllocator& _alloc)
    : initialPose(_alloc)
    , footprint(_alloc)
    , laserSensors(_alloc)
    , sonarSensors(_alloc)
    , rfidSensors(_alloc)
    , co2Sensors(_alloc)
    , soundSensors(_alloc)
    , thermalSensors(_alloc)
    , kinematicModel(_alloc)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::Pose2D_<ContainerAllocator>  _initialPose_type;
  _initialPose_type initialPose;

   typedef  ::stdr_msgs::FootprintMsg_<ContainerAllocator>  _footprint_type;
  _footprint_type footprint;

   typedef std::vector< ::stdr_msgs::LaserSensorMsg_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::stdr_msgs::LaserSensorMsg_<ContainerAllocator> >::other >  _laserSensors_type;
  _laserSensors_type laserSensors;

   typedef std::vector< ::stdr_msgs::SonarSensorMsg_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::stdr_msgs::SonarSensorMsg_<ContainerAllocator> >::other >  _sonarSensors_type;
  _sonarSensors_type sonarSensors;

   typedef std::vector< ::stdr_msgs::RfidSensorMsg_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::stdr_msgs::RfidSensorMsg_<ContainerAllocator> >::other >  _rfidSensors_type;
  _rfidSensors_type rfidSensors;

   typedef std::vector< ::stdr_msgs::CO2SensorMsg_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::stdr_msgs::CO2SensorMsg_<ContainerAllocator> >::other >  _co2Sensors_type;
  _co2Sensors_type co2Sensors;

   typedef std::vector< ::stdr_msgs::SoundSensorMsg_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::stdr_msgs::SoundSensorMsg_<ContainerAllocator> >::other >  _soundSensors_type;
  _soundSensors_type soundSensors;

   typedef std::vector< ::stdr_msgs::ThermalSensorMsg_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::stdr_msgs::ThermalSensorMsg_<ContainerAllocator> >::other >  _thermalSensors_type;
  _thermalSensors_type thermalSensors;

   typedef  ::stdr_msgs::KinematicMsg_<ContainerAllocator>  _kinematicModel_type;
  _kinematicModel_type kinematicModel;




  typedef boost::shared_ptr< ::stdr_msgs::RobotMsg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::stdr_msgs::RobotMsg_<ContainerAllocator> const> ConstPtr;

}; // struct RobotMsg_

typedef ::stdr_msgs::RobotMsg_<std::allocator<void> > RobotMsg;

typedef boost::shared_ptr< ::stdr_msgs::RobotMsg > RobotMsgPtr;
typedef boost::shared_ptr< ::stdr_msgs::RobotMsg const> RobotMsgConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::stdr_msgs::RobotMsg_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::stdr_msgs::RobotMsg_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace stdr_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/opt/ros/indigo/share/nav_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'stdr_msgs': ['/home/kin/fyp2016/ros/src/stdr_simulator/stdr_msgs/msg', '/home/kin/fyp2016/ros/build-src-Desktop_Qt_5_7_0_GCC_64bit-Default/devel/share/stdr_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::stdr_msgs::RobotMsg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::stdr_msgs::RobotMsg_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::stdr_msgs::RobotMsg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::stdr_msgs::RobotMsg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::stdr_msgs::RobotMsg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::stdr_msgs::RobotMsg_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::stdr_msgs::RobotMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ffa138f7f6a9c979acfb84d2c8e73a39";
  }

  static const char* value(const ::stdr_msgs::RobotMsg_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xffa138f7f6a9c979ULL;
  static const uint64_t static_value2 = 0xacfb84d2c8e73a39ULL;
};

template<class ContainerAllocator>
struct DataType< ::stdr_msgs::RobotMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "stdr_msgs/RobotMsg";
  }

  static const char* value(const ::stdr_msgs::RobotMsg_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::stdr_msgs::RobotMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geometry_msgs/Pose2D initialPose\n\
\n\
stdr_msgs/FootprintMsg footprint\n\
\n\
stdr_msgs/LaserSensorMsg[] laserSensors\n\
stdr_msgs/SonarSensorMsg[] sonarSensors\n\
stdr_msgs/RfidSensorMsg[] rfidSensors\n\
stdr_msgs/CO2SensorMsg[] co2Sensors\n\
stdr_msgs/SoundSensorMsg[] soundSensors\n\
stdr_msgs/ThermalSensorMsg[] thermalSensors\n\
\n\
stdr_msgs/KinematicMsg kinematicModel\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose2D\n\
# This expresses a position and orientation on a 2D manifold.\n\
\n\
float64 x\n\
float64 y\n\
float64 theta\n\
================================================================================\n\
MSG: stdr_msgs/FootprintMsg\n\
geometry_msgs/Point[] points\n\
float32 radius # for circular footprints\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: stdr_msgs/LaserSensorMsg\n\
# Laser Sensor description\n\
float32 maxAngle\n\
float32 minAngle\n\
float32 maxRange\n\
float32 minRange\n\
int32 numRays\n\
\n\
stdr_msgs/Noise noise\n\
\n\
float32 frequency\n\
\n\
string frame_id\n\
geometry_msgs/Pose2D pose # sensor pose, relative to robot center\n\
\n\
================================================================================\n\
MSG: stdr_msgs/Noise\n\
bool noise\n\
float32 noiseMean\n\
float32 noiseStd\n\
\n\
================================================================================\n\
MSG: stdr_msgs/SonarSensorMsg\n\
# Rfid sensor description\n\
float32 maxRange\n\
float32 minRange\n\
float32 coneAngle\n\
\n\
float32 frequency\n\
stdr_msgs/Noise noise\n\
\n\
string frame_id\n\
geometry_msgs/Pose2D pose # sensor pose, relative to robot center\n\
\n\
================================================================================\n\
MSG: stdr_msgs/RfidSensorMsg\n\
# Rfid sensor description\n\
float32 maxRange\n\
float32 angleSpan\n\
float32 signalCutoff\n\
\n\
float32 frequency\n\
\n\
string frame_id\n\
geometry_msgs/Pose2D pose # sensor pose, relative to robot center\n\
\n\
================================================================================\n\
MSG: stdr_msgs/CO2SensorMsg\n\
# Sensor description\n\
\n\
float32 maxRange\n\
float32 frequency\n\
string frame_id\n\
\n\
# sensor pose, relative to robot center\n\
geometry_msgs/Pose2D pose \n\
\n\
================================================================================\n\
MSG: stdr_msgs/SoundSensorMsg\n\
# Sensor description\n\
\n\
float32 maxRange\n\
float32 frequency\n\
float32 angleSpan\n\
string frame_id\n\
\n\
# sensor pose, relative to robot center\n\
geometry_msgs/Pose2D pose \n\
\n\
================================================================================\n\
MSG: stdr_msgs/ThermalSensorMsg\n\
# Sensor description\n\
\n\
float32 maxRange\n\
float32 frequency\n\
float32 angleSpan\n\
string frame_id\n\
\n\
# sensor pose, relative to robot center\n\
geometry_msgs/Pose2D pose \n\
\n\
================================================================================\n\
MSG: stdr_msgs/KinematicMsg\n\
# Container for the kinematic model parameters. The parameters selected/\n\
# are quite general. For a more accurate motion model a per-kinematic model\n\
# approach should be followed.\n\
# Parameters are in the form a_C_D, where C is affected by D.\n\
# ux is the linear speed\n\
# uy is the lateral speed (for omni vehicles)\n\
# w is the angular speed\n\
# g is a cofficient that directly affects the angular speed\n\
# For more information check the MotionController::sampleVelocities function.\n\
\n\
string type\n\
float32 a_ux_ux\n\
float32 a_ux_uy\n\
float32 a_ux_w\n\
float32 a_uy_ux\n\
float32 a_uy_uy\n\
float32 a_uy_w\n\
float32 a_w_ux\n\
float32 a_w_uy\n\
float32 a_w_w\n\
float32 a_g_ux\n\
float32 a_g_uy\n\
float32 a_g_w\n\
";
  }

  static const char* value(const ::stdr_msgs::RobotMsg_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::stdr_msgs::RobotMsg_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.initialPose);
      stream.next(m.footprint);
      stream.next(m.laserSensors);
      stream.next(m.sonarSensors);
      stream.next(m.rfidSensors);
      stream.next(m.co2Sensors);
      stream.next(m.soundSensors);
      stream.next(m.thermalSensors);
      stream.next(m.kinematicModel);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RobotMsg_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::stdr_msgs::RobotMsg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::stdr_msgs::RobotMsg_<ContainerAllocator>& v)
  {
    s << indent << "initialPose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose2D_<ContainerAllocator> >::stream(s, indent + "  ", v.initialPose);
    s << indent << "footprint: ";
    s << std::endl;
    Printer< ::stdr_msgs::FootprintMsg_<ContainerAllocator> >::stream(s, indent + "  ", v.footprint);
    s << indent << "laserSensors[]" << std::endl;
    for (size_t i = 0; i < v.laserSensors.size(); ++i)
    {
      s << indent << "  laserSensors[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::stdr_msgs::LaserSensorMsg_<ContainerAllocator> >::stream(s, indent + "    ", v.laserSensors[i]);
    }
    s << indent << "sonarSensors[]" << std::endl;
    for (size_t i = 0; i < v.sonarSensors.size(); ++i)
    {
      s << indent << "  sonarSensors[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::stdr_msgs::SonarSensorMsg_<ContainerAllocator> >::stream(s, indent + "    ", v.sonarSensors[i]);
    }
    s << indent << "rfidSensors[]" << std::endl;
    for (size_t i = 0; i < v.rfidSensors.size(); ++i)
    {
      s << indent << "  rfidSensors[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::stdr_msgs::RfidSensorMsg_<ContainerAllocator> >::stream(s, indent + "    ", v.rfidSensors[i]);
    }
    s << indent << "co2Sensors[]" << std::endl;
    for (size_t i = 0; i < v.co2Sensors.size(); ++i)
    {
      s << indent << "  co2Sensors[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::stdr_msgs::CO2SensorMsg_<ContainerAllocator> >::stream(s, indent + "    ", v.co2Sensors[i]);
    }
    s << indent << "soundSensors[]" << std::endl;
    for (size_t i = 0; i < v.soundSensors.size(); ++i)
    {
      s << indent << "  soundSensors[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::stdr_msgs::SoundSensorMsg_<ContainerAllocator> >::stream(s, indent + "    ", v.soundSensors[i]);
    }
    s << indent << "thermalSensors[]" << std::endl;
    for (size_t i = 0; i < v.thermalSensors.size(); ++i)
    {
      s << indent << "  thermalSensors[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::stdr_msgs::ThermalSensorMsg_<ContainerAllocator> >::stream(s, indent + "    ", v.thermalSensors[i]);
    }
    s << indent << "kinematicModel: ";
    s << std::endl;
    Printer< ::stdr_msgs::KinematicMsg_<ContainerAllocator> >::stream(s, indent + "  ", v.kinematicModel);
  }
};

} // namespace message_operations
} // namespace ros

#endif // STDR_MSGS_MESSAGE_ROBOTMSG_H
