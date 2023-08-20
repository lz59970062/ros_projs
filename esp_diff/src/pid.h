#ifndef __PID_H_
#define __PID_H_
#define fitter_array_len 5
typedef unsigned char uint8_t;
#include <Arduino.h>
#include <Preferences.h>

#define sqrt_2 1.4142135623730950488016887242097
#define PI 3.1415926535897932384626433832795
#define ISR_FLOAT 1
#if ISR_FLOAT==1
#define FLOAT double 
#else
#define FLOAT float 
#endif

class PID : public Preferences
{
public:
    PID(FLOAT kp, FLOAT ki, FLOAT kd, FLOAT output_min, FLOAT output_max, FLOAT error_max, uint8_t method, FLOAT db, char *name);
    FLOAT kp, ki, kd;
    FLOAT error, error_last, error_sum;
    FLOAT error_max;
    FLOAT output, output_last;
    FLOAT  setpoint;
    FLOAT output_max, output_min;
    FLOAT input_array[fitter_array_len];
    uint8_t optimize_mode;
    FLOAT input;
    String name;
    // 死区
    FLOAT deadband;
    FLOAT optimize();
    void print_pid_data();
    void Angle_pid(FLOAT input);
    void set_pid(FLOAT kp, FLOAT ki, FLOAT kd);
    void reset_pid();
    void set_output_max(FLOAT min, FLOAT max);
    FLOAT Compute(FLOAT input);
    FLOAT Compute2(FLOAT expect, FLOAT input);
    FLOAT median_filter(FLOAT *array, FLOAT input, int size);
    FLOAT avg_filter(FLOAT *array, FLOAT input, int size);
    void read_flash_param();
    void write_flash_param();
};

void Speed_pid();
void Total_speed_pid(FLOAT Vx,FLOAT Vy);
void Gyro_pid();
void Angle_pid(FLOAT input);
void pos_PID_init_all(void);
void angle_PID_init_all(void);
void speed_PID_init_all(void);
void Distance_pid(FLOAT mx,FLOAT my);
void save_all_param(void);

extern PID speed_pid1;
extern PID speed_pid2;
 
extern PID dis_pid1;
extern PID dis_pid2;
 
extern PID gyro_pid;
extern PID Speed_x;
 
extern PID angle_pid;
extern PID Dis_x;
 
extern float Eyd,Exd;
extern float expa,expg;
#endif
