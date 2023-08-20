#ifndef __CONFIG_H__
#define __CONFIG_H__
#define WIFI_SSID "orangepi"
// #define WIFI_SSID "qaz"
#define WIFI_PASS "12345678"
#define WIFI_REMOTE_IP "192.168.2.1"
#define UDP_TARGET_IP "192.168.8.239"
#define NODE_NAME "esp_diff"
// #define WIFI_REMOTE_IP1  192
// #define WIFI_REMOTE_IP2  168
// #define WIFI_REMOTE_IP3  0
// #define WIFI_REMOTE_IP4  103

#define ROS_TASK_STACK_SIZE        (int)(8192 * 3)
#define ROS_TASK_PRIORITY          4

#define MOTOR_TASK_STACK_SIZE      (int)(1024 * 2)
#define MOTOR_TASK_PRIORITY        3

#define PID_TASK_STACK_SIZE        (int)(1024 * 4)
#define PID_TASK_PRIORITY          4

#define DATA_UPDATE_TASK_STACK_SIZE  (int)(1024 * 3)
#define DATA_UPDATE_TASK_PRIORITY    4

#define UDP_TASK_STACK_SIZE        (int)(1024 * 4)
#define UDP_TASK_PRIORITY          4

#define freq_imu                   200
#define freq_voltage               4
#define freq_odom                  100
#define spin_freq                  200
#define tf_freq                    150

#endif