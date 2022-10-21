## Description

A tiny program to read temperature and humidity from the SHT21 sensor (I2C).

The same functionality could be achieved through a LKM (see [`using-lkm` directory](https://github.com/dehre/beaglebone-stuff/blob/main/using-lkm/README.md)).

## Build, run, and clean:

```sh
# build
mkdir -p build
cd build
cmake ..
make

# sftp the executable into the BBB
sftp-bbb
> put ./build/i2c

# run
./i2c

# clean
rm -rf build
```

## Circuit

<img src="./circuit.svg" width=70% height=70%>

## Official documentation

https://www.kernel.org/doc/Documentation/i2c/dev-interface
