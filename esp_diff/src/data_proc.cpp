#include "data_proc.h"
#include "robot.h"
#include "serial.com.h"
#define measeureF 0
xSemaphoreHandle xSemaphore_data_send = NULL;

Ser_Comunicate ser_com(7, 6);
TimerHandle_t xTimer;
void vTimerCallback(TimerHandle_t pxTimer)
{
    // 在这个函数中，将flag4重置为初始值
    flag4 = 0;
    digitalWrite(8, HIGH);
}

void checkAndStartTimer(int flag)
{

    // 计算定时器的超时时间，这里是500000毫秒（500秒）
    const TickType_t xTimerPeriod = pdMS_TO_TICKS(50 * flag);

    // 如果定时器已经存在，停止并删除它
    if (xTimer != NULL)
    {
        // 停止定时器
        xTimerStop(xTimer, 0);
        // 删除定时器
        xTimerDelete(xTimer, 0);
        xTimer = NULL;
    }
    // 创建定时器
    xTimer = xTimerCreate(
        "MyTimer",     // 定时器的名称，
        xTimerPeriod,  // 定时器的周期
        pdFALSE,       // pdFALSE 表示这是一次性定时器，pdTRUE 表示这是自动重载定时器
        (void *)0,     // 定时器ID，这个值将作为定时器回调函数的参数
        vTimerCallback // 定时器回调函数
    );

    // 检查定时器是否创建成功
    if (xTimer == NULL)
    {
        // 定时器创建失败，处理错误...
    }
    else
    {
        // 启动定时器，立即开始计时，不阻塞
        if (xTimerStart(xTimer, 0) != pdPASS)
        {
            // 定时器启动失败，处理错误...
        }
        else
        {
            Serial.println("xTimerStart ok");
        }
    }
    digitalWrite(8, LOW);
}
Remote_node *node;
typedef struct
{
    uint8_t head1, head2;
    uint16_t length;
    uint32_t time;
    short odom_x;
    short odom_y;
    float yaw;
    float vx;
    // float wz;
    // short left_wheel_speed, right_wheel_speed;
    short left_wheel_distance, right_wheel_distance;
    uint8_t forword_dis, left_dis, right_dis, back_dis;
    uint32_t state_flags;
    uint32_t check;
} robot_state_data_t;
const size_t robot_data_size = sizeof(robot_state_data_t);
robot_state_data_t robot_state_data;

uint32_t check_sum(uint8_t *data, uint8_t len)
{
    uint32_t sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += data[i];
    }
    return sum;
}

void data_proc_cb(AsyncUDPPacket *packet)
{

    if (packet->length() > 0)
    {

        uint8_t *data = packet->data();

        if (packet->length() == 8)
        {
            if (data[0] == 0x55)
            {
                switch (data[1])
                {
                case 1:
                    robot_cmd.linear_x = (int)(*(int *)(data + 4));
                    // Serial.printf("linear_x:%f\n", robot_cmd.linear_x);
                    // robot_cmd.control_distance = 0;
                    break;
                case 2:
                    robot_cmd.angular_z = (float)(*(float *)(data + 4));
                    // Serial.printf("angular_z:%f\n", robot_cmd.angular_z);
                    // robot_cmd.control_angle = 0;
                    break;
                case 3:
                    robot_cmd.dis_x = (int)(*(int *)(data + 4));
                    // Serial.printf("dis_x:%f\n", robot_cmd.dis_x);
                    // robot_cmd.control_distance = 1;
                    break;
                case 4:
                    robot_cmd.angle_z = (float)(*(float *)(data + 4));
                    // Serial.printf("angle_z:%f\n", robot_cmd.angle_z);
                    // robot_cmd.control_angle = 1;
                    break;
                case 5:
                    flag1 = (*(uint8_t *)(data + 4));
                    flag2 = (*(uint8_t *)(data + 5));
                    flag3 = (*(uint8_t *)(data + 6));
                    flag4 = (*(uint8_t *)(data + 7));
                    // Serial.printf("flag1:%d,flag2:%d,flag3:%d,flag4:%d\n", flag1, flag2, flag3, flag4);
                    if (flag4 >= 2)
                    {
                        checkAndStartTimer(flag4);
                    }
                default:
                    break;
                }
            }
        }
        else
        {
            Serial.printf("data length error\n");
        }
    }
}

void ser_data_proc_cb(DataPacket *packet)
{

    if (packet->length() > 0)
    {

        uint8_t *data = packet->data();

        if (packet->length() == 8)
        {
            if (data[0] == 0x55)
            {
                switch (data[1])
                {
                case 1:
                    robot_cmd.linear_x = (int)(*(int *)(data + 4));
                    // Serial.printf("linear_x:%f\n", robot_cmd.linear_x);
                    // robot_cmd.control_distance = 0;
                    break;
                case 2:
                    robot_cmd.angular_z = (float)(*(float *)(data + 4));
                    // Serial.printf("angular_z:%f\n", robot_cmd.angular_z);
                    // robot_cmd.control_angle = 0;
                    break;
                case 3:
                    robot_cmd.dis_x = (int)(*(int *)(data + 4));
                    // Serial.printf("dis_x:%f\n", robot_cmd.dis_x);
                    // robot_cmd.control_distance = 1;
                    break;
                case 4:
                    robot_cmd.angle_z = (float)(*(float *)(data + 4));
                    // Serial.printf("angle_z:%f\n", robot_cmd.angle_z);
                    // robot_cmd.control_angle = 1;
                    break;
                case 5:
                    flag1 = (*(uint8_t *)(data + 4));
                    flag2 = (*(uint8_t *)(data + 5));
                    flag3 = (*(uint8_t *)(data + 6));
                    flag4 = (*(uint8_t *)(data + 7));
                    // Serial.printf("flag1:%d,flag2:%d,flag3:%d,flag4:%d\n", flag1, flag2, flag3, flag4);
                    if (flag4 >= 2)
                    {
                        checkAndStartTimer(flag4);
                    }
                default:
                    break;
                }
            }
        }
        else
        {
            Serial.printf("data length error\n");
        }
    }
}

void task_data_proc(void *pvParameter)
{

    TickType_t lasttick = xTaskGetTickCount();
#if measeureF
    int tick = 0, last_time, freq;
#endif
    while (1)
    {
        vTaskDelayUntil(&lasttick, 10);

        if (node == NULL)
        {

            node = udp.get_node("process_node");
            if (node != NULL)
            {
                Serial.println("[udpnode] node found");
                node->inited = 1;
                // udp.adversting = 0;
                // udp.node_finding = 0;
                node->data_cb = data_proc_cb;
            }
            else
            {
                Serial.println("[udpnode]node not found");
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        if (node != NULL && node->inited == 0)
        {
            node->inited = 1;
            node->data_cb = data_proc_cb;
            vTaskDelay(2 / portTICK_PERIOD_MS);
        }
        else if (node != NULL && node->inited == 1)
        {
            robot_state_data.head1 = 0x55;
            robot_state_data.head2 = 0xaa;
            robot_state_data.length = robot_data_size - 4; // 表示数据包的长度  除去head1,head2,length
            robot_state_data.odom_x = (short)robot_state.odom_x;
            robot_state_data.odom_y = (short)robot_state.odom_y;
            robot_state_data.yaw = robot_state.yaw;
            robot_state_data.vx = robot_state.vx;
            // robot_state_data.wz = robot_state.wz;
            // robot_state_data.left_wheel_speed = (short)robot_state.left_wheel_speed;
            // robot_state_data.right_wheel_speed = (short)robot_state.right_wheel_speed;
            robot_state_data.left_wheel_distance = (short)robot_state.left_wheel_distance;
            robot_state_data.right_wheel_distance = (short)robot_state.right_wheel_distance;
            robot_state_data.time = millis();
            robot_state_data.forword_dis = (uint8_t)constrain(robot_state.forward_dis, 0, 255);
            robot_state_data.left_dis = (uint8_t)constrain(robot_state.left_dis, 0, 255);
            robot_state_data.right_dis = (uint8_t)constrain(robot_state.right_dis, 0, 255);
            robot_state_data.back_dis = 0;
            robot_state_data.state_flags = robot_state.state_flags;
            robot_state_data.check = check_sum(((uint8_t *)&(robot_state_data)), robot_data_size - 4);
            node->send_data((uint8_t *)&robot_state_data, robot_data_size);
            // ser_com.write((uint8_t *)&robot_state_data, robot_data_size);
#if measeureF
            if (millis() - last_time > 1000)
            {
                freq = tick;

                Serial.printf("freq:%d\n", freq);
                tick = 0;
                last_time = millis();
            }
            tick++;
#endif
            // xSemaphoreGive(xSemaphore_data_send);
            // node->send_data(data_str);
            // vTaskDelay(5 / portTICK_PERIOD_MS);
            // Serial.printf("foword dis :%d,left_dis:%d,right dis:%d\n",robot_state_data.forword_dis,robot_state_data.left_dis,robot_state_data.right_dis);
        }
    }
}

void ser_task_data_proc(void *pvParameter)
{

    TickType_t lasttick = xTaskGetTickCount();
#if measeureF
    int tick = 0, last_time, freq;
#endif
    ser_com.begin(921600 / 8, &Serial2, ser_data_proc_cb);
    while (1)
    {
        vTaskDelayUntil(&lasttick, 10);

        robot_state_data.head1 = 0x55;
        robot_state_data.head2 = 0xaa;
        robot_state_data.length = robot_data_size - 4; // 表示数据包的长度  除去head1,head2,length
        robot_state_data.odom_x = (short)robot_state.odom_x;
        robot_state_data.odom_y = (short)robot_state.odom_y;
        robot_state_data.yaw = robot_state.yaw;
        robot_state_data.vx = robot_state.vx;
        // robot_state_data.wz = robot_state.wz;
        // robot_state_data.left_wheel_speed = (short)robot_state.left_wheel_speed;
        // robot_state_data.right_wheel_speed = (short)robot_state.right_wheel_speed;
        robot_state_data.left_wheel_distance = (short)robot_state.left_wheel_distance;
        robot_state_data.right_wheel_distance = (short)robot_state.right_wheel_distance;
        robot_state_data.time = millis();
        robot_state_data.forword_dis = (uint8_t)constrain(robot_state.forward_dis, 0, 255);
        robot_state_data.left_dis = (uint8_t)constrain(robot_state.left_dis, 0, 255);
        robot_state_data.right_dis = (uint8_t)constrain(robot_state.right_dis, 0, 255);
        robot_state_data.back_dis = 0;
        robot_state_data.state_flags = robot_state.state_flags;
        robot_state_data.check = check_sum(((uint8_t *)&(robot_state_data)), robot_data_size - 4);
        // node->send_data((uint8_t *)&robot_state_data, robot_data_size);
        ser_com.write((uint8_t *)&robot_state_data, robot_data_size); 
#if measeureF
        if (millis() - last_time > 1000)
        {
            freq = tick;

            Serial.printf("freq:%d\n", freq);
            tick = 0;
            last_time = millis();
        }
        tick++;
#endif
        // xSemaphoreGive(xSemaphore_data_send);
        // node->send_data(data_str);
        // vTaskDelay(5 / portTICK_PERIOD_MS);
        // Serial.printf("foword dis :%d,left_dis:%d,right dis:%d\n",robot_state_data.forword_dis,robot_state_data.left_dis,robot_state_data.right_dis);
    }
}

void tata_proc_init()
{
    xSemaphore_data_send = xSemaphoreCreateMutex();
    xTaskCreatePinnedToCore(task_data_proc,
                            "data_proc", 2048 * 6, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(ser_task_data_proc,
                            "ser_data_proc", 2048 * 6, NULL, 5, NULL, 0);
}

// #include "data_proc.h"
// #include "robot.h"
// #include "serial.com.h"
// #define measeureF 0
// TimerHandle_t xTimer;
// void vTimerCallback(TimerHandle_t pxTimer)
// {
//     // 在这个函数中，将flag4重置为初始值
//     flag4 = 0;
//     digitalWrite(8,HIGH);
// }

// void checkAndStartTimer()
// {

//     // 计算定时器的超时时间，这里是500000毫秒（500秒）
//     const TickType_t xTimerPeriod = pdMS_TO_TICKS(500);

//     // 如果定时器已经存在，停止并删除它
//     if (xTimer != NULL)
//     {
//         // 停止定时器
//         xTimerStop(xTimer, 0);
//         // 删除定时器
//         xTimerDelete(xTimer, 0);
//         xTimer = NULL;
//     }
//     // 创建定时器
//     xTimer = xTimerCreate(
//         "MyTimer",     // 定时器的名称，
//         xTimerPeriod,  // 定时器的周期
//         pdFALSE,       // pdFALSE 表示这是一次性定时器，pdTRUE 表示这是自动重载定时器
//         (void *)0,     // 定时器ID，这个值将作为定时器回调函数的参数
//         vTimerCallback // 定时器回调函数
//     );

//     // 检查定时器是否创建成功
//     if (xTimer == NULL)
//     {
//         // 定时器创建失败，处理错误...
//     }
//     else
//     {
//         // 启动定时器，立即开始计时，不阻塞
//         if (xTimerStart(xTimer, 0) != pdPASS)
//         {
//             // 定时器启动失败，处理错误...
//         }
//         else
//         {
//             Serial.println("xTimerStart ok");
//         }
//     }
//     digitalWrite(8,LOW);
// }

// typedef struct
// {
//     uint8_t head1, head2;
//     uint16_t length;
//     uint32_t time;
//     short odom_x;
//     short odom_y;
//     float yaw;
//     float vx;
//     float wz;
//     short left_wheel_speed, right_wheel_speed;
//     short left_wheel_distance, right_wheel_distance;
//     float dis;
//     uint32_t state_flags;
//     uint32_t check;
// } robot_state_data_t;
// const size_t robot_data_size = sizeof(robot_state_data_t);
// robot_state_data_t robot_state_data;

// uint32_t check_sum(uint8_t *data, uint8_t len)
// {
//     uint32_t sum = 0;
//     for (int i = 0; i < len; i++)
//     {
//         // if(i==0||i==(len-1)){
//         //     Serial.printf("data:%d\n",data[i]);
//         // }
//         sum += data[i];
//     }
//     return sum;
// }
// void data_proc_cb(DataPacket *packet)
// {

//     if (packet->length() > 0)
//     {

//         uint8_t *data = packet->data();

//         if (packet->length() == 8)
//         {
//             if (data[0] == 0x55)
//             {
//                 switch (data[1])
//                 {
//                 case 1:
//                     robot_cmd.linear_x = (int)(*(int *)(data + 4));
//                     Serial.printf("linear_x:%f\n", robot_cmd.linear_x);
//                     robot_cmd.control_distance = 0;
//                     break;
//                 case 2:
//                     robot_cmd.angular_z = (float)(*(float *)(data + 4));
//                     Serial.printf("angular_z:%f\n", robot_cmd.angular_z);
//                     robot_cmd.control_angle = 0;
//                     break;
//                 case 3:
//                     robot_cmd.dis_x = (int)(*(int *)(data + 4));
//                     Serial.printf("dis_x:%f\n", robot_cmd.dis_x);
//                     robot_cmd.control_distance = 1;
//                     break;
//                 case 4:
//                     robot_cmd.angle_z = (float)(*(float *)(data + 4));
//                     Serial.printf("angle_z:%f\n", robot_cmd.angle_z);
//                     robot_cmd.control_angle = 1;
//                     break;
//                 case 5:
//                     flag1 = (*(uint8_t *)(data + 4));
//                     flag2 = (*(uint8_t *)(data + 5));
//                     flag3 = (*(uint8_t *)(data + 6));
//                     flag4 = (*(uint8_t *)(data + 7));
//                     Serial.printf("flag1:%d,flag2:%d,flag3:%d,flag4:%d\n", flag1, flag2, flag3, flag4);
//                     if(flag4==4){
//                         checkAndStartTimer();
//                     }
//                 default:
//                     break;
//                 }
//             }
//         }
//         else
//         {
//             Serial.printf("data length error\n");
//         }
//     }
// }

// void task_data_proc(void *pvParameter)
// {

//     TickType_t lasttick = xTaskGetTickCount();
// #if measeureF
//     int tick = 0, last_time, freq;
// #endif
//     while (1)
//     {
//         vTaskDelayUntil(&lasttick, 10);
//         if (ser_com.remote_node_name == "")
//         {
//             vTaskDelay(1000 / portTICK_PERIOD_MS);
//             Serial.println("wait for node");
//         }
//         else if (ser_com.remote_node_name == "process_node")
//         {
//             //    Serial.println("send to process_node");
//             robot_state_data.head1 = 0x55;
//             robot_state_data.head2 = 0xaa;
//             robot_state_data.length = robot_data_size - 4; // 表示数据包的长度  除去head1,head2,length
//             robot_state_data.odom_x = (short)robot_state.odom_x;
//             robot_state_data.odom_y = (short)robot_state.odom_y;
//             robot_state_data.yaw = robot_state.yaw;
//             robot_state_data.vx = robot_state.vx;
//             robot_state_data.wz = robot_state.wz;
//             robot_state_data.left_wheel_speed = (short)robot_state.left_wheel_speed;
//             robot_state_data.right_wheel_speed = (short)robot_state.right_wheel_speed;
//             robot_state_data.left_wheel_distance = (short)robot_state.left_wheel_distance;
//             robot_state_data.right_wheel_distance = (short)robot_state.right_wheel_distance;
//             robot_state_data.time = millis();
//             robot_state_data.dis = robot_state.forward_dis;
//             robot_state_data.state_flags = robot_state.state_flags;
//             robot_state_data.check = check_sum(((uint8_t *)&(robot_state_data)), robot_data_size - 4);
//             // Serial.printf("data length:%d,check:%d \n",robot_data_size,robot_state_data.check);
//             // for (int i=0;i<robot_data_size;i++)
//             // {
//             //     Serial.printf("%d,",((uint8_t *)&(robot_state_data))[i]);
//             // }
//             ser_com.write((uint8_t *)&robot_state_data, robot_data_size);

// #if measeureF
//             if (millis() - last_time > 1000)
//             {
//                 freq = tick;

//                 Serial.printf("freq:%d\n", freq);
//                 tick = 0;
//                 last_time = millis();
//             }
//             tick++;
// #endif

//             // node->send_data(data_str);
//             // vTaskDelay(5 / portTICK_PERIOD_MS);
//         }
//     }
// }

// void tata_proc_init()
// {
//     xTaskCreatePinnedToCore(task_data_proc,
//                             "data_proc", 2048 * 6, NULL, 5, NULL, 1);
//     ser_com.begin(921600, &Serial2, data_proc_cb);
// }
