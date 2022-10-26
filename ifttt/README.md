## Description

Using the [*If This Then That*](https://ifttt.com/explore) web service from the BBB to trigger crazy automated actions,
such as interacting with Amazon Alexa, creating a Google Calendar event, or parking an Husqvarna Automower.

## Description - Details

The `ifttt` program reads the room's temperature (or, in this case, generates a random one), and sends an http request to `maker.ifttt.com` if it's higher than 30°C.

For simplicity, I set up my `ifttt.com` account so that it sends me an email when it receives a request labeled `high_temperature`.

The `ifttt` program is automatically run by the linux cron daemon once per minute.

## Build and Run

Refer to the top-level README for instructions on building.

Before running, open the `.env` file and adjust the variable `IFTTT_KEY`.

```sh
# (on the VM) sftp the executable and the .env file into the BBB
sftp-bbb
> put build/bin/ifttt
> put .env

# (on the BBB) run
./ifttt
```

The program will (of course) fail if you didn't set up a WebHook on IFTTT.com or didn't set the `IFTTT_KEY` env variable.

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

Instead of generating a random temperature each time the program is run, you could easily use the SHT21 sensor to measure the real one.  
Check the [`i2c`](https://github.com/dehre/beaglebone-stuff/blob/main/i2c/README.md) directory for details on setting it up.

## Making HTTP Requests

The library [`cpp-httplib`](https://github.com/yhirose/cpp-httplib) has greatly sped up the task of making HTTP requests.  
It's been installed through Conan (check `conanfile.txt` and `CMakeLists.txt` for details).

## What else is possible with IFTTT?

A ton of stuff, check https://ifttt.com/explore
