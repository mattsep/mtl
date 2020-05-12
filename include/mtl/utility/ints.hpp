#pragma once

#include <cstdint>

#include "mtl/common.hpp"

namespace mtl::utility {

// ----------------------------------------------
// int_bits_t
// ----------------------------------------------

template <usize Bits>
struct int_bits;

template <>
struct int_bits<8> {
  using type = int8_t;
};

template <>
struct int_bits<16> {
  using type = int16_t;
};

template <>
struct int_bits<32> {
  using type = int32_t;
};

template <>
struct int_bits<64> {
  using type = int64_t;
};

template <>
struct int_bits<128> {
  using type = int128_t;
};

template <usize Bits>
using int_bits_t = typename int_bits<Bits>::type;

// ----------------------------------------------
// uint_bits_t
// ----------------------------------------------

template <usize Bits>
struct uint_bits;

template <>
struct uint_bits<8> {
  using type = uint8_t;
};

template <>
struct uint_bits<16> {
  using type = uint16_t;
};

template <>
struct uint_bits<32> {
  using type = uint32_t;
};

template <>
struct uint_bits<64> {
  using type = uint64_t;
};

template <>
struct uint_bits<128> {
  using type = uint128_t;
};

template <usize Bits>
using uint_bits_t = typename uint_bits<Bits>::type;

// ----------------------------------------------
// int_least_bits_t
// ----------------------------------------------

template <usize Bits>
struct int_least_bits {
  // clang-format off
  using type = 
  std::conditional_t<(Bits <= 8),
    int_bits_t<8>,
    std::conditional_t<(Bits <= 16),
      int_bits_t<16>,
      std::conditional_t<(Bits <= 32),
        int_bits_t<32>,
        std::conditional_t<(Bits <= 64),
          int_bits_t<64>,
          std::conditional_t<(Bits <= 128),
            int_bits_t<128>,
            void
          >
        >
      >
    >
  >;
  // clang-format on
};

template <usize Bits>
using int_least_bits_t = typename int_least_bits<Bits>::type;

// ----------------------------------------------
// uint_least_bits_t
// ----------------------------------------------

template <usize Bits>
struct uint_least_bits;

}  // namespace mtl::utility