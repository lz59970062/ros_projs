#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "Arduino.h"
#include "encoder.h"
#include "motor.h"
#include "pid.h"
#include "JY901.h"
#include "param.h"
#include "config.h"



void start_robot();
typedef struct
{
    float linear_x;
    float angular_z;
    short control_distance;
    short control_angle;
    float dis_x;
    float angle_z;
} Robot_cmd;

class Robot_state
{
public:
    Robot_state()
    {
        this->odom_x = 0;
        this->odom_y = 0;
        this->yaw = 0;
        this->vx = 0;

        this->wz = 0;
    }
    FLOAT odom_x;
    FLOAT odom_y;
    FLOAT yaw;
    FLOAT vx;
    FLOAT wz;
    uint32_t state_flags;
    FLOAT left_wheel_speed, right_wheel_speed;
    FLOAT left_wheel_distance, right_wheel_distance;
    FLOAT exp_left_wheel_speed, exp_right_wheel_speed;
    FLOAT yaw_offset;
    float forward_dis, left_dis, right_dis;
};

extern Robot_cmd robot_cmd;
extern Robot_state robot_state;

#endif