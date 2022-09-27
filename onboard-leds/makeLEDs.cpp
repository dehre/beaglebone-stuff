#include "LED.hpp"
#include <array>
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <iostream>
#include <string>
#include <unistd.h> // for getuid

int main(int argc, const char *argv[])
{
    if (getuid() != 0)
    {
        std::cerr << "Please run the program with root permissions\n";
        return EXIT_FAILURE;
    }
    if (argc != 2)
    {
        std::cerr << "Usage: ./makeLEDs <command>\n";
        std::cerr << "        <command> is one of: \"on\", \"off\", \"flash\"\n";
        return EXIT_FAILURE;
    }

    std::array<LED, 4> leds{LED(0), LED(1), LED(2), LED(3)};
    std::string command{argv[1]};
    for (auto led : leds)
    {
        if (command == "on")
        {
            led.turnOn();
        }
        else if (command == "off")
        {
            led.turnOff();
        }
        else if (command == "flash")
        {
            led.flash();
        }
        else
        {
            std::cerr << "Invalid command: " << command << '\n';
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
