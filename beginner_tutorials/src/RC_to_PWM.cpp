#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include <ros/ros.h>

#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Int16.h>

int Arr[2];
void arrayCallback(const std_msgs::Int16MultiArray::ConstPtr& array); 

int main(int argc, char **argv){
	ros::init(argc, argv, "RC_to_PWM");
	ros::NodeHandle nh;

    ros::Publisher PWMs=nh.advertise<std_msgs::Int16MultiArray>("PWMs", 100);
    ros::Subscriber RC_to_PWM=nh.subscribe("/RC_readings", 100, &arrayCallback);
    //ros::Rate loop_rate(200);
	std_msgs::Int16MultiArray PWM_temp;

    while(ros::ok()){	
		PWM_temp.data[0]=Arr[0];
		PWM_temp.data[1]=Arr[1];
	
			
		PWMs.publish(PWM_temp);
		
		ros::spinOnce();
		//loop_rate.sleep();
	}
    return 0;   
}
void arrayCallback(const std_msgs::Int16MultiArray::ConstPtr &array){
	for(int i=0;i<3;i++){
		Arr[i]=array->data[i];
	}