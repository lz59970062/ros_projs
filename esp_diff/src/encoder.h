#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "Arduino.h"

#include <ESP32Encoder.h>
/// attention global unit is  centimeter

/// bellow are motor Parameters///////////
#define RATE 100.0f
// 轮子直径
#define WHEEL_BASE (0.128 * 100)                             // 轮子间距
#define ACLE_BASE (0.925 * 100)                              // 轮子中心到车身中心距离
#define WHEEL_DIAMETER (0.048 * 100)                         // 轮子直径
#define WHEEL_RESOLUTION 520                                 // 20,13x20x2=780
#define WHEEL_SCALE (PI * WHEEL_DIAMETER / WHEEL_RESOLUTION) // ÂÖ×ÓËÙ¶Èm/sÓë±àÂëÆ÷×ª»»ÏµÊý

/// ////////////////////////////////

class WheelEncoder : public ESP32Encoder
{
public:
    WheelEncoder(int input_a, int input_b);
    WheelEncoder(int input_a, int input_b, bool change_dir);
    // void init_whell_param(float wheel_d = WHEEL_DIAMETER, float encoder_multiples = EncoderMultiples, float encoder_precision = Encoder_precision, float reduction_ratio = Reduction_Ratio);

    void init_hardware();

    void encoder_reset();
    void encoder_deinit();
    bool change_dir = false;
    float speed = 0;
    float distance = 0;
    inline float get_distance()
    {
        return this->distance = get_cnt() * WHEEL_SCALE;
    }
    inline double get_speed()
    {
        unsigned long now_time = micros();
        long now_count = get_cnt();
        double dt = (now_time - last_speed_update_time) * 0.000001;
        int delt_cnt = now_count - last_count;
        double speed = delt_cnt * WHEEL_SCALE / dt;
        last_speed_update_time = now_time;
        last_count = now_count;
        return this->speed = speed;
    }
    inline long get_cnt()
    {
        return this->change_dir ? -getCount() : getCount();
    }

private:
    int encoder_cnt = 0;
    bool _usemy_int = false;
    float _wheel_diameter, _encoder_multiples, _encoder_precision, _reduction_ratio;
    long last_speed_update_time;
    int last_count;
};

extern WheelEncoder enc1, enc2; 
#endif