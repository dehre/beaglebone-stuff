#include "MQTT.hpp"
#include <iostream>

#define ADAFRUIT_MQTT_BROKER

#ifdef ADAFRUIT_MQTT_BROKER
const char *g_address{"tcp://io.adafruit.com:1883"};
const char *g_clientId{"BBB"};
const char *g_topic{"marcello_45/feeds/temperature"};
const char *g_payload{"Hello world"};
const char *g_adafruitUsername{"marcello_45"};
#else
const char *g_address{"tcp://localhost:1883"};
const char *g_clientId{"BBB"};
const char *g_topic{"temperature"};
const char *g_payload{"Hello world"};
const char *g_adafruitUsername{nullptr};
#endif

int main()
{
    const char *adafruitKey{nullptr};
#ifdef ADAFRUIT_MQTT_BROKER
    adafruitKey = std::getenv("ADAFRUIT_KEY");
    if (!adafruitKey)
    {
        std::cerr << "Env variable $ADAFRUIT_KEY not provided\n";
        return 1;
    }
#endif

    try
    {

        MQTT::Client client(g_address, g_clientId);
        client.connect(g_adafruitUsername, adafruitKey);
        client.publishMessage(g_topic, g_payload, 1000);
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
