#pragma once

#include "I2C.hpp"

class SHT21 : private I2C
{
  public:
    SHT21(int i2cInstance) : I2C(i2cInstance, m_i2cAddress)
    {
    }

    virtual ~SHT21()
    {
    }

    double readTemperature()
    {
        this->write<1>({{m_trigTempMeasurement}});
        auto rawDataArr{this->read<2>()};
        uint16_t rawData{static_cast<uint16_t>((rawDataArr[0] << 8) | (rawDataArr[1] & 0xFC))};
        double temperature{-46.85 + 175.72 / 65536.0 * static_cast<double>(rawData)};
        return temperature;
    }

  private:
    static constexpr int m_i2cAddress{0x40};
    static constexpr int m_trigTempMeasurement{0xE3};
};
