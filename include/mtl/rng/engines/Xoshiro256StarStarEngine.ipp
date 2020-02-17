#pragma once

#include "mtl/Assert.hpp"
#include "mtl/BitFun.hpp"
#include "mtl/Common.hpp"
#include "mtl/rng/engines/SplitMix64Engine.hpp"
#include "mtl/rng/engines/Xoshiro256StarStarEngine.hpp"


namespace mtl::rng {

void Xoshiro256StarStarEngine::seed(u64 s) noexcept
{
  auto engine = SplitMix64Engine{s};
  state_[0] = engine.next();
  state_[1] = engine.next();
  state_[2] = engine.next();
  state_[3] = engine.next();

  MTL_ASSERT(state_[0] != 0 && state_[1] != 0 && state_[2] != 0 && state_[3] != 0,
             "xoshiro256** engine cannot be initialized with an all-zero state");
}


u64 Xoshiro256StarStarEngine::next() noexcept
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


void Xoshiro256StarStarEngine::discard(usize n) noexcept
{
  while (n != 0) {
    next();
    --n;
  }
}


}  // namespace mtl::rng