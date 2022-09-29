#pragma once

#include <string_view>

class GPIO
{
  private:
    static constexpr std::string_view gpioPath{"/sys/class/gpio"};
    static constexpr std::string_view ocpPath{"/sys/devices/platform/ocp"};

    std::string_view m_label{};
    std::string_view m_gpio{};

  public:
    // TODO LORIS: hide constructor, use static public method instead
    GPIO(std::string_view label, std::string_view gpio) : m_label{label}, m_gpio{gpio}
    {
    }

    void readValue();
    void writeValue(std::string_view val);
};
