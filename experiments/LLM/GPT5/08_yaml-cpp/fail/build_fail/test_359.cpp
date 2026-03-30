// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_to_odd_normal_interval_test_359.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using Policy =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd_t;

// A minimal "SignedSignificandBits" test double that satisfies the interface
// required by Policy::normal_interval(...).
struct SignedSignificandBitsStub {
  bool even_bits = false;

  constexpr bool has_even_significand_bits() const noexcept { return even_bits; }
};

}  // namespace

TEST(NearestToOddNormalIntervalTest_359, ReturnsExpectedBoundaryWhenEvenBits_359) {
  const SignedSignificandBitsStub s{true};

  const auto interval = Policy::normal_interval(s);

  // Compare against a value constructed only via the public type.
  // This assumes interval_type::symmetric_boundary is constructible from a bool,
  // as implied by the provided interface/implementation snippet.
  using ReturnT = decltype(interval);
  const ReturnT expected{!s.has_even_significand_bits()};

  EXPECT_EQ(interval, expected);
}

TEST(NearestToOddNormalIntervalTest_359, ReturnsExpectedBoundaryWhenOddBits_359) {
  const SignedSignificandBitsStub s{false};

  const auto interval = Policy::normal_interval(s);

  using ReturnT = decltype(interval);
  const ReturnT expected{!s.has_even_significand_bits()};

  EXPECT_EQ(interval, expected);
}

TEST(NearestToOddNormalIntervalTest_359, IsConstexprAndNoexcept_359) {
  constexpr SignedSignificandBitsStub s1{true};
  constexpr SignedSignificandBitsStub s2{false};

  static_assert(noexcept(Policy::normal_interval(s1)),
                "normal_interval(...) should be noexcept");
  static_assert(noexcept(Policy::normal_interval(s2)),
                "normal_interval(...) should be noexcept");

  // Constexpr evaluation (compile-time)
  constexpr auto r1 = Policy::normal_interval(s1);
  constexpr auto r2 = Policy::normal_interval(s2);

  using ReturnT = decltype(r1);
  static_assert(r1 == ReturnT{!s1.has_even_significand_bits()},
                "constexpr result mismatch for even_bits=true");
  static_assert(r2 == ReturnT{!s2.has_even_significand_bits()},
                "constexpr result mismatch for even_bits=false");
}