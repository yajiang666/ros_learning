#include"ros/ros.h"
#include"turtlesim/Pose.h"
#include"tf2_ros/transform_broadcaster.h"
#include"geometry_msgs/TransformStamped.h"
#include"tf2/LinearMath/Quaternion.h"
// #include"std_msgs/String.h"
/*主要就是以下几个操作
首先需要接受前面那个小乌龟的位置信息
然后要把他按照一定的频率发送给后面那个小乌龟
*/
std::string name;
void domsgs(const turtlesim::Pose::ConstPtr& pose){
    static tf2_ros::TransformBroadcaster tfb;
    geometry_msgs::TransformStamped tfs;
    tfs.header.stamp=ros::Time::now();
    tfs.header.frame_id="world";
    tfs.child_frame_id=name;
    tf2::Quaternion qt;
    qt.setRPY(0,0,pose->theta);
    tfs.transform.translation.x=pose->x;
    tfs.transform.translation.y=pose->y;
    tfs.transform.translation.z=0;
    tfs.transform.rotation.x=qt.getX();
    tfs.transform.rotation.y=qt.getY();
    tfs.transform.rotation.z=qt.getZ();
    tfs.transform.rotation.w=qt.getW();
    tfb.sendTransform(tfs);
}
int main(int argc,char* argv[]){
    /*解析launch文件*/
    ros::init(argc,argv,"turtle_tracking_pub");
    if(argc!=2) {
        ROS_ERROR("please input the right number");
    }
    else{
        name=argv[1];
    }
    //首先是接受信息
    ros::NodeHandle nh;
    //修改关键点 要修改这个名称
    ros::Subscriber sub=nh.subscribe<turtlesim::Pose>(name+"/pose",100,domsgs);
    ros::spin();
    return 0;
}