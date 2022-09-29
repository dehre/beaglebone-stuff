#pragma once

/*
 * From: https://github.com/beagleboard/bb.org-overlays/blob/master/tools/beaglebone-universal-io/config-pin#L479
 */

#include <map>
#include <string_view>

struct PinConfig
{
    const bool isGPIO;
    // TODO LORIS: string_view
    const char *GPIO;
    const char *PinMux[10];
};

// clang-format off
const std::map<std::string_view, PinConfig> PinMappings
{
    {
        "p8_15",
        {.isGPIO = true,
         .GPIO = "47",
         .PinMux = {"default", "gpio", "gpio_pu", "gpio_pd", "gpio_input", "qep", "pru_ecap", "pruin"}},
    },
    {
        "p8_16",
        {.isGPIO = true,
         .GPIO = "46",
         .PinMux = {"default", "gpio", "gpio_pu", "gpio_pd", "gpio_input", "qep", "pruin"}}
    }
};
// clang-format on
