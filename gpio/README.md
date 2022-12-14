## Description

A tiny program to control the GPIO pins on the board.

### Build and sftp the executable into the board:

Refer to the top-level README for instructions on building.

```sh
# (on the VM) sftp the executable into the BBB
sftp-bbb
> put build/bin/gpio
```

### Synopsis

```sh
./gpio <pin> <command> <target> [input]
```

Where:

    * <pin>: (pin formatted as "p8_16")
    * <command>: "read" or "write"
    * <target>: "value" or "direction"
    * <input>: (used only with write commands)

### Usage:

```sh
# Example: set pin p9_12 as output and and turn it on
./gpio p9_12 write direction out
./gpio p9_12 write value 1

# Example: set pin p8_16 as input with internal pull-up resistor and read its value
./gpio p8_16 write direction in+
./gpio p8_16 read value
```
