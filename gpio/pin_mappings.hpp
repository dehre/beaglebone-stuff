#pragma once

/*
 * From: https://github.com/beagleboard/bb.org-overlays/blob/master/tools/beaglebone-universal-io/config-pin#L479
 */

#include <map>
#include <string_view>

struct PinConfig
{
    const bool is_gpio;
    const std::string_view gpio_number;
    const std::string_view pin_mux[10];
};

// clang-format off
const std::map<std::string_view, PinConfig> pin_mappings
{
    {
        "p8_16",
        {.is_gpio = true,
         .gpio_number = "46",
         .pin_mux = {"default", "gpio", "gpio_pu", "gpio_pd"}}
    },
    {
        "p9_12",
        {.is_gpio = true,
         .gpio_number = "60",
         .pin_mux = {"default", "gpio", "gpio_pu", "gpio_pd"}}
    }
};
// clang-format on
