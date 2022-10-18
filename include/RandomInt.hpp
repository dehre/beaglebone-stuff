#pragma once

#include <cassert>
#include <random>

class RandomInt
{
  public:
    RandomInt() : m_rng{std::mt19937(std::random_device{}())}
    {
    }

    int generate(int minInclusive, int maxInclusive)
    {
        assert(minInclusive < maxInclusive); /* better than the anonymous segfault */
        std::uniform_int_distribution<int> uni(minInclusive, maxInclusive);
        return uni(m_rng);
    }

  private:
    std::mt19937 m_rng{};
};
