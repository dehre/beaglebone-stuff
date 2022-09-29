#include "GPIO.hpp"
#include "PinMappings.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

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
