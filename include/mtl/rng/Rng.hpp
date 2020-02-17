#pragma once

#include "mtl/Common.hpp"
#include "mtl/rng/engines/SplitMix64Engine.hpp"
#include "mtl/rng/engines/Xoshiro256StarStarEngine.hpp"


namespace mtl::rng {

using DefaultRandomEngine = Xoshiro256StarStarEngine;

template <class Engine = DefaultRandomEngine>
class Rng {
public:
  Rng(u64 seed) noexcept : engine_{seed} {}

  real_t uniform() noexcept;
  real_t uniform(real_t min, real_t max) noexcept;

  real_t normal() noexcept;
  real_t normal(real_t mean, real_t stddev) noexcept;

private:
  Engine engine_;
};


}  // namespace mtl::rng


#if defined(MTL_CONFIG_HEADER_ONLY)
#  include "mtl/rng/Rng.ipp"
#endif