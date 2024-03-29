/*
 * R3.h
 *
 *  Created on: 12/08/2013
 *      Author: wasiq
 */

#ifndef R3_H_
#define R3_H_
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>


#include <sstream>
#include "math.h"
#include "Robot.h"
#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"

class Poop:Robot
{
public:
  double distance;
  double initialX;
  double initialY;
  std::string poopOwner;
  geometry_msgs::Twist poopVel;
  double linear_x;
  double constLinear;
  double angular_z;
  double theta;
  double nodeDistance;
  double targetTheta;
  int width;
  int length;
  ros::Publisher publishPoop;
  bool doStop;

  ros::Subscriber sheepPos;
  ros::Subscriber sheepVel;
  ros::Subscriber poopReq;


  void StageLaser_callback(sensor_msgs::LaserScan msg);
  Poop(std::string robot_name, int argc, char **argv);
  ~Poop();
  ros::NodeHandle run();
  void stageOdom_callback (nav_msgs::Odometry msg);
  void setPoop (geometry_msgs::Twist msg);
  void stageStop_callback (std_msgs::String msg);
  void requestPoop(const std_msgs::String::ConstPtr& request);

};

#endif /* R3_H_ */
