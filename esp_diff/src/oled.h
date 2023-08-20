#ifndef __OLEDDISPLAY_H__
#define __OLEDDISPLAY_H__


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
void oled_init();
void oled_show_connecting(String wifissid);
void oled_show_connection(String wifissid,String ip);

#endif