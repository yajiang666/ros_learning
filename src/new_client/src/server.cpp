#include"ros/ros.h"
#include"new_client/addition.h"
bool domsg(new_client::addition::Request &request,new_client::addition::Response &response){
    int num1=request.num1;
    int num2=request.num3;
    response.sum=num1+num2;
    ROS_INFO("the sum is %d",response.sum);
    return true;
}
int main(int argc,char *argv[]){
    ros::init( argc,argv,"add_nums");
    ros::NodeHandle nh;
    ros::ServiceServer sever=nh.advertiseService("addition",domsg);
    ROS_INFO("The request is accepted");
    ros::spin();
    return 0;
}
// bool doReq(new_client::addition::Request& req,
//           new_client::addition::Response& resp){
//     int num1 = req.num1;
//     int num2 = req.num3;

//     // ROS_INFO("服务器接收到的请求数据为:num1 = %d, num2 = %d",num1, num3);

//     //逻辑处理
//     // if (num1 < 0 || num2 < 0)
//     // {
//     //     ROS_ERROR("提交的数据异常:数据不可以为负数");
//     //     return false;
//     // }

//     //如果没有异常，那么相加并将结果赋值给 resp
//     resp.sum = num1 + num2;
//     return true;


// }

// int main(int argc, char *argv[])
// {
//     // setlocale(LC_ALL,"");
//     // 2.初始化 ROS 节点
//     ros::init(argc,argv,"AddInts_Server");
//     // 3.创建 ROS 句柄
//     ros::NodeHandle nh;
//     // 4.创建 服务 对象
//     ros::ServiceServer server = nh.advertiseService("addition",doReq);
//     // ROS_INFO("服务已经启动....");
//     //     5.回调函数处理请求并产生响应
//     //     6.由于请求有多个，需要调用 ros::spin()
//     ros::spin();
//     return 0;
// }