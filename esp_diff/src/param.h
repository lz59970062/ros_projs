#ifndef __PARAM_H__
#define __PARAM_H__
#include <Arduino.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "pid.h"
#include "config.h"
 
class Param : public AsyncWebServer
{
public:
    Param() : AsyncWebServer(80)
    {
    }
    void begin_server();
    void recover_param();
    void save_flag();
    void get_flag(int *flag1,int *flag2,int *flag3,int *flag4);
    
};
extern int flag1,flag2,flag3,flag4;

#endif
