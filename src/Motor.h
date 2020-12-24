#ifndef MOTOR
#define MOTOR

#include <Arduino.h>

class Motor
{
private:
    int ml_ctrl;
    int ml_pwm;
    int mr_ctrl;
    int mr_pwm;

public:
    Motor();
    ~Motor();

    void init(int ml_ctrl, int ml_pwm, int mr_ctrl, int mr_pwm);
    void Car_front();
    void Car_back();
    void Car_left();
    void Car_right();
    void Car_Stop();
    void Car_T_left();
    void Car_T_right();
};

#endif
