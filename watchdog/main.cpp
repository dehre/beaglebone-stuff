#include "Watchdog.hpp"
#include <iostream>

// TODO LORIS: do I really need sudo permissions?
// TODO LORIS: refactor main do-while loop in a more c++ way?

int main()
{
    try
    {
        Watchdog wdg(20);
        int state;
        std::cout << "Press f to feed the dog, h to say hello, q to quit\n";
        do
        {
            state = getchar();
            switch (state)
            {
            case 'f':
                std::cout << "Feed!\n";
                wdg.feed();
                break;
            case 'h':
                std::cout << "hello!\n";
                break;
            }
        } while (state != 'q');
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
