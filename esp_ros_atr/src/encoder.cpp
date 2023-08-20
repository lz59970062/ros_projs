#include "encoder.h"

WheelEncoder enc1(Encoder1_A, Encoder1_B, 1);
WheelEncoder enc3(Encoder3_A, Encoder3_B, 1);
WheelEncoder enc2(Encoder2_A, Encoder2_B);
WheelEncoder enc4(Encoder4_A, Encoder4_B);

WheelEncoder &enca = enc2, &encb = enc1, &encc = enc4, &encd = enc3;

WheelEncoder::WheelEncoder(int input_a, int input_b) : ESP32Encoder()
{
    aPinNumber = static_cast<gpio_num_t>(input_a);
    bPinNumber = static_cast<gpio_num_t>(input_b);
    pinMode(input_a, INPUT_PULLDOWN);
    pinMode(input_b, INPUT_PULLDOWN);
    change_dir = false;
}
WheelEncoder::WheelEncoder(int input_a, int input_b, bool change_dir) : ESP32Encoder()
{
    aPinNumber = static_cast<gpio_num_t>(input_a);
    bPinNumber = static_cast<gpio_num_t>(input_b);
    pinMode(input_a, INPUT_PULLDOWN);
    pinMode(input_b, INPUT_PULLDOWN);
    this->change_dir = change_dir;
}

void WheelEncoder::init_hardware()
{
    useInternalWeakPullResistors = DOWN;
    attachHalfQuad(aPinNumber, bPinNumber);
    setCount(0);
    last_speed_update_time = micros();
    last_count = getCount();
}

void WheelEncoder::encoder_reset()
{
    setCount(0);
}

