## Description

Writing a driver that toggles the LED when each time the button is pressed.  
The driver is built as a kernel module (LKM), so that it can be dynamically loaded and unloaded.

## Circuit

<img src="./circuit.svg" width=70% height=70%>

## Build the LKM - Foreword

Although cross-compiling a LKM is possible, I preferred compiling it directly from the BBB for simplicity.

Assuming the basic tools are already installed there (`sudo apt install build-essential`),
it should be quite straightforward to [set up vscode for remote development](https://code.visualstudio.com/docs/remote/ssh).

## Build the LKM

*This entire section assumes you're on the BBB.*

First, install the Linux kernel headers:

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

If no errors popped up, you should be good already.  
A new file named `hello.ko` should have been generated:

```sh
ls -l | grep *.ko
```

Output:

```sh
-rw-r--r-- 1 debian debian 5148 Jan 01 00:00 hello.ko
```

## Use the LKM

Finally you can play around with the module:

```sh
# insert the module
sudo insmod hello.ko

# remove the module
sudo rmmod hello.ko

# get info about the module
modinfo hello.ko

# get other info about the module
ls /sys/module/hello

# get other info about the module
cat /proc/modules | grep hello
```

The `printk` outputs can be viewed in the kernel ring buffer or in the kernel log:

```sh
# kernel ring buffer
dmesg | tail -n 5

# kernel log (the `+G` flag jumps to the end)
less +G /var/log/kern.log
```

## The `hello` LKM

TODO LORIS

`hello.c` is the tiniest LKM
