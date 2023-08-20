#ifndef __PID_H_
#define __PID_H_
#define fitter_array_len 5
typedef unsigned char uint8_t;
#include <Arduino.h>
#include <Preferences.h>

#define sqrt_2 1.4142135623730950488016887242097
#define PI 3.1415926535897932384626433832795

class PID : public Preferences
{
public:
    PID(float kp, float ki, float kd, float output_min, float output_max, float error_max, uint8_t method, float db, char *name);
    float kp, ki, kd;
    float error, error_last, error_sum;
    float error_max;
    float output, output_last;
    float setpoint;
    float output_max, output_min;
    float input_array[fitter_array_len];
    uint8_t optimize_mode;
    float input;
    String name;
    // 死区
    float deadband;
    float optimize();
    void print_pid_data();
    void Angle_pid(float input);
    void set_pid(float kp, float ki, float kd);
    void reset_pid();
    void set_output_max(float min, float max);
    float Compute(float input);
    float Compute2(float expect, float input);
    float median_filter(float *array, float input, int size);
    float avg_filter(float *array, float input, int size);
    void read_flash_param();
    void write_flash_param();
};

void Speed_pid();
void Total_speed_pid(float Vx,float Vy);
void Gyro_pid();
void Angle_pid(float input);
void pos_PID_init_all(void);
void angle_PID_init_all(void);
void speed_PID_init_all(void);
void Distance_pid(float mx,float my);
void save_all_param(void);

extern PID speed_pid1;
extern PID speed_pid2;
extern PID speed_pid3;
extern PID speed_pid4;
extern PID dis_pid1;
extern PID dis_pid2;
extern PID dis_pid3;
extern PID dis_pid4;
extern PID gyro_pid;
extern PID Speed_x;
extern PID Speed_y;
extern PID angle_pid;
extern PID Dis_x;
extern PID Dis_y;


extern float Eyd,Exd;
extern float expa,expg;
#endif
