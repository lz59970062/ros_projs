#include "ws2812.h"
#define NUM_LEDS 1       //定义LED数量
#define LED_IO 26
#define DATA_PIN LED_IO  
CRGB leds[NUM_LEDS];     //定义CRGB的led灯数组

led_con_t led_state;
// struct led_cont_t led_con;
int cR[8] = { 255, 0, 0, 255, 255, 0, 255, 0 };
int cG[8] = { 0, 255, 0, 255, 0, 255, 255, 0 };
int cB[8] = { 0, 0, 255, 0, 255, 255, 255, 0 };



//0:normal 1:wifi_not_connect 2:ros not connect  3: low_power 
uint8_t get_state(uint8_t flag){//The purpose of this function is to determine the position of the highest set bit (the bit with the value of 1) in the binary representation of the input flag
  uint8_t state =0;
  for (int i=0;i<8;i++){
    if((flag>>i)&0x1){
      state=i;
    }
  }
  return state;
}
void ws2812_task(void* arg)
{
  Serial.println("ws2812_task start");
  while (1)
  {
    // Serial.println(get_state(led_state.flag));
    switch (get_state(led_state.flag))
    {
      case NORMAL:
        for (int a = 0; a < NUM_LEDS; a++)
        {
          for (int RGB = 0; RGB < 8; RGB++)
          {
            led_state.led_color[a].r = 180;
            led_state.led_color[a].g = 0;
            led_state.led_color[a].b = 180;
            FastLED.show();  //开始展示
            delay(100);
          }
        }
        break;
      case LOW_POWER:
        for (int a = 0; a < NUM_LEDS; a++)
        {
          led_state.led_color[a].r = 0;
          led_state.led_color[a].g = 0;
          led_state.led_color[a].b = 0;
          FastLED.show();  //开始展示
          delay(100);
        }
        break;
      case WIFI_NOT_CONNECT:
        for (int a = 0; a < NUM_LEDS; a++)
        {
          led_state.led_color[a].r = 255;
          led_state.led_color[a].g = 0;
          led_state.led_color[a].b = 0;
          FastLED.show();  //开始展示
          delay(100);
        }
        break;
      case ROS_NOT_CONNECT:
        for (int a = 0; a < NUM_LEDS; a++)
        {
          led_state.led_color[a].r = 0;
          led_state.led_color[a].g = 255;
          led_state.led_color[a].b = 0;
          FastLED.show();  //开始展示
          delay(100);
        }
        break;
      default:
        break;
    }
  }
}

void set_state(uint8_t state){
  uint8_t init_=1;
  led_state.flag|= state==0?0:init_<<state;
  
}
void clear_state(){
  led_state.flag=0;
}
void ws2812_init()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(80);
  // FastLED.show();
  led_state.led_color = leds;
  led_state.flag = NORMAL;
  BaseType_t xReturn = xTaskCreatePinnedToCore(ws2812_task,   /* Function to implement the task */
                                               "ws2812_task", /* Name of the task */
                                               1536,           /* Stack size in words */
                                               NULL,          /* Task input parameter */
                                               4,             /* Priority of the task */
                                               NULL,          /* Task handle. */
                                               1);            /* Core where the task should run */
  if (xReturn != pdPASS)
  {
    Serial.printf("create ws2812_task failed");
  }
  else{
    Serial.printf("create ws2812_task success");
  }
}
void ws2812_show_blink()
{
  //每个灯珠都走7种颜色（一个一个走），第一个走完7种颜色后到第二个开始走7种颜色，以此类推。
  for (int a = 0; a < NUM_LEDS; a++)
  {
    for (int RGB = 0; RGB < 8; RGB++)
    {
      leds[a].r = cR[RGB];
      leds[a].g = cG[RGB];
      leds[a].b = cB[RGB];
      FastLED.show();  //开始展示
      delay(500);      //延迟500毫秒
    }
  }

  //每一个LED灯逐个闪烁绿色
  // for(int i=0;i<NUM_LEDS;i++){
  //   leds[i] = CRGB::Green;
  //   FastLED.show();
  //   delay(3000);
  //   leds[i] = CRGB::Black;
  //   FastLED.show();
  //   delay(100);
  // }
  // delay(1000);

  //循环10次
  for (int k = 0; k < 10; k++)
  {
    //整个灯条 彩虹色渐变
    int h = 0;
    for (int j = 0; j < 225; j++)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CHSV((h + (255 / NUM_LEDS) * i), 255, 255);  //用HSV色彩空间不断改变H即可

        FastLED.show();
      }
      delay(1);
      h = (h + 2) % 255;
    }
  }

  FastLED.show();
  delay(1000);
}

void ws2812_set_color(uint8_t r, uint8_t g, uint8_t b)
{
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].r = r;
    leds[i].g = g;
    leds[i].b = b;
  }
  FastLED.show();
}