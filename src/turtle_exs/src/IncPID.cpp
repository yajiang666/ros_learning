#include"turtle_exs/IncPID.h"
// #include"ros/ros.h"
namespace incpid_ns
{
    
 // namespace name

//构造函数，用给定的参数和初始值初始化成员函数，关键在于一开始的时候这些个前面没有的参数都是要初始为0的
IncPID::IncPID(double Kp, double Ki, double Kd, double umax, double umin) {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
        this->umax = umax;
        this->umin = umin;
        this->ek = 0;
        this->ek_1 = 0;
        this->ek_2 = 0;
        this->uk = 0;
        this->uk_1 = 0;
        this->deltaUk = 0;
    }
    void IncPID::limit(){
        if(this->uk>this->umax) this->uk=this->umax;
        if(this->uk<this->umin) this->uk=this->umin;
    }
    double IncPID::output(){
        return this->uk;
    }
    void IncPID::update(){
        this->uk=this->uk_1+this->deltaUk;
        this->uk_1=this->uk;
    }
    void IncPID::calc(double ek) {
        this->ek = ek; // 更新当前误差
        // 根据增量PID公式计算输出变化量
        this->deltaUk = this->Kp * (this->ek - this->ek_1) + 
                        this->Ki * this->ek + 
                        this->Kd * (this->ek - 2 * this->ek_1 + this->ek_2);
        // 更新上一次和上上次的误差
        this->ek_2 = this->ek_1;
        this->ek_1 = this->ek;
    }
}