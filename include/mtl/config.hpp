#pragma once

#include <complex>
#include <cstdint>

#if !defined(MTL_CONFIG_INDEX_TYPE)
#  define MTL_CONFIG_INDEX_TYPE std::size_t
#endif

#if !defined(MTL_CONFIG_INTEGER_TYPE)
#  define MTL_CONFIG_INTEGER_TYPE std::int64_t
#endif

#if !defined(MTL_CONFIG_REAL_TYPE)
#  define MTL_CONFIG_REAL_TYPE double
#endif

#if !defined(MTL_CONFIG_COMPLEX_TYPE)
#  define MTL_CONFIG_COMPLEX_TYPE std::complex<double>
#endif

#if !defined(MTL_CONFIG_ASSERT_ABORTS) || !defined(MTL_CONFIG_ASSERT_THROWS)
#  define MTL_CONFIG_ASSERT_ABORTS
#endif

namespace mtl::config {

using index_type = MTL_CONFIG_INDEX_TYPE;
using integer_type = MTL_CONFIG_INTEGER_TYPE;
using real_type = MTL_CONFIG_REAL_TYPE;
using complex_type = MTL_CONFIG_COMPLEX_TYPE;

#if defined(MTL_CONFIG_ASSERT_ABORTS)
constexpr bool assert_aborts = true;
#else
constexpr bool assert_aborts = false;
#endif

}  // namespace mtl::config

#undef MTL_CONFIG_INDEX_TYPE
#undef MTL_CONFIG_INTEGER_TYPE
#undef MTL_CONFIG_REAL_TYPE
#undef MTL_CONFIG_COMPLEX_TYPE
#undef MTL_CONFIG_ASSERT_ABORTS
#undef MTL_CONFIG_ASSERT_THROWS