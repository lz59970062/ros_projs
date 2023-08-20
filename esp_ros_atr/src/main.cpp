#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "encoder.h"
#include "motor.h"
#include "ws2812.h"
#include <math.h>
#include "JY901.h"
#include "comunicate.h"
#include "ros_process.h"
#include "config.h"
#include "param.h"
#include "robot.h"
Param param;

 
void udp_task(void *arg);
 
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  ws2812_init();
  set_state(WIFI_NOT_CONNECT);
  Serial.println("start init");
  motor_init();
  udp.begin(28288);

  delay(50);
  set_state(ROS_NOT_CONNECT);
  // ws2812_set_color(120, 0,120);
  ros_init(WIFI_REMOTE_IP, 11411);
  delay(30);
  param.begin_server();
  param.recover_param();
  BaseType_t xReturned;
  imu.init();
  start_robot();

  xReturned = xTaskCreatePinnedToCore(udp_task, "udp_task", UDP_TASK_STACK_SIZE, NULL, UDP_TASK_PRIORITY, NULL, 0);
  if (xReturned == pdPASS)
  {
    Serial.println("[OS] udp_task task created");
  }
  else
  {
    Serial.printf("[OS] udp_task task created failed, code 0x%lx\n", xReturned);
  }
  // //start scheduler
  // vTaskStartScheduler();
  // Serial.println("start scheduler failed");
}

void udp_task(void *arg)
{
  Remote_node *remote_node;
  SemaphoreHandle_t xMutex_udp;
  xMutex_udp = xSemaphoreCreateMutex();

  while (1)
  {
    if (remote_node == NULL)
    {
      remote_node = udp.get_node("process_node");
      if (remote_node != NULL)
      {
        Serial.println("[udpC] get process_node");
        udp.adversting = false;
        udp.node_finding = false;
      }
      else
      {
        Serial.println("[udpC] get process_node failed");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    }

    if (remote_node != NULL)
    {
      // Serial.println(remote_node->ip);
      String str;
      if (!flag1)
        vTaskDelay(1000);

      xSemaphoreTake(xMutex_udp, portMAX_DELAY);
      switch (flag1)
      {
      case 1:
        str = String(speed_pid1.setpoint) + "," + String(speed_pid1.input);
        udp.write_node(str, *remote_node);
        break;
      case 2:
        str = String(speed_pid2.setpoint) + "," + String(speed_pid2.input);
        udp.write_node(str, *remote_node);
        break;
      case 3:
        str = String(speed_pid3.setpoint) + "," + String(speed_pid3.input);
        udp.write_node(str, *remote_node);
        break;
      case 4:
        str = String(speed_pid4.setpoint) + "," + String(speed_pid4.input);
        udp.write_node(str, *remote_node);
        break;
      case 5:
        str = String(gyro_pid.setpoint) + "," + String(gyro_pid.input);
        udp.write_node(str, *remote_node);
        break;
      case 6:
        str = String(ros_imu_data.gz) + "," + String(gyro_pid.input) + "," + String(gyro_pid.setpoint) + "," + String(gyro_pid.output);
        udp.write_node(str, *remote_node);
        break;
      case 7:
        str = String(ros_odom_data.vx) + "," + String(Speed_x.setpoint);
        udp.write_node(str, *remote_node);
        break;
      case 8:
        str = String(ros_odom_data.vy) + "," + String(Speed_y.setpoint);
        udp.write_node(str, *remote_node);
        break;
      case 9:
        str = String(ros_euler_data.yaw) + "," + String(angle_pid.setpoint);
        udp.write_node(str, *remote_node);
        break;
      case 10:
        str = String(ros_odom_data.vx) + "," + String(ros_odom_data.vy) + "," + String(ros_odom_data.x) + "," + String(ros_odom_data.y);
        udp.write_node(str, *remote_node);
        break;
      case 11:
        str = String(ros_odom_data.x) + "," + String(Exd);
        udp.write_node(str, *remote_node);
        break;
      case 12:
        str = String(ros_odom_data.y) + "," + String(Eyd);
        udp.write_node(str, *remote_node);
        break;
      case 13:
        str = String(ros_imu_data.ax) + "," + String(ros_imu_data.ay) + "," + String(ros_imu_data.az);
        udp.write_node(str, *remote_node);
        break;
      case 14: // send Q
        str = String(ros_imu_data.q0, 4) + "," + String(ros_imu_data.q1, 4) + "," + String(ros_imu_data.q2, 4) + "," + String(ros_imu_data.q3, 4);
        udp.write_node(str, *remote_node);
        break;
      case 15:
        str = String(ros_euler_data.roll) + "," + String(ros_euler_data.pitch) + "," + String(ros_euler_data.yaw);
        udp.write_node(str, *remote_node);
        break;
      case 16:
        str = String(ros_speed_data.speed1) + "," + String(ros_speed_data.speed2) + "," + String(ros_speed_data.speed3) + "," + String(ros_speed_data.speed4);
        udp.write_node(str, *remote_node);
        break;
      };
      xSemaphoreGive(xMutex_udp);
    }
    vTaskDelay(4);
  }
}

void loop()
{
  delay(1000000);
}
