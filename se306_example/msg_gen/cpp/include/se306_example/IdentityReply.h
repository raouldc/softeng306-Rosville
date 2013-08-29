/* Auto-generated by genmsg_cpp for file /home/george/groovy_workspace/sandbox/se306_example/msg/IdentityReply.msg */
#ifndef SE306_EXAMPLE_MESSAGE_IDENTITYREPLY_H
#define SE306_EXAMPLE_MESSAGE_IDENTITYREPLY_H
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
struct IdentityReply_ {
  typedef IdentityReply_<ContainerAllocator> Type;

  IdentityReply_()
  : sender()
  , destination()
  , type()
  , height(0)
  {
  }

  IdentityReply_(const ContainerAllocator& _alloc)
  : sender(_alloc)
  , destination(_alloc)
  , type(_alloc)
  , height(0)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _sender_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  sender;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _destination_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  destination;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _type_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  type;

  typedef int32_t _height_type;
  int32_t height;


  typedef boost::shared_ptr< ::se306_example::IdentityReply_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::se306_example::IdentityReply_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct IdentityReply
typedef  ::se306_example::IdentityReply_<std::allocator<void> > IdentityReply;

typedef boost::shared_ptr< ::se306_example::IdentityReply> IdentityReplyPtr;
typedef boost::shared_ptr< ::se306_example::IdentityReply const> IdentityReplyConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::se306_example::IdentityReply_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::se306_example::IdentityReply_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace se306_example

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::se306_example::IdentityReply_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::se306_example::IdentityReply_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::se306_example::IdentityReply_<ContainerAllocator> > {
  static const char* value() 
  {
    return "16415d0f14ac4b91c2997429aeb65a9e";
  }

  static const char* value(const  ::se306_example::IdentityReply_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x16415d0f14ac4b91ULL;
  static const uint64_t static_value2 = 0xc2997429aeb65a9eULL;
};

template<class ContainerAllocator>
struct DataType< ::se306_example::IdentityReply_<ContainerAllocator> > {
  static const char* value() 
  {
    return "se306_example/IdentityReply";
  }

  static const char* value(const  ::se306_example::IdentityReply_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::se306_example::IdentityReply_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string sender\n\
string destination\n\
string type\n\
int32 height\n\
\n\
";
  }

  static const char* value(const  ::se306_example::IdentityReply_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::se306_example::IdentityReply_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.sender);
    stream.next(m.destination);
    stream.next(m.type);
    stream.next(m.height);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct IdentityReply_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::se306_example::IdentityReply_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::se306_example::IdentityReply_<ContainerAllocator> & v) 
  {
    s << indent << "sender: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.sender);
    s << indent << "destination: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.destination);
    s << indent << "type: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.type);
    s << indent << "height: ";
    Printer<int32_t>::stream(s, indent + "  ", v.height);
  }
};


} // namespace message_operations
} // namespace ros

#endif // SE306_EXAMPLE_MESSAGE_IDENTITYREPLY_H

