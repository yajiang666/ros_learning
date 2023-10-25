#include"ros/ros.h"
#include"tf2_ros/transform_listener.h"
#include"tf2_ros/buffer.h"
#include"geometry_msgs/Twist.h"
#include"geometry_msgs/TransformStamped.h"
#include"turtle_exs/IncPID.h"
int main(int argc,char* argv[]){
    ros::init(argc,argv,"control_turtle2");
    ros::NodeHandle nh;
    tf2_ros::Buffer bf;
    tf2_ros::TransformListener tfl(bf);
    ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",1000);//这个地方其实是要对turtle2进行操作，也就是控制这个turtle2跟随，而且这个只是简单的初始化
    ros::Rate rate(50);
    while (ros::ok())
    {
        try{
            geometry_msgs::TransformStamped tfs=bf.lookupTransform("turtle2","turtle1",ros::Time(0));
            geometry_msgs::Twist twist;
            //创建一个pid类
            incpid_ns::IncPID linear_pid_x(0.5, 0.1, 0.01, 10.0, -10.0);
            auto error_x=sqrt(pow(tfs.transform.translation.x,2)+pow(tfs.transform.translation.y,2));
            linear_pid_x.calc(error_x);
            linear_pid_x.update();
            linear_pid_x.limit();
            twist.linear.x=linear_pid_x.output();
            auto error_yaw=atan2(tfs.transform.translation.y,tfs.transform.translation.x);
            incpid_ns::IncPID linear_pid_yaw(4, 0.5, 0.01, 70.0, -70.0);
            linear_pid_yaw.calc(error_yaw);
            linear_pid_yaw.update();
            linear_pid_yaw.limit();
            twist.angular.z=linear_pid_yaw.output();
            //这里再发布
            pub.publish(twist);
        }
        catch(const std::exception& e){
            ROS_INFO("errr is %s",e.what());
        }
        rate.sleep();
        ros::spinOnce();
    }   
    return 0;
}