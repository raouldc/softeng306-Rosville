/* Auto-generated by genmsg_cpp for file /home/shahhome/workspace/project1/se306_example/msg/Grass.msg */
#ifndef SE306_EXAMPLE_MESSAGE_GRASS_H
#define SE306_EXAMPLE_MESSAGE_GRASS_H
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
struct Grass_ {
  typedef Grass_<ContainerAllocator> Type;

  Grass_()
  : robot_name()
  , px(0)
  , py(0)
  {
  }

  Grass_(const ContainerAllocator& _alloc)
  : robot_name(_alloc)
  , px(0)
  , py(0)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _robot_name_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  robot_name;

  typedef int64_t _px_type;
  int64_t px;

  typedef int64_t _py_type;
  int64_t py;


  typedef boost::shared_ptr< ::se306_example::Grass_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::se306_example::Grass_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct Grass
typedef  ::se306_example::Grass_<std::allocator<void> > Grass;

typedef boost::shared_ptr< ::se306_example::Grass> GrassPtr;
typedef boost::shared_ptr< ::se306_example::Grass const> GrassConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::se306_example::Grass_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::se306_example::Grass_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace se306_example

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::se306_example::Grass_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::se306_example::Grass_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::se306_example::Grass_<ContainerAllocator> > {
  static const char* value() 
  {
    return "82eb8202e95e71eede1f9a296896b7d3";
  }

  static const char* value(const  ::se306_example::Grass_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x82eb8202e95e71eeULL;
  static const uint64_t static_value2 = 0xde1f9a296896b7d3ULL;
};

template<class ContainerAllocator>
struct DataType< ::se306_example::Grass_<ContainerAllocator> > {
  static const char* value() 
  {
    return "se306_example/Grass";
  }

  static const char* value(const  ::se306_example::Grass_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::se306_example::Grass_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string robot_name\n\
int64 px\n\
int64 py\n\
\n\
";
  }

  static const char* value(const  ::se306_example::Grass_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::se306_example::Grass_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.robot_name);
    stream.next(m.px);
    stream.next(m.py);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Grass_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::se306_example::Grass_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::se306_example::Grass_<ContainerAllocator> & v) 
  {
    s << indent << "robot_name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.robot_name);
    s << indent << "px: ";
    Printer<int64_t>::stream(s, indent + "  ", v.px);
    s << indent << "py: ";
    Printer<int64_t>::stream(s, indent + "  ", v.py);
  }
};


} // namespace message_operations
} // namespace ros

#endif // SE306_EXAMPLE_MESSAGE_GRASS_H

