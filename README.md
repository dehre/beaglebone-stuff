# BeagleBone Stuff

A collection of tiny embedded-linux projects to be run on the BeagleBone Black (BBB).  

You can find a README in every directory describing what that specific project doing and how to run it.

## Details about the BBB and the OS

Processor: AM3358 ARM Cortex-A8

OS: Debian 10.3 Buster IoT (without graphical desktop)

## Setup

I recommend reading `cross-compilation-setup/README.md` first.  
It explains how I set up my computer (Mac M1) to cross compile programs for the board and upload them there.  

## Building

The project uses a global CMake file with different targets.  
Dependencies are managed through Conan.  
The file `profile_crossbuild` tells the latter which platform we're generating binary files for.

```sh
mkdir build
cd build

conan install .. --build=missing --profile=../profile_crossbuild

cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Build
cmake --build .
```

The executables will be placed in `build/bin`.

If, for debugging purposes, you want to build the projects for the local VM:

```sh
mkdir build
cd build

conan install .. --build=missing

cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Build -DBUILD_LOCAL=1
cmake --build .
```

Exception: the project `onboard-leds` is built using a regular `Makefile`, so `cd` into the directory and simply call `make`.

Exception: the project `writing-lkm` uses `Kbuild`; check its readme for details.

## The projects

Here are the projects, in the order they've been developed:

* `onboard-leds`: play with the onboard LEDs (turn on, turn off, flash)

* `gpio`: a cli utility that allows changing direction, pull-up/down resistor, and value of gpio pins

* `using-lkm`: use the pre-built LKM to read a temperature sensor (I2C)

* `i2c`: use system calls to read a temperature sensor (I2C) 

* `ifttt`: use the [*IFTTT*](https://ifttt.com/explore) web service, and set up a cron daemon

* `mqtt`: publish data to Adafruit's MQTT broker (or to a local Mosquitto broker)

* `watchdog`: use the watchdog timer to reboot the board after 30 seconds of inactivity

* `writing-lkm`: write a tiny loadable kernel module

Others:

* `dotenv`: a tiny static library used to parse the `.env` file
