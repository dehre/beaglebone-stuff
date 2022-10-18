## Description

A tiny program that publishes a random temperature to the Adafruit MQTT broker.

[Adafruit IO](https://io.adafruit.com) has been chosen because it's free (up to 30 messages per minute) and
it provides easy to set up dashboards to visualize the data.  
Except for minor changes, the program should equally work with other MQTT brokers, such as [HiveMQ](https://www.hivemq.com) or [Cedalo](https://cedalo.com/mqtt-broker-pro-mosquitto).

## Set up Adafruit IO

1. Create a new account at `io.adafruit.com`

2. Create a new Feed named `temperature` (or whatever)

3. Open `main.cpp` and adjust the variables `g_adafruitUsername` and `g_topic`

4. Get your AIO key (you'll need it to run the program)

### Build and Run

Refer to the top-level README for instructions on building.

The program expects the `ADAFRUIT_KEY` environment variable to be set before running:

```sh
# sftp the executable into the BBB
sftp-bbb
> put ./build/mqtt

# run
ADAFRUIT_KEY=yourKey ./mqtt
```

## Dependencies

This project relies on the [Eclipse Paho MQTT client library}(https://github.com/eclipse/paho.mqtt.c),  
which is installed through Conan.
