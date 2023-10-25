#include"ros/ros.h"
#include"tf2_ros/static_transform_broadcaster.h"
#include"geometry_msgs/TransformStamped.h"
#include"tf2/LinearMath/Quaternion.h"
/*
需求：发布两个坐标系之间的转换关系
创建发布对象
组织被发布的消息
发布数据
spin()
*/
int main(int argc,char* argv[]){
    ros::init(argc,argv,"static_pub");
    ros::NodeHandle nh;
    tf2_ros::StaticTransformBroadcaster pub;
    geometry_msgs::TransformStamped ts;
    ts.header.stamp=ros::Time::now();
    ts.header.frame_id="base_link";
    ts.child_frame_id="lase_link";
    ts.transform.translation.x=0.2;
    ts.transform.translation.x=0.6;
    ts.transform.translation.x=0.7;
    tf2::Quaternion qt;
    //这个qt对象的作用就是将转向角转换成为四元数；
    qt.setRPY(0,0,0);
    ts.transform.rotation.x=qt.getX();
    ts.transform.rotation.y=qt.getY();
    ts.transform.rotation.z=qt.getZ();
    ts.transform.rotation.w=qt.getW();
    pub.sendTransform(ts);
    ros::spin();
    return 0;
}