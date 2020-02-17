#pragma once

#include "mtl/BitFun.hpp"
#include "mtl/Common.hpp"
#include "mtl/rng/Rng.hpp"


namespace mtl::rng {

template <class Engine>
real_t Rng<Engine>::uniform() noexcept
{
  static_assert(sizeof(decltype(engine_())) >= sizeof(real_t),
                "Random engine doesn't provide enough bits for the current choice of real_t");

  auto randu = engine_();
  if constexpr (std::is_same_v<real_t, float>) {
    return (randu >> (bit_width(randu) - 24)) * real_t{0x1.0p-24};
  } else if constexpr (std::is_same_v<real_t, double>) {
    return (randu >> (bit_width(randu) - 53)) * real_t{0x1.0p-53};
  }
}


template <class Engine>
real_t Rng<Engine>::uniform(real_t min, real_t max) noexcept
{
  return (max - min) * uniform() + min;
}


template <class Engine>
real_t Rng<Engine>::normal() noexcept
{
  static real_t cache = 0.0;
  static bool has_cached_value = false;

  if (has_cached_value) {
    has_cached_value = false;
    return cache;
  } else {
    real_t u, v;
    real_t s = 0.0;
    while (s == 0.0 || s >= 1.0) {
      u = uniform(-1, 1);
      v = uniform(-1, 1);
      s = u * u + v * v;
    }

    s = std::sqrt(-2.0 * std::log(s) / s);

    has_cached_value = true;
    cache = v * s;

    return u * s;
  }
}


template <class Engine>
real_t Rng<Engine>::normal(real_t mean, real_t stddev) noexcept
{
  return stddev * normal() + mean;
}

}  // namespace mtl::rng