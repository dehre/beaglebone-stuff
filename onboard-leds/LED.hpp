#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class LED
{
  private:
    int m_id;
    std::string m_path;

    void m_write(const std::string &fileName, const std::string &value)
    {
        std::string fullPath = m_path + fileName;
        std::ofstream file(fullPath);
        if (!file)
        {
            std::cerr << "Error: failed to open file: " << fullPath << '\n';
            return;
        }
        file << value;
    }

    void m_removeTrigger()
    {
        m_write("trigger", "none");
    }

  public:
    LED(int led) : m_id{led}
    {
        std::ostringstream path;
        path << "/sys/class/leds/beaglebone:green:usr" << m_id << "/";
        m_path = path.str();
    }
    ~LED(){};

    void turnOn()
    {
        m_removeTrigger();
        m_write("brightness", "1");
    }

    void turnOff()
    {
        m_removeTrigger();
        m_write("brightness", "0");
    };

    void flash()
    {
        m_write("trigger", "timer");
        m_write("delay_on", "500");
        m_write("delay_off", "500");
    };
};
