#ifndef __ROS_PROCESS_H__
#define __ROS_PROCESS_H__
#include "ros.h"
#include "sensor_msgs/Imu.h"
#include "std_msgs/Float32.h"
#include "nav_msgs/Odometry.h"
#include "config.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16MultiArray.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_broadcaster.h"
#include "ws2812.h"
void ros_init(char *ip, int port);
void ros_publish_speed(float speed1, float speed2, float speed3, float speed4);
void ros_publish_distance(float distance1, float distance2, float distance3, float distance4);
void ros_publish_motor_input(float motor_input1, float motor_input2, float motor_input3, float motor_input4);
void ros_publish_motor_pid_output(float &motor_pid_output1, float &motor_pid_output2, float &motor_pid_output3,
                                  float &motor_pid_output4);
void ros_publish_imu(float &ax, float &ay, float &az, float &gx, float &gy, float &gz,float &q0,float &q1,float &q2,float &q3);
void ros_publish_odom(float &x, float &y, float &z, float &vx, float &vy, float &vz,float &q0,float &q1,float &q2,float &q3);
void ros_task(void *pvParameters);
void  ros_twist_fitler( float vx, float vy );
void ros_publish_expect_speed(float speed1, float speed2, float speed3, float speed4);
struct ros_imu_data_
{
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float q0;
  float q1;
  float q2;
  float q3;
};
struct ros_odom_data_
{
  float x;
  float y;
  float z;
  float vx;
  float vy;
  float vz;
};
struct ros_speed_data_
{
  float speed1;
  float speed2;
  float speed3;
  float speed4;
};
struct ros_distance_data_
{
  float distance1;
  float distance2;
  float distance3;
  float distance4;
};
struct ros_motor_input_data_
{
  float motor_input1;
  float motor_input2;
  float motor_input3;
  float motor_input4;
};
struct ros_motor_pid_output_data_
{
  float motor_pid_output1;
  float motor_pid_output2;
  float motor_pid_output3;
  float motor_pid_output4;
};

typedef struct
{
  float exps1, exps2, exps3, exps4;
} ros_expect_speed_data_t;
typedef struct
{
  float roll, pitch, yaw;
} ros_euler_data_t;
typedef struct{
  float cmd_vx,cmd_vy,cmd_wz;
}ros_cmd_t;
typedef struct ros_imu_data_ ros_imu_data_t;
typedef struct ros_odom_data_ ros_odom_data_t;
typedef struct ros_speed_data_ ros_speed_data_t;
typedef struct ros_distance_data_ ros_distance_data_t;
typedef struct ros_motor_input_data_ ros_motor_input_data_t;
typedef struct ros_motor_pid_output_data_ ros_motor_pid_output_data_t;

extern ros_imu_data_t ros_imu_data;
extern ros_odom_data_t ros_odom_data;
extern ros_speed_data_t ros_speed_data;
extern ros_distance_data_t ros_distance_data;
extern ros_motor_input_data_t ros_motor_input_data;
extern ros_motor_pid_output_data_t ros_motor_pid_output_data;
extern ros_expect_speed_data_t ros_expect_speed_data;
extern float ros_voltage_data;
extern ros_euler_data_t ros_euler_data;
extern ros_cmd_t ros_cmd_data;
// extern ros::NodeHandle nh;
#endif