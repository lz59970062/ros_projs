
#include "comunicate.h"
xSemaphoreHandle xSemaphore_broadcast = NULL;

UDPComunicate udp;
void udp_broadcast_task(void *pvParameter)
{

    UDPComunicate *udp = (UDPComunicate *)pvParameter;
    xSemaphore_broadcast = xSemaphoreCreateMutex();
    while (1)
    {
        if(udp->adversting){
        xSemaphoreTake(xSemaphore_broadcast, portMAX_DELAY);
        udp->broadcast_self_node();
        xSemaphoreGive(xSemaphore_broadcast);
        vTaskDelay(2048 / portTICK_PERIOD_MS);
        }
        else{
            vTaskDelay( 200000/ portTICK_PERIOD_MS);
        }
    }
}
Remote_node::Remote_node() {}
void Remote_node::init_node(String _name, String _ip, uint32_t _port)
{
    name = _name;
    ip = _ip;
    port = _port;
    node_ip.fromString(ip);
}
Remote_node::Remote_node(String _name, String _ip, uint32_t _port)
{
    name = _name;
    ip = _ip;
    port = _port;
    node_ip.fromString(ip);
    this->connection_type = connection_type;
}
size_t Remote_node::send_data(String data)
{
    return udp.writeTo((uint8_t *)data.c_str(), data.length(), node_ip, port);
}

UDPComunicate::UDPComunicate() : AsyncUDP()
{
}

void UDPComunicate::begin(int port)
{
    const String CONNECTED_MESSAGE = "WiFi connected";
    const String IP_ADDRESS_MESSAGE = "IP address: ";
    localPort = port;
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(CONNECTED_MESSAGE);
    Serial.println(IP_ADDRESS_MESSAGE);
    remote_IP.fromString(UDP_TARGET_IP);
    Serial.println(WiFi.localIP());
    AsyncUDP::connect(remote_IP, localPort);

    xTaskCreatePinnedToCore(udp_broadcast_task,
                            "UDP_broadcast", 2048 * 3, this, 1, NULL, 0);
    if (AsyncUDP::listen(localPort))
    {
        Serial.println("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("Port: ");

        Serial.println(localPort);
        AsyncUDP::onPacket([](AsyncUDPPacket packet)
                           {
                                   int cast_type = packet.isBroadcast() ? 2 : packet.isMulticast() ? 1: 0;
                                //    Serial.printf("UDP Packet Type: %d, From %s:%d, To %s:%d, Length %u, Data: %s\n",
                                //                  cast_type,
                                //                  packet.remoteIP().toString().c_str(), packet.remotePort(),
                                //                  packet.localIP().toString().c_str(), packet.localPort(),
                                //                  packet.length(),
                                //                  packet.data());
                                if(cast_type==0){
                                    for (int i = 0; i < MAX_REMOTE_NODE; i++) {
                                        if (udp.remote_node_list[i].inited && 
                                            udp.remote_node_list[i].node_ip == packet.remoteIP() && 
                                            udp.remote_node_list[i].port == packet.remotePort()) 
                                            {
                                                udp.remote_node_list[i].data_cb(&packet);
                                            }
                                        }
               
                                    }
                                if (cast_type == 2){
                                    if(udp.node_finding){
                                                        //add new node to list
                                                        if(packet.data()[0] == 'N'&& packet.data()[1] == 'o'&& packet.data()[2] == 'd'&& packet.data()[3] == 'e'){
                                                        String data = String((char *)packet.data());
                                                        int last_d=0;
                                                        String name = data.substring(5, last_d=data.indexOf(","));
                                                        String ip = data.substring(last_d+1, last_d=data.indexOf(",",last_d+1));
                                                        uint32_t port = data.substring(last_d+1).toInt();
                                                        Serial.printf("Find node: %s, %s, %d\n", name.c_str(), ip.c_str(), port);
                                                        if(!udp.has_node(name)){
                                                             bool ret=udp.add_node(name, ip, port);
                                                             if (ret)
                                                             {
                                                                 Serial.println("Add node success");
                                                             }
                                                             else
                                                             {
                                                                 Serial.println("Add node failed");
                                                             }
                                                            // udp.print_node_list();
                                                        }
                                                        }
                                                    }
     } });
    }
    else
    {
        Serial.println("UDP Listen failed");
    }
}
size_t UDPComunicate::write(uint8_t *data, size_t len)
{
    return AsyncUDP::writeTo(data, len, remote_IP, localPort);
}
size_t UDPComunicate::write(String data)
{
    return AsyncUDP::writeTo((uint8_t *)data.c_str(), data.length(), remote_IP, localPort);
}
size_t UDPComunicate::write_node(uint8_t *data, int len, Remote_node &node)
{
    return AsyncUDP::writeTo(data, len, node.node_ip, node.port);
}
size_t UDPComunicate::write_node(String data, Remote_node &node)
{
    return AsyncUDP::writeTo((uint8_t *)data.c_str(), data.length(), node.node_ip, node.port);
}

size_t UDPComunicate::broadcast(uint8_t *data, size_t len)
{
    return AsyncUDP::broadcastTo(data, len, localPort);
}

size_t UDPComunicate::broadcast(String data)
{
    return AsyncUDP::broadcastTo((uint8_t *)data.c_str(), data.length(), localPort);
}
void UDPComunicate::print_node_list()
{
    for (int i = 0; i < MAX_REMOTE_NODE; i++)
    {
        if (remote_node_list[i].name != "")
        {
            Serial.printf("Node %d: %s, %s, %d\n", i, remote_node_list[i].name.c_str(), remote_node_list[i].ip.c_str(), remote_node_list[i].port);
        }
    }
}
bool UDPComunicate::has_node(String name)
{
    for (int i = 0; i < MAX_REMOTE_NODE; i++)
    {
        if (remote_node_list[i].name == name)
        {
            return true;
        }
    }
    return false;
}
Remote_node *UDPComunicate::get_node(String name)
{
    for (int i = 0; i < MAX_REMOTE_NODE; i++)
    {
        // Serial.println(remote_node_list[i].name);
        // Serial.println(name);
        if (remote_node_list[i].name == name)
        {
            return &remote_node_list[i];
        }
    }
    return NULL;
}
bool UDPComunicate::add_node(String name, String ip, uint32_t port)
{
    for (int i = 0; i < MAX_REMOTE_NODE; i++)
    {
        if (remote_node_list[i].name == "")
        {
            remote_node_list[i] = Remote_node(name, ip, port);
            return true;
        }
    }
    return false;
}
bool UDPComunicate::add_node(Remote_node node)
{
    for (int i = 0; i < MAX_REMOTE_NODE; i++)
    {
        if (remote_node_list[i].name == "")
        {
            remote_node_list[i] = node;
            return true;
        }
    }
    return false;
}
void UDPComunicate::del_node(String name)
{
    for (int i = 0; i < MAX_REMOTE_NODE; i++)
    {
        if (remote_node_list[i].name == name)
        {
            remote_node_list[i] = Remote_node();
            return;
        }
    }
}
void UDPComunicate::broadcast_self_node()
{
    String data = "Node:" + self_node_name + "," + WiFi.localIP().toString() + "," + String(localPort);
    broadcast(data);
}
