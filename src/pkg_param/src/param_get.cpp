#include"ros/ros.h"
int main(int argc,char *argv[]){
    ros::init(argc,argv,"C_get");
    ros::NodeHandle nh;
    int radius=nh.param("radus",5);
    std::vector<std::string> names;
    nh.getParamNames(names);
    for (int i =0 ; i < names.size(); i++)
    {
        ROS_INFO("the name is %s",names[i].c_str());
    }
    
    // nh.setParam("ridus",20);
    return 0;
}