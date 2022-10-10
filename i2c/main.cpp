#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdint>
#include <iostream>

#include "I2C.hpp"

int main()
{
    I2C sensor{I2C(2, 0x40)};

    sensor.writei2c<1>({{0xE3}});
    auto data_arr{sensor.readi2c<2>()};

    uint16_t raw_reading{static_cast<uint16_t>((data_arr[0] << 8) | (data_arr[1] & 0xFC))};
    double rawReadingDouble{static_cast<double>(raw_reading)};
    double dst{-46.85 + 175.72 / 65536.0 * rawReadingDouble};

    std::cout << "Everything went well! Got data: " << dst << '\n';
}

// int main()
// {
//     std::cout << "Starting the application\n";

//     int file;
//     if ((file = open("/dev/i2c-2", O_RDWR)) < 0)
//     {
//         perror("failed to open the bus\n");
//         return 1;
//     };
//     if (ioctl(file, I2C_SLAVE, 0x40) < 0)
//     {
//         perror("Failed to connect to the sensor\n");
//         return 1;
//     }

//     char writeBuffer[1]{0xE3};
//     if (write(file, writeBuffer, 1) != 1)
//     {
//         perror("Failed to write 0xE3\n");
//         return 1;
//     }

//     uint8_t data_arr[2]{};
//     if (read(file, data_arr, 2) != 2)
//     {
//         perror("Failed to read raw data\n");
//         return 1;
//     }

//     uint16_t raw_reading{(data_arr[0] << 8) | (data_arr[1] & 0xFC)};
//     float dst{-46.85 + 175.72 / 65536 * (float)raw_reading};

//     std::cout << "Everything went well! Got data: " << dst << '\n';
//     close(file);
//     return 0;
// }
