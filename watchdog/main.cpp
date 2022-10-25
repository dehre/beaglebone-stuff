#include <cerrno>  // for errno
#include <cstring> // for strerror
#include <fcntl.h>
#include <iostream>
#include <linux/watchdog.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define WATCHDOG "/dev/watchdog"

int main()
{
    unsigned int interval = 20;
    int fd;
    if ((fd = open(WATCHDOG, O_RDWR)) < 0)
    {
        std::cerr << "failed to open watchdog\n";
        std::cerr << "Error: " << strerror(errno) << '\n';
        return 1;
    };
    if (ioctl(fd, WDIOC_SETTIMEOUT, &interval) != 0)
    {
        std::cerr << "failed to set the watchdog interval\n";
        std::cerr << "Error: " << strerror(errno) << '\n';
        close(fd);
        return 1;
    }

    std::cout << "Press f to feed the dog, h to say hello, q to quit\n";
    int state;
    do
    {
        state = getchar();
        switch (state)
        {
        case 'f':
            std::cout << "Feed!\n";
            ioctl(fd, WDIOC_KEEPALIVE, NULL);
            break;
        case 'h':
            std::cout << "hello!\n";
            break;
        }
    } while (state != 'q');

    std::cout << "Closing the application\n";
    close(fd);
    return 0;
}
