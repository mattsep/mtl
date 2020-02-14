#pragma once

#define MTL_VERSION_MAJOR 0
#define MTL_VERSION_MINOR 1
#define MTL_VERSION_PATCH 0
#define MTL_VERSION_STR   "0.1.0"
#define MTL_VERSION       (10000 * MTL_VERSION_MAJOR + 100 * MTL_VERSION_MINOR + MTL_VERSION_PATCH)

#if !defined(MTL_CONFIG_INTEGER_TYPE)
#  define MTL_CONFIG_INTEGER_TYPE i64
#endif

#if !defined(MTL_CONFIG_REAL_TYPE)
#  define MTL_CONFIG_REAL_TYPE f64
#endif

#if !defined(MTL_CONFIG_COMPLEX_TYPE)
#  define MTL_CONFIG_COMPLEX_TYPE std::complex<real_t>
#endif