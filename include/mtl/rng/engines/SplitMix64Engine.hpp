/**
 * SplitMix64 Generator
 *
 * See http://prng.di.unimi.it/ for more details.
 */

#pragma once

#include "mtl/Common.hpp"

namespace mtl::rng {

class SplitMix64Engine {
public:
  using result_type = u64;

  SplitMix64Engine(result_type s) noexcept : state_{s} {}

  inline void seed(result_type s) noexcept { state_ = s; }

  inline result_type operator()() noexcept
  {
    state_ += 0x9E3779B97F4A7C15;

    auto temp = state_;
    temp = (temp ^ (temp >> 30)) * 0xBF58476D1CE4E5B9;
    temp = (temp ^ (temp >> 27)) * 0x94D049BB133111EB;
    return (temp ^ (temp >> 31));
  }

  inline void discard(size_t n) noexcept { state_ += n * 0x9E3779B97F4A7C15; }
  
  constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min(); }
  constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max(); }

private:
  result_type state_;
};

}  // namespace mtl::rng