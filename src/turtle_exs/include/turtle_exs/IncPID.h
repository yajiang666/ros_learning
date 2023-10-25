#pragma once
#include"ros/ros.h"
#include"tf2_ros/transform_listener.h"
#include"tf2_ros/buffer.h"
#include"geometry_msgs/Twist.h"
#include"geometry_msgs/TransformStamped.h"
namespace incpid_ns{
    class IncPID
    {
    private:
        double Kp; // 比例增益
        double Ki; // 积分增益
        double Kd; // 微分增益
        double ek; // 当前误差
        double ek_1; // 上一次误差
        double ek_2; // 上上次误差
        double uk; // 当前输出
        double uk_1; // 上一次输出
        double deltaUk; // 输出变化量
        double umax; // 最大输出限制
        double umin; // 最小输出限制
    public:
        IncPID(double Kp, double Ki, double Kd, double umax, double umin);
        void limit();
        void calc(double ek);
        void update();
        double output();
    };
}