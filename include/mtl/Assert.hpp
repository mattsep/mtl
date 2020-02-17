#pragma once

#include <cstdio>

#include "mtl/Macros.hpp"

#if defined(NDEBUG)
#  define MTL_ASSERT(cond, ...) void(0)
#else
#  define MTL_ASSERT(cond, ...)                                                                    \
    mtl::internal::AssertionHandler{!!(cond), MTL_STRINGIFY(cond), __FILE__, __LINE__}(__VA_ARGS__)
#endif

namespace mtl::internal {

class AssertionHandler {
public:
  AssertionHandler(bool cond, const char* condstr, const char* file, int line)
    : cond_{cond}, condstr_{condstr}, file_{file}, line_{line}
  {
  }

  void operator()()
  {
    if (!cond_) {
      std::printf("Assertion failed: '%s'\n", condstr_);
      std::printf("  file: '%s'\n", file_);
      std::printf("  line: %d\n", line_);
    }
  }

  template <class... Args>
  void operator()(const char* message, Args&&... args)
  {
    if (!cond_) {
      (*this)();
      std::printf("  message: ");
      if constexpr (sizeof...(Args) > 0) {
        std::printf(message, MTL_FORWARD(args)...);
        std::printf("\n");
      } else {
        std::puts(message);
      }
    }
  }

private:
  bool cond_;
  const char* condstr_;
  const char* file_;
  const int line_;
};

}  // namespace mtl::internal