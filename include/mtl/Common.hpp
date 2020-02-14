#pragma once

#include <cassert>
#include <climits>
#include <complex>
#include <cstdint>
#include <limits>

#include "mtl/Config.hpp"

namespace mtl {

static_assert(CHAR_BIT == 8, "MTL assumes that a byte is 8 bits");
static_assert(sizeof(float) == 4 && sizeof(double) == 8 && std::numeric_limits<float>::is_iec559 &&
                  std::numeric_limits<double>::is_iec559,
              "MTL assumes IEEE 754 compliant floating point types");

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using usize = std::size_t;
using ubyte = unsigned char;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using isize = std::ptrdiff_t;

using f32 = float;
using f64 = double;

using integer_t = MTL_CONFIG_INTEGER_TYPE;
using real_t = MTL_CONFIG_REAL_TYPE;
using complex_t = MTL_CONFIG_COMPLEX_TYPE;

}  // namespace mtl