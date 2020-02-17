/**
 * Xoshiro256** Generator
 *
 * See http://prng.di.unimi.it/ for more details.
 */

#pragma once

#include "mtl/Common.hpp"


namespace mtl::rng {

class Xoshiro256StarStarEngine {
public:
  using result_type = u64;

  Xoshiro256StarStarEngine(u64 s) noexcept { seed(s); }

  void seed(u64 s) noexcept;

  u64 next() noexcept;

  void discard(size_t n) noexcept;

  u64 operator()() noexcept { return next(); }

  static constexpr u64 min() { return std::numeric_limits<u64>::min(); }

  static constexpr u64 max() { return std::numeric_limits<u64>::max(); }

private:
  u64 state_[4];
};

}  // namespace mtl::rng


#if defined(MTL_CONFIG_HEADER_ONLY)
#  include "mtl/rng/engines/Xoshiro256StarStarEngine.ipp"
#endif