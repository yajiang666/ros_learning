#include"ros/ros.h"
#include"turtlesim/Pose.h"
#include"tf2_ros/transform_broadcaster.h"
#include"geometry_msgs/TransformStamped.h"
#include"tf2/LinearMath/Quaternion.h"
//意思理解错了，其实这个文件就是实现的一个
void domsgs(const turtlesim::Pose::ConstPtr& temp_pose){
    static tf2_ros::TransformBroadcaster pub;//避免每次循环都重新创建
    geometry_msgs::TransformStamped ts;
    ts.header.frame_id="world";
    ts.header.stamp=ros::Time::now();
    ts.child_frame_id="turtle1";
    ts.transform.translation.x=temp_pose->x;
    ts.transform.translation.y=temp_pose->y;
    ts.transform.translation.z=0;
    //四元数设置
    tf2::Quaternion qt;
    qt.setRPY(0,0,temp_pose->theta);
    ts.transform.rotation.x=qt.getX();
    ts.transform.rotation.y=qt.getY();
    ts.transform.rotation.z=qt.getZ();
    ts.transform.rotation.w=qt.getW();
    //到这一步也就是说现在的这个坐标转换关系已经设置好了，但是还需要进行应用
    pub.sendTransform(ts);
}
int main(int argc,char *argv[]){
    ros::init(argc,argv,"dynamic_pub");
    ros::NodeHandle nh;
    ros::Subscriber sub=nh.subscribe("turtle1/pose",1000,domsgs);
    ros::spin();
    return 0;
}