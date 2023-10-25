#include"ros/ros.h"
#include"new_client/addition.h"
int main(int argc,char *argv[]){
    ros::init( argc,argv,"add_nums_clent");
    ros::NodeHandle nh;
    ros::ServiceClient client=nh.serviceClient<new_client::addition>("addition");
    new_client::addition ai;
    ai.request.num1=31;
    ai.request.num3=35;
    bool flag=client.call(ai);
    if(flag){
        ROS_INFO("sum is %d",ai.response.sum);
    }else{
        ROS_INFO("false");
    }
    return 0;
}