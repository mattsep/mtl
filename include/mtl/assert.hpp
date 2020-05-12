/**
 * @file assert.hpp
 * @brief Defines a alternative assert macro and associated assert handler that allows for
 *        formatted output messages.
 */

#pragma once

#include <stdexcept>
#include <type_traits>

#include "fmt/format.h"

#include "mtl/common.hpp"

#define MTL_STRINGIFY(expr) MTL_STRINGIFY_IMPL(expr)
#define MTL_STRINGIFY_IMPL(expr) #expr

#if !defined(NDEBUG)
#define MTL_ASSERT(cond, ...) (void(0))
#define MTL_HANDLE_ASSERT(cond, ...) (void(0))
#else
#define MTL_HANDLE_ASSERT(handler, cond, ...)                                                      \
  mtl::assertion<handler>{!!(cond), MTL_STRINGIFY(cond), __FILE__, __LINE__}(__VA_ARGS__)
#define MTL_ASSERT(cond, ...) MTL_HANDLE_ASSERT(mtl::default_assertion_handler, cond, __VA_ARGS__)
#endif

namespace mtl {

class assertion_error : public std::runtime_error {
public:
  assertion_error(std::string const& msg) : std::runtime_error{msg} {}
  assertion_error(czstring msg) : std::runtime_error{msg} {}
  assertion_error(assertion_error const& other) noexcept = default;
};

class assertion_failure_throws {
public:
  static void handle(std::string const& message) { throw assertion_error(message); }
};

class assertion_failure_aborts {
public:
  static void handle(std::string const& message) {
    fmt::print(stderr, message);
    std::abort();
  }
};

using default_assertion_handler =
    std::conditional_t<config::assert_aborts, assertion_failure_aborts, assertion_failure_throws>;

template <class Handler = default_assertion_handler>
class assertion {
public:
  using handler = Handler;

  assertion(bool cond, czstring condstr, czstring file, int line)
    : cond_{cond}, condstr_{condstr}, file_{file}, line_{line} {}

  void operator()() {
    if (!cond_) {
      auto msg = format_message();
      handler::handle(msg);
    }
  }

  template <class... Args>
  void operator()(czstring message, Args&&... args) {
    if (!cond_) {
      auto msg = format_message(message, std::forward<Args>(args)...);
      handler::handle(msg);
    }
  }

private:
  bool cond_;
  czstring condstr_;
  czstring file_;
  const int line_;

  auto format_message() const {
    fmt::memory_buffer buf;
    fmt::format_to(buf, "Assertion failed: '{}'\n", condstr_);
    fmt::format_to(buf, "  file: '{}'\n", file_);
    fmt::format_to(buf, "  line: {}\n", line_);
    return fmt::to_string(buf);
  }

  template <class... Args>
  auto format_message(czstring message, Args&&... args) const {
    auto msg = fmt::format(message, std::forward<Args>(args)...);

    fmt::memory_buffer buf;
    fmt::format_to(buf, "Assertion failed: '{}'\n", condstr_);
    fmt::format_to(buf, "  file: '{}'\n", file_);
    fmt::format_to(buf, "  line: {}\n", line_);
    fmt::format_to(buf, "  message: {}\n", msg);

    return fmt::to_string(buf);
  }
};

}  // namespace mtl

#if defined(MTL_BUILD_TESTS)

#include "doctest/doctest.h"

TEST_CASE("mtl::assert") {


}

#endif