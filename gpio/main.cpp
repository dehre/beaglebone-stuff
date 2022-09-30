#include "GPIO.hpp"
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <iostream>
#include <string_view>

// ./gpio p8_16 write direction in+
// ./gpio p8_16 read value

static void printUsageAndThrow()
{
    std::cerr << "Invalid arguments provided.\n";
    std::cerr << "    Usage: ./gpio <pin> <command> <target> [input]\n";
    std::cerr << "    <pin>: (pin formatted as \"p8_16\")\n";
    std::cerr << "    <command>: \"read\" or \"write\"\n";
    std::cerr << "    <target>: \"value\" or \"direction\"\n";
    std::cerr << "    <input>: (used only with write commands)\n";

    throw std::invalid_argument{"Invalid arguments provided"};
}

int main(int argc, const char *argv[])
{
    try
    {
        if (argc < 4 || argc > 5)
        {
            printUsageAndThrow();
        }

        auto pin{GPIO::create(argv[1])};
        std::string_view command{argv[2]};
        std::string_view target{argv[3]};

        if (command == "read")
        {
            if (target == "value")
            {
                pin.readValue();
            }
            else if (target == "direction")
            {
                pin.readDirection();
            }
            else
            {
                printUsageAndThrow();
            }
        }
        else if (command == "write")
        {
            if (argc != 5)
            {
                printUsageAndThrow();
            }
            std::string_view input{argv[4]};
            if (target == "value")
            {
                pin.writeValue(input);
            }
            else if (target == "direction")
            {
                pin.writeDirection(input);
            }
            else
            {
                printUsageAndThrow();
            }
        }
        else
        {
            printUsageAndThrow();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
