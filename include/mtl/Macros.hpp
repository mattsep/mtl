#pragma once

#define MTL_FORWARD(arg) std::forward<decltype(arg)>(arg)
#define MTL_REQUIRE(...) typename = std::enable_if_t<(__VA_ARGS__)>