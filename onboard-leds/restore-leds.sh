#!/bin/bash

LED_PATH=/sys/class/leds/beaglebone:green:usr

echo "Restoring the LED default states"

echo "heartbeat" >> $LED_PATH"0/trigger"
echo "mmc0" >> $LED_PATH"1/trigger"
echo "cpu0" >> $LED_PATH"2/trigger"
echo "mmc1" >> $LED_PATH"3/trigger"
