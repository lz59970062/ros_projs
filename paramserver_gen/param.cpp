#include "param.h"
float  ksp1,ksi1,ksd1,exps1,ksp2,ksi2,ksd2,exps2;
float  kgp,kgi,kgd,expg,kap,kai,kad,expa,KSxp,KSxi,KSxd,Exs,KDxp,KDxi,KDxd,Exd;
int  flag4, savep, flag1, flag2, flag3;
const char *var_list0[]={"ksp1","ksi1","ksd1","exps1","ksp2","ksi2","ksd2","exps2","flag1","flag2","flag3","flag4","savep"};
const char *var_list1[]={"kgp","kgi","kgd","expg","kap","kai","kad","expa","KSxp","KSxi","KSxd","Exs","KDxp","KDxi","KDxd","Exd","savep"};
String processor_page0(const String &var){
if(var==var_list0[0]){
return String(ksp1,4);
}
else if(var==var_list0[0]){
return String(ksp1,4);
}
else if(var==var_list0[1]){
return String(ksi1,4);
}
else if(var==var_list0[2]){
return String(ksd1,4);
}
else if(var==var_list0[3]){
return String(exps1,4);
}
else if(var==var_list0[4]){
return String(ksp2,4);
}
else if(var==var_list0[5]){
return String(ksi2,4);
}
else if(var==var_list0[6]){
return String(ksd2,4);
}
else if(var==var_list0[7]){
return String(exps2,4);
}
else if(var==var_list0[8]){
return String(flag1);
}
else if(var==var_list0[9]){
return String(flag2);
}
else if(var==var_list0[10]){
return String(flag3);
}
else if(var==var_list0[11]){
return String(flag4);
}
else if(var==var_list0[12]){
return String(savep);
}
else return String();
}
String processor_page1(const String &var){
if(var==var_list1[0]){
return String(kgp,4);
}
else if(var==var_list1[0]){
return String(kgp,4);
}
else if(var==var_list1[1]){
return String(kgi,4);
}
else if(var==var_list1[2]){
return String(kgd,4);
}
else if(var==var_list1[3]){
return String(expg,4);
}
else if(var==var_list1[4]){
return String(kap,4);
}
else if(var==var_list1[5]){
return String(kai,4);
}
else if(var==var_list1[6]){
return String(kad,4);
}
else if(var==var_list1[7]){
return String(expa,4);
}
else if(var==var_list1[8]){
return String(KSxp,4);
}
else if(var==var_list1[9]){
return String(KSxi,4);
}
else if(var==var_list1[10]){
return String(KSxd,4);
}
else if(var==var_list1[11]){
return String(Exs,4);
}
else if(var==var_list1[12]){
return String(KDxp,4);
}
else if(var==var_list1[13]){
return String(KDxi,4);
}
else if(var==var_list1[14]){
return String(KDxd,4);
}
else if(var==var_list1[15]){
return String(Exd,4);
}
else if(var==var_list1[16]){
return String(savep);
}
else return String();
}
void Param::begin_server(){
  SPIFFS.begin();
  AsyncWebServer::on("/", HTTP_GET, [](AsyncWebServerRequest *request){request->send(SPIFFS, "/setting1.html", String(), false,processor_page0);});
  AsyncWebServer::on("/setting1.html", HTTP_GET, [](AsyncWebServerRequest *request){request->send(SPIFFS,"/setting1.html", String(), false,processor_page0);});
  AsyncWebServer::on("/setting2.html", HTTP_GET, [](AsyncWebServerRequest *request){request->send(SPIFFS,"/setting2.html", String(), false,processor_page1);});
  AsyncWebServer::on("/setting1.html", HTTP_POST, [](AsyncWebServerRequest *request){
        int params = request->params();
        for (int i = 0; i < params; i++)
        {
AsyncWebParameter *p = request->getParam(i);
if (p->isPost())
            {  if(p->name()=="ksp1"){
    ksp1=p->value().toFloat();
  }
  else if(p->name()=="ksi1"){
    ksi1=p->value().toFloat();
  }
  else if(p->name()=="ksd1"){
    ksd1=p->value().toFloat();
  }
  else if(p->name()=="exps1"){
    exps1=p->value().toFloat();
  }
  else if(p->name()=="ksp2"){
    ksp2=p->value().toFloat();
  }
  else if(p->name()=="ksi2"){
    ksi2=p->value().toFloat();
  }
  else if(p->name()=="ksd2"){
    ksd2=p->value().toFloat();
  }
  else if(p->name()=="exps2"){
    exps2=p->value().toFloat();
  }
  else if(p->name()=="flag1"){
    flag1=p->value().toInt();
  }
  else if(p->name()=="flag2"){
    flag2=p->value().toInt();
  }
  else if(p->name()=="flag3"){
    flag3=p->value().toInt();
  }
  else if(p->name()=="flag4"){
    flag4=p->value().toInt();
  }
  else if(p->name()=="savep"){
    savep=p->value().toInt();
  }
}}
request->send(SPIFFS,"/setting1.html", String(), false,processor_page0);}); 
  AsyncWebServer::on("/setting2.html", HTTP_POST, [](AsyncWebServerRequest *request){
        int params = request->params();
        for (int i = 0; i < params; i++)
        {
AsyncWebParameter *p = request->getParam(i);
if (p->isPost())
            {  if(p->name()=="kgp"){
    kgp=p->value().toFloat();
  }
  else if(p->name()=="kgi"){
    kgi=p->value().toFloat();
  }
  else if(p->name()=="kgd"){
    kgd=p->value().toFloat();
  }
  else if(p->name()=="expg"){
    expg=p->value().toFloat();
  }
  else if(p->name()=="kap"){
    kap=p->value().toFloat();
  }
  else if(p->name()=="kai"){
    kai=p->value().toFloat();
  }
  else if(p->name()=="kad"){
    kad=p->value().toFloat();
  }
  else if(p->name()=="expa"){
    expa=p->value().toFloat();
  }
  else if(p->name()=="KSxp"){
    KSxp=p->value().toFloat();
  }
  else if(p->name()=="KSxi"){
    KSxi=p->value().toFloat();
  }
  else if(p->name()=="KSxd"){
    KSxd=p->value().toFloat();
  }
  else if(p->name()=="Exs"){
    Exs=p->value().toFloat();
  }
  else if(p->name()=="KDxp"){
    KDxp=p->value().toFloat();
  }
  else if(p->name()=="KDxi"){
    KDxi=p->value().toFloat();
  }
  else if(p->name()=="KDxd"){
    KDxd=p->value().toFloat();
  }
  else if(p->name()=="Exd"){
    Exd=p->value().toFloat();
  }
  else if(p->name()=="savep"){
    savep=p->value().toInt();
  }
}}
request->send(SPIFFS,"/setting2.html", String(), false,processor_page1);}); 
AsyncWebServer::begin();
    Serial.println("Server started at http://");
    Serial.println(WiFi.localIP());
}

void Param::recover_param()
{
    ksp1 = speed_pid1.kp;
    ksi1 = speed_pid1.ki;
    ksd1 = speed_pid1.kd;
    ksp2 = speed_pid2.kp;
    ksi2 = speed_pid2.ki;
    ksd2 = speed_pid2.kd;

 
     
    kgp = gyro_pid.kp;
    kgi = gyro_pid.ki;
    kgd = gyro_pid.kd;
    kap = angle_pid.kp;
    kai = angle_pid.ki;
    kad = angle_pid.kd;


    KSxp = Speed_x.kp;
    KSxi = Speed_x.ki;
    KSxd = Speed_x.kd;
     
    KDxp = Distance_x.kp;
    KDxi = Distance_x.ki;
    KDxd = Distance_x.kd;


  

    

    // get_flag(&flag1,&flag2,&flag3,&flag4);
}