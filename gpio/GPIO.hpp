#pragma once

#include <string>
#include <string_view>

class GPIO
{
  public:
    GPIO(std::string_view label);
    void read_value();
    void write_value(std::string_view val);
    void read_direction();
    void write_direction(std::string_view dir);

  private:
    static std::string build_path_from_template(std::string_view templ, std::string_view str);
    static std::string str_to_upper(const std::string &str);
    static std::string read(const std::string &path);
    static void write(const std::string &path, std::string_view text);

    std::string m_label{};
    std::string m_gpio_number{};
    std::string m_path_to_gpio_value{};
    std::string m_path_to_gpio_direction{};
    std::string m_path_to_pin_mux{};

    static constexpr std::string_view template_path_to_gpio_value{"/sys/class/gpio/gpio{}/value"};
    static constexpr std::string_view template_path_to_gpio_direction{"/sys/class/gpio/gpio{}/direction"};
    static constexpr std::string_view template_path_to_pin_mux{"/sys/devices/platform/ocp/ocp:{}_pinmux/state"};
};
