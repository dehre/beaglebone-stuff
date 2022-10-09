#include "GPIO.hpp"
#include "PinMappings.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

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
    std::ostringstream pathToValue{};
    pathToValue << GPIO::gpioPath << "/gpio" << m_gpio << "/value";
    std::cout << "Pin " << m_label << " value: " << read(pathToValue.str()) << '\n';
}

void GPIO::writeValue(std::string_view val)
{
    if (val != "0" && val != "1")
    {
        throw std::invalid_argument{"Invalid <input> for \"value\" <target>"};
    }
    std::ostringstream pathToValue{};
    pathToValue << GPIO::gpioPath << "/gpio" << m_gpio << "/value";
    write(pathToValue.str(), val);
}

void GPIO::readDirection()
{
    std::ostringstream pathToDirection{};
    pathToDirection << GPIO::gpioPath << "/gpio" << m_gpio << "/direction";
    std::cout << "Pin " << m_label << " direction: " << read(pathToDirection.str()) << '\n';
}

void GPIO::writeDirection(std::string_view dir)
{
    std::ostringstream pathToDirection{};
    pathToDirection << GPIO::gpioPath << "/gpio" << m_gpio << "/direction";
    std::ostringstream pathToPinMux{};
    pathToPinMux << GPIO::ocpPath << "/ocp:" << strToUpper(m_label) << "_pinmux/state";

    if (dir == "default")
    {
        write(pathToPinMux.str(), "default");
        write(pathToDirection.str(), "in");
    }
    else if (dir == "in" || dir == "out")
    {
        write(pathToPinMux.str(), "default");
        write(pathToDirection.str(), dir);
    }
    else if (dir == "in+" || dir == "in-")
    {
        dir == "in+" ? write(pathToPinMux.str(), "gpio_pu") : write(pathToPinMux.str(), "gpio_pd");
        write(pathToDirection.str(), "in");
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
