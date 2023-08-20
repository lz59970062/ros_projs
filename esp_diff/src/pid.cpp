#include "pid.h"
#include "robot.h"

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
PID Dis_x(0, 0, 0, -1024, 1024, 800, 1, 5, "Dis_x");
PID Dis_y(0, 0, 0, -1024, 1024, 800, 1, 5, "Dis_y");

#elif MOTOR_NUM == 2
PID speed_pid1(0.1, 0.1, 0.1, -480, 480, 400, 1, 0.1, "speed_pid1");
PID speed_pid2(0.1, 0.1, 0.1, -480, 480, 400, 1, 0.1, "speed_pid2");

PID Speed_x(0, 0, 0, -512, 512, 800, 1, 2, "Speed_x");
PID Dis_x(0, 0, 0, -1024, 1024, 800, 1, 5, "Dis_x");
#endif
PID gyro_pid(0, 0, 0, -512 * 2, 512 * 2, 800, 1, 0.1, "gyro_pid");
PID angle_pid(0, 0, 0, -512, 512, 800, 1, 0.02, "angle_pid");
PID::PID(FLOAT _kp, FLOAT _ki, FLOAT _kd, FLOAT _output_min, FLOAT _output_max, FLOAT _error_max, uint8_t _method, FLOAT _db, char *name) : Preferences()
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
    gyro_pid.write_flash_param();
    angle_pid.write_flash_param();
    Speed_x.write_flash_param();
    Dis_x.write_flash_param();
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
FLOAT PID::Compute(FLOAT input)
{
    this->input = input;
    error = setpoint - input;
    if (abs(error) < deadband)
    {
        error = 0;
    }
    error = median_filter(input_array, error, fitter_array_len);
    error_sum += optimize() * error;
    error_sum = constrain(error_sum, -output_max * 3, output_max * 3);
    output = (kp * error) + (ki * error_sum) + (kd * (error - error_last));
    error_last = error;
    this->output = constrain(output, -output_max, output_max);
    return this->output;
}
FLOAT PID::optimize()
{
    FLOAT outout = 0;
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
FLOAT PID::Compute2(FLOAT expect, FLOAT input)
{
    setpoint = expect;
    Compute(input);
    return output;
}
FLOAT PID::avg_filter(FLOAT *array, FLOAT input, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        array[i] = array[i + 1];
    }
    array[size - 1] = input;
    FLOAT temp = 0;
    for (i = 0; i < size; i++)
    {
        temp += array[i];
    }
    return temp / size;
}
FLOAT PID::median_filter(FLOAT *array, FLOAT input, int size)
{
    int i;
    FLOAT temp[5];
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
                FLOAT temp1 = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = temp1;
            }
        }
    }
    return temp[(int)(size / 2)];
}
void PID::set_pid(FLOAT kp, FLOAT ki, FLOAT kd)
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
void PID::set_output_max(FLOAT min, FLOAT max)
{
    output_max = max;
    output_min = min;
}

void Speed_pid()
{
    speed_pid1.Compute2(speed_pid1.setpoint, speed_pid1.input);
    speed_pid2.Compute2(speed_pid2.setpoint, speed_pid2.input);
}
void Total_speed_pid(FLOAT Vx, FLOAT Vy)
{

    Speed_x.Compute2(Speed_x.setpoint, Vx);
}
void Gyro_pid()
{
 
    gyro_pid.setpoint = (double)robot_cmd.angular_z + (double)angle_pid.output;
 
    gyro_pid.input = robot_state.wz;
 
    if (abs(gyro_pid.setpoint) < 0.001)
    {
        gyro_pid.error_sum = 0;
    }
    
    gyro_pid.Compute2(gyro_pid.setpoint, gyro_pid.input);
}
void Angle_pid(FLOAT input)
{
    angle_pid.input = input;
    angle_pid.Compute2(expa, angle_pid.input);
}
void Distance_pid(FLOAT mx, FLOAT my)
{
    Dis_x.setpoint = Exd;

    Dis_x.Compute(mx);
}