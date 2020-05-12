/**
 * @file jsf.hpp
 * @brief An implementation of Bob Jenkin's Small/Fast Random Engine.
 *
 * See https://burtleburtle.net/bob/rand/smallprng.html for more details. Implementation details
 * for Jsf8 and Jsf16 can be found at
 * https://www.pcg-random.org/posts/bob-jenkins-small-prng-passes-practrand.html
 */

#pragma once

#include "mtl/common.hpp"
#include "mtl/utility/bits.hpp"

namespace mtl::random {

namespace internal {

  template <class ResultType, u8 P, u8 Q, u8 R>
  class jsf {
    static_assert(std::is_unsigned_v<ResultType>,
                  "The JSF random engine must return unsigned integral types.");

  public:
    using seed_type = ResultType;
    using result_type = ResultType;

    jsf(seed_type s) noexcept { seed(s); }

    auto seed(seed_type s) noexcept -> void {
      a_ = static_cast<result_type>(0xF1EA5EED);
      b_ = c_ = d_ = s;
      discard(20);
    }

    auto next() noexcept -> result_type {
      using namespace mtl::utility;

      u32 e_;
      e_ = a_ - rotl(b_, P);
      a_ = b_ ^ rotl(c_, Q);
      if constexpr (R == 0) {
        b_ = c_ + d_;
      } else {
        b_ = c_ + rotl(d_, R);
      }
      c_ = d_ + e_;
      d_ = e_ + a_;
      return d_;
    }

    auto operator()() noexcept -> result_type { return next(); }

    auto discard(usize n) noexcept -> void {
      while (n != 0) {
        next();
        --n;
      }
    }

    static constexpr auto min() -> result_type { return std::numeric_limits<result_type>::min(); }

    static constexpr auto max() -> result_type { return std::numeric_limits<result_type>::max(); }

  private:
    result_type a_, b_, c_, d_;
  };

}  // namespace internal

using jsf8 = internal::jsf<u8, 1, 4, 0>;
using jsf16 = internal::jsf<u16, 13, 8, 0>;
using jsf32 = internal::jsf<u32, 27, 17, 0>;
using jsf64 = internal::jsf<u64, 7, 13, 37>;

}  // namespace mtl::random