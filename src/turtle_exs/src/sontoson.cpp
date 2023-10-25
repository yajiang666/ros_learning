#include"ros/ros.h"
#include"tf2_ros/transform_listener.h"
#include"tf2_ros/buffer.h"
#include"geometry_msgs/PointStamped.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"
//首先这个时候已经有了两个静态转换关系了，所以这个时候需要订阅这两个消息，然后找到son1坐标中的点相对于son2坐标中的位置
int main(int argc, char* argv[]){
    ros::init(argc,argv,"sontoson");    
    ros::NodeHandle nh;
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);//其实到这里我有一个问题就是说，这个订阅的数据到底是怎么存放到buffer里面的
    //定义一个点
    geometry_msgs::PointStamped psson1;//坐标点
    psson1.header.stamp=ros::Time::now();
    psson1.header.frame_id="son1";
    psson1.point.x=1;
    psson1.point.y=2;
    psson1.point.z=3;
    ros::Rate r(10);
    while (ros::ok())
    {   
        try{
            geometry_msgs::PointStamped psson2=buffer.transform(psson1,"son2");
            ROS_INFO("the con in son2 is (%f,%f,%f)",
            psson2.point.x,psson2.point.y,psson2.point.z);
        }
        catch(const std::exception& e){
            ROS_INFO("the erro is %s",e.what());
        }
        r.sleep();
        ros::spinOnce();
    }
    return 0;
}