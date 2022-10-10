#include "GPIO.hpp"
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <iostream>
#include <string_view>

// ./gpio p8_16 write direction in+
// ./gpio p8_16 read value

static void printUsage();

int main(int argc, const char *argv[])
{
    try
    {
        if (argc < 4 || argc > 5)
        {
            throw std::invalid_argument{"Invalid number of arguments"};
        }

        auto pin{GPIO(argv[1])};
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
                throw std::invalid_argument{"Invalid <target> for \"read\" <command>"};
            }
        }
        else if (command == "write")
        {
            if (argc != 5)
            {
                throw std::invalid_argument{"Missing <input> for \"write\" <command>"};
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
                throw std::invalid_argument{"Invalid <target> for \"write\" <command>"};
            }
        }
        else
        {
            throw std::invalid_argument{"Invalid <command>"};
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        printUsage();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

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
