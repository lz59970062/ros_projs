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
#include "oled.h"
#include "config.h"
#include "param.h"
#include "robot.h"
#include "data_proc.h"
#include "distance.hpp"

Param param;

void udp_task(void *arg);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  const int pin = 8;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  ws2812_init();
  set_state(WIFI_NOT_CONNECT);
  Serial.println("start init");
  Wire.begin(IIC_SDA, IIC_SCL, 400000);
  Wire1.begin(17,18,  400000);
  oled_init();
  motor_init();
  // enc1.init_hardware();
  // enc2.init_hardware();
  // mot1.write(480);
  // mot2.write(480);
  // while (1)
  // {
  //   delay(10);
  //   Serial.printf("1:%.3f 2:%.3f\n", enc1.get_speed(), enc2.get_speed());
  // }

  oled_show_connecting(WIFI_SSID);
  udp.begin(28288);
  set_state(ROS_NOT_CONNECT);
  delay(10);
  tata_proc_init();
  oled_show_connection(WIFI_SSID, WiFi.localIP().toString());
  param.begin_server();
  param.recover_param();
  imu.init();
  tof_setup();
  start_robot();
  BaseType_t xReturned;
  xReturned = xTaskCreatePinnedToCore(udp_task, "udp_task", UDP_TASK_STACK_SIZE, NULL, UDP_TASK_PRIORITY, NULL, 0);
  if (xReturned == pdPASS)
  {
    Serial.println("[OS] udp_task task created");
  }
  else
  {
    Serial.printf("[OS] udp_task task created failed, code 0x%lx\n", xReturned);
  }
}

void udp_task(void *arg)
{
  Remote_node *remote_node;
  SemaphoreHandle_t xMutex_udp;
  xMutex_udp = xSemaphoreCreateMutex();
  // pinMode(1, INPUT);

  while (1)
  {
    if (remote_node == NULL)
    {
      remote_node = udp.get_node("plot_node");
      if (remote_node != NULL)
      {
        Serial.println("[udpC] get plot_node");
        // udp.adversting = false;
        // udp.nodb false;
      }
      else
      {
        Serial.println("[udpC] get plot_node failed");
        // Serial.printf("adc:%f\n", analogRead(1)*3.3/4096.0*11.555/1.39);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
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
        str = String(speed_pid1.setpoint) + "," + String(speed_pid1.input) + "\n";
        remote_node->send_data(str);
        break;
      case 2:
        str = String(speed_pid2.setpoint) + "," + String(speed_pid2.input) + "\n";
        remote_node->send_data(str);
        break;
      case 3:
        str = String(gyro_pid.setpoint) + "," + String(gyro_pid.input) + "\n";
        remote_node->send_data(str);
        break;
      case 4:
        str = String(robot_state.yaw) + "\n";
        remote_node->send_data(str);
        break;
      case 5:
        str = String(speed_pid1.setpoint) + "," + String(speed_pid2.setpoint) + "\n";
        remote_node->send_data(str);
        break;
      case 6:
        str = String(speed_pid1.input) + "," + String(speed_pid2.input) + "\n";
        remote_node->send_data(str);
        break;

      case 7:
        str = String(speed_pid1.input) + "," + String(speed_pid1.error) + "," + String(speed_pid1.error_sum) + "," + String(speed_pid1.output) + "\n";
        remote_node->send_data(str);
        break;

      case 8:
        str = String(angle_pid.setpoint) + "," + String(angle_pid.input) + "\n";
        remote_node->send_data(str);
        break;
      case 9:
        str = String(robot_state.odom_x) + "," + String(robot_state.odom_y) + "\n";
        remote_node->send_data(str);
        break;
      case 10:
        str = String(Dis_x.setpoint) + "," + String(Dis_x.input) + "\n";
        remote_node->send_data(str);
        break;
      };

      xSemaphoreGive(xMutex_udp);
    }
    vTaskDelay(4);
  }
}

void loop()
{
  delay(10000000);
}
