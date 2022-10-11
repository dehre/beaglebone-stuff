#include "SHT21.hpp"
#include <iostream>

constexpr int g_i2cInstance{2};

int main()
{
    try
    {
        SHT21 sensor(g_i2cInstance);
        auto temperature{sensor.readTemperature()};
        auto humidity{sensor.readHumidity()};
        std::cout << "Temperature: " << temperature << "°C - Humidity: " << humidity << "% \n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
