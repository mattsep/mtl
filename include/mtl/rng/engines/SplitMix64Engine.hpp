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

  SplitMix64Engine(u64 s) noexcept : state_{s} {}

  void seed(u64 s) noexcept { state_ = s; }

  u64 next() noexcept;

  void discard(size_t n) noexcept { state_ += n * u64{0x9E3779B97F4A7C15}; }

  u64 operator()() noexcept { return next(); }

  static constexpr u64 min() { return std::numeric_limits<u64>::min(); }

  static constexpr u64 max() { return std::numeric_limits<u64>::max(); }

private:
  u64 state_;
};

}  // namespace mtl::rng


#if defined(MTL_CONFIG_HEADER_ONLY)
#  include "mtl/rng/engines/SplitMix64Engine.ipp"
#endif