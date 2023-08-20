#include "pid.h"


#if MOTOR_NUM == 4
PID speed_pid1(0.1, 0.1, 0.1, -512, 512, 400, 1, 0.0001, "speed_pid1");
PID speed_pid2(0.1, 0.1, 0.1, -512, 512, 400, 1, 0.0001, "speed_pid2");
PID speed_pid3(0.1, 0.1, 0.1, -512, 512, 400, 1, 0.0001, "speed_pid3");
PID speed_pid4(0.1, 0.1, 0.1, -512, 512, 400, 1, 0.0001, "speed_pid4");
PID dis_pid1(0, 0, 0, -512, 512, 1024, 1, 0.001, "distance_pid1");
PID dis_pid2(0, 0, 0, -512, 512, 1024, 1, 0.001, "distance_pid2");
PID dis_pid3(0, 0, 0, -512, 512, 1024, 1, 0.001, "distance_pid3");
PID dis_pid4(0, 0, 0, -512, 512, 1024, 1, 0.001, "distance_pid4");
PID Speed_x(0, 0, 0, -512, 512, 800, 1, 2, "Speed_x");
PID Speed_y(0, 0, 0, -512, 512, 800, 1, 2, "Speed_y");
PID Dis_x(0,0,0,-1024,1024,800,1,5,"Dis_x");
PID Dis_y(0,0,0,-1024,1024,800,1,5,"Dis_y");

#elif MOTOR_NUM == 2
PID speed_pid1(0.1, 0.1, 0.1, -512, 512, 400, 1, 2);
PID speed_pid2(0.1, 0.1, 0.1, -512, 512, 400, 1, 2);
PID dis_pid1(0, 0, 0, -512, 512, 1024, 1, 2);
PID dis_pid2(0, 0, 0, -512, 512, 1024, 1, 2);
#endif
PID gyro_pid(0, 0, 0, -512*2, 512*2, 800, 1, 0.001, "gyro_pid");
PID angle_pid(0, 0, 0, -512, 512, 800, 1, 0.5, "angle_pid");
PID::PID(float _kp, float _ki, float _kd, float _output_min, float _output_max, float _error_max, uint8_t _method, float _db, char *name) : Preferences()
{
    bool temp = begin(name, false, "nvs");
    uint8_t saved = getUChar("saved", 0);
    if (!saved)
    {
        kp = _kp;
        ki = _ki;
        kd = _kd;
    }
    else
    {
        kp = getFloat("kp", 0);
        ki = getFloat("ki", 0);
        kd = getFloat("kd", 0);
    }
    output_max = _output_max;
    output_min = _output_min;
    error_max = _error_max;
    optimize_mode = _method;
    error_sum = 0;
    error_last = 0;
    output_last = 0;
    error = 0;
    output = 0;
    setpoint = 0;
    deadband = _db;

    this->name = String(name);
    if (temp)
    {
        Serial.printf("open %s success\n", name);
    }
    else
    {
        Serial.printf("open %s fail\n", name);
    }
}

void speed_PID_init_all()
{
}
void angle_PID_init_all()
{
}
void pos_PID_init_all()
{
}
void save_all_param()
{
    speed_pid1.write_flash_param();
    speed_pid2.write_flash_param();
    speed_pid3.write_flash_param();
    speed_pid4.write_flash_param();
    dis_pid1.write_flash_param();
    dis_pid2.write_flash_param();
    dis_pid3.write_flash_param();
    dis_pid4.write_flash_param();
    gyro_pid.write_flash_param();
    angle_pid.write_flash_param();
    Speed_x.write_flash_param();
    Speed_y.write_flash_param();
    Dis_x.write_flash_param();
    Dis_y.write_flash_param();
}
void PID::print_pid_data()
{
    Serial.printf("now pid data is:%s\n", name.c_str());
    Serial.printf("kpid:%f,%f,%f\n", kp, ki, kd);
    Serial.printf("output_max:%f,output_min:%f\n", output_max, output_min);
    Serial.printf("error_last:%f,error:%f,error_sum:%f\n", error_last, error, error_sum);
    Serial.printf("output:%f\n\n", output);
}
void PID::read_flash_param()
{
    this->kp = getFloat("kp", 0);
    this->ki = getFloat("ki", 0);
    this->kd = getFloat("kd", 0);
    Serial.printf("get param: kp:%f,ki:%f,kd:%f\n", kp, ki, kd);
}
void PID::write_flash_param()
{
    putFloat("kp", this->kp);
    putFloat("ki", this->ki);
    putFloat("kd", this->kd);
    putUChar("saved", 1);
}
float PID::Compute(float input)
{
    this->input = input;
    error = setpoint - input;
    if (abs(error) < deadband)
    {
        error = 0;
    }
    error = avg_filter(input_array, error, fitter_array_len);
    error_sum += optimize() * error;
    error_sum = constrain(error_sum, -output_max * 3, output_max * 3);
    output = (kp * error) + (ki * error_sum) + (kd * (error - error_last));
    error_last = error;
    this->output = constrain(output, -output_max, output_max);
    return this->output;
}
float PID::optimize()
{
    float outout = 0;
    switch (optimize_mode)
    {
    case 1:
        if (abs(error) < error_max)
        {
            outout = 1;
        }
        else
        {
            outout = 0;
        }
        return outout;
    case 2:
        if (abs(error) < error_max)
        {
            outout = 1 - abs(error / error_max);
        }
        else
        {
            outout = 0;
        }
        return outout;

    default:
        return 1;
    }
}
float PID::Compute2(float expect, float input)
{
    setpoint = expect;
    Compute(input);
    return output;
}
float PID::avg_filter(float *array, float input, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        array[i] = array[i + 1];
    }
    array[size - 1] = input;
    float temp = 0;
    for (i = 0; i < size; i++)
    {
        temp += array[i];
    }
    return temp / size;
}
float PID::median_filter(float *array, float input, int size)
{
    int i;
    float temp[5];
    for (i = 0; i < size; i++)
    {
        array[i] = array[i + 1];
        temp[i] = array[i];
    }
    array[size - 1] = input;
    temp[size - 1] = input;
    for (i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (temp[j] > temp[j + 1])
            {
                float temp1 = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = temp1;
            }
        }
    }
    return temp[(int)(size / 2)];
}
void PID::set_pid(float kp, float ki, float kd)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}
void PID::reset_pid()
{
    error_sum = 0;
    error_last = 0;
    output_last = 0;
    error = 0;
    output = 0;
}
void PID::set_output_max(float min, float max)
{
    output_max = max;
    output_min = min;
}

void Speed_pid()
{
    speed_pid1.Compute2(speed_pid1.setpoint, speed_pid1.input);
    speed_pid2.Compute2(speed_pid2.setpoint, speed_pid2.input);
    speed_pid3.Compute2(speed_pid3.setpoint, speed_pid3.input);
    speed_pid4.Compute2(speed_pid4.setpoint, speed_pid4.input);
}
void Total_speed_pid(float Vx,float Vy)
{
 
    Speed_x.Compute2(Speed_x.setpoint,Vx);
    Speed_y.Compute2(Speed_y.setpoint,Vy);

}
void Gyro_pid(){
    
    gyro_pid.Compute2(gyro_pid.setpoint, gyro_pid.input);
}
void Angle_pid(float input){
    angle_pid.input = input;
    angle_pid.Compute2(expa, angle_pid.input);
}
void Distance_pid(float mx,float my){
    Dis_x.setpoint = Exd;
    Dis_y.setpoint = Eyd;
    Dis_x.Compute (mx);
    Dis_y.Compute (my);
}