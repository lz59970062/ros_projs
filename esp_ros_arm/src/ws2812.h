#ifndef __WS2812_H__
#define __WS2812_H__
#include <FastLED.h>
#include <Arduino.h>
#define LEDS_COUNT 1
#define LEDS_PIN LED_IO
#define CHANNEL 0
void ws2812_init(void);
void ws2812_set_color(uint8_t r, uint8_t g, uint8_t b);
void ws2812_show_blink();
void set_state(uint8_t state);
enum flag_t
{
  NORMAL,
  WIFI_NOT_CONNECT,
  ROS_NOT_CONNECT,
  LOW_POWER
};

struct led_con
{
  CRGB *led_color;
  uint8_t flag;
};
typedef struct led_con led_con_t;
extern led_con_t led_state;
#endif