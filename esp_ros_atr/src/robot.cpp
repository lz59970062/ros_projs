#include "robot.h"
xTaskHandle data_read_handle;
float wz_from_wheel = 0;
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
    while (1)
    {
        count++;
        vTaskDelayUntil(&PreviousWakeTime, TimeIncrement);
        xSemaphoreTake(xMutex_pid, portMAX_DELAY);
        // if (count % 3 == 0)
        // {
        gyro_pid.setpoint = ros_cmd_data.cmd_wz;
        gyro_pid.input = ros_imu_data.gz;
        if (abs(gyro_pid.setpoint) < 0.001)
        {
            gyro_pid.error_sum = 0;
        }
        Gyro_pid();
        // }

        speed_pid1.setpoint = ros_expect_speed_data.exps1 + ros_cmd_data.cmd_vx - ros_cmd_data.cmd_vy - gyro_pid.output * (MEC_WHEEL_BASE / 2 + MEC_ACLE_BASE / 2);
        speed_pid2.setpoint = ros_expect_speed_data.exps2 + ros_cmd_data.cmd_vx + ros_cmd_data.cmd_vy + gyro_pid.output * (MEC_WHEEL_BASE / 2 + MEC_ACLE_BASE / 2);
        speed_pid3.setpoint = ros_expect_speed_data.exps3 + ros_cmd_data.cmd_vx + ros_cmd_data.cmd_vy - gyro_pid.output * (MEC_WHEEL_BASE / 2 + MEC_ACLE_BASE / 2);
        speed_pid4.setpoint = ros_expect_speed_data.exps4 + ros_cmd_data.cmd_vx - ros_cmd_data.cmd_vy + gyro_pid.output * (MEC_WHEEL_BASE / 2 + MEC_ACLE_BASE / 2);

        // speed_pid1.setpoint = ros_expect_speed_data.exps1 + ros_cmd_data.cmd_vx - ros_cmd_data.cmd_vy - ros_cmd_data.cmd_wz * (MEC_WHEEL_BASE / 2 + MEC_ACLE_BASE / 2);
        // speed_pid2.setpoint = ros_expect_speed_data.exps2 + ros_cmd_data.cmd_vx + ros_cmd_data.cmd_vy + ros_cmd_data.cmd_wz * (MEC_WHEEL_BASE / 2 + MEC_ACLE_BASE / 2);
        // speed_pid3.setpoint = ros_expect_speed_data.exps3 + ros_cmd_data.cmd_vx + ros_cmd_data.cmd_vy - ros_cmd_data.cmd_wz * (MEC_WHEEL_BASE / 2 + MEC_ACLE_BASE / 2);
        // speed_pid4.setpoint = ros_expect_speed_data.exps4 + ros_cmd_data.cmd_vx - ros_cmd_data.cmd_vy + ros_cmd_data.cmd_wz * (MEC_WHEEL_BASE / 2 + MEC_ACLE_BASE / 2);

        speed_pid1.input = enca.speed;
        speed_pid2.input = encb.speed;
        speed_pid3.input = encc.speed;
        speed_pid4.input = encd.speed;

        Speed_pid();

        xSemaphoreGive(xMutex_pid);
        // Serial.printf("sp:%f,%f,%f,%f\r",Motor_speed[0],Motor_speed[1],Motor_speed[2],Motor_speed[3]);
        // mot1.write(speed_pid1.output);
        // mot2.write(speed_pid2.output);
        // mot3.write(speed_pid3.output);
        // mot4.write(speed_pid4.output);
        mota.write(speed_pid1.output);
        motb.write(speed_pid2.output);
        motc.write(speed_pid3.output);
        motd.write(speed_pid4.output);
    }
}

void data_read(void *arg)
{

    Serial.println("data task start");

    // 用于保存上次时间。调用后系统自动更新
    static portTickType PreviousWakeTime;

    // 设置延时时间20ms，将时间转为节拍数
    const portTickType TimeIncrement = pdMS_TO_TICKS(10);
    static double posx = 0, posy = 0;
    const double DATA_PERIOD = 0.01;
    // 获取当前系统时间
    PreviousWakeTime = xTaskGetTickCount();
    while (1)
    {
        vTaskDelayUntil(&PreviousWakeTime, TimeIncrement);
        // ros_distance_data.distance1 = enc1.get_distance();
        // ros_distance_data.distance2 = enc2.get_distance();
        // ros_distance_data.distance3 = enc3.get_distance();
        // ros_distance_data.distance4 = enc4.get_distance();

        ros_speed_data.speed1 = enc1.get_speed();
        ros_speed_data.speed2 = enc2.get_speed();
        ros_speed_data.speed3 = enc3.get_speed();
        ros_speed_data.speed4 = enc4.get_speed();

        //   	R_Vel.RT_IX = (( R_Wheel_A.RT + R_Wheel_B.RT + R_Wheel_C.RT + R_Wheel_D.RT)/4)*1000;
        // R_Vel.RT_IY = ((-R_Wheel_A.RT + R_Wheel_B.RT + R_Wheel_C.RT - R_Wheel_D.RT)/4)*1000;
        // R_Vel.RT_IW = ((-R_Wheel_A.RT + R_Wheel_B.RT - R_Wheel_C.RT + R_Wheel_D.RT)/4/(MEC_WHEEL_BASE/2+MEC_ACLE_BASE/2))*1000;

        ros_twist_fitler((enca.speed + encb.speed + encc.speed + encd.speed) / 4,
                         (-enca.speed + encb.speed + encc.speed - encd.speed) / 4);

        posx += (ros_odom_data.vx * cos(ros_euler_data.yaw) - ros_odom_data.vy * sin(ros_euler_data.yaw)) * DATA_PERIOD;
        posy += (ros_odom_data.vx * sin(ros_euler_data.yaw) + ros_odom_data.vy * cos(ros_euler_data.yaw)) * DATA_PERIOD;

        ros_odom_data.x = posx;
        ros_odom_data.y = posy;
        ros_odom_data.z = 0;

        // Serial.printf("dis:%f, %f, %f, %f\n", ros_distance_data.distance1, ros_distance_data.distance2, ros_distance_data.distance3, ros_distance_data.distance4);
        // Serial.printf("sp: %f, %f, %f, %f\n", ros_speed_data.speed1, ros_speed_data.speed2, ros_speed_data.speed3, ros_speed_data.speed4);
        // ros_odom_data.x=sqrt_2/2*(ros_distance_data.distance1+ros_distance_data.distance2+ros_distance_data.distance3+ros_distance_data.distance4);
        // ros_odom_data.y=sqrt_2/2*(-ros_distance_data.distance1+ros_distance_data.distance2+ros_distance_data.distance3-ros_distance_data.distance4);
    }
}
void start_robot()
{
    enc1.init_hardware();
    enc2.init_hardware();
    enc3.init_hardware();
    enc4.init_hardware();
    xTaskCreatePinnedToCore(task_robot, "task_robot", 4096, NULL, 4, NULL, 1);
    BaseType_t xReturned = xTaskCreatePinnedToCore(data_read, "data_read", DATA_READ_TASK_STACK_SIZE, NULL, DATA_READ_TASK_PRIORITY, &data_read_handle, 0);
    if (xReturned == pdPASS)
    {
        Serial.println("[OS] data_read task created");
    }
    else
    {
        Serial.printf("[OS] data_read task created failed, code 0x%lx\n", xReturned);
    }
}
