## Description

A tiny program to control the onboard LEDs.

Build, run, and clean:

```sh
make

# <command> is one of "on", "off", or "flash"
sudo ./makeLEDs <command>

make clean
```

Restore the default LEDs functionality:

```sh
./restoreLEDs.sh
```
