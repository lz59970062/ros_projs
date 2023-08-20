#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include "distance.hpp"
#include "robot.h"
VL53L0X sensor1(Wire1);
VL53L0X sensor2(Wire);
TOF tof;
void tof_task(void *arg)
{
    float last_forward_dis = 0, last_left_dis = 0, last_right_dis = 0;
    while (1)
    {
        robot_state.forward_dis = tof.ReadDistance() / 10.0;
        robot_state.forward_dis = last_forward_dis == 0 ? robot_state.forward_dis : (last_forward_dis + robot_state.forward_dis) / 2;
        last_forward_dis = robot_state.forward_dis;

        robot_state.right_dis = sensor2.readRangeContinuousMillimeters() / 10;
        robot_state.left_dis = sensor1.readRangeContinuousMillimeters() / 10;
        // robot_state.left_dis = last_left_dis == 0 ? robot_state.left_dis : (last_left_dis + robot_state.left_dis) / 2;
        // robot_state.right_dis = last_right_dis == 0 ? robot_state.right_dis : (last_right_dis + robot_state.right_dis) / 2;
        last_left_dis = robot_state.left_dis;
        last_right_dis = robot_state.right_dis;

        // Serial.printf("Range1 left: %d, Range2 right: %d,range3 forward: %d\n", (int)robot_state.left_dis, (int)robot_state.right_dis, (int)robot_state.forward_dis);
        vTaskDelay(40);
    }
}

void tof_setup()
{
    sensor1.init();
    sensor2.init();
    sensor1.setTimeout(500);
    sensor2.setTimeout(500);
    sensor1.startContinuous();
    sensor2.startContinuous();
    xTaskCreatePinnedToCore(tof_task, "tof_task", 2048*3, NULL, 5, NULL, 1);
}