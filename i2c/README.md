## Description

A tiny program to read temperature and humidity from the SHT21 sensor (I2C).

The same functionality could be achieved through a LKM (see [`using-lkm` directory](https://github.com/dehre/beaglebone-stuff/blob/main/using-lkm/README.md)).

## Build and Run:

Refer to the top-level README for instructions on building.

```sh
# (on the VM) sftp the executable into the BBB
sftp-bbb
> put build/bin/i2c

# (on the BBB) run
./i2c
```

## Circuit

<img src="./circuit.svg" width=70% height=70%>

## Official documentation

https://www.kernel.org/doc/Documentation/i2c/dev-interface
