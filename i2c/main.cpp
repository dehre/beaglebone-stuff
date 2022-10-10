#include "SHT21.hpp"
#include <cstdint>
#include <iostream>

constexpr int g_i2cInstance{2};

int main()
{
    try
    {
        SHT21 sensor(g_i2cInstance);
        auto temperature{sensor.readTemperature()};
        std::cout << "Everything went well! Got data: " << temperature << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        // TODO LORIS: print usage
    }
}
