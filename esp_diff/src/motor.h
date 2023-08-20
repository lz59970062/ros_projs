#ifndef __MOTOR_H
#define __MOTOR_H
#include <Arduino.h>
#include "config.h"
void motor_init();
#define ENABLE_QUEUE 0
class Motor
{
public:
    static uint8_t chan_idx;
    Motor(int pina, int pinb, bool inv = false);
    void begin();
    int get_input();
    void write(int duty);

private:
    int freq = 20000;
    int pina, pinb;
    int ch1, ch2;
    bool inv;
    int max_duty = 511;
    int now_input;
};
extern int Motor_Num;

#if MOTOR_NUM == 4
extern Motor mot1;
extern Motor mot2;
extern Motor mot3;
extern Motor mot4;
extern Motor &mota;
extern Motor &motb;
extern Motor &motc;
extern Motor &motd;
#elif MOTOR_NUM == 2
extern Motor mot1;
extern Motor mot2;
 
#endif

#if ENABLE_QUEUE == 1
extern xQueueHandle motor_q;
#endif
#endif