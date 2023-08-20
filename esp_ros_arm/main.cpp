#include <Arduino.h>
#include <ESP32Servo.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include "ws2812.h"
#include "comunicate.h"
const char *ssid = "qaz";
const char *password = "12345678";
const char *ip = "192.168.149.239";
int i = ARDUHAL_LOG_LEVEL_DEBUG;
// Define the servo objects and PWM pins
Servo servo1;
int servo1Pin = Sev1; // PWM pin for servo 1

Servo servo2;
int servo2Pin = Sev2; // PWM pin for servo 2

Servo servo3;
int servo3Pin = Sev3; // PWM pin for servo 3

Servo servo4;
int servo4Pin = Sev4; // PWM pin for servo 4

Servo servo5;
int servo5Pin = Sev5; // PWM pin for servo 5

Servo servo6;
int servo6Pin = Sev6; // PWM pin for servo 6

// Define the ROS node and publishers
ros::NodeHandle nh;

std_msgs::Float32 joint1_msg;
// ros::Publisher joint1_pub("joint1_pos", &joint1_msg);

std_msgs::Float32 joint2_msg;
// ros::Publisher joint2_pub("joint2_pos", &joint2_msg);

std_msgs::Float32 joint3_msg;
// ros::Publisher joint3_pub("joint3_pos", &joint3_msg);

std_msgs::Float32 joint4_msg;
// ros::Publisher joint4_pub("joint4_pos", &joint4_msg);

std_msgs::Float32 joint5_msg;
// ros::Publisher joint5_pub("joint5_pos", &joint5_msg);

std_msgs::Float32 joint6_msg;
// ros::Publisher joint6_pub("joint5_pos", &joint6_msg);

// Define the callback functions for the joint position messages
void joint1_callback(const std_msgs::Float32 &msg)
{
    servo1.write(msg.data);
    Serial.printf("joint1:%f deg", msg.data);
}

void joint2_callback(const std_msgs::Float32 &msg)
{
    servo2.write(msg.data);
    Serial.printf("joint2:%f deg", msg.data);
}

void joint3_callback(const std_msgs::Float32 &msg)
{
    servo3.write(msg.data);
    Serial.printf("joint3:%f deg", msg.data);
}

void joint4_callback(const std_msgs::Float32 &msg)
{
    servo4.write(msg.data);
    Serial.printf("joint4:%f deg", msg.data);
}
void joint5_callback(const std_msgs::Float32 &msg)
{
    servo5.write(msg.data);
    Serial.printf("joint5:%f deg", msg.data);
}
void joint6_callback(const std_msgs::Float32 &msg)
{
    servo6.write(msg.data);
    Serial.printf("joint6:%f deg", msg.data);
}

ros::Subscriber<std_msgs::Float32> joint1_sub("joint1_sub", &joint1_callback);
ros::Subscriber<std_msgs::Float32> joint2_sub("joint2_sub", &joint2_callback);
ros::Subscriber<std_msgs::Float32> joint3_sub("joint3_sub", &joint3_callback);
ros::Subscriber<std_msgs::Float32> joint4_sub("joint4_sub", &joint4_callback);
ros::Subscriber<std_msgs::Float32> joint5_sub("joint5_sub", &joint5_callback);
ros::Subscriber<std_msgs::Float32> joint6_sub("joint6_sub", &joint6_callback);
void setup()
{
    Serial.begin(115200);
    Serial.println("Starting...");
    servo1.attach(servo1Pin, 500, 2500);
    servo2.attach(servo2Pin, 480, 2450);
    servo3.attach(servo3Pin, 480, 2450);
    servo4.attach(servo4Pin, 500, 2520);
    servo5.attach(servo5Pin, 450, 2450);
    servo6.attach(servo6Pin, 500, 2500);
    servo1.write(0);
    delay(500);
    servo2.write(0);
    delay(500);
    servo3.write(0);
    delay(500);
    servo4.write(0);
    delay(500);
    servo5.write(0);
    delay(500);
    servo6.write(80);
    ws2812_init();
    set_state(WIFI_NOT_CONNECT);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    set_state(ROS_NOT_CONNECT);
    udp.begin(28288);
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    IPAddress server;
    uint16_t port = 11411;

    server.fromString(ip);

    nh.getHardware()->setConnection(server, port);
    delay(10);
    nh.initNode();

    // Another way to get IP
    Serial.print("IP = ");
    Serial.println(nh.getHardware()->getLocalIP());

    // nh.advertise(joint1_pub);
    // nh.advertise(joint2_pub);
    // nh.advertise(joint3_pub);
    // nh.advertise(joint4_pub);
    // nh.advertise(joint5_pub);
    // nh.advertise(joint6_pub);
    // Subscribe to the joint position messages

    nh.subscribe(joint1_sub);
    nh.subscribe(joint2_sub);
    nh.subscribe(joint3_sub);
    nh.subscribe(joint4_sub);
    nh.subscribe(joint5_sub);
    nh.subscribe(joint6_sub);
    joint1_msg.data = 0;
    joint2_msg.data = 0;
    joint3_msg.data = 0;
    joint4_msg.data = 0;
    joint5_msg.data = 0;
    joint6_msg.data = 0;
}

char str[13]; // Updated the size of the str array
int angle[6]; // Updated to correct number of elements (6 instead of 5)

void loop()
{
    // Serial.println(0.1);
    if (nh.connected())
    {
        led_state.flag = 0;
    }
    else
    {
        set_state(ROS_NOT_CONNECT);
    }
    delay(2);
    nh.spinOnce();
    // delay(10);
}
