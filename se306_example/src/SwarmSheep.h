/* Auto-generated by genmsg_cpp for file /home/wasiq/groovy_workspace/sandbox/se306_example/msg/SwarmSheep.msg */
#ifndef SE306_EXAMPLE_MESSAGE_SWARMSHEEP_H
#define SE306_EXAMPLE_MESSAGE_SWARMSHEEP_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace se306_example
{
template <class ContainerAllocator>
struct SwarmSheep_ {
  typedef SwarmSheep_<ContainerAllocator> Type;

  SwarmSheep_()
  : abs_linear_x(0.0)
  , abs_angular_z(0.0)
  , px(0.0)
  , py(0.0)
  , angle(0.0)
  {
  }

  SwarmSheep_(const ContainerAllocator& _alloc)
  : abs_linear_x(0.0)
  , abs_angular_z(0.0)
  , px(0.0)
  , py(0.0)
  , angle(0.0)
  {
  }

  typedef double _abs_linear_x_type;
  double abs_linear_x;

  typedef double _abs_angular_z_type;
  double abs_angular_z;

  typedef double _px_type;
  double px;

  typedef double _py_type;
  double py;

  typedef double _angle_type;
  double angle;


  typedef boost::shared_ptr< ::se306_example::SwarmSheep_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::se306_example::SwarmSheep_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct SwarmSheep
typedef  ::se306_example::SwarmSheep_<std::allocator<void> > SwarmSheep;

typedef boost::shared_ptr< ::se306_example::SwarmSheep> SwarmSheepPtr;
typedef boost::shared_ptr< ::se306_example::SwarmSheep const> SwarmSheepConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::se306_example::SwarmSheep_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::se306_example::SwarmSheep_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace se306_example

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::se306_example::SwarmSheep_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::se306_example::SwarmSheep_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::se306_example::SwarmSheep_<ContainerAllocator> > {
  static const char* value() 
  {
    return "8983f0b21e77c836d3700967c5fb91b8";
  }

  static const char* value(const  ::se306_example::SwarmSheep_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x8983f0b21e77c836ULL;
  static const uint64_t static_value2 = 0xd3700967c5fb91b8ULL;
};

template<class ContainerAllocator>
struct DataType< ::se306_example::SwarmSheep_<ContainerAllocator> > {
  static const char* value() 
  {
    return "se306_example/SwarmSheep";
  }

  static const char* value(const  ::se306_example::SwarmSheep_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::se306_example::SwarmSheep_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float64 abs_linear_x\n\
float64 abs_angular_z\n\
float64 px\n\
float64 py\n\
float64 angle\n\
";
  }

  static const char* value(const  ::se306_example::SwarmSheep_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::se306_example::SwarmSheep_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::se306_example::SwarmSheep_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.abs_linear_x);
    stream.next(m.abs_angular_z);
    stream.next(m.px);
    stream.next(m.py);
    stream.next(m.angle);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct SwarmSheep_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::se306_example::SwarmSheep_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::se306_example::SwarmSheep_<ContainerAllocator> & v) 
  {
    s << indent << "abs_linear_x: ";
    Printer<double>::stream(s, indent + "  ", v.abs_linear_x);
    s << indent << "abs_angular_z: ";
    Printer<double>::stream(s, indent + "  ", v.abs_angular_z);
    s << indent << "px: ";
    Printer<double>::stream(s, indent + "  ", v.px);
    s << indent << "py: ";
    Printer<double>::stream(s, indent + "  ", v.py);
    s << indent << "angle: ";
    Printer<double>::stream(s, indent + "  ", v.angle);
  }
};


} // namespace message_operations
} // namespace ros

#endif // SE306_EXAMPLE_MESSAGE_SWARMSHEEP_H
