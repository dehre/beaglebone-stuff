#include "GPIO.hpp"
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <iostream>
#include <string_view>

static void printUsage();

int main(int argc, const char *argv[])
{
    try
    {
        if (argc < 4)
        {
            throw std::invalid_argument{"Invalid number of arguments"};
        }

        auto pin{GPIO(argv[1])};
        std::string_view command{argv[2]};
        std::string_view target{argv[3]};
        std::string_view input{};
        (command == "write" && argc != 5) ? throw std::invalid_argument{"Missing <input> for \"write\""}
                                          : input = argv[4];

        if (command == "read" && target == "value")
        {
            pin.readValue();
        }
        else if (command == "read" && target == "direction")
        {
            pin.readDirection();
        }
        else if (command == "write" && target == "value")
        {
            pin.writeValue(input);
        }
        else if (command == "write" && target == "direction")
        {
            pin.writeDirection(input);
        }
        else
        {
            throw std::invalid_argument{"Invalid arguments provided"};
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n\n";
        printUsage();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*
 * Examples:
 * ./gpio p8_16 read value
 * ./gpio p8_16 write direction in+
 */
static void printUsage()
{
    std::cerr << "Usage: ./gpio <pin> <command> <target> [input]\n";
    std::cerr << "    <pin>: pin formatted as \"p8_16\"\n";
    std::cerr << "    <command>: \"read\" or \"write\"\n";
    std::cerr << "    <target>: \"value\" or \"direction\"\n";
    std::cerr << "    [input] when <command>==\"write\" && <target>==\"value\": \"0\" or \"1\"\n";
    std::cerr << "    [input] when <command>==\"write\" && <target>==\"direction\":"
                 "\"in\" or \"in+\" or \"in-\" or \"out\"\n";
}
