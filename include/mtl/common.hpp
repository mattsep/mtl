#pragma once

#include <climits>
#include <cstdint>
#include <limits>

#include "mtl/config.hpp"
#include "mtl/version.hpp"

#if CHAR_BIT != 8
#error MTL assumes that a byte consists of 8 bits
#endif

static_assert(sizeof(float) == 4 && sizeof(double) == 8 && std::numeric_limits<float>::is_iec559 &&
                  std::numeric_limits<double>::is_iec559,
              "MTL assumes IEEE 754 compliant floating point types");

namespace mtl {

using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::int8_t;

using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::uint8_t;

using std::ptrdiff_t;
using std::size_t;

#if defined(__SIZEOF_INT128__)
using int128_t = __int128_t;
using uint128_t = __uint128_t;
#else
// TODO: maybe implement a basic uint128_t type in cases where it isn't available?
#error MTL requires the existence of a 128-bit integral type
#endif

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = int128_t;
using ibyte = i8;
using isize = ptrdiff_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = uint128_t;
using ubyte = u8;
using usize = size_t;

using f32 = float;
using f64 = double;

using zstring = char*;
using czstring = char const*;

using t = ssize_t;

using index_t = config::index_type;
using integer_t = config::integer_type;
using real_t = config::real_type;
using complex_t = config::complex_type;

}  // namespace mtl