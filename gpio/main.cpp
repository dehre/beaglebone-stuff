#include "GPIO.hpp"
#include <iostream>

int main()
{
    try
    {
        auto pin{GPIO::create("p8_16")};
        pin.readValue();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
