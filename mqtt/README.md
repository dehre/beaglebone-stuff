## Description

A tiny program that reads the room's temperature (or, in this case, generates a random one), and publishes it to the Adafruit MQTT broker.

[Adafruit IO](https://io.adafruit.com) has been chosen because it's free (up to 30 messages per minute) and
it provides easy to set up dashboards to visualize the data.  
Except for minor changes, the program should equally work with other MQTT brokers, such as [HiveMQ](https://www.hivemq.com) or [Cedalo](https://cedalo.com/mqtt-broker-pro-mosquitto).

## Set up Adafruit IO

1. Create a new account at `io.adafruit.com`

2. Create a new Feed named `temperature`

3. Get your AIO key (you'll need it to run the program)

4. Open the `.env` file and adjust the variables `ADAFRUIT_USERNAME` and `ADAFRUIT_KEY`

### Build and Run

Refer to the top-level README for instructions on building.

Run:

```sh
# (on the VM) sftp the executable and the .env file into the BBB
sftp-bbb
> put build/bin/mqtt
> put .env

# (on the BBB) run
./mqtt
```

## Using a local Mosquitto broker

Before trying to publish data to `adafruit.io`, it might be useful to try the program locally.  
In that case, simply adjust the `.env` file to look like:

```
ADAFRUIT_ADDRESS=tcp://localhost:1883
ADAFRUIT_USERNAME=
ADAFRUIT_KEY=
```

Then install a local Mosquitto server and the Mosquitto client applications:

```sh
sudo apt update
sudo apt install mosquitto
sudo apt install mosquitto-clients
```

Finally, start the subscriber client on a terminal, and run the program on a different one:

```sh
# on terminal A
mosquitto_sub -v -t "user/feeds/temperature"

# on terminal B
./mqtt
```

## Interacting with the SHT21 Temperature Sensor + Circuit

Instead of generating a random temperature each time the program is run, you could easily use the SHT21 sensor to measure the real one.  
Check the [`i2c`](https://github.com/dehre/beaglebone-stuff/blob/main/i2c/README.md) directory for details on setting it up.

## Dependencies

This project relies on the [Eclipse Paho MQTT client library}(https://github.com/eclipse/paho.mqtt.c),  
which is installed through Conan.
