#pragma once

#include <string>
#include <string_view>

class GPIO
{
  public:
    GPIO(std::string_view label);
    void readValue();
    void writeValue(std::string_view val);
    void readDirection();
    void writeDirection(std::string_view dir);

  private:
    static std::string buildPathFromTemplate(std::string_view templ, std::string_view str);
    static std::string strToUpper(const std::string &str);
    static std::string read(const std::string &path);
    static void write(const std::string &path, std::string_view text);

    std::string m_label{};
    std::string m_gpioNumber{};
    std::string m_pathToGpioValue{};
    std::string m_pathToGpioDirection{};
    std::string m_pathToPinMux{};

    static constexpr std::string_view templatePathToGpioValue{"/sys/class/gpio/gpio{}/value"};
    static constexpr std::string_view templatePathToGpioDirection{"/sys/class/gpio/gpio{}/direction"};
    static constexpr std::string_view templatePathToPinMux{"/sys/devices/platform/ocp/ocp:{}_pinmux/state"};
};
