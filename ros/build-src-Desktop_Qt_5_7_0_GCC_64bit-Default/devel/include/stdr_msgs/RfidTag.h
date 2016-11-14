// Generated by gencpp from file stdr_msgs/RfidTag.msg
// DO NOT EDIT!


#ifndef STDR_MSGS_MESSAGE_RFIDTAG_H
#define STDR_MSGS_MESSAGE_RFIDTAG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose2D.h>

namespace stdr_msgs
{
template <class ContainerAllocator>
struct RfidTag_
{
  typedef RfidTag_<ContainerAllocator> Type;

  RfidTag_()
    : tag_id()
    , message()
    , pose()  {
    }
  RfidTag_(const ContainerAllocator& _alloc)
    : tag_id(_alloc)
    , message(_alloc)
    , pose(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _tag_id_type;
  _tag_id_type tag_id;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _message_type;
  _message_type message;

   typedef  ::geometry_msgs::Pose2D_<ContainerAllocator>  _pose_type;
  _pose_type pose;




  typedef boost::shared_ptr< ::stdr_msgs::RfidTag_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::stdr_msgs::RfidTag_<ContainerAllocator> const> ConstPtr;

}; // struct RfidTag_

typedef ::stdr_msgs::RfidTag_<std::allocator<void> > RfidTag;

typedef boost::shared_ptr< ::stdr_msgs::RfidTag > RfidTagPtr;
typedef boost::shared_ptr< ::stdr_msgs::RfidTag const> RfidTagConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::stdr_msgs::RfidTag_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::stdr_msgs::RfidTag_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::stdr_msgs::RfidTag_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::stdr_msgs::RfidTag_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::stdr_msgs::RfidTag_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::stdr_msgs::RfidTag_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::stdr_msgs::RfidTag_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::stdr_msgs::RfidTag_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::stdr_msgs::RfidTag_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e37433c890cfe140ccbef22419fae16c";
  }

  static const char* value(const ::stdr_msgs::RfidTag_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe37433c890cfe140ULL;
  static const uint64_t static_value2 = 0xccbef22419fae16cULL;
};

template<class ContainerAllocator>
struct DataType< ::stdr_msgs::RfidTag_<ContainerAllocator> >
{
  static const char* value()
  {
    return "stdr_msgs/RfidTag";
  }

  static const char* value(const ::stdr_msgs::RfidTag_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::stdr_msgs::RfidTag_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Rfid tag description\n\
\n\
string tag_id\n\
string message\n\
geometry_msgs/Pose2D pose # sensor pose, relative to the map origin\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose2D\n\
# This expresses a position and orientation on a 2D manifold.\n\
\n\
float64 x\n\
float64 y\n\
float64 theta\n\
";
  }

  static const char* value(const ::stdr_msgs::RfidTag_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::stdr_msgs::RfidTag_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.tag_id);
      stream.next(m.message);
      stream.next(m.pose);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RfidTag_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::stdr_msgs::RfidTag_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::stdr_msgs::RfidTag_<ContainerAllocator>& v)
  {
    s << indent << "tag_id: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.tag_id);
    s << indent << "message: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.message);
    s << indent << "pose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose2D_<ContainerAllocator> >::stream(s, indent + "  ", v.pose);
  }
};

} // namespace message_operations
} // namespace ros

#endif // STDR_MSGS_MESSAGE_RFIDTAG_H
