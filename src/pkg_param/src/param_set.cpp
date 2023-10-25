#include"ros/ros.h"
int main(int argc,char *argv[]){
    ros::init(argc,argv,"C_set");
    ros::NodeHandle nh;
    nh.setParam("type","xiaohung");
    nh.setParam("ridus",20);
    return 0;
}