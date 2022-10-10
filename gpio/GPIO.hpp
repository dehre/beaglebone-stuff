#pragma once

#include <string>
#include <string_view>

class GPIO
{
  private:
    std::string_view m_label{};
    std::string_view m_gpio{};
    std::string m_gpioValuePath{};
    std::string m_gpioDirectionPath{};
    std::string m_pinMuxPath{};
    // TODO LORIS: name param gpioNumber
    GPIO(std::string_view label, std::string_view gpio);

    static constexpr std::string_view gpioValueTemplatePath{"/sys/class/gpio/gpio{}/value"};
    static constexpr std::string_view gpioDirectionTemplatePath{"/sys/class/gpio/gpio{}/direction"};
    static constexpr std::string_view pinMuxTemplatePath{"/sys/devices/platform/ocp/ocp:{}_pinmux/state"};
    static std::string buildPathFromTemplate(const std::string_view &templ, std::string_view str);

    static std::string read(std::string_view path);
    static void write(std::string_view path, std::string_view text);

  public:
    // TODO LORIS: make it a public constructor instead
    static GPIO create(std::string_view label);
    void readValue();
    void writeValue(std::string_view val);
    void readDirection();
    void writeDirection(std::string_view dir);
};
