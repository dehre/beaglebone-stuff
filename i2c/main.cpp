#include "SHT21.hpp"
#include <iostream>

constexpr int g_i2c_instance{2};

int main()
{
    try
    {
        SHT21 sensor(g_i2c_instance);
        auto temperature{sensor.read_temperature()};
        auto humidity{sensor.read_humidity()};
        std::cout << "Temperature: " << temperature << "°C - Humidity: " << humidity << "% \n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
