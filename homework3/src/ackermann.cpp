#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
// defining node variables
const float L= 2.65; // 
const float WheelTireRatio = 17.3; // 
  
ros::Publisher CmdVelpub;
ros::Publisher Steeringpub;

geometry_msgs::Twist cmd_vel;

void DiffCallback(const geometry_msgs::TwistConstPtr& msg)
{
  // msg variables
  double vel = msg -> linear.x;
  double psydot = msg -> angular.z;

  std_msgs::Float64 CmdVel;
  std_msgs::Float64 Steering;

  double dsteering = WheelTireRatio*(atan((L*psydot)/vel));
  CmdVel.data = vel;
  Steering.data = dsteering;
  CmdVelpub.publish(CmdVel);
  Steeringpub.publish(Steering);

}
int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "diff_drive");
  ros::NodeHandle node;
  

  

  CmdVelpub = node.advertise<std_msgs::Float64>("/audibot/cmd_vel/",1);

  Steeringpub = node.advertise<std_msgs::Float64>("/audibot/steering_cmd",1);
  
  ros::Subscriber sub = node.subscribe("/twist_cmd", 1, DiffCallback);
  ros::spin();

  return 0;
} 
