# BeagleBone Stuff

A collection of tiny (and unrelated) projects that can be run on the BeagleBone Black (BBB).  

There's a README in every directory describing what that specific project doing, so you can randomly navigate through them.

## Details about the BBB

Processor: AM3358 ARM Cortex-A8

OS: Debian 10.3 Buster IoT (without graphical desktop)

## Setup

If you want to run a project on your own BBB, I suggest reading `cross-compilation-setup/README.md` first.  
It explains how I set up my computer (Mac M1) to cross compile programs for the board and upload them there.

## Building

The project uses a global CMake file with different targets.  
Dependencies are managed with Conan.

```sh
mkdir build
cd build

conan install ..

cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Build
cmake --build .
```

The executables will be placed in `build/bin`.

## The projects

Here are the projects, in the order they've been developed:

* `onboard-leds`: play with the onboard LEDs

* `gpio`: a cli utility to change the GPIO configuration for the pins and update their values

* `using-lkm`: 

* `i2c`:

* `ifttt`: ... and Linux's cron daemon
