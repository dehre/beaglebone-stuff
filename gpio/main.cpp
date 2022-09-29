#include "GPIO.hpp"
#include <iostream>

int main()
{
    auto pin{GPIO::create("p8_16")};
    if (!pin.has_value())
    {
        std::cerr << "Invalid pin provided\n";
    }
    pin->readValue();
}
