#include "GPIO.hpp"
#include "PinMappings.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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

std::string GPIO::read(std::string_view path)
{
    std::ifstream iFile{path};
    if (iFile.fail())
    {
        throw "hello world";
    }

    std::string strBuf{};
    std::getline(iFile, strBuf);
    return strBuf;
}

void GPIO::write(std::string_view path, std::string_view text)
{
    std::ofstream oFile{path};
    if (oFile.fail())
    {
        throw "hello world";
    }
    oFile << text;
}

void GPIO::readValue()
{
    std::ostringstream fullPath{};
    fullPath << GPIO::gpioPath << "/gpio" << m_gpio << "/value";
    std::cout << "Pin " << m_label << " value: " << read(fullPath.str()) << '\n';
}

void GPIO::writeValue(std::string_view val)
{
    std::ostringstream fullPath{};
    fullPath << GPIO::gpioPath << "/gpio" << m_gpio << "/value";
    write(fullPath.str(), val);
}

void GPIO::readDirection()
{
    std::ostringstream fullPath{};
    fullPath << GPIO::gpioPath << "/gpio" << m_gpio << "/direction";
    std::cout << "Pin " << m_label << " direction: " << read(fullPath.str()) << '\n';
}

// TODO LORIS: set ocp too
void GPIO::writeDirection(std::string_view dir)
{
    std::ostringstream fullPath{};
    fullPath << GPIO::gpioPath << "/gpio" << m_gpio << "/direction";
    write(fullPath.str(), dir);
}
