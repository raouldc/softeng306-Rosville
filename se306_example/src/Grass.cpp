/*
 * Grass.cpp
 *
 *  Created on: Aug 14, 2013
 *      Author: Kirushi Arunthavasothy
 */

#include "Grass.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Custom.h"

#include <sstream>
#include "math.h"
#include "Robot.h"
#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"

Grass::Grass(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number) {
  moistCont = 0;
  maxMoistCont = 0;
  height = 5;
  maxHeight = 20;
  angular_z = 0;
  width = 1;
  length = 2;
  soilQual = 0;
  maxSoilQuality = 10;
}

Grass::~Grass()
{
  // TODO Auto-generated destructor stub
}

void Grass::identityReply_callBack(se306_example::IdentityReply reply)
{
  // if we are the destination then process
  if (reply.destination.compare(this->robot_name) == 0) {
    ROS_INFO("reply received from [%s]", reply.destination.c_str());
  }

}
// response to an object requesting identity details
void Grass::identityRequest_callBack(se306_example::IdentityRequest request)
{
  // if we are not the sender then process the request
  if (request.sender.compare(this->robot_name) != 0) {
    ROS_INFO("Request received");
    se306_example::IdentityReply reply;

    bool result = doesIntersect(request.px, request.py);
    if (result) {
      reply.height = this->height;
      reply.sender = robot_name;
      reply.destination = request.sender;
      reply.type = "Grass";
      Reply_pub.publish(reply);
      ROS_INFO("reply sent");
      ROS_INFO("SUCCESS");
    }
  }
}

bool Grass::doesIntersect(float x, float y) {
  double leftX = px-(width/2.0);
  double rightX = px+(width/2.0);
  double top = py+(length/2.0);
  double bottom = py-(length/2.0);
  geometry_msgs::Twist angular;

  bool matchesInX=false;
  bool matchesInY=false;
  //ROS_INFO("leftX: %f, rightX: %f, top: %f, bottom: %f , currentX:%f, currentY:%f", leftX, rightX, top, bottom,px,py);
  if(leftX <= x && rightX >= x) {
    matchesInX=true;
    //ROS_INFO("Matching in X direction");
  }
  if(top >= y && bottom <= y) {
    matchesInY=true;
    //ROS_INFO("Matching in Y direction");
  }
  if (matchesInY && matchesInX) {
    angular.angular.z = 1;
    ROS_INFO("angular is %f", angular.angular.z);
    spin.publish(angular);
  }

  return matchesInY && matchesInX;
}

// CALL BACK METHOD TO DELEGATE ITS POSITION
void Grass::stageOdom_callback(nav_msgs::Odometry msg){
  this->px = this->px+msg.pose.pose.position.x;
  this->py = this->py+msg.pose.pose.position.y;
}

// CHECKS RAINFALL AND INCREMENTS/DECREMENTS MOISTURE LEVEL
void Grass::rainfall_callback(const std_msgs::String::ConstPtr& rainfall) {

  if (rainfall->data.compare("Sunny")==0) {
    moistCont = moistCont - 20;
    soilQual = soilQual - 1;
  } else if (rainfall->data.compare("Raining")==0) {
    moistCont = moistCont + 50;
    soilQual = soilQual + 1;
  }

  if (moistCont > 100 || soilQual > 10) {
    moistCont = 100;
    soilQual = 10;
  }
  if(moistCont < 0 || soilQual < 0) {
    moistCont = 0;
    soilQual = 0;
  }

  grow(moistCont);
}

// INCREASES AND DECREASES HEIGHT DEPENDING ON MOISTURE
void Grass::grow(double moisture) {

  if (moisture > 0 && soilQual > 0) {
    height = height+((moisture+soilQual))/100;
  } else if (moisture < 20 && height != 0) {
    height = height-abs((moisture+soilQual))/10;
  }
  if (height < 0) {
    height = 0;

  }
  // moistCont to 0, to stop growth
  if (height > maxHeight) {
    height = maxHeight;
    moistCont = 0;
    soilQual = 0;
  }
}


void Grass::eatenCallback(const std_msgs::String::ConstPtr& msg) {
  this->height = this->height-5;
  if (this->height < 0) {
    this->height = 0;
  }
  if (this->height < 5) {
    message = robot_name+robot_number+": Stop";
    Eaten_pub.publish(message);
  }
  ROS_INFO("New height is: %f", this->height);
}

ros::NodeHandle Grass::run(){

  ros::NodeHandle n = Robot::run();

  // LISTEN
  ros::Subscriber receive_rainfall = n.subscribe<std_msgs::String>("weather/status",1000, &Grass::rainfall_callback, this);
  ros::Subscriber requestPos = n.subscribe<se306_example::IdentityRequest>("identityRequest",1000, &Grass::identityRequest_callBack, this);
  ros::Subscriber replyPos = n.subscribe<se306_example::IdentityReply>("identityReply",1000, &Grass::identityReply_callBack,this);
  ros::Subscriber eatSub = n.subscribe<std_msgs::String>(robot_name+robot_number+"/eat",1000, &Grass::eatenCallback,this);

  // ADD SUBSCRIBERS TO LIST
  std::list<ros::Subscriber>::iterator it;
  it = subsList.end();
  subsList.insert(it,receive_rainfall);
  subsList.insert(it,requestPos);
  subsList.insert(it,replyPos);
  subsList.insert(it,eatSub);


  // TO CHANGE ANGULAR VELOCITY SET A PUBLISHER TO LISTEN ON CMD_VEL
  spin = n.advertise<geometry_msgs::Twist>(robot_name+robot_number+"/cmd_vel",1000);


  // CREATE MOISTURE AND HEIGHT TOPICS TO PUBLISH TOWARDS
  Request_pub = n.advertise<se306_example::IdentityRequest>("identityRequest", 1000);
  Reply_pub = n.advertise<se306_example::IdentityReply>("identityReply", 1000);
  Eaten_pub = n.advertise<std_msgs::String>(robot_name+robot_number+"/eaten", 1000);



  // ADD PUBLISHERS TO LIST
  std::list<ros::Publisher>::iterator iter;
  iter = pubsList.end();
  pubsList.insert(iter, spin);


  // SENDING AT 10 MESSAGES A SECOND
  ros::Rate loop_rate(10);


  // INITIALIZE VARIABLES TO PUBLISH
  std_msgs::String moisture;
  geometry_msgs::Twist angular;
  //se306_example::Custom grass;

  //  // SET ANGULAR VELOV
  //  this->angular_z = 0.2;

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  return n;
}

int main(int argc, char **argv)
{
  Grass robot = Grass("Grass",argc,argv,10,20,"One");
  robot.run();
  return 0;
}

