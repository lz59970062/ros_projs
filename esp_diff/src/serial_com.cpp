
#include "serial.com.h"

Ser_Comunicate ::Ser_Comunicate(int tx, int rx) : tx_pin(tx), rx_pin(rx)
{
}
 

void Ser_Comunicate ::begin(long bute_rate, HardwareSerial *serial, void (*d_cb)(DataPacket *))
{
    if (serial == NULL)
    {
        Serial.printf("Serial is NULL\n");
        return;
    }
    if (d_cb == NULL)
    {
        Serial.printf("d_cb is NULL\n");
        return;
    }
    Ser = serial;
    this->data_cb = d_cb;
    Ser->begin(bute_rate, SERIAL_8N1, rx_pin, tx_pin);
    Serial.printf("Start init serial node rate is %d, node name is %s\n", bute_rate, self_node_name.c_str());
 
    Ser->onReceive([&]
                   {
        uint8_t head[4];
        head[0]=Ser->peek();  
        if(head[0]==0x55){
            int data_len=Ser->available();
            if(data_len>0){
                uint8_t *data_buff=new uint8_t[data_len];
                DataPacket packet(data_buff,data_len);
                Ser->readBytes(data_buff,data_len);
                this->data_cb(&packet);
                delete  data_buff;
             
            }   
        } },
                   true); // 设置回调函数
}

size_t Ser_Comunicate ::write(uint8_t *data, size_t len)
{
    uint8_t tail[2]={'\r','\t'};
    size_t ret = this->Ser->write(data, len);
    this->Ser->write((uint8_t *)tail, 2);
    return ret;
}
size_t Ser_Comunicate ::write(String data)
{
    // data += "\r\t";
    return this->Ser->write(data.c_str(), data.length());
}

size_t Ser_Comunicate ::broadcast(uint8_t *data, size_t len)
{
    return this->write(data, len);
}

size_t Ser_Comunicate ::broadcast(String data)
{
    return this->write((uint8_t *)data.c_str(), data.length());
}

bool Ser_Comunicate ::has_node(String name)
{
    return name == remote_node_name;
}

void Ser_Comunicate ::broadcast_self_node()
{
    String data = "Node:" + self_node_name + ",\n";
    broadcast(data);
}
