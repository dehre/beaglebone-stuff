#pragma once

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <array>
#include <cstring>
#include <stdexcept>

class I2C
{
  public:
    I2C(int instance, int slaveAddress) : m_slaveAddress{slaveAddress}
    {
        m_pathToDev.replace(m_pathToDev.find("{}"), 2, std::to_string(instance));
        if ((m_fd = open(m_pathToDev.data(), O_RDWR)) < 0)
        {
            throw std::invalid_argument("Invalid i2c instance provided\n");
        };

        if (ioctl(m_fd, I2C_SLAVE, m_slaveAddress) < 0)
        {
            throw std::invalid_argument("Invalid slave address provided\n");
        }
    }

    virtual ~I2C()
    {
        close(m_fd);
    }

    template <size_t size> void write(std::array<uint8_t, size> buffer)
    {
        if (::write(m_fd, buffer.data(), buffer.size()) != 1)
        {
            std::string errmsg{};
            errmsg.append("Failed to write: ").append(std::strerror(errno));
            throw std::runtime_error(errmsg);
        }
    }

    template <size_t size> std::array<uint8_t, size> read()
    {
        std::array<uint8_t, size> buffer{};
        if (::read(m_fd, buffer.data(), buffer.size()) != buffer.size())
        {
            std::string errmsg{};
            errmsg.append("Failed to read: ").append(std::strerror(errno));
            throw std::runtime_error(errmsg);
        }
        return buffer;
    }

  private:
    std::string m_pathToDev{"/dev/i2c-{}"};
    int m_fd{};
    int m_slaveAddress{};
};
