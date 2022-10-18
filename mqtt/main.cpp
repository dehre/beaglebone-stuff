#include "MQTT.hpp"
#include "RandomInt.hpp"
#include <cstdio>
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

const int g_publishMessageTimeoutMs{1000};

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
        int temperature{RandomInt{}.generate(15, 40)};
        char temperatureStr[3]; /* 2 chars + null character */
        snprintf(temperatureStr, 3, "%d", temperature);

        MQTT::Client client(g_address, g_clientId);
        client.connect(g_adafruitUsername, adafruitKey);
        client.publishMessage(g_topic, temperatureStr, g_publishMessageTimeoutMs);
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
