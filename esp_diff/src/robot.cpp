#include "robot.h"
#include "distance.hpp"
xTaskHandle data_update_handle;
float wz_from_wheel = 0;
Robot_cmd robot_cmd = {0};
Robot_state robot_state;

void task_robot(void *arg)
{

    SemaphoreHandle_t xMutex_pid;
    xMutex_pid = xSemaphoreCreateMutex();
    uint32_t count = 0;
    // 用于保存上次时间。调用后系统自动更新
    static portTickType PreviousWakeTime;

    // 设置延时时间20ms，将时间转为节拍数
    const portTickType TimeIncrement = pdMS_TO_TICKS(10);

    // 获取当前系统时间
    PreviousWakeTime = xTaskGetTickCount();
    robot_state.yaw_offset = 0u;

    long last_blink = millis();
    robot_cmd.dis_x = 0;
    Dis_x.error_sum = 0;
    Dis_x.output = 0;

    robot_cmd.angle_z = 0;
    angle_pid.error_sum = 0;
    angle_pid.output = 0;

    while (1)
    {
        count++;

        vTaskDelayUntil(&PreviousWakeTime, TimeIncrement);
        xSemaphoreTake(xMutex_pid, portMAX_DELAY);

        // if (robot_cmd.control_angle == 1 || flag3 == 1)
        // {
        //     angle_pid.Compute2(robot_cmd.angle_z, robot_state.yaw);
        // }
        // else
        // {
        //     robot_cmd.angle_z = 0;
        //     angle_pid.error_sum = 0;
        //     angle_pid.output = 0;
        // }
        gyro_pid.setpoint = robot_cmd.angular_z + angle_pid.output;
        gyro_pid.input = robot_state.wz;
        if (abs(gyro_pid.setpoint) < 0.001)
        {
            gyro_pid.error_sum = 0;
        }
        Gyro_pid();

        // if (robot_cmd.control_distance == 1 || flag4 == 1)
        // {
        //     Dis_x.Compute2(robot_cmd.dis_x, robot_state.forward_dis);
        // }
        // else
        // {
        //     robot_cmd.dis_x = 0;
        //     Dis_x.error_sum = 0;
        //     Dis_x.output = 0;
        // }

        speed_pid1.setpoint = robot_state.exp_right_wheel_speed + Dis_x.output + robot_cmd.linear_x + gyro_pid.output * (WHEEL_BASE / 2);
        speed_pid2.setpoint = robot_state.exp_left_wheel_speed + Dis_x.output + robot_cmd.linear_x - gyro_pid.output * (WHEEL_BASE / 2);

        speed_pid1.input = enc1.speed;
        speed_pid2.input = enc2.speed;
        Speed_pid();
        xSemaphoreGive(xMutex_pid);
        if (flag2 == 1)
        {
            mot1.write(0);
            mot2.write(0);
        }
        else
        {
            mot1.write(speed_pid1.output);
            mot2.write(speed_pid2.output);
        }
    }
}

int ti_arr[10] = {0};

void IRAM_ATTR task_robot_timer_handler()
{

    // static SemaphoreHandle_t xMutex_pid = xSemaphoreCreateMutex();

    static uint32_t count = 0;
    // uint32_t count = 0;
    // // 用于保存上次时间。调用后系统自动更新
    count++;
    // ti_arr[count%10]=micros();

    // // xSemaphoreTake(xMutex_pid, portMAX_DELAY);

    // if (robot_cmd.control_angle == 1 || flag3 == 1)
    // {
    //     angle_pid.Compute2(robot_cmd.angle_z, robot_state.yaw);
    // }
    // else
    // {
    //     robot_cmd.angle_z = 0;
    //     angle_pid.error_sum = 0;
    angle_pid.output = 0;
    // }
    if (flag3 == 99)
    {
        gyro_pid.error_sum = 0;
        // gyro_pid.output=0;
    }
    Gyro_pid();

    // if (robot_cmd.control_distance == 1 || flag4 == 1)
    // {
    //     Dis_x.Compute2(robot_cmd.dis_x, robot_state.forward_dis);
    // }
    // else
    // {
    //     robot_cmd.dis_x = 0;
    // Dis_x.error_sum = 0;
    Dis_x.output = 0;
    // }

    speed_pid1.setpoint = robot_state.exp_right_wheel_speed + Dis_x.output + robot_cmd.linear_x + gyro_pid.output * (WHEEL_BASE / 2);
    speed_pid2.setpoint = robot_state.exp_left_wheel_speed + Dis_x.output + robot_cmd.linear_x - gyro_pid.output * (WHEEL_BASE / 2);

    speed_pid1.input = enc1.speed;
    speed_pid2.input = enc2.speed;
    Speed_pid();
    // xSemaphoreGive(xMutex_pid);
    if (flag2 == 1)
    {
        mot1.write(0);
        mot2.write(0);
    }
    else
    {
        mot1.write(speed_pid1.output);
        mot2.write(speed_pid2.output);
    }
}

bool deflect(float angle, float patience)
{
    angle += PI;
    int ange_num = (angle / (PI / 2) + 0.5);
    float round_angle = angle * (PI / 2);
    return abs(angle - round_angle) > (patience * (PI / 180));
}

void data_update(void *arg)
{

    Serial.println("data task start");

    // 用于保存上次时间。调用后系统自动更新
    static portTickType PreviousWakeTime;

    // 设置延时时间20ms，将时间转为节拍数
    const portTickType TimeIncrement = pdMS_TO_TICKS(10);
    static double posx = -10, posy = 20;
    double DATA_PERIOD = 0;
    long last_time = millis();

    // 获取当前系统时间
    PreviousWakeTime = xTaskGetTickCount();

    while (1)
    {
        vTaskDelayUntil(&PreviousWakeTime, TimeIncrement);
        DATA_PERIOD = (millis() - last_time) / 1000.0;

        last_time = millis();
        if (abs(0.01 - DATA_PERIOD) > 0.01)
        {
            Serial.printf("DATA_PERIOD = %f\n", DATA_PERIOD);
            DATA_PERIOD = 0.01;
        }
        if (robot_state.yaw_offset == 0)
        {
            robot_state.yaw_offset = imu.yaw;
        }
        if (robot_state.yaw_offset != 0)
        {
            robot_state.yaw = fmod(imu.yaw - robot_state.yaw_offset + 3 * PI, (2 * PI)) - PI;
            if ((robot_state.left_dis + robot_state.right_dis) < 33)
            { // 此时可以用来修正
                if (deflect(robot_state.yaw, 10))
                { // 说明偏移已经很严重
                    // 对robot_stateyawoffset进行修正
                    float idea_angle = robot_state.yaw > 0 ? int(robot_state.yaw / (PI / 2) + 0.5) : int(robot_state.yaw / (PI / 2) - 0.5); // 取最接近Pi/2
                    idea_angle *= (float)(PI / 2);
                    robot_state.yaw_offset = imu.yaw - idea_angle;
                }
            }
        }
        else
            robot_state.yaw = imu.yaw;

        robot_state.wz = (imu.gyroz + imu.lgyroz) / 2;
        robot_state.right_wheel_speed = enc1.get_speed();
        robot_state.left_wheel_speed = enc2.get_speed();
        robot_state.left_wheel_distance = enc2.get_distance();
        robot_state.right_wheel_distance = enc1.get_distance();

        robot_state.vx = (robot_state.right_wheel_speed + robot_state.left_wheel_speed) / 2;

        posx += (robot_state.vx * cos(robot_state.yaw)) * DATA_PERIOD;
        posy += (robot_state.vx * sin(robot_state.yaw)) * DATA_PERIOD;

        robot_state.odom_x = posx;
        robot_state.odom_y = posy;
        // for(int i=0;i<10;i++)
        // {
        //     if(ti_arr[i]!=0)
        //     {
        //         Serial.printf("%d ",ti_arr[(i+1)%10]-ti_arr[i]);
        //     }
        // }
        // Serial.println();
        //    Serial.printf("dis:%f\n",robot_state.forward_dis);
    }
}

void start_robot()
{
    enc1.init_hardware();
    enc2.init_hardware();

    // xTaskCreatePinnedToCore(task_robot, "task_robot", 4096, NULL, 4, NULL, 1);
    BaseType_t xReturned = xTaskCreatePinnedToCore(data_update, "  data_update", DATA_UPDATE_TASK_STACK_SIZE, NULL, DATA_UPDATE_TASK_PRIORITY, &data_update_handle, 0);
    if (xReturned == pdPASS)
    {
        Serial.println("[OS] data_read task created");
    }
    else
    {
        Serial.printf("[OS] data_read task created failed, code 0x%lx\n", xReturned);
    }
    // task_robot_timer_handler();

    auto timer = timerBegin(3, 80, true);                        // 初始化
    timerAttachInterrupt(timer, task_robot_timer_handler, true); // 调用中断函数
    timerAlarmWrite(timer, 10000, true);                         // timerBegin的参数二 80位80MHZ，这里为1000000  意思为1秒
    timerAlarmEnable(timer);                                     // 定时器使能
}
