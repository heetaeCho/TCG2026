// TEST_ID: 313
#include <cstdint>
#include <type_traits>

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

// Alias the function under test to keep test code readable.
template <int K, class Int>
constexpr Int ComputePower(Int a) noexcept {
  return YAML::jkj::dragonbox::detail::compute_power<K, Int>(a);
}

}  // namespace

TEST(ComputePowerTest_313, IsNoexcept_313) {
  static_assert(noexcept(ComputePower<0, int>(1)), "compute_power should be noexcept");
  static_assert(noexcept(ComputePower<3, std::uint64_t>(2u)),
                "compute_power should be noexcept");
}

TEST(ComputePowerTest_313, KZeroReturnsOne_Int_313) {
  constexpr int v = ComputePower<0, int>(123);
  EXPECT_EQ(v, 1);
}

TEST(ComputePowerTest_313, KZeroReturnsOne_UInt64_313) {
  constexpr std::uint64_t v = ComputePower<0, std::uint64_t>(123u);
  EXPECT_EQ(v, 1u);
}

TEST(ComputePowerTest_313, KOneReturnsSameValue_Int_313) {
  constexpr int a = 7;
  constexpr int v = ComputePower<1, int>(a);
  EXPECT_EQ(v, a);
}

TEST(ComputePowerTest_313, KOneReturnsSameValue_UInt64_313) {
  constexpr std::uint64_t a = 7u;
  constexpr std::uint64_t v = ComputePower<1, std::uint64_t>(a);
  EXPECT_EQ(v, a);
}

TEST(ComputePowerTest_313, SmallPowersMatchExpected_Int_313) {
  // Keep values small to avoid signed overflow / UB.
  EXPECT_EQ((ComputePower<2, int>(3)), 9);
  EXPECT_EQ((ComputePower<3, int>(2)), 8);
  EXPECT_EQ((ComputePower<4, int>(2)), 16);
  EXPECT_EQ((ComputePower<5, int>(1)), 1);
}

TEST(ComputePowerTest_313, SmallPowersMatchExpected_UInt64_313) {
  EXPECT_EQ((ComputePower<2, std::uint64_t>(3u)), 9u);
  EXPECT_EQ((ComputePower<3, std::uint64_t>(2u)), 8u);
  EXPECT_EQ((ComputePower<10, std::uint64_t>(2u)), 1024u);
}

TEST(ComputePowerTest_313, ZeroBaseBehavior_313) {
  // Boundary behavior for base == 0.
  EXPECT_EQ((ComputePower<0, int>(0)), 1);
  EXPECT_EQ((ComputePower<1, int>(0)), 0);
  EXPECT_EQ((ComputePower<7, int>(0)), 0);

  EXPECT_EQ((ComputePower<0, std::uint64_t>(0u)), 1u);
  EXPECT_EQ((ComputePower<1, std::uint64_t>(0u)), 0u);
  EXPECT_EQ((ComputePower<7, std::uint64_t>(0u)), 0u);
}

TEST(ComputePowerTest_313, NegativeBaseWithOddEvenExponent_Int_313) {
  // Uses small magnitudes to avoid overflow.
  EXPECT_EQ((ComputePower<2, int>(-3)), 9);    // even exponent => non-negative
  EXPECT_EQ((ComputePower<3, int>(-3)), -27);  // odd exponent => negative
}

TEST(ComputePowerTest_313, CanBeEvaluatedAtCompileTime_313) {
  // Verification of constexpr usability (observable via compilation).
  constexpr int v1 = ComputePower<6, int>(2);
  constexpr std::uint64_t v2 = ComputePower<6, std::uint64_t>(2u);

  static_assert(v1 == 64, "2^6 should be 64");
  static_assert(v2 == 64u, "2^6 should be 64");

  EXPECT_EQ(v1, 64);
  EXPECT_EQ(v2, 64u);
}

TEST(ComputePowerTest_313, ConsistentAcrossCalls_313) {
  // Same inputs should produce the same output (basic determinism).
  const int a = 5;
  const auto x1 = ComputePower<4, int>(a);
  const auto x2 = ComputePower<4, int>(a);
  EXPECT_EQ(x1, x2);

  const std::uint64_t b = 5u;
  const auto y1 = ComputePower<4, std::uint64_t>(b);
  const auto y2 = ComputePower<4, std::uint64_t>(b);
  EXPECT_EQ(y1, y2);
}