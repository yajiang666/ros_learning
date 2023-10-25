#include"ros/ros.h"
#include"tf2_ros/buffer.h"
#include"tf2_ros/transform_listener.h"
#include"geometry_msgs/PointStamped.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"
/*
第一步，肯定要包含头文件，
然后创建转换对象接收转换关系，
然后再使用接收到的转换关系进行变换。
*/
int main(int argc,char *argv[]){
    ros::init(argc,argv,"demo02_static_sub");
    ros::NodeHandle nh;
    tf2_ros::Buffer buffer;//这个代码里面的这个buffer是有什么用，主要就是将listener中监听到的数据存储在这里面
    tf2_ros::TransformListener listener(buffer);//这个listener又有什么用
    geometry_msgs::PointStamped ps;
    ps.header.stamp=ros::Time::now();
    ps.header.frame_id="laser"; 
    ps.point.x=1.2;
    ps.point.y=1.9;
    ps.point.z=1.5;
    ros::Duration d(5);//这个是为了保证接收方转换之前这个发布方已经发布了。
    d.sleep();
    ros::Rate r(10);
    while (ros::ok())
    {
        geometry_msgs::PointStamped ps_out;
        ps_out=buffer.transform(ps,"base_link");
        ROS_INFO("(%.2f,%.2f,%.2f)",ps_out.point.x,ps_out.point.y,ps_out.point.z);
        r.sleep();
        // ros::spinOnce();
    }
    
    return 0;
}