#pragma once

#include <cerrno>  // for errno
#include <cstring> // for strerror
#include <fstream>
#include <iostream>
#include <string>

class LED
{
  public:
    LED(int led) : m_id{led}, m_path{"/sys/class/leds/beaglebone:green:usr" + std::to_string(led) + "/"}
    {
    }
    ~LED(){};

    void turn_on()
    {
        m_remove_trigger();
        m_write("brightness", "1");
    }

    void turn_off()
    {
        m_remove_trigger();
        m_write("brightness", "0");
    }

    void flash()
    {
        m_write("trigger", "timer");
        m_write("delay_on", "500");
        m_write("delay_off", "500");
    };

  private:
    int m_id;
    std::string m_path;

    void m_write(const std::string &file_name, const std::string &value)
    {
        std::string full_path = m_path + file_name;
        std::ofstream file(full_path);
        if (file.fail())
        {
            std::cerr << "Error: failed to open " << full_path << ": " << strerror(errno) << '\n';
            return;
        }
        file << value;
    }

    void m_remove_trigger()
    {
        m_write("trigger", "none");
    }
};
