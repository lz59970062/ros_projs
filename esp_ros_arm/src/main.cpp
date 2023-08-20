// #include <Arduino.h>
// #include <ESP32Servo.h>
// #include <ros.h>
// #include <std_msgs/Float32.h>
// #include "ws2812.h"
// #include "comunicate.h"
// #include <moveo_moveit/ArmJointState.h>
// #include <std_msgs/Int16.h>
// #include <std_msgs/UInt16.h>
// const char *ssid = "qaz";
// const char *password = "12345678";
// const char *ip = "192.168.218.240";
// int i = ARDUHAL_LOG_LEVEL_DEBUG;
// // Define the servo objects and PWM pins

// // Define the servo objects and PWM pins
// Servo servo1;
// int servo1Pin = Sev1; // PWM pin for servo 1

// Servo servo2;
// int servo2Pin = Sev2; // PWM pin for servo 2

// Servo servo3;
// int servo3Pin = Sev3; // PWM pin for servo 3

// Servo servo4;
// int servo4Pin = Sev4; // PWM pin for servo 4

// Servo servo5;
// int servo5Pin = Sev5; // PWM pin for servo 5

// Servo servo6;
// int servo6Pin = Sev6; // PWM pin for servo 6

// Servo &gripper = servo6;

// int joint_angle[6];

// std_msgs::Int16 msg;

// // instantiate publisher (for debugging purposes)
// // ros::Publisher angles("joint_angles_feedback",&msg);

// void arm_cb(const moveo_moveit::ArmJointState &arm_angles)
// {

//     joint_angle[0] = arm_angles.position1;
//     joint_angle[1] = arm_angles.position2;
//     joint_angle[2] = arm_angles.position3;
//     joint_angle[3] = arm_angles.position4;
//     joint_angle[4] = arm_angles.position5;
//     joint_angle[5] = arm_angles.position6; // gripper position <-135-135>
//     servo1.write(joint_angle[0]);
//     servo2.write(joint_angle[1]);
//     servo3.write(joint_angle[2]);
//     servo4.write(joint_angle[3]);
//     servo5.write(joint_angle[4]);
//     servo6.write(joint_angle[5]);
// }
// void gripper_cb(const std_msgs::UInt16 &cmd_msg)
// {
//     gripper.write(cmd_msg.data);              // Set servo angle, should be from 0-180
//     digitalWrite(13, HIGH - digitalRead(13)); // Toggle led
// }
// // Define the ROS node and publishers
// ros::NodeHandle nh;
// // instantiate subscribers
// ros::Subscriber<moveo_moveit::ArmJointState> arm_sub("joint_angles", arm_cb); // subscribes to joint_angles on arm
// ros::Subscriber<std_msgs::UInt16> gripper_sub("gripper_angle", gripper_cb);  // subscribes to gripper position
// // to publish from terminal: rostopic pub gripper_angle std_msgs/UInt16 <0-180>

// void setup()
// {
//     Serial.begin(115200);
//     Serial.println("Starting...");
//     servo1.attach(servo1Pin, 500, 2500);
//     servo2.attach(servo2Pin, 480, 2450);
//     servo3.attach(servo3Pin, 480, 2450);
//     servo4.attach(servo4Pin, 500, 2520);
//     servo5.attach(servo5Pin, 450, 2450);
//     servo6.attach(servo6Pin, 500, 2500);
//     servo1.write(0);
//     delay(500);
//     servo2.write(0);
//     delay(500);
//     servo3.write(0);
//     delay(500);
//     servo4.write(0);
//     delay(500);
//     servo5.write(0);
//     delay(500);
//     servo6.write(80);
//     ws2812_init();
//     set_state(WIFI_NOT_CONNECT);
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.print(".");
//     }
//     set_state(ROS_NOT_CONNECT);
//     udp.begin(28288);
//     Serial.println("WiFi connected");
//     Serial.println("IP address: ");
//     Serial.println(WiFi.localIP());
//     IPAddress server;
//     uint16_t port = 11412;

//     server.fromString(ip);

//     nh.getHardware()->setConnection(server, port);
//     delay(10);
//     nh.initNode();
//     nh.subscribe(arm_sub);
//     nh.subscribe(gripper_sub);
//     // Another way to get IP
//     Serial.print("IP = ");
//     Serial.println(nh.getHardware()->getLocalIP());

// }

// char str[13]; // Updated the size of the str array
// int angle[6]; // Updated to correct number of elements (6 instead of 5)

// void loop()
// {
//     // Serial.println(0.1);
//     if (nh.connected())
//     {
//         led_state.flag = 0;
//     }
//     else
//     {
//         set_state(ROS_NOT_CONNECT);
//     }

//     delay(2);
//     nh.spinOnce();
//     // delay(10);
// }

#include "Arduino.h"
#include <ESP32Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/JointState.h>
#include "ws2812.h"
#include "comunicate.h"
const char *ssid = "nano_ap";
const char *password = "12345678";
const char *ip = "192.168.195.239";
ros::NodeHandle nh;

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

Servo &gripper = servo6;
Servo &wrist = servo4;
Servo &elbow = servo3;
Servo &shoulder = servo2;
Servo &base = servo1;

double base_angle = 90;
double shoulder_angle = 90;
double elbow_angle = 90;
double wrist_angle = 90;

double prev_base = 0;
double prev_shoulder = 0;
double prev_elbow = 0;
double prev_wrist = 0;

int gripperState = 0;
int positionChanged = 0;
double radiansToDegrees(float position_radians);
static int start_joint_num = 4;
void servo_cb(const sensor_msgs::JointState &cmd_msg)
{
    static long last_ti;
    base_angle = radiansToDegrees(cmd_msg.position[0 + start_joint_num]);
    shoulder_angle = radiansToDegrees(cmd_msg.position[1 + start_joint_num]);
    elbow_angle = radiansToDegrees(cmd_msg.position[2 + start_joint_num]);
    wrist_angle = radiansToDegrees(cmd_msg.position[3 + start_joint_num]);

    base.write(base_angle);
    shoulder.write(shoulder_angle);
    elbow.write(elbow_angle);
    wrist.write(wrist_angle);
    servo5.write(radiansToDegrees(cmd_msg.position[4+ start_joint_num]));
    servo6.write(radiansToDegrees(cmd_msg.position[5+ start_joint_num]));


    if (prev_base == base_angle && prev_shoulder == shoulder_angle && prev_elbow == elbow_angle && prev_wrist == wrist_angle && positionChanged == 0)
    {
        if (gripperState == 0)
        {
            gripper.write(130);
            gripperState = 1;
        }
        else if (gripperState == 1)
        {
            gripper.write(90);
            gripperState = 0;
        }
        positionChanged = 1;
    }
    else if ((prev_base != base_angle || prev_shoulder != shoulder_angle || prev_elbow != elbow_angle || prev_wrist != wrist_angle) && positionChanged == 1)
    {
        positionChanged = 0;
    }

    prev_base = base_angle;
    prev_shoulder = shoulder_angle;
    prev_elbow = elbow_angle;
    prev_wrist = wrist_angle;
    long dt=millis()-last_ti;
    last_ti=millis();
    Serial.printf("dt:%d,base:%f,shoulder:%f,elbow:%f,wrist:%f\n", dt,base_angle, shoulder_angle, elbow_angle, wrist_angle);
}

ros::Subscriber<sensor_msgs::JointState> sub("joint_states", servo_cb);

void setup()
{
    Serial.begin(115200);
    servo1.attach(servo1Pin, 500, 2500);
    servo2.attach(servo2Pin, 500, 2500);
    servo3.attach(servo3Pin, 500, 2500);
    servo4.attach(servo4Pin, 500, 2500);
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
    // float cnt=0;
    // while(1){
    //     cnt+=0.1;
    //     servo3.write(sin(cnt)*90);
    //     servo2.write(cos(cnt)*45);
    //     servo4.write(sin(cnt)*45);
    //     delay(50);
    // }
    delay(1);
    ws2812_init();
   

#if ROSSERIAL_TCP
 set_state(WIFI_NOT_CONNECT);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    set_state(ROS_NOT_CONNECT);
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    IPAddress server;
    uint16_t port = 11412;
    server.fromString(ip);
    nh.getHardware()->setConnection(server, port);
    nh.initNode();
    broadcaster.init(nh);

    Serial.print("IP = ");
    Serial.println(nh.getHardware()->getLocalIP());
#else
    set_state(ROS_NOT_CONNECT);
    Serial2.begin(460800, SERIAL_8N1, 16, 17);

    nh.getHardware()->setPort(&Serial2);
    nh.getHardware()->setBaud(460800);

    nh.initNode();
#endif

    nh.subscribe(sub);

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
    servo6.write(130);
    delay(1);
}

void loop()
{
    if (nh.connected())
    {
        led_state.flag = 0;
    }
    else
    {
        set_state(ROS_NOT_CONNECT);
    }
    nh.spinOnce();
    delay(10);
}

double radiansToDegrees(float position_radians)
{
    position_radians = position_radians;
    return position_radians * 57.2958;
}
