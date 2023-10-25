#include"ros/ros.h"
#include"turtlesim/Spawn.h"
int main(int argc,char* argv[]){
    //这个地方应该是要自定义创建一个小乌龟
    ros::init(argc,argv,"turtle_start");
    ros::NodeHandle nh;
    ros::ServiceClient sc=nh.serviceClient<turtlesim::Spawn>("/spawn");
    ros::service::waitForService("/spawn");
    turtlesim::Spawn spawn;
    spawn.request.name="turtle2";
    spawn.request.x=1.0;
    spawn.request.y=2.0;
    spawn.request.theta=3.1415926;
    bool flag=sc.call(spawn);
    if(flag){
        ROS_INFO("the turtle2 is started");
    }
    else{
        ROS_INFO("the turtle2 is not started");
    }
    ros::spin();
    return 0;
}