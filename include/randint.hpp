#pragma once

#include <cassert>
#include <random>
#include <type_traits>

/*
 * A simplified version of https://en.cppreference.com/w/cpp/experimental/randint
 */
template <typename T> T randint(T min_inclusive, T max_inclusive)
{
    static_assert(std::is_integral<T>::value, "randint works with integers only");
    assert(min_inclusive < max_inclusive); /* better than the anonymous segfault */
    std::random_device seed{};
    std::mt19937 rng(seed());
    std::uniform_int_distribution<T> uni(min_inclusive, max_inclusive);
    return uni(rng);
}
