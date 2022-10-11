## Description

Using a pre-build LKM (Linux Kernel Module) to read temperature and humidity from the SHT21 sensor (I2C).

The same functionality could be achieved by programmatically accessing the i2c device (see [`i2c` directory](https://github.com/dehre/beaglebone-stuff/blob/main/i2c/I2C.hpp)).

## Circuit

<img src="./circuit.svg" width=70% height=70%>

## LKM - Source code and docs

Here's the source code for the kernel module: https://github.com/torvalds/linux/blob/master/drivers/hwmon/sht21.c

The official documentation: https://docs.kernel.org/hwmon/sht21.html

## LKM - How to use it

First, power up the BBB and ssh into it.  
Then connect the +3.3V and GND pins to the external circuit.

Finally:

```sh
# gain root privileges, or use `sudo` each time you're asked
sudu su

# verify that the sht21 kernel module exists
find "/lib/modules/$(uname -r)/kernel/drivers/hwmon" -name sht21.ko.xz

# load the module
modprobe sht21

# let the kernel know to which bus the sensor is connected
echo sht21 0x40 > /sys/bus/i2c/devices/i2c-2/new_device

# the sensor values should now be exposed at /sys/class/hwmon/hwmon0 (or hwmon<some other number>)
cd /sys/class/hwmon/hwmon0

# read temperature, humidity, and eic (electronic identification code) through sysfs
cat temp1_input
cat humidity1_input
cat eic
```

## Aside: `i2cdetect`

Linux provides a set of tools, named `i2c-tools`, for interfacing to I2C bus devices.  
To install it:

```sh
sudo apt install i2c-tools
```

Among those tools, `i2cdetect` is supposed to detect which devices are present on the bus.  
Turns out it's not able to detect the SHT21:

```sh
i2cdetect -y -r 2
```

Output:

```
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --
```

Check this post for a more detailed description: https://forum.beagleboard.org/t/bbb-debian-10-3-sht21-sensor-not-detected-i2c/32946

## Aside - The LKM implementation

For reference, I copied the current LKM implementation into [`sht21.c`](https://github.com/dehre/beaglebone-stuff/blob/main/using-lkm/sht21.c).
