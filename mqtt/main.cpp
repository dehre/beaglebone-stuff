#include "MQTT.hpp"
#include <iostream>

#define ADDRESS "tcp://localhost:1883"
#define CLIENTID "ExampleClientPub"
#define TOPIC "temperature"
#define PAYLOAD "Hello World!"

int main()
{
    try
    {
        MQTT::Client client(ADDRESS, CLIENTID);
        client.connect();
        client.publishMessage(TOPIC, PAYLOAD, 1000);
        client.disconnect();
    }
    catch (const MQTT::Error &e)
    {
        std::cerr << "MQTT Exception:" << e.what() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
