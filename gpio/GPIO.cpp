#include "GPIO.hpp"
#include "pin_mappings.hpp"
#include <cerrno>  // for errno
#include <cstring> // for strerror
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

/*
 * PUBLIC
 */

GPIO::GPIO(std::string_view label) : m_label{label}
{
    const auto found{pin_mappings.find(label)};
    if (found == pin_mappings.cend())
    {
        throw std::invalid_argument{"Invalid label provided"};
    }
    if (!(*found).second.is_gpio)
    {
        throw std::invalid_argument{"The pin provided cannot be used as GPIO"};
    }
    m_gpio_number = (*found).second.gpio_number;
    m_path_to_gpio_value = build_path_from_template(GPIO::template_path_to_gpio_value, m_gpio_number);
    m_path_to_gpio_direction = build_path_from_template(GPIO::template_path_to_gpio_direction, m_gpio_number);
    m_path_to_pin_mux = build_path_from_template(GPIO::template_path_to_pin_mux, str_to_upper(m_label));
}

void GPIO::read_value()
{
    const std::string value{read(m_path_to_gpio_value)};
    std::cout << "Pin " << m_label << " value: " << value << '\n';
}

void GPIO::write_value(std::string_view val)
{
    if (val != "0" && val != "1")
    {
        throw std::invalid_argument{"Invalid <input> for \"value\""};
    }
    write(m_path_to_gpio_value, val);
}

void GPIO::read_direction()
{
    const std::string direction{read(m_path_to_gpio_direction)};
    std::cout << "Pin " << m_label << " direction: " << direction << '\n';
}

void GPIO::write_direction(std::string_view dir)
{
    if (dir == "default")
    {
        write(m_path_to_pin_mux, "default");
        write(m_path_to_gpio_direction, "in");
    }
    else if (dir == "in" || dir == "out")
    {
        write(m_path_to_pin_mux, "default");
        write(m_path_to_gpio_direction, dir);
    }
    else if (dir == "in+" || dir == "in-")
    {
        dir == "in+" ? write(m_path_to_pin_mux, "gpio_pu") : write(m_path_to_pin_mux, "gpio_pd");
        write(m_path_to_gpio_direction, "in");
    }
    else
    {
        throw std::invalid_argument{"Invalid <input> for \"direction\""};
    }
}

/*
 * PRIVATE
 */

std::string GPIO::build_path_from_template(std::string_view templ, std::string_view str)
{
    std::string path{templ};
    size_t start_pos{path.find("{}")};
    path.replace(start_pos, 2, str);
    return path;
}

std::string GPIO::str_to_upper(const std::string &str)
{
    std::string result{str};
    for (auto &c : result)
    {
        c = static_cast<char>(toupper(c));
    }
    return result;
}

std::string GPIO::read(const std::string &path)
{
    std::ifstream i_file{path};
    if (i_file.fail())
    {
        std::ostringstream err{};
        err << "Could not open file \"" << path << "\" for reading: " << std::strerror(errno);
        throw std::ios::failure{err.str()};
    }

    std::string text{};
    std::getline(i_file, text);
    return text;
}

void GPIO::write(const std::string &path, std::string_view text)
{
    std::ofstream o_file{path};
    if (o_file.fail())
    {
        std::ostringstream err{};
        err << "Could not open file \"" << path << "\" for writing: " << std::strerror(errno);
        throw std::ios::failure{err.str()};
    }
    o_file << text;
    std::cout << "Written \"" << text << "\" to \"" << path << "\"\n";
}
