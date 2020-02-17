#pragma once

#include "mtl/Common.hpp"
#include "mtl/rng/engines/SplitMix64Engine.hpp"


namespace mtl::rng {

u64 SplitMix64Engine::next() noexcept
{
  state_ += u64{0x9E3779B97F4A7C15};
  auto out = state_;

  out = (out ^ (out >> 30)) * u64{0xBF58476D1CE4E5B9};
  out = (out ^ (out >> 27)) * u64{0x94D049BB133111EB};
  out = (out ^ (out >> 31));

  return out;
}

}  // namespace mtl::rng