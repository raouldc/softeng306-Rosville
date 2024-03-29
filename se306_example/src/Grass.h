
/*
 * Grass.h
 *
 *  Created on: Aug 14, 2013
 *      Author: ace
 */

#ifndef GRASS_H_
#define GRASS_H_
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
#include "stdio.h"
#include "string.h"
#include "Custom.h"

#include <sstream>
#include "math.h"
#include "Robot.h"

#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"
#include "../msg_gen/cpp/include/se306_example/eatGrass.h"
#include "../msg_gen/cpp/include/se306_example/cover.h"

class Grass:Robot
{
public:
  Grass(std::string robot_name, int argc, char **argv);
  ~Grass();
  ros::NodeHandle run();
  void stageOdom_callback (nav_msgs::Odometry msg);
  void rainfall_callback (const std_msgs::String::ConstPtr& msg);
  void grow(double moisture);
  void identityReply_callBack(se306_example::IdentityReply reply);
  void identityRequest_callBack(se306_example::IdentityRequest request);
  bool doesIntersect(float x, float y);
  void eatenCallback(se306_example::eatGrass msg);
protected:
  ros::Publisher Request_pub;
  ros::Publisher Eaten_pub;
  ros::Publisher Reply_pub;
  ros::Publisher spin;
  ros::Subscriber laser;
  ros::Publisher Cover_pub;
  double soilQual;
  double maxSoilQuality;
  double maxMoistCont;
  double angular_z;
  double height;
  double moistCont;
  std::string robot_number;
  int width;
  int maxHeight;
  int length;
  std_msgs::String message;
  std::string field;
};


#endif /* GRASS_H_ */

