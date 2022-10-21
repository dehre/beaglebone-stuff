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
    I2C(int instance, int slave_address) : m_slave_address{slave_address}
    {
        m_path_to_dev.replace(m_path_to_dev.find("{}"), 2, std::to_string(instance));
        if ((m_fd = open(m_path_to_dev.data(), O_RDWR)) < 0)
        {
            throw std::invalid_argument("Failed to create i2c instance: invalid device provided");
        };

        if (ioctl(m_fd, I2C_SLAVE, m_slave_address) < 0)
        {
            throw std::invalid_argument("Failed to create i2c instance: invalid slave address provided");
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
            std::string errmsg{"Failed to write to " + m_path_to_dev + ": " + std::strerror(errno)};
            throw std::runtime_error(errmsg);
        }
    }

    template <size_t size> std::array<uint8_t, size> read()
    {
        std::array<uint8_t, size> buffer{};
        if (::read(m_fd, buffer.data(), buffer.size()) != buffer.size())
        {
            std::string errmsg{"Failed to read from " + m_path_to_dev + ": " + std::strerror(errno)};
            throw std::runtime_error(errmsg);
        }
        return buffer;
    }

  private:
    std::string m_path_to_dev{"/dev/i2c-{}"};
    int m_fd{};
    int m_slave_address{};
};
