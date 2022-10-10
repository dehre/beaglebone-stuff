#pragma once

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <array>
#include <sstream>
#include <stdexcept>
#include <string>

class I2C
{
  public:
    I2C(int instance, int slaveAddress) : m_slaveAddress{slaveAddress}
    {
        std::ostringstream pathToDev;
        pathToDev << "/dev/i2c-" << instance;

        if ((m_devFile = open(pathToDev.str().data(), O_RDWR)) < 0)
        {
            throw std::invalid_argument("Failed to open the bus\n");
        };

        if (ioctl(m_devFile, I2C_SLAVE, m_slaveAddress) < 0)
        {
            throw std::invalid_argument("Failed to connect to the sensor\n");
        }
    }

    ~I2C()
    {
        close(m_devFile);
    }

    template <size_t size> void writei2c(std::array<uint8_t, size> buffer)
    {
        if (write(m_devFile, buffer.data(), buffer.size()) != 1)
        {
            throw std::invalid_argument("Failed to write 0xE3\n");
        }
    }

    template <size_t size> std::array<uint8_t, size> readi2c()
    {
        std::array<uint8_t, size> buffer{};
        if (read(m_devFile, buffer.data(), buffer.size()) != buffer.size())
        {
            throw std::invalid_argument("Failed to read raw data\n");
        }
        return buffer;
    }

  private:
    int m_devFile{};
    int m_slaveAddress{};
};
