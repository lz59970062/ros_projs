#ifndef __SERIAL_COM_H__
#define __SERIAL_COM_H__

#include <Arduino.h>
#include "config.h"
class DataPacket
{
public:
    uint8_t *_data;
    size_t len;
    DataPacket(uint8_t *data, size_t len) : _data(data), len(len){};
    ~DataPacket(){};
    int length()
    {
        return len;
    }
    uint8_t *data()
    {
        return _data;
    }
};
class Ser_Comunicate
{
public:
    IPAddress remote_IP;
    Ser_Comunicate (int tx,int rx ); 
    HardwareSerial *Ser;
    const String self_node_name = NODE_NAME;
    String remote_node_name = "";
    bool adversting = true, node_finding = true;
    void begin(long  bute_rate, HardwareSerial *serial, void (*d_cb)(DataPacket *));
    size_t write(uint8_t *data, size_t len);
    size_t write(String data);
    size_t broadcast(uint8_t *data, size_t len);
    size_t broadcast(String data);
    void broadcast_self_node();
    bool has_node(String name);
    void (*data_cb)(DataPacket *);
    private:
    int tx_pin, rx_pin;

 
};

#endif // __SERIAL_COM_H__