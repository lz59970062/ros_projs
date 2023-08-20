#include "param.h"
float  ksp1,ksi1,ksd1,exps1,ksp2,ksi2,ksd2,exps2,ksp3,ksi3,ksd3,exps3,ksp4,ksi4,ksd4,exps4,kdp1,kdi1,kdd1,expd1,kdp2,kdi2,kdd2,expd2,kdp3,kdi3,kdd3,expd3,kdp4,kdi4,kdd4,expd4;
float  kgp,kgi,kgd,expg,kap,kai,kad,expa,KSxp,KSxi,KSxd,Exs,KSyp,KSyi,KSyd,Eys,KDxp,KDxi,KDxd,Exd,KDyp,KDyi,KDyd,Eyd;
int  flag1, flag4, savep, flag3, flag2;
const char *var_list0[]={"ksp1","ksi1","ksd1","exps1","ksp2","ksi2","ksd2","exps2","ksp3","ksi3","ksd3","exps3","ksp4","ksi4","ksd4","exps4","kdp1","kdi1","kdd1","expd1","kdp2","kdi2","kdd2","expd2","kdp3","kdi3","kdd3","expd3","kdp4","kdi4","kdd4","expd4","flag1","flag2","flag3","flag4","savep"};
const char *var_list1[]={"kgp","kgi","kgd","expg","kap","kai","kad","expa","KSxp","KSxi","KSxd","Exs","KSyp","KSyi","KSyd","Eys","KDxp","KDxi","KDxd","Exd","KDyp","KDyi","KDyd","Eyd","savep"};
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
return String(ksp3,4);
}
else if(var==var_list0[9]){
return String(ksi3,4);
}
else if(var==var_list0[10]){
return String(ksd3,4);
}
else if(var==var_list0[11]){
return String(exps3,4);
}
else if(var==var_list0[12]){
return String(ksp4,4);
}
else if(var==var_list0[13]){
return String(ksi4,4);
}
else if(var==var_list0[14]){
return String(ksd4,4);
}
else if(var==var_list0[15]){
return String(exps4,4);
}
else if(var==var_list0[16]){
return String(kdp1,4);
}
else if(var==var_list0[17]){
return String(kdi1,4);
}
else if(var==var_list0[18]){
return String(kdd1,4);
}
else if(var==var_list0[19]){
return String(expd1,4);
}
else if(var==var_list0[20]){
return String(kdp2,4);
}
else if(var==var_list0[21]){
return String(kdi2,4);
}
else if(var==var_list0[22]){
return String(kdd2,4);
}
else if(var==var_list0[23]){
return String(expd2,4);
}
else if(var==var_list0[24]){
return String(kdp3,4);
}
else if(var==var_list0[25]){
return String(kdi3,4);
}
else if(var==var_list0[26]){
return String(kdd3,4);
}
else if(var==var_list0[27]){
return String(expd3,4);
}
else if(var==var_list0[28]){
return String(kdp4,4);
}
else if(var==var_list0[29]){
return String(kdi4,4);
}
else if(var==var_list0[30]){
return String(kdd4,4);
}
else if(var==var_list0[31]){
return String(expd4,4);
}
else if(var==var_list0[32]){
return String(flag1);
}
else if(var==var_list0[33]){
return String(flag2);
}
else if(var==var_list0[34]){
return String(flag3);
}
else if(var==var_list0[35]){
return String(flag4);
}
else if(var==var_list0[36]){
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
return String(KSyp,4);
}
else if(var==var_list1[13]){
return String(KSyi,4);
}
else if(var==var_list1[14]){
return String(KSyd,4);
}
else if(var==var_list1[15]){
return String(Eys,4);
}
else if(var==var_list1[16]){
return String(KDxp,4);
}
else if(var==var_list1[17]){
return String(KDxi,4);
}
else if(var==var_list1[18]){
return String(KDxd,4);
}
else if(var==var_list1[19]){
return String(Exd,4);
}
else if(var==var_list1[20]){
return String(KDyp,4);
}
else if(var==var_list1[21]){
return String(KDyi,4);
}
else if(var==var_list1[22]){
return String(KDyd,4);
}
else if(var==var_list1[23]){
return String(Eyd,4);
}
else if(var==var_list1[24]){
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
    speed_pid1.kp=ksp1;
  }
  else if(p->name()=="ksi1"){
    ksi1=p->value().toFloat();
    speed_pid1.ki=ksi1;
  }
  else if(p->name()=="ksd1"){
    ksd1=p->value().toFloat();
    speed_pid1.kd=ksd1;
  }
  else if(p->name()=="exps1"){
    exps1=p->value().toFloat();
    ros_expect_speed_data.exps1=exps1;
  }
  else if(p->name()=="ksp2"){
    ksp2=p->value().toFloat();
    speed_pid2.kp=ksp2;
  }
  else if(p->name()=="ksi2"){
    ksi2=p->value().toFloat();
    speed_pid2.ki=ksi2;
  }
  else if(p->name()=="ksd2"){
    ksd2=p->value().toFloat();
    speed_pid2.kd=ksd2;
  }
  else if(p->name()=="exps2"){
    exps2=p->value().toFloat();
    ros_expect_speed_data.exps2=exps2;

  }
  else if(p->name()=="ksp3"){
    ksp3=p->value().toFloat();
    speed_pid3.kp=ksp3;
  }
  else if(p->name()=="ksi3"){
    ksi3=p->value().toFloat();
    speed_pid3.ki=ksi3;
  }
  else if(p->name()=="ksd3"){
    ksd3=p->value().toFloat();
    speed_pid3.kd=ksd3;
  }
  else if(p->name()=="exps3"){
    exps3=p->value().toFloat();
    ros_expect_speed_data.exps3=exps3;
  }
  else if(p->name()=="ksp4"){
    ksp4=p->value().toFloat();
    speed_pid4.kp=ksp4;
  }
  else if(p->name()=="ksi4"){
    ksi4=p->value().toFloat();
    speed_pid4.ki=ksi4;
  }
  else if(p->name()=="ksd4"){
    ksd4=p->value().toFloat();
    speed_pid4.kd=ksd4;
  }
  else if(p->name()=="exps4"){
    exps4=p->value().toFloat();
    ros_expect_speed_data.exps4=exps4;
  }
  else if(p->name()=="kdp1"){
    kdp1=p->value().toFloat();

  }
  else if(p->name()=="kdi1"){
    kdi1=p->value().toFloat();
  }
  else if(p->name()=="kdd1"){
    kdd1=p->value().toFloat();
  }
  else if(p->name()=="expd1"){
    expd1=p->value().toFloat();
  }
  else if(p->name()=="kdp2"){
    kdp2=p->value().toFloat();
  }
  else if(p->name()=="kdi2"){
    kdi2=p->value().toFloat();
  }
  else if(p->name()=="kdd2"){
    kdd2=p->value().toFloat();
  }
  else if(p->name()=="expd2"){
    expd2=p->value().toFloat();
  }
  else if(p->name()=="kdp3"){
    kdp3=p->value().toFloat();
  }
  else if(p->name()=="kdi3"){
    kdi3=p->value().toFloat();
  }
  else if(p->name()=="kdd3"){
    kdd3=p->value().toFloat();
  }
  else if(p->name()=="expd3"){
    expd3=p->value().toFloat();
  }
  else if(p->name()=="kdp4"){
    kdp4=p->value().toFloat();
  }
  else if(p->name()=="kdi4"){
    kdi4=p->value().toFloat();
  }
  else if(p->name()=="kdd4"){
    kdd4=p->value().toFloat();
  }
  else if(p->name()=="expd4"){
    expd4=p->value().toFloat();
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
    if(savep==1){
      save_all_param();
    }
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
    gyro_pid.kp=kgp;
  }
  else if(p->name()=="kgi"){
    kgi=p->value().toFloat();
    gyro_pid.ki=kgi;
  }
  else if(p->name()=="kgd"){
    kgd=p->value().toFloat();
    gyro_pid.kd=kgd;
  }
  else if(p->name()=="expg"){
    expg=p->value().toFloat();
    ros_cmd_data.cmd_wz=expg;
  }
  else if(p->name()=="kap"){
    kap=p->value().toFloat();
    angle_pid.kp=kap;

  }
  else if(p->name()=="kai"){
    kai=p->value().toFloat();
    angle_pid.ki=kai;
  }
  else if(p->name()=="kad"){
    kad=p->value().toFloat();
    angle_pid.kd=kad;
  }
  else if(p->name()=="expa"){
    expa=p->value().toFloat();
    angle_pid.setpoint=expa;
  }
  else if(p->name()=="KSxp"){
    KSxp=p->value().toFloat();
    Speed_x.kp=KSxp;
  }
  else if(p->name()=="KSxi"){
    KSxi=p->value().toFloat();
    Speed_x.ki=KSxi;
  }
  else if(p->name()=="KSxd"){
    KSxd=p->value().toFloat();
    Speed_x.kd=KSxd;
  }
  else if(p->name()=="Exs"){
    Exs=p->value().toFloat();
    ros_cmd_data.cmd_vx=Exs;
  }
  else if(p->name()=="KSyp"){
    KSyp=p->value().toFloat();
    Speed_y.kp=KSyp;
  }
  else if(p->name()=="KSyi"){
    KSyi=p->value().toFloat();
    Speed_y.ki=KSyi;
  }
  else if(p->name()=="KSyd"){
    KSyd=p->value().toFloat();
    Speed_y.kd=KSyd;
  }
  else if(p->name()=="Eys"){
    Eys=p->value().toFloat();
    ros_cmd_data.cmd_vy=Eys;
  }
  else if(p->name()=="KDxp"){
    KDxp=p->value().toFloat();
    Dis_x.kp=KDxp;
  
  }
  else if(p->name()=="KDxi"){
    KDxi=p->value().toFloat();
    Dis_x.ki=KDxi;
  }
  else if(p->name()=="KDxd"){
    KDxd=p->value().toFloat();
    Dis_x.kd=KDxd;
  }
  else if(p->name()=="Exd"){
    Exd=p->value().toFloat();
    Dis_x.setpoint=Exd;
  }
  else if(p->name()=="KDyp"){
    KDyp=p->value().toFloat();
    Dis_y.kp=KDyp;
  }
  else if(p->name()=="KDyi"){
    KDyi=p->value().toFloat();
    Dis_y.ki=KDyi;
  }
  else if(p->name()=="KDyd"){
    KDyd=p->value().toFloat();
    Dis_y.kd=KDyd;
  }
  else if(p->name()=="Eyd"){
    Eyd=p->value().toFloat();
    Dis_y.setpoint=Eyd;
  }
  else if(p->name()=="savep"){
    savep=p->value().toInt();
    if(savep==1){
      save_all_param();
    }
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
    ksp3 = speed_pid3.kp;
    ksi3 = speed_pid3.ki;
    ksd3 = speed_pid3.kd;
    ksp4 = speed_pid4.kp;
    ksi4 = speed_pid4.ki;
    ksd4 = speed_pid4.kd;
    kdp1 = dis_pid1.kp;
    kdi1 = dis_pid1.ki;
    kdd1 = dis_pid1.kd;
    kdp2 = dis_pid2.kp;
    kdi2 = dis_pid2.ki;
    kdd2 = dis_pid2.kd;
    kdp3 = dis_pid3.kp;
    kdi3 = dis_pid3.ki;
    kdd3 = dis_pid3.kd;
    kdp4 = dis_pid4.kp;
    kdi4 = dis_pid4.ki;
    kdd4 = dis_pid4.kd;
    kgp = gyro_pid.kp;
    kgi = gyro_pid.ki;
    kgd = gyro_pid.kd;
    kap = angle_pid.kp;
    kai = angle_pid.ki;
    kad = angle_pid.kd;
    KSxp = Speed_x.kp;
    KSxi = Speed_x.ki;
    KSxd = Speed_x.kd;
    KSyp = Speed_y.kp;
    KSyi = Speed_y.ki;
    KSyd = Speed_y.kd;
    KDxp = Dis_x.kp;
    KDxi = Dis_x.ki;
    KDxd = Dis_x.kd;
    KDyp = Dis_y.kp;
    KDyi = Dis_y.ki;
    KDyd = Dis_y.kd;

    // get_flag(&flag1,&flag2,&flag3,&flag4);
}