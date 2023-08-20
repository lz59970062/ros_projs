#include "motor.h"
int Motor_Num = MOTOR_NUM;
// 定义消息队列

#if ENABLE_QUEUE == 1
xQueueHandle motor_q;
SemaphoreHandle_t xMutex_motor;
#endif
#if MOTOR_NUM == 4
Motor mot1(Motor1_A, Motor1_B);
Motor mot2(Motor2_A, Motor2_B);
Motor mot3(Motor3_A, Motor3_B,1);
Motor mot4(Motor4_A, Motor4_B,1);
Motor &mota=mot2;
Motor &motb=mot1;
Motor &motc=mot4;
Motor &motd=mot3;
#elif MOTOR_NUM == 2
Motor mot1(Motor1_A, Motor1_B, 1);
Motor mot2(Motor2_A, Motor2_B);
#endif

uint8_t chan_idx = 0;

Motor::Motor(int pina, int pinb, bool inv)
{
    this->pina = pina;
    this->pinb = pinb;
    this->inv = inv;
}
void Motor::begin()
{
    ch1 = chan_idx++;
    ch2 = chan_idx++;
    ledcSetup(ch1, freq, 10);
    ledcSetup(ch2, freq, 10);
    ledcAttachPin(pina, ch1);
    ledcAttachPin(pinb, ch2);
}
void Motor::write(int duty)
{
    
    inv ? duty = -duty : duty;
    now_input = duty;
    duty = constrain(duty, -max_duty, max_duty);
    // Serial.printf("duty %d ch1:%d ch2:%d  ", duty,ch1,ch2);
    ledcWrite(ch1, 512 - duty);
    ledcWrite(ch2, 512 + duty);
}
int Motor::get_input()
{
    return this->now_input;
}

#if ENABLE_QUEUE == 1
void motor_task(void *arg)
{
    short motor_duty[MOTOR_NUM];
    BaseType_t ret = pdPASS;
    while (1)
    {
        ret = xQueueReceive(motor_q,        // 消息队列的句柄
                            motor_duty,     // 发送的消息内容
                            portMAX_DELAY); // 等待时间 一直等
        if (ret == pdTRUE)
        {
            // Serial.printf("data rec %d,%d,%d,%d\n",motor_duty[0],motor_duty[1],motor_duty[2],motor_duty[3]);
            xSemaphoreTake(xMutex_motor, portMAX_DELAY);
#if MOTOR_NUM == 4
            mot1.write(motor_duty[0]);
            mot2.write(motor_duty[1]);
            mot3.write(motor_duty[2]);
            mot4.write(motor_duty[3]);
#elif MOTOR_NUM == 2
            mot1.write(motor_duty[0]);
            mot2.write(motor_duty[1]);
#endif
            xSemaphoreGive(xMutex_motor);
        }
        else
        {
            Serial.printf("err,code 0x%lx", ret);
        }
    }
}
#endif 
void motor_init()
{
    if (Motor_Num == 4)
    {

        mot1.begin();
        mot2.begin();
        mot3.begin();
        mot4.begin();
        mot1.write(0);
        mot2.write(0);
        mot3.write(0);
        mot4.write(0);
        Serial.println("4 motor init ok");
    }
    else if (Motor_Num == 2)
    {
        mot1.begin();
        mot2.begin();
        mot1.write(0);
        mot2.write(0);
        Serial.println("2 motor init ok");
    }
    // mot1.write(100);
    // mot2.write(100);
    // mot3.write(100);
    // mot4.write(100);
    // while(1)
    // delay(5000);
    #if ENABLE_QUEUE == 1
    motor_q = xQueueCreate(10, MOTOR_NUM * 2);
    if (motor_q != NULL)
    {
        Serial.println("电机消息队列创建成功");
    }
    else
    {
        Serial.println("电机消息队列创建失败");
    }
    xMutex_motor = xSemaphoreCreateMutex();
    
    xTaskCreatePinnedToCore(motor_task, "motor_task", MOTOR_TASK_STACK_SIZE, NULL, MOTOR_TASK_PRIORITY, NULL, 0);
    #endif
}
