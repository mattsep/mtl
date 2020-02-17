/**
 * Xoshiro256** Generator
 *
 * See http://prng.di.unimi.it/ for more details.
 */

#pragma once

#include "mtl/BitFun.hpp"
#include "mtl/Common.hpp"
#include "mtl/rng/SplitMix64.hpp"

namespace mtl::rng {

class Xoshiro256Engine {
public:
  using result_type = u64;

  Xoshiro256Engine(result_type s) noexcept { seed(s); }

  inline void seed(result_type s) noexcept
  {
    assert(s > 0);
    init_state(s);
  }

  result_type operator()() noexcept
  {
    const auto out = 9 * rotl(5 * state_[1], 7);
    const auto tmp = state_[1] << 17;

    state_[2] ^= state_[0];
    state_[3] ^= state_[1];
    state_[1] ^= state_[2];
    state_[0] ^= state_[3];

    state_[2] ^= tmp;
    state_[3] = rotl(state_[3], 45);

    return out;
  }

  void discard(size_t n) noexcept
  {
    while (n != 0) {
      (*this)();
      --n;
    }
  }

  constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }
  constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }

private:
  result_type state_[4];

  void init_state(result_type seed) noexcept
  {
    auto generator = SplitMix64Engine(seed);
    state_[0] = generator();
    state_[1] = generator();
    state_[2] = generator();
    state_[3] = generator();
  }
};  // namespace mtl::random

}  // namespace mtl::rng