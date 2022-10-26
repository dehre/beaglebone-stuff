## Description

Use the watchdog timer to automatically reboot the board if the user doesn't feed it every 30 seconds by sending text to stdin.

The timer can be stopped by typing `q` or `quit`.

### Build and Run

Refer to the top-level README for instructions on building.

Run:

```sh
# (on the VM) sftp the executable into the BBB
sftp-bbb
> put build/bin/watchdog

# (on the BBB) run
./watchdog
```

## Official documentation

https://www.kernel.org/doc/Documentation/watchdog/watchdog-api.txt
