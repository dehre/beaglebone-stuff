#include "GPIO.hpp"
#include "PinMappings.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

/*
 * PUBLIC
 */

GPIO::GPIO(std::string_view label) : m_label{label}
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
    m_gpioNumber = (*found).second.gpioNumber;
    m_pathToGpioValue = buildPathFromTemplate(GPIO::templatePathToGpioValue, m_gpioNumber);
    m_pathToGpioDirection = buildPathFromTemplate(GPIO::templatePathToGpioDirection, m_gpioNumber);
    m_pathToPinMux = buildPathFromTemplate(GPIO::templatePathToPinMux, strToUpper(m_label));
}

void GPIO::readValue()
{
    std::cout << "Pin " << m_label << " value: " << read(m_pathToGpioValue) << '\n';
}

void GPIO::writeValue(std::string_view val)
{
    if (val != "0" && val != "1")
    {
        throw std::invalid_argument{"Invalid <input> for \"value\""};
    }
    write(m_pathToGpioValue, val);
}

void GPIO::readDirection()
{
    std::cout << "Pin " << m_label << " direction: " << read(m_pathToGpioDirection) << '\n';
}

void GPIO::writeDirection(std::string_view dir)
{
    if (dir == "default")
    {
        write(m_pathToPinMux, "default");
        write(m_pathToGpioDirection, "in");
    }
    else if (dir == "in" || dir == "out")
    {
        write(m_pathToPinMux, "default");
        write(m_pathToGpioDirection, dir);
    }
    else if (dir == "in+" || dir == "in-")
    {
        dir == "in+" ? write(m_pathToPinMux, "gpio_pu") : write(m_pathToPinMux, "gpio_pd");
        write(m_pathToGpioDirection, "in");
    }
    else
    {
        throw std::invalid_argument{"Invalid <input> for \"direction\""};
    }
}

/*
 * PRIVATE
 */

std::string GPIO::buildPathFromTemplate(std::string_view templ, std::string_view str)
{
    std::string path{templ};
    size_t startPos{path.find("{}")};
    path.replace(startPos, 2, str);
    return path;
}

std::string GPIO::strToUpper(const std::string &str)
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
    std::ifstream iFile{path};
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

void GPIO::write(const std::string &path, std::string_view text)
{
    std::ofstream oFile{path};
    if (oFile.fail())
    {
        std::ostringstream message{};
        message << "Could not open file for writing: " << path;
        throw std::ios::failure{message.str()};
    }
    oFile << text;
    std::cout << "Written \"" << text << "\" to \"" << path << "\"\n";
}
