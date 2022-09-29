#include "GPIO.hpp"
#include <iostream>

int main()
{
    GPIO thisPin("p8_16", "46");
    thisPin.readValue();
}
