#include "GPIO.hpp"
#include "PinMappings.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// TODO LORIS: private method?
static std::string strToUpper(std::string_view str);

GPIO GPIO::create(std::string_view label)
{
    const auto found{PinMappings.find(label)};
    if (found == PinMappings.cend())
    {
        throw std::invalid_argument{"Invalid label provided"};
    }
    if (!(*found).second.isGPIO)
    {
        throw std::invalid_argument{"The pin provided cannot be used as GPIO"};
    }
    return GPIO(label, (*found).second.GPIO);
}

GPIO::GPIO(std::string_view label, std::string_view gpio) : m_label{label}, m_gpio{gpio}
{
    m_gpioValuePath = buildPathFromTemplate(GPIO::gpioValueTemplatePath, m_gpio);
    m_gpioDirectionPath = buildPathFromTemplate(GPIO::gpioDirectionTemplatePath, m_gpio);
    m_pinMuxPath = buildPathFromTemplate(GPIO::pinMuxTemplatePath, strToUpper(m_label));
}

std::string GPIO::buildPathFromTemplate(const std::string_view &templ, std::string_view str)
{
    std::string path{templ};
    size_t startPos{path.find("{}")};
    path.replace(startPos, 2, str);
    return path;
}

std::string GPIO::read(std::string_view path)
{
    std::ifstream iFile{path.data()};
    if (iFile.fail())
    {
        std::ostringstream message{};
        message << "Could not open file for reading: " << path;
        throw std::ios::failure{message.str()};
    }

    std::string text{};
    std::getline(iFile, text);
    return text;
}

void GPIO::write(std::string_view path, std::string_view text)
{
    std::ofstream oFile{path.data()};
    if (oFile.fail())
    {
        std::ostringstream message{};
        message << "Could not open file for writing: " << path;
        throw std::ios::failure{message.str()};
    }
    oFile << text;
    std::cout << "Written \"" << text << "\" to \"" << path << "\"\n";
}

void GPIO::readValue()
{
    std::cout << "Pin " << m_label << " value: " << read(m_gpioValuePath) << '\n';
}

void GPIO::writeValue(std::string_view val)
{
    if (val != "0" && val != "1")
    {
        throw std::invalid_argument{"Invalid <input> for \"value\" <target>"};
    }
    write(m_gpioValuePath, val);
}

void GPIO::readDirection()
{
    std::cout << "Pin " << m_label << " direction: " << read(m_gpioDirectionPath) << '\n';
}

void GPIO::writeDirection(std::string_view dir)
{
    if (dir == "default")
    {
        write(m_pinMuxPath, "default");
        write(m_gpioDirectionPath, "in");
    }
    else if (dir == "in" || dir == "out")
    {
        write(m_pinMuxPath, "default");
        write(m_gpioDirectionPath, dir);
    }
    else if (dir == "in+" || dir == "in-")
    {
        dir == "in+" ? write(m_pinMuxPath, "gpio_pu") : write(m_pinMuxPath, "gpio_pd");
        write(m_gpioDirectionPath, "in");
    }
    else
    {
        throw std::invalid_argument{"Invalid <input> for \"direction\" <target>"};
    }
}

static std::string strToUpper(std::string_view str)
{
    std::string result{str};
    for (auto &c : result)
    {
        c = static_cast<char>(toupper(c));
    }
    return result;
}
