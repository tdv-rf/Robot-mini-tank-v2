#include <Arduino.h>
#include "Motor.h"

int ML_Ctrl; // define the direction control pin of left motor
int ML_PWM;  //define PWM control pin of left motor
int MR_Ctrl; //define the direction control pin of right motor
int MR_PWM;  //define PWM control pin of right motor

Motor::~Motor()
{
}

Motor::Motor()
{
}

/***************the function to run motor***************/
void Motor::init(int ml_ctrl, int ml_pwm, int mr_ctrl, int mr_pwm)
{
    ML_Ctrl = ml_ctrl;
    ML_PWM = ml_pwm;
    MR_Ctrl = mr_ctrl;
    MR_PWM = mr_pwm;
    pinMode(ML_Ctrl, OUTPUT);
    pinMode(ML_PWM, OUTPUT);
    pinMode(MR_Ctrl, OUTPUT);
    pinMode(MR_PWM, OUTPUT);
}

void Motor::Car_front()
{
    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 200);
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 200);
}
void Motor::Car_back()
{
    digitalWrite(MR_Ctrl, HIGH);
    analogWrite(MR_PWM, 200);
    digitalWrite(ML_Ctrl, HIGH);
    analogWrite(ML_PWM, 200);
}
void Motor::Car_left()
{
    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 255);
    digitalWrite(ML_Ctrl, HIGH);
    analogWrite(ML_PWM, 255);
}
void Motor::Car_right()
{
    digitalWrite(MR_Ctrl, HIGH);
    analogWrite(MR_PWM, 255);
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 255);
}
void Motor::Car_Stop()
{
    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 0);
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 0);
}
void Motor::Car_T_left()
{
    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 255);
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 180);
}
void Motor::Car_T_right()
{
    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 180);
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 255);
}