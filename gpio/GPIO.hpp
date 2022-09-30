#pragma once

#include <string>
#include <string_view>

class GPIO
{
  private:
    std::string_view m_label{};
    std::string_view m_gpio{};
    GPIO(std::string_view label, std::string_view gpio);

    static constexpr std::string_view gpioPath{"/sys/class/gpio"};
    static constexpr std::string_view ocpPath{"/sys/devices/platform/ocp"};
    static std::string read(std::string_view path);
    static void write(std::string_view path, std::string_view text);

  public:
    static GPIO create(std::string_view label);
    void readValue();
    void writeValue(std::string_view val);
    void readDirection();
    void writeDirection(std::string_view dir);
};
