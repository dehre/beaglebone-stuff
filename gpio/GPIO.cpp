#include "GPIO.hpp"
#include "PinMappings.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

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
}

std::string GPIO::read(std::string_view path)
{
    std::ifstream iFile{path};
    if (iFile.fail())
    {
        std::ostringstream errMessage{};
        errMessage << "Could not open file for reading: " << path;
        throw std::ios::failure{errMessage.str()};
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
        std::ostringstream errMessage{};
        errMessage << "Could not open file for writing: " << path;
        throw std::ios::failure{errMessage.str()};
    }
    oFile << text;
}

void GPIO::readValue()
{
    std::ostringstream fullPath{};
    fullPath << GPIO::gpioPath << "/gpio" << m_gpio << "/value";
    std::cout << "Pin " << m_label << " value: " << read(fullPath.str()) << '\n';
}

// TODO LORIS: use enum for value, and remove throwing errors?
void GPIO::writeValue(std::string_view val)
{
    if (val != "0" && val != "1")
    {
        throw std::invalid_argument{"Invalid value provided"};
    }
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

// TODO LORIS: use enum for direction, and remove throwing errors?
// TODO LORIS: set ocp too
void GPIO::writeDirection(std::string_view dir)
{
    if (dir != "in" && dir != "out")
    {
        throw std::invalid_argument{"Invalid direction provided"};
    }
    std::ostringstream fullPath{};
    fullPath << GPIO::gpioPath << "/gpio" << m_gpio << "/direction";
    write(fullPath.str(), dir);
}
