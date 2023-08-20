#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "Arduino.h"

#include <ESP32Encoder.h>

/// bellow are motor Parameters///////////
#define RATE 100.0f
// 轮子直径
#define MEC_WHEEL_BASE 0.196                                             // 轮子间距
#define MEC_ACLE_BASE 0.160                                              // 轮子中心到车身中心距离
#define MEC_WHEEL_DIAMETER 0.098                                         // 轮子直径
#define MEC_WHEEL_RESOLUTION 780                                         // 30,13x30x2=780
#define MEC_WHEEL_SCALE (PI * MEC_WHEEL_DIAMETER / MEC_WHEEL_RESOLUTION) // ÂÖ×ÓËÙ¶Èm/sÓë±àÂëÆ÷×ª»»ÏµÊý

/// ////////////////////////////////

class WheelEncoder : public ESP32Encoder
{
public:
    WheelEncoder(int input_a, int input_b);
    WheelEncoder(int input_a, int input_b, bool change_dir);
    // void init_whell_param(float wheel_d =MEC_WHEEL_DIAMETER, float encoder_multiples = EncoderMultiples, float encoder_precision = Encoder_precision, float reduction_ratio = Reduction_Ratio);

    void init_hardware();

    void encoder_reset();
    void encoder_deinit();
    bool change_dir = false;
    float speed = 0;
    float distance = 0;
    inline float get_distance()
    {
        return this->distance = get_cnt() * MEC_WHEEL_SCALE;
    }
    inline double get_speed()
    {
        unsigned long now_time = micros();
        long now_count = get_cnt();
        double dt = (now_time - last_speed_update_time) * 0.000001;
        int delt_cnt = now_count - last_count;
        double speed = delt_cnt * MEC_WHEEL_SCALE / dt;
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

extern WheelEncoder enc1, enc2, enc3, enc4;
extern WheelEncoder &enca, &encb, &encc, &encd;
#endif