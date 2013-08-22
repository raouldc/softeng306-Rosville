/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: Shreya
 */

#include "Sheep1.h"
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

/*Constructor
 * The :RobotRobot(robot_name,argc,argv,px,py,robot_number) part at the end
 * tells the compiler to run the superclass constructor
 * It is exactly like the super(robot_name,argc,argv,px,py) call in Java
 * if you are unsure of what that means look it up in the link provided
 * http://docs.oracle.com/javase/tutorial/java/IandI/super.html
 *  */
Sheep1::Sheep1(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
	//can do extra stuff here if you like
	//this-> x = px;
	//this-> y = py;
	distance = 30;
	linear_x = -0.2;
	angular_z = 0.0;
	theta = 120.0*M_PI/180.0;
	constLinear = -0.2;
	nodeDistance = 30;
	targetTheta = 0;

}
/*destrustor
 * I have not implemented it here but you should*/
Sheep1::~Sheep1()
{
	// TODO Auto-generated destructor stub
}

/*Callback method for the robots position*/
void Sheep1::stageOdom_callback(nav_msgs::Odometry msg){
	//int x = msg.linear.x;
	px = 15 + msg.pose.pose.position.x;
	py =20 + msg.pose.pose.position.y;
	//ROS_INFO("x: %f", msg.pose.pose.orientation.x);
	//ROS_INFO("y: %f", msg.pose.pose.orientation.y);
	//ROS_INFO("W: %f", msg.pose.pose.orientation.w);
	//ROS_INFO("z: %f", msg.pose.pose.orientation.z);
	// w = 1 robot moving -x direction
	/* if(msg.pose.pose.orientation.w == 1) {
                theta = 0;
        } else if(msg.pose.pose.orientation.w >= 0.7 && msg.pose.pose.orientation.z >= 0.7) {
        // w = 0.7 and z = 0.7 robot moving -y direction
                theta = 270;
        } else if(msg.pose.pose.orientation.z <= -0.7) {
        // z = -0.7 robot moving +y direction
                theta = 90;
        } else if(msg.pose.pose.orientation.w == -1){
        // w = -1 robot moving +x direction
                theta = 3.14;
        } else {*/
	if(targetTheta == 0) {
		theta = Sheep1::computeTheta(msg.pose.pose.position.x, msg.pose.pose.position.y);
	}
}

double Sheep1::computeTheta(double x, double y) {
	double calc;
	if(x <= 0 && y >= 0) {
		if(y == 0) {
			return 0;
		} else if(x == 0) {
			return M_PI/2.0;
		}
		calc = atan(y/x);
		calc = 0 - calc;
		return calc;
	} else if(x > 0 && y > 0) {
		calc = atan(y/x);
		calc = M_PI - calc;
		return calc;
	} else if(x >= 0 && y <= 0) {
		if(y == 0) {
			return M_PI;
		} else if(x == 0) {
			return (3.0*M_PI)/2.0;
		}
		calc = atan(y/x);
		calc = M_PI - calc;
		return calc;
	} else if (x < 0 && y < 0) {
		calc = atan(y/x);
		calc = (2.0*M_PI) - calc;
		return calc;
	}

	return calc;

}

void Sheep1::stageOdom_callback1(se306_example::Custom grass){


	double tempDistanceX = grass.px - px;
	double tempDistanceY = grass.py - py;

	/*if(((grass.py) < (py+1)) && ((grass.py) > (py-1))) {
                        distance = px - (grass.px);
                }*/
	nodeDistance = sqrt((tempDistanceX*tempDistanceX) + (tempDistanceY*tempDistanceY));
	if(nodeDistance <= 0.5) {
		int i = 0;
		while(i<4000) {
			RobotNode_cmdvel.linear.x = 0.0;
			RobotNode_cmdvel.angular.z = 0.0;
			RobotNode_stage_pub.publish(RobotNode_cmdvel);
			i++;
		}
	}

	//Rotate


	//double thetaNew = atan(grass.py/grass.px);
	if(targetTheta == 0) {
		double calc = Sheep1::computeTheta(tempDistanceX, tempDistanceY);
		targetTheta = calc - theta;
	}

	//

	while(targetTheta != 0.0000) {
		if(targetTheta < 0.00000000) {
			angular_z = (2.0/18.0);
			linear_x = 0.0;
			targetTheta += 0.0209;
			//theta -= 0.0209;
			if(targetTheta > 0.000000) {
				targetTheta = 0.0;
			}
		} else if(targetTheta > 0.00000000) {
			angular_z = -(2.0/18.0);
			linear_x = 0.0;
			targetTheta -= 0.0209;
			//theta += 0.0209;
			if(targetTheta < 0.0000000) {
				targetTheta = 0.0;
			}
			//ROS_INFO("theta: %f", targetTheta);
		}
		RobotNode_cmdvel.linear.x = linear_x;
				//RobotNode_cmdvel.linear.y = 0.2;
				RobotNode_cmdvel.angular.z = angular_z;

				RobotNode_stage_pub.publish(RobotNode_cmdvel);
	}
	//ROS_INFO("%f", thetaNew);
	/*if(tempDistanceY <= 0) {
                //RobotNode_cmdvel.linear.x = .0;
                RobotNode_cmdvel.angular.z = -45.0;
                RobotNode_stage_pub.publish(RobotNode_cmdvel);
                RobotNode_cmdvel.angular.z = 0.0;
                RobotNode_stage_pub.publish(RobotNode_cmdvel);
        }*/

	//ROS_INFO("x: %f, y: %f", grass.px, grass.py);
	/*if(tempDistanceX <= 0.5 && tempDistanceY <= 0.5) {
                        if(theta == 0) {
                                nodeDistance = tempDistanceX;
                        }
                }
                nodeDistance = tempDistanceX;*/

	//ROS_INFO("name: %c", grass.robot_name.c_str());
	ROS_INFO("x: %f", grass.px);
	ROS_INFO("y: %f", grass.py);

}

void Sheep1::StageLaser_callback(sensor_msgs::LaserScan msg)
{
	int i;
	for(i=0; i<10; i++) {
		distance = msg.ranges[0];
		//ROS_INFO("distance: %f", msg.ranges[i]);
	}
	distance = msg.ranges[0];
}

void turnSheep(void) {
	//RobotNode_cmdvel
	//RobotNode_stage_pub.publish(RobotNode_cmdvel);
}

/*The run method that we use to run the robot*/
ros::NodeHandle Sheep1::run(){
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
	ros::Publisher RobotNode_stage_pub1 = n.advertise<se306_example::Custom>("sheep", 1000);

	std::stringstream ss;
	ss<<robot_name;
	//ros::Subscriber StageOdo_sub = n.subscribe<nav_msgs::Odometry>(("robot_"+ss.str()+"/message_name"),1000, R3::stageOdom_callback);
	ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>(robot_name+robot_number+"/odom",1000, &Sheep1::stageOdom_callback, this);
	ros::Subscriber stageOdo_sub1 = n.subscribe<se306_example::Custom>("grass",1000, &Sheep1::stageOdom_callback1, this);

	ros::Subscriber StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>(robot_name+robot_number+"/base_scan",1000, &Sheep1::StageLaser_callback, this);

	std::list<ros::Subscriber>::iterator it;
	it = subsList.end();
	subsList.insert(it,stageOdo_sub);

	//double th = 90*M_PI/2.0;
	ros::Rate loop_rate(10);
	nav_msgs::Odometry odom;
	geometry_msgs::Quaternion odom_quat;

	//se306_example::Grass grass;

	/*define the while loop here*/
	while (ros::ok())
	{

		// RobotNode_cmdvel.angular.x = 0.2;
		//RobotNode_cmdvel.angular.y = 0.5;
		if(distance <= 1) {
			angular_z = 45.0;
			linear_x = - (constLinear - 0.8);
		} else if(nodeDistance <= 0.5){
			linear_x = - (constLinear - 0.8);
			angular_z = 45.0;
		} else if(targetTheta != 0) {
			if(targetTheta < 0) {
				angular_z = -(2.0/18.0);
				linear_x = 0.0;
				targetTheta += 0.0209;
				theta -= 0.0209;
				if(targetTheta > 0) {
					targetTheta = 0;
				}
			} else if(targetTheta > 0) {
				angular_z = (2.0/18.0);
				linear_x = 0.0;
				targetTheta -= 0.0209;
				theta += 0.0209;
				if(targetTheta < 0) {
					targetTheta = 0;
				}
			}
		}
		else {
			linear_x = constLinear;
			angular_z = 0.0;
		}
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
	Sheep1 robot = Sheep1("Sheep",argc,argv,15,20,"One");

	robot.run();
	return 0;
}

