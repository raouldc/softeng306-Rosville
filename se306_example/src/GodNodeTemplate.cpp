#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//-----Publisher variables
//PublisherDeclaration
//-----[END]Publisher variables

//-----Subscriber callbacks
//subscriberCallBacksMethods
//-----[END] Subscriber callbacks

ros::Publisher Weather_publisher;//To Sheep

int main(int argc, char **argv)
{

  ros::init(argc, argv, "GodNode");

  //NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

  // Advertisements.....
  //RegisterPublisher


  //Setting up subscribers...
  //SetupSubscribers

  Weather_publisher = n.advertise<std_msgs::String>("weather/status", 1000); //To SheepOne

  ros::Rate loop_rate(10);

  //a count of howmany messages we have sent
  int count = 0;

  ////messages
  //velocity of this RobotNode
  std_msgs::String status;
  status.data="Sunny";
  while (ros::ok())
  {
    if (count%5 == 0) {
      if (status.data.compare("Sunny") == 0) {
        status.data = "Raining";
        ROS_INFO("rainy");
      } else {
        status.data = "Sunny";
        ROS_INFO("sunny");
      }
    }

    ros::spinOnce();

    loop_rate.sleep();
    count=count+1;
  }

  return 0;

}
