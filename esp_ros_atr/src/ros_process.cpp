#include "ros_process.h"
#include "kalman.h"

#define ROSSERIAL_TCP 1
Matrix<2, 1> xv = {0, 0};
Matrix<2, 2> Pv = {1, 0, 0, 1};
Matrix<2, 2> Qv = {0.003, 0, 0, 0.003};
Matrix<2, 2> Rv = {0.02, 0, 0, 0.02};
Matrix<2, 2> Fv = {1, 0, 0, 1};
Matrix<2, 2> Hv = {1, 0, 0, 1};
Matrix<2, 2> Bv = {0, 0, 0, 0};
KalmanFilter2D odom_v(xv, Pv, Qv, Rv, Fv, Hv, Bv);

ros_imu_data_t ros_imu_data;
ros_odom_data_t ros_odom_data;
ros_speed_data_t ros_speed_data;
ros_distance_data_t ros_distance_data;
ros_motor_input_data_t ros_motor_input_data;
ros_motor_pid_output_data_t ros_motor_pid_output_data;
ros_expect_speed_data_t ros_expect_speed_data;
ros_euler_data_t ros_euler_data;
ros_cmd_t ros_cmd_data;
float ros_voltage_data;
// 创建ros节点
ros::NodeHandle nh;
// 创建发布者
sensor_msgs::Imu imu_msg;
ros::Publisher imu_pub("imu", &imu_msg);
std_msgs::Float32 voltage_msg;
ros::Publisher voltage_pub("voltage", &voltage_msg);
std_msgs::Float32MultiArray speed_msg;
ros::Publisher speed_pub("speed", &speed_msg);
std_msgs::Float32MultiArray expect_speed_msg;
ros::Publisher expect_speed_pub("expect_speed", &expect_speed_msg);
std_msgs::Float32MultiArray distance_msg;
ros::Publisher distance_pub("distance", &distance_msg);

std_msgs::Float32MultiArray motor_input_msg;
ros::Publisher motor_input_pub("motor_input", &motor_input_msg);

std_msgs::Float32MultiArray motor_pid_output_msg;
ros::Publisher motor_pid_output_pub("motor_pid_output", &motor_pid_output_msg);

nav_msgs::Odometry odom_msg;
ros::Publisher odom_pub("odom", &odom_msg);
// mutex
SemaphoreHandle_t xMutex = NULL;

geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;

char base_link[] = "/base_link";
char odom[] = "/odom";

// 创建订阅者

void host_out_cb(const std_msgs::String &msg)
{
  Serial.println(msg.data);
}
void flag_cb(const std_msgs::Int16MultiArray &msg)
{
  Serial.println(msg.data[0]);
}
void cmd_vel_cb(const geometry_msgs::Twist &msg)
{
  Serial.println(msg.linear.x);
  Serial.println(msg.angular.z);
  ros_cmd_data.cmd_vx = msg.linear.x;
  ros_cmd_data.cmd_vy = msg.linear.y;
  ros_cmd_data.cmd_wz = msg.angular.z;
}
ros::Subscriber<std_msgs::String> sub_host_out("ROS_HOST_OUTPUT", &host_out_cb);

ros::Subscriber<std_msgs::Int16MultiArray> flag_sub("ROS_HOST_INPUT", &flag_cb);

ros::Subscriber<geometry_msgs::Twist> cmd_vel_sub("cmd_vel", &cmd_vel_cb);

void broadcasttf()
{
  t.header.stamp = nh.now();
  t.header.frame_id = odom;
  t.child_frame_id = base_link;
  t.transform.translation.x = ros_odom_data.x;
  t.transform.translation.y = ros_odom_data.y;
  t.transform.translation.z = 0.0;
  t.transform.rotation = odom_msg.pose.pose.orientation;
  broadcaster.sendTransform(t);
}
// 创建服务
// ros::ServiceServer<std_msgs::Float32> srv("add_two_ints", &add);
// nh.advertiseService(srv);
// 创建客户端
// ros::ServiceClient<std_msgs::Float32> client("add_two_ints", &add);
// nh.serviceClient(client);
// 创建参数
// ros::Param<std_msgs::Float32> param("foo");
// nh.param("foo", param, 0.0);
// 创建时间

void ros_init(char *ip, int port)
{
  // 发布数据

#if ROSSERIAL_TCP
  IPAddress server;
  server.fromString(ip);
  nh.getHardware()->setConnection(server, port);
  nh.initNode();
  broadcaster.init(nh);

  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());
#else

  Serial2.begin(460800, SERIAL_8N1, 18, 17);

  nh.getHardware()->setPort(&Serial2);
  nh.getHardware()->setBaud(460800);

  nh.initNode();
#endif

  broadcaster.init(nh);
  nh.advertise(imu_pub);
  nh.advertise(voltage_pub);

  nh.advertise(odom_pub);
  // nh.advertise(expect_speed_pub);
  nh.subscribe(sub_host_out);
  nh.subscribe(flag_sub);
  nh.subscribe(cmd_vel_sub);

  // 初始化数据
  imu_msg.header.frame_id = "imu_link";
  imu_msg.header.stamp = nh.now();
  imu_msg.orientation_covariance[0] = 1e-6;
  imu_msg.orientation_covariance[4] = 1e-6;
  imu_msg.orientation_covariance[8] = 1e-6;

  imu_msg.angular_velocity_covariance[0] = 1e-5;
  imu_msg.angular_velocity_covariance[4] = 1e-5;
  imu_msg.angular_velocity_covariance[8] = 1e-5;

  imu_msg.linear_acceleration_covariance[0] = 1e-3;
  imu_msg.linear_acceleration_covariance[4] = 1e-3;
  imu_msg.linear_acceleration_covariance[8] = 1e-3;

  odom_msg.header.frame_id = "odom";
  odom_msg.child_frame_id = "base_link";
  odom_msg.pose.pose.position.x = 0;
  odom_msg.pose.pose.position.y = 0;
  odom_msg.pose.pose.position.z = 0;
  odom_msg.pose.pose.orientation.x = 0;
  odom_msg.pose.pose.orientation.y = 0;
  odom_msg.pose.pose.orientation.z = 0;
  odom_msg.pose.pose.orientation.w = 1;
  odom_msg.twist.twist.linear.x = 0;
  odom_msg.twist.twist.linear.y = 0;
  odom_msg.twist.twist.linear.z = 0;
  odom_msg.twist.twist.angular.x = 0;
  odom_msg.twist.twist.angular.y = 0;
  odom_msg.twist.twist.angular.z = 0;
  BaseType_t ros_task_t;
  ros_task_t = xTaskCreatePinnedToCore(ros_task, "ros_task", ROS_TASK_STACK_SIZE, NULL, ROS_TASK_PRIORITY, NULL, 1);

  if (ros_task_t != pdPASS)
  {
    Serial.println("[OS]Create ros_task failed");
    while (1)
      ;
  }
  else
  {
    Serial.println("[OS]Create ros_task success");
  }
}
void ros_publish_voltage()
{
  float voltage = analogRead(Bat_Pin) * 0.004816671;
  if (voltage < 11.2)
  {
    set_state(LOW_POWER);
  }
  else
  {
    if (LOW_POWER == get_state())
    {
      clear_state(LOW_POWER);
    }
  }

  voltage_msg.data = voltage;
  voltage_pub.publish(&voltage_msg);
}

void ros_publish_imu(float &ax, float &ay, float &az, float &gx, float &gy, float &gz, float &q0, float &q1, float &q2, float &q3)
{
  imu_msg.header.stamp = nh.now();
  imu_msg.linear_acceleration.x = ax * 9.8;
  imu_msg.linear_acceleration.y = ay * 9.8;
  imu_msg.linear_acceleration.z = az * 9.8;
  imu_msg.angular_velocity.x = gx;
  imu_msg.angular_velocity.y = gy;
  imu_msg.angular_velocity.z = gz;
  imu_msg.orientation.w = q0;
  imu_msg.orientation.x = q1;
  imu_msg.orientation.y = q2;
  imu_msg.orientation.z = q3;

  imu_pub.publish(&imu_msg);
}

void ros_publish_odom(float &x, float &y, float &z, float &vx, float &vy, float &vz, float &q0, float &q1, float &q2, float &q3)
{
  odom_msg.header.stamp = nh.now();
  odom_msg.pose.pose.position.x = x;
  odom_msg.pose.pose.position.y = y;
  odom_msg.pose.pose.position.z = z;
  odom_msg.twist.twist.linear.x = vx;
  odom_msg.twist.twist.linear.y = vy;
  odom_msg.twist.twist.linear.z = vz;
  odom_msg.pose.pose.orientation.w = q0;
  odom_msg.pose.pose.orientation.x = q1;
  odom_msg.pose.pose.orientation.y = q2;
  odom_msg.pose.pose.orientation.z = q3;
  odom_msg.pose.covariance[0] = 1e-7;
  odom_msg.pose.covariance[7] = 1e-7;
  odom_msg.pose.covariance[14] = 1e-7;
  odom_msg.pose.covariance[21] = 1e-7;
  odom_msg.pose.covariance[28] = 1e-7;
  odom_msg.pose.covariance[35] = 1e-7;

  odom_msg.twist.covariance[0] = odom_v.P(0, 0);
  odom_msg.twist.covariance[7] = odom_v.P(1, 1);
  odom_msg.twist.covariance[14] = 0;
  odom_msg.twist.covariance[21] = 0;
  odom_msg.twist.covariance[28] = 0;
  odom_msg.twist.covariance[35] = 1e-7;
  odom_pub.publish(&odom_msg);
}
void ros_twist_fitler(float vx, float vy)
{

  Matrix<2, 1> odom_zv = {vx, vy};

  odom_v.predict();
  odom_v.update(odom_zv);

  ros_odom_data.vx = odom_v.x(0);
  ros_odom_data.vy = odom_v.x(1);
  ros_odom_data.vz = 0;
}

void ros_task(void *pvParameters)
{
  int pre_freq = 500;
  int delay_time = 1000 / pre_freq;
  static portTickType PreviousWakeTime;

  static unsigned int imu_count = 0, voltage_count = 12, odom_count = 66, spin_count = 9, tf_count = 3; // sstart counter

  const uint32_t period_imu = pre_freq / freq_imu, period_voltage = pre_freq / freq_voltage, period_odom = pre_freq / freq_odom, period_spin = pre_freq / spin_freq, period_tf = pre_freq / tf_freq;
  xMutex = xSemaphoreCreateMutex();
  const portTickType TimeIncrement = pdMS_TO_TICKS(delay_time);
  PreviousWakeTime = xTaskGetTickCount();
  Serial.println("[OS]ros_task start");
  while (1)
  {
    vTaskDelayUntil(&PreviousWakeTime, TimeIncrement);
    if (nh.connected())
    {

      xSemaphoreTake(xMutex, portMAX_DELAY);

      if (imu_count++ % period_imu == 0)
      {
        ros_publish_imu(ros_imu_data.ax, ros_imu_data.ay, ros_imu_data.az, ros_imu_data.gx, ros_imu_data.gy,
                        ros_imu_data.gz, ros_imu_data.q0, ros_imu_data.q1, ros_imu_data.q2, ros_imu_data.q3);
      }
      if (voltage_count++ % period_voltage == 0)
      {
        ros_publish_voltage();
      }

      if (odom_count++ % period_odom == 0)
      {
        ros_publish_odom(ros_odom_data.x, ros_odom_data.y, ros_odom_data.z, ros_odom_data.vx, ros_odom_data.vy,
                         ros_odom_data.vz, ros_imu_data.q0, ros_imu_data.q1, ros_imu_data.q2, ros_imu_data.q3);
      }
      if (tf_count++ % period_tf == 0)
      {
        broadcasttf();
      }

      if (ROS_NOT_CONNECT)
      {
        clear_state(ROS_NOT_CONNECT);
      }
    }
    else
    {
      set_state(ROS_NOT_CONNECT);
    }
    if (spin_count++ % period_spin == 0)
    {

      nh.spinOnce();
    }
    xSemaphoreGive(xMutex);
    
  }
}