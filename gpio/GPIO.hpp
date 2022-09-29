#pragma once

#include <optional>
#include <string_view>

class GPIO
{
  private:
    static constexpr std::string_view gpioPath{"/sys/class/gpio"};
    static constexpr std::string_view ocpPath{"/sys/devices/platform/ocp"};

    std::string_view m_label{};
    std::string_view m_gpio{};
    GPIO(std::string_view label, std::string_view gpio);

  public:
    static std::optional<GPIO> create(std::string_view label);
    void readValue();
    void writeValue(std::string_view val);
};
