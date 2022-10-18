## Description

Using the [*If This Then That*](https://ifttt.com/explore) web service from the BBB to trigger crazy automated actions,
such as interacting with Amazon Alexa, creating a Google Calendar event, or parking an Husqvarna Automower.

## Description - Details

The `ifttt` program reads the room's temperature using the SHT21 sensor, and sends an http request to `maker.ifttt.com` if it's higher than 30°C.

For simplicity, I set up my `ifttt.com` account so that it sends me an email when it receives a request labeled `high_temperature`.

The `ifttt` program is automatically run by the linux cron daemon once per minute.

## Build and Run

Refer to the top-level README for instructions on building.

The program expects the `IFTTT_KEY` environment variable to be set before running:

```sh
# sftp the executable into the BBB
sftp-bbb
> put ./build/ifttt

# on the BBB, set the IFTTT_KEY env variable and run the program
export IFTTT_KEY=theKeyYouReceivedWhenYouSetUpTheWebHook
./ifttt
```

The program will (of course) fail if you didn't set up a WebHook on IFTTT.com or didn't export the `IFTTT_KEY` env variable.

## Setting up the Linux Cron Daemon

In the BBB, edit `/etc/crontab` so that it runs the executable every minute, and redirect stdout and stderr to a file:

```sh
sudo su
vi /etc/crontab
```

Add this line:

```
* * * * * root IFTTT_KEY=yourKey /home/debian/ifttt >> /home/debian/ifttt-logs.txt 2>&1
```

Here's a nice online tool that helps with cron schedule expressions.

## Interacting with the SHT21 Temperature Sensor + Circuit

Check the [`i2c`](https://github.com/dehre/beaglebone-stuff/blob/main/i2c/README.md) directory for details on setting it up.

## Making HTTP Requests

The library [`cpp-httplib`](https://github.com/yhirose/cpp-httplib) has greatly sped up the task of making HTTP requests.  
It's been installed through Conan (check `conanfile.txt` and `CMakeLists.txt` for details).

## What else is possible with IFTTT?

A ton of stuff, check https://ifttt.com/explore
