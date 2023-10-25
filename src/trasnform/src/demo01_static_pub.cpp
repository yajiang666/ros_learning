#include"ros/ros.h"
#include"tf2_ros/static_transform_broadcaster.h"//static_transform_broadcaster
#include"geometry_msgs/TransformStamped.h"
// #include"geometry_msgs/Quaternion.h"
#include"tf2/LinearMath/Quaternion.h"
int main(int argc,char *argv[]){
    ros::init(argc,argv,"demo01_static_pub");
    // ros::NodeHandle nh;
    tf2_ros::StaticTransformBroadcaster pub;
    geometry_msgs::TransformStamped tfs;
    tfs.header.stamp=ros::Time::now();
    tfs.header.seq = 100;
    tfs.header.frame_id="base_link";
    tfs.child_frame_id="laser";
    tfs.transform.translation.x=0.2;
    tfs.transform.translation.y=0.0;
    tfs.transform.translation.z=0.5;
    // geometry_msgs::Quaternion Qt;
    tf2::Quaternion QT;
    QT.setRPY(0,0,0);   //according to rad
    tfs.transform.rotation.x=QT.getX();
    tfs.transform.rotation.y=QT.getY();
    tfs.transform.rotation.z=QT.getZ();
    tfs.transform.rotation.w=QT.getW();
    pub.sendTransform(tfs);
    ros::spin();
    
    return 0;
}//总的来说，静态坐标变换是分为两个信息，一个是static