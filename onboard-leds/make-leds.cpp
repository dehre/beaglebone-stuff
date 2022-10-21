#include "LED.hpp"
#include <array>
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <iostream>
#include <string_view>

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <command>\n";
        std::cerr << "        <command> is one of: \"on\", \"off\", \"flash\"\n";
        return EXIT_FAILURE;
    }

    std::array<LED, 4> leds{LED(0), LED(1), LED(2), LED(3)};
    std::string_view command{argv[1]};
    for (auto led : leds)
    {
        if (command == "on")
        {
            led.turn_on();
        }
        else if (command == "off")
        {
            led.turn_off();
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
