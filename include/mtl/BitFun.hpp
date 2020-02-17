#pragma once

#include <cstring>

#include "mtl/Common.hpp"
#include "mtl/Macros.hpp"

namespace mtl {

template <class T>
constexpr usize bit_width() noexcept
{
  return CHAR_BIT * sizeof(T);
}

template <class T>
constexpr usize bit_width(T) noexcept
{
  return bit_width<T>();
}

template <class To, class From,
          MTL_REQUIRE(sizeof(To) == sizeof(From) && std::is_trivially_copyable_v<To> &&
                      std::is_trivially_copyable_v<From>)>
To bit_cast(From from) noexcept
{
  To to;
  std::memcpy(&to, &from, sizeof(to));
  return to;
}

template <class T>
constexpr T rotl(T t, usize k) noexcept
{
  return (t << k) | (t >> (bit_width(t) - k));
}

template <class T>
constexpr T rotr(T t, usize k) noexcept
{
  return (t >> k) | (t << (bit_width(t) - k));
}

}  // namespace mtl