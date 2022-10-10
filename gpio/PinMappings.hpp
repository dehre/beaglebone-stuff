#pragma once

/*
 * From: https://github.com/beagleboard/bb.org-overlays/blob/master/tools/beaglebone-universal-io/config-pin#L479
 */

#include <map>
#include <string_view>

struct PinConfig
{
    const bool isGPIO;
    // TODO LORIS: rename GPIONumber
    const std::string_view GPIO;
    const std::string_view PinMux[10];
};

// clang-format off
const std::map<std::string_view, PinConfig> PinMappings
{
    {
        "p8_16",
        {.isGPIO = true,
         .GPIO = "46",
         .PinMux = {"default", "gpio", "gpio_pu", "gpio_pd"}}
    },
    {
        "p9_12",
        {.isGPIO = true,
         .GPIO = "60",
         .PinMux = {"default", "gpio", "gpio_pu", "gpio_pd"}}
    }
};
// clang-format on
