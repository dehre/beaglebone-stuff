#include "I2C.hpp"
#include <cstdint>
#include <iostream>

constexpr int g_i2cInstance{2};
constexpr int g_sensorI2CAddress{0x40};

constexpr int g_sensorTrigTempMeasurement{0xE3};

int main()
{
    try
    {
        I2C sensor{I2C(g_i2cInstance, g_sensorI2CAddress)};

        sensor.write<1>({{g_sensorTrigTempMeasurement}});
        auto rawTemperatureArr{sensor.read<2>()};
        uint16_t rawTemperature{static_cast<uint16_t>((rawTemperatureArr[0] << 8) | (rawTemperatureArr[1] & 0xFC))};

        double temperature{-46.85 + 175.72 / 65536.0 * static_cast<double>(rawTemperature)};
        std::cout << "Everything went well! Got data: " << temperature << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        // TODO LORIS: print usage
    }
}
