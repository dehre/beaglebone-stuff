#include "Watchdog.hpp"
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <iostream>
#include <string>

int main()
{
    try
    {
        Watchdog wdg(30);
        std::cout << "Type any string to feed the dog (timeout: 30s), use \"q\" or \"quit\" to quit\n";
        std::string buf{};
        while (true)
        {
            std::getline(std::cin, buf);
            buf.erase(buf.find_last_not_of(" \n\r\t") + 1); /* trim trailing whitespaces */
            if (buf == "q" || buf == "quit")
            {
                break;
            }
            std::cout << "[feed]\n";
            wdg.feed();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
