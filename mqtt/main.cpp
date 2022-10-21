#include "MQTT.hpp"
#include "RandomInt.hpp"
#include "dotenv.hpp"
#include <cstdio>
#include <iostream>
#include <stdexcept>

const char *g_clientId{"BBB"};
const char *g_template_topic{"{}/feeds/temperature"};
const int g_publishMessageTimeoutMs{1000};

struct AdafruitEnvs
{
    const std::string adafruit_address;
    const std::string adafruit_username;
    const std::string adafruit_key;
};
static AdafruitEnvs get_adafruit_envs();

int main()
{
    try
    {
        const auto [adafruit_address, adafruit_username, adafruit_key]{get_adafruit_envs()};
        if (adafruit_address.empty())
        {
            /* Even when using a local mqtt broker, the local ip address must be provided */
            throw std::logic_error{"Env variable ADAFRUIT_ADDRESS not provided"};
        }

        std::string topic{g_template_topic};
        topic.replace(topic.find("{}"), 2, adafruit_username.empty() ? "user" : adafruit_username);

        int temperature_int{RandomInt{}.generate(15, 40)};
        char temperature[3];                             /* 2 chars + null character */
        snprintf(temperature, 3, "%d", temperature_int); // TODO LORIS: get rid of temperature_int

        MQTT::Client client(adafruit_address.c_str(), g_clientId);
        client.connect(adafruit_username.empty() ? nullptr : adafruit_username.c_str(),
                       adafruit_key.empty() ? nullptr : adafruit_key.c_str());
        client.publishMessage(topic.c_str(), temperature, g_publishMessageTimeoutMs);
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

static AdafruitEnvs get_adafruit_envs()
{
    const auto envs{dotenv::parse()};

    std::string adafruit_address{};
    auto adafruit_address_it{envs.find("ADAFRUIT_ADDRESS")};
    if (adafruit_address_it != envs.cend())
    {
        adafruit_address = adafruit_address_it->second;
    }

    std::string adafruit_username{};
    auto adafruit_username_it{envs.find("ADAFRUIT_USERNAME")};
    if (adafruit_username_it != envs.cend())
    {
        adafruit_username = adafruit_username_it->second;
    }

    std::string adafruit_key{};
    auto adafruit_key_it{envs.find("ADAFRUIT_KEY")};
    if (adafruit_key_it != envs.cend())
    {
        adafruit_key = adafruit_key_it->second;
    }

    return {
        .adafruit_address = adafruit_address,
        .adafruit_username = adafruit_username,
        .adafruit_key = adafruit_key,
    };
}
