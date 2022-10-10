#pragma once

#include <string>
#include <string_view>

class GPIO
{
  private:
    std::string_view m_label{};
    std::string_view m_gpioNumber{};
    std::string m_pathToGpioValue{};
    std::string m_pathToGpioDirection{};
    std::string m_pathToPinMux{};
    GPIO(std::string_view label, std::string_view gpioNumber);

    static constexpr std::string_view templatePathToGpioValue{"/sys/class/gpio/gpio{}/value"};
    static constexpr std::string_view templatePathToGpioDirection{"/sys/class/gpio/gpio{}/direction"};
    static constexpr std::string_view templatePathToPinMux{"/sys/devices/platform/ocp/ocp:{}_pinmux/state"};
    static std::string buildPathFromTemplate(const std::string_view &templ, std::string_view str);

    static std::string read(std::string_view path);
    static void write(std::string_view path, std::string_view text);

  public:
    GPIO(std::string_view label);
    void readValue();
    void writeValue(std::string_view val);
    void readDirection();
    void writeDirection(std::string_view dir);
};
