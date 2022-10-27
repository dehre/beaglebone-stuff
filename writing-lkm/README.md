## Description

Writing a device driver that toggles the LED each time the button is pressed (on rising edges).  
The driver is built as a kernel module, so that it can be dynamically loaded and unloaded.

## Circuit

<img src="./circuit.svg" width=70% height=70%>

## Build the LKM - Foreword

Although cross-compiling a LKM is possible, I chose to compile it directly on the BBB for simplicity.

Assuming the basic tools are already installed there (`sudo apt install build-essential`),
it should be quite straightforward to [set up VSCode for remote development](https://code.visualstudio.com/docs/remote/ssh).

To upload the source code on the board:

```sh
cd beaglebone-stuff
sftp-bbb
> put -r writing-lkm
```

## Build the LKM

*This entire section assumes you're on the BBB.*

First, install the appropriate Linux kernel headers:

```sh
sudo apt update
sudo apt install linux-headers-$(uname -r)
```

They will be placed under `/lib/modules/$(uname -r)/build/include`.

Then simply call `make` to build the LKM:

```sh
cd writing-lkm
make
```

If no errors popped up, new file named `led_driver.ko` should have been generated:

```sh
ls -l | grep *.ko
```

Output:

```sh
-rw-r--r-- 1 debian debian 7436 Jan 01 00:00 led_driver.ko
```

## Use the LKM

Finally, play around with the module:

```sh
# insert the module
sudo insmod led_driver.ko

# remove the module
sudo rmmod led_driver.ko

# get info about the module
modinfo led_driver.ko

# get other info about the module
ls /sys/module/led_driver

# get other info about the module
cat /proc/modules | grep led_driver
```

The `printk` output can be viewed in the kernel ring buffer or in the kernel log:

```sh
# kernel ring buffer
dmesg | tail -n 5

# kernel log (the `+G` flag jumps to the end)
less +G /var/log/kern.log
```

## The `hello.ko` LKM

The file `hello.c` contains the source code for a simpler LKM.  
All it does is printing a message when it's loaded and unloaded from the kernel.

It can be useful for debugging, and doesn't require setting up an external circuit.

To use it, update the first line in the `Makefile` to look like:

```sh
obj-m+=hello.o
```

Then build and load the module:

```sh
make

sudo insmod hello.ko
sudo rmmod hello.ko
```
