#include "GPIO.hpp"
#include "PinMappings.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

std::optional<GPIO> GPIO::create(std::string_view label)
{
    const auto found{PinMappings.find(label)};
    if (found == PinMappings.cend())
    {
        return {};
    }
    if (!(*found).second.isGPIO)
    {
        return {};
    }
    return GPIO(label, (*found).second.GPIO);
}

GPIO::GPIO(std::string_view label, std::string_view gpio) : m_label{label}, m_gpio{gpio}
{
}

void GPIO::readValue()
{
    // TODO LORIS:  abstract boilerplate
    std::ostringstream fullPath{};
    fullPath << GPIO::gpioPath << "/gpio" << m_gpio << "/value";

    std::ifstream iFile{fullPath.str()};
    if (iFile.fail())
    {
        throw "hello world";
    }

    char buffer[100];
    iFile.getline(buffer, 100);
    std::cout << "Pin " << m_label << " value: " << buffer << '\n';
}

void GPIO::writeValue(std::string_view val)
{
    // TODO LORIS:  abstract boilerplate
    std::ostringstream fullPath{};
    fullPath << GPIO::gpioPath << "/gpio" << m_gpio << "/value";

    std::ofstream oFile{fullPath.str()};
    if (oFile.fail())
    {
        throw "hello world";
    }
    oFile << val;
}
