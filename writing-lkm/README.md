## Description

## Build the LKM - Foreword

Although cross-compiling a LKM is possible, I preferred compiling it directly from the BBB for simplicity.

That means:

1. write code on the VM (or local machine)

2. sftp the files into the BBB

3. call `make` and check for compiler errors

So, before proceeding into the next section, copy the entire `writing-lkm` directory into the BBB:

```sh
sftp-bbb
> put -r writing-lkm/
```

## Build the LKM

*This entire section assumes you're on the BBB.*

First, install the Linux kernel headers:

```sh
# on the BBB
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

# get info about the module
modinfo hello.ko

# remove the module
sudo rmmod hello.ko
```

The `printk` outputs can be viewed in the kernel ring buffer or in the kernel log:

```sh
# option a
dmesg | tail -n 5

# option b (the `+G` flag jumps to the end)
less +G /var/log/kern.log
```
