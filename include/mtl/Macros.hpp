#pragma once

#include <utility>


#define MTL_FORWARD(arg) std::forward<decltype(arg)>(arg)

#define MTL_REQUIRE(...) std::enable_if_t<(__VA_ARGS__), int> = 0

#define MTL_STRINGIFY(expr)      MTL_STRINGIFY_IMPL(expr)
#define MTL_STRINGIFY_IMPL(expr) #expr