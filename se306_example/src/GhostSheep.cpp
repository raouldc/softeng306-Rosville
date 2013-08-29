/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: Shreya
 */

#include "GhostSheep.h"
#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include "Custom.h"

#include <sstream>
#include "math.h"
#include "Robot.h"
#include "std_msgs/Bool.h"

#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"
#include "../msg_gen/cpp/include/se306_example/FollowSheep.h"

/*Constructor
 * The :RobotRobot(robot_name,argc,argv,px,py,robot_number) part at the end
 * tells the compiler to run the superclass constructor
 * It is exactly like the super(robot_name,argc,argv,px,py) call in Java
 * if you are unsure of what that means look it up in the link provided
 * http://docs.oracle.com/javase/tutorial/java/IandI/super.html
 *  */
GhostSheep::GhostSheep(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
	//can do extra stuff here if you like
	//this-> x = px;
	//this-> y = py;
	distance = 15;
	linear_x = 0.0;
	angular_z = 0.0;
	theta = 0.0;
	width = 1;
	length = 2;
	followSheep = true;
	grassDetected = false;
	grassPX = -1;
	grassPY = -1;
	counter = 0;

}
/*destrustor
 * I have not implemented it here but you should*/
GhostSheep::~GhostSheep()
{
	// TODO Auto-generated destructor stub
}

/*Callback method for the robots position*/
void GhostSheep::stageOdom_callback(nav_msgs::Odometry msg){
	//int x = msg.linear.x;
	px = 5 + msg.pose.pose.position.x;
	py =10 + msg.pose.pose.position.y;

	double theCorrectTheta = yawFromQuaternion(msg.pose.pose.orientation.x, msg.pose.pose.orientation.y,msg.pose.pose.orientation.z,msg.pose.pose.orientation.w);
		theta = theCorrectTheta;
}

double GhostSheep::yawFromQuaternion(double x, double y, double z, double w) {
		double a = atan2((2.0*(w*z + x*y)),(1.0-2.0*(y*y+z*z)));
		a = a * 180/M_PI;
		if(a<0) {
			a = 360 +a;
		}
		return a;
}


void GhostSheep::stagecmd_callback(geometry_msgs::Twist msg){
	//int x = msg.linear.x;
	if(!followSheep) {
		linear_x = 0;
		angular_z = 0;
	} else {
		linear_x = msg.linear.x;
		angular_z = msg.angular.z;
	}


}

void GhostSheep::StageLaser_callback(sensor_msgs::LaserScan msg)
{
	distance = msg.ranges[20];
	se306_example::IdentityRequest request;
	//ROS_INFO("distance: %f", distance);
	if(distance <= 10) {
		changeFollow(true);
		if(!grassDetected) {
		linear_x = 0.0;
		angular_z = 0.0;
		changeFollow(true);
		RobotNode_cmdvel.linear.x = linear_x;
				RobotNode_cmdvel.angular.z = angular_z;

				RobotNode_stage_pub.publish(RobotNode_cmdvel);

		request.sender = robot_name;

		std::list<double> pose = calculateTheta(theta, distance);
		double x = pose.front();
		double y = pose.back();

		request.px = this->px+x+(width/2.0);
		//pose.pop_front();
		request.py = py+y+(length/2.0);
		//pose.pop_front();

		//ROS_INFO("x: %f", request.px);
		//ROS_INFO("y: %f", request.py);

		Request_pub.publish(request);

		//std_msgs::String status;
		//status.data = "stop";
		//Stop_pub.publish(status);
		ROS_INFO("Request sent");

		//ROS_INFO("theta: %f", theta);
		} else if(grassReached()) {
			linear_x = 0;
			angular_z = 0;
			counter++;
			if(counter > 50) {
				grassPX = -1;
				grassPY = -1;
				linear_x = 2.0;
				angular_z = 0;
				changeFollow(false);
				counter = 0;
			}
		} else {
			linear_x = 2.0;
			angular_z = 0.0;
		}
	}


}

bool GhostSheep::grassReached() {
	if(grassPX != -1 && grassPY != -1) {
		if(px <= grassPX+1 && px >= grassPX-1) {
			if(py <= grassPY+1 && py >= grassPY-1) {
				return true;
			}
		}
	}
	return false;
}

void GhostSheep::changeFollow(bool follow) {
	se306_example::FollowSheep status;
	if(follow) {
		followSheep = follow;

		status.follow = "follow";
		status.linear_x = linear_x;
		status.angular_z = angular_z;
		status.theta = theta;
		//ROS_INFO("theta: %f", theta);
		Follow_pub.publish(status);
		ROS_INFO("follow sent");
	} else {
		followSheep = follow;
		status.follow = "Don't follow";
		Follow_pub.publish(status);
	}

}

void GhostSheep::identityReply_callBack(se306_example::IdentityReply reply)
{
	ROS_INFO("reply received");
	if(reply.destination.compare(robot_name)==0) {
		if(reply.type.compare("Grass")==0) {
			grassDetected = true;
			grassPX = reply.px;
			grassPY = reply.py;
			ROS_INFO("Grass detected");
		}else if(reply.type.compare("sheep")==0){
		        ROS_INFO("Swarm starting");
		        /*to get swarm:
		         * calculate the distance between you and the sheep
		         * if he is travelling the same direction as you
		         * then
		         * make sure you stay some distance from the sheep at all times
		         * set your angular_z to be his angular_z and the same with
		         * linear_x
		         * if he is not travelling the same direction as you
		         * then pick the one with the greatest x value
		         * if this doesnt work then pick the one with the greates y value
		         * set this angular_z and linear_x to be yours
		         * end
		         * swarm should work.
		         * */

		}
		else  {
			ROS_INFO("Don't know what it is");
		}
	}

}

std::list<double> GhostSheep::calculateTheta(double theta, double distance)
{

        std::list<double> result;
        double calcualted_theta;
        /*there are 4 cases in which differing methods have to be used
         * case 1 : when theta is between 0 and 90
         * case 2 : when theta is between 90 and 180
         * case 3 : when theta is between 180 and 270
         * case 4 : when theta is between 270 and 360
         * then there are the obvious cases that sin and cos and stuff will
         * not work for when theta == 0 or 90 or 270 or 360*/

        /*easy cases*/
        result.clear();
        if (theta==0){
          result.push_back(distance);
          result.push_back(0.00);
        }else if(theta == 90.00){
        	//ROS_INFO("theta is 90");
          result.push_back(0.00);
          result.push_back(distance);
        }else if (theta==180){
          result.push_back(-distance);
          result.push_back(0.00);
        }else if (theta == 270){
          result.push_back(0.00);
          result.push_back(-distance);
        }
        /*case 1 : if theta is between 0 and 90 then the theta of the triangle that
         * we made will be the same theta as what is given to us*/
        else if ((theta>0)&&(theta<90)){
          calcualted_theta = theta * (M_PI/180.0);
          //x value is dist*cos(calculated_theta)
          //y value is dist*sin(calculated_theta)d
          result.push_back(distance * cos(calcualted_theta));
          result.push_back(distance * sin(calcualted_theta));

        }
        /*case 2: if the theta is between 90 and 180, then the theta of the triangle is 180-theta*/
        else if((theta>90)&&(theta<180)){
          calcualted_theta = 180 - theta;
          result.push_back(-distance * cos(calcualted_theta));
          result.push_back(distance * sin(calcualted_theta));

        }
        /*case 3 : if the theta value is between 180 and 270*/
        else if ((theta>180)&&(theta<270)){
          /*calulated theta must be theta - 180*/
          calcualted_theta = theta - 180;
          result.push_back(-distance * cos(calcualted_theta));
          result.push_back(-distance * sin(calcualted_theta));
        }
        /*case 4 : when theta is between 270 and 360*/
        else {
          /*calculated theta must be 360-theta*/
          calcualted_theta = 360 - theta;
          result.push_back(distance * cos(calcualted_theta));
          result.push_back(distance * sin(calcualted_theta));
        }

	//return result;
        return result;
}


/*The run method that we use to run the robot*/
ros::NodeHandle GhostSheep::run(){
	/*always call this line it defines the Nodehandler
	 * it also creates the callback for the postion message*/
	ros::NodeHandle n = Robot::run();
	/*To define a new message
	 * std::stringstream ss;
	 * ss<<robot_name;
	 * ros::Subscriber name_of_message = n.subscribe<nav_msgs::Odometry>("robot_"+ss.str()+"/message_name",1000, &Robot::callback_function,this);
	 *
	 * Then add to the list of subscribers
	 *   std::list<ros::Subscriber>::iterator it;
	 *   it = subsList.end();
	 *   subsList.insert(it,StageOdo_sub);
	 *
	 * Publishers are defined in exactly the same way as they are in the given examoles
	 * But you must add them to the publisherList*/
	//advertise() function will tell ROS that you want to publish on a given topic_
	//to stage
	RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>(robot_name+robot_number+"/cmd_vel",1000);
	//ros::Publisher RobotNode_stage_pub1 = n.advertise<geometry_msgs::Twist>("grass",1000);
	Request_pub = n.advertise<se306_example::IdentityRequest>("identityRequest", 1000);
	Reply_pub = n.advertise<se306_example::IdentityReply>("identityReply", 1000);
	Follow_pub = n.advertise<se306_example::FollowSheep>("SheepOne/follow", 1000);

	std::stringstream ss;
	ss<<robot_name;

	ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>(robot_name+robot_number+"/odom",1000, &GhostSheep::stageOdom_callback, this);
	ros::Subscriber stageOdo_sub1 = n.subscribe<geometry_msgs::Twist>("SheepOne/cmd_vel",1000, &GhostSheep::stagecmd_callback, this);
	//ros::Subscriber stageOdo_sub2 = n.subscribe<std_msgs::String>("SheepOne/stop",1000, &GhostSheep::stageStop_callback, this);
	ros::Subscriber StageLaser_sub3 = n.subscribe<sensor_msgs::LaserScan>(robot_name+robot_number+"/base_scan",1000, &GhostSheep::StageLaser_callback, this);
	ros::Subscriber StageOdo_sub2 = n.subscribe<se306_example::IdentityReply>("identityReply",1000, &GhostSheep::identityReply_callBack,this);

	std::list<ros::Subscriber>::iterator it;
	it = subsList.end();
	subsList.insert(it,stageOdo_sub);

	//double th = 90*M_PI/2.0;
	ros::Rate loop_rate(10);
	nav_msgs::Odometry odom;
	geometry_msgs::Quaternion odom_quat;

	//se306_example::Grass gras2

	/*define the while loop here*/
	while (ros::ok())
	{

		// RobotNode_cmdvel.angular.x = 0.2;
		//RobotNode_cmdvel.angular.y = 0.5;


		RobotNode_cmdvel.linear.x = linear_x;
		//RobotNode_cmdvel.linear.y = 0.2;
		RobotNode_cmdvel.angular.z = angular_z;

		RobotNode_stage_pub.publish(RobotNode_cmdvel);
		//RobotNode_stage_pub.publish(grass);
		//ROS_INFO("OK");
		ros::spinOnce();
		loop_rate.sleep();
	}
	return n;

}

int main(int argc, char **argv)
{
	GhostSheep robot = GhostSheep("GhostSheep",argc,argv,15,20,"One");
	robot.run();
	return 0;
}

