#pragma once

#include "I2C.hpp"

class SHT21 : private I2C
{
  public:
    SHT21(int i2c_instance) : I2C(i2c_instance, m_i2c_address)
    {
    }

    virtual ~SHT21()
    {
    }

    double read_temperature()
    {
        this->write<1>({{m_trig_temp_measurement}});
        auto raw_data_arr{this->read<2>()};
        uint16_t raw_data{static_cast<uint16_t>((raw_data_arr[0] << 8) | (raw_data_arr[1] & 0xFC))};
        double temperature{-46.85 + 175.72 / 65536.0 * static_cast<double>(raw_data)};
        return temperature;
    }

    double read_humidity()
    {
        this->write<1>({{m_trig_humid_measurement}});
        auto raw_data_arr{this->read<2>()};
        uint16_t raw_data{static_cast<uint16_t>((raw_data_arr[0] << 8) | (raw_data_arr[1] & 0xFC))};
        double humidity{-6.0 + 125.0 / 65536.0 * static_cast<double>(raw_data)};
        return humidity;
    }

  private:
    static constexpr int m_i2c_address{0x40};
    static constexpr int m_trig_temp_measurement{0xE3};
    static constexpr int m_trig_humid_measurement{0xE5};
};
