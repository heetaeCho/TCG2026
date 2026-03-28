// File: ./TestProjects/yaml-cpp/test/dragonbox_to_even_policy_test_386.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Policy = YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::to_even_t;

class ToEvenRoundingPolicyTest_386 : public ::testing::Test {};

TEST_F(ToEvenRoundingPolicyTest_386, PreferRoundDownIsNoexcept_386) {
  static_assert(noexcept(Policy::prefer_round_down(std::uint32_t{0})),
                "prefer_round_down must be noexcept for uint32_t");
  static_assert(noexcept(Policy::prefer_round_down(std::uint64_t{0})),
                "prefer_round_down must be noexcept for uint64_t");
}

TEST_F(ToEvenRoundingPolicyTest_386, PreferRoundDownIsConstexpr_386) {
  // Compile-time evaluation checks (constexpr).
  constexpr bool v0 = Policy::prefer_round_down(std::uint32_t{0});
  constexpr bool v1 = Policy::prefer_round_down(std::uint32_t{1});
  constexpr bool v2 = Policy::prefer_round_down(std::uint32_t{2});

  static_assert(v0 == false, "Expected false for 0");
  static_assert(v1 == true, "Expected true for 1");
  static_assert(v2 == false, "Expected false for 2");

  // Also sanity-check at runtime.
  EXPECT_FALSE(v0);
  EXPECT_TRUE(v1);
  EXPECT_FALSE(v2);
}

TEST_F(ToEvenRoundingPolicyTest_386, PreferRoundDownReturnsTrueForOddValues_386) {
  EXPECT_TRUE(Policy::prefer_round_down(std::uint32_t{1}));
  EXPECT_TRUE(Policy::prefer_round_down(std::uint32_t{3}));
  EXPECT_TRUE(Policy::prefer_round_down(std::uint32_t{5}));

  EXPECT_TRUE(Policy::prefer_round_down(std::uint64_t{1}));
  EXPECT_TRUE(Policy::prefer_round_down(std::uint64_t{3}));
  EXPECT_TRUE(Policy::prefer_round_down(std::uint64_t{999999999999999999ULL}));
}

TEST_F(ToEvenRoundingPolicyTest_386, PreferRoundDownReturnsFalseForEvenValues_386) {
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{0}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{2}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{4}));

  EXPECT_FALSE(Policy::prefer_round_down(std::uint64_t{0}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint64_t{2}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint64_t{1000000000000000000ULL}));
}

TEST_F(ToEvenRoundingPolicyTest_386, PreferRoundDownHandlesBoundaryValues_386) {
  // Boundary / extreme values for unsigned types.
  const std::uint32_t u32_max = std::numeric_limits<std::uint32_t>::max(); // odd
  const std::uint64_t u64_max = std::numeric_limits<std::uint64_t>::max(); // odd

  EXPECT_TRUE(Policy::prefer_round_down(u32_max));
  EXPECT_TRUE(Policy::prefer_round_down(u64_max));

  // One less than max is even for these unsigned max values.
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<std::uint32_t>(u32_max - 1)));
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<std::uint64_t>(u64_max - 1)));
}

TEST_F(ToEvenRoundingPolicyTest_386, PreferRoundDownWorksWithDifferentUnsignedWidths_386) {
  // Ensure the template works across several common unsigned carrier widths.
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<std::uint8_t>(0)));
  EXPECT_TRUE(Policy::prefer_round_down(static_cast<std::uint8_t>(1)));
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<std::uint16_t>(2)));
  EXPECT_TRUE(Policy::prefer_round_down(static_cast<std::uint16_t>(7)));
}

TEST_F(ToEvenRoundingPolicyTest_386, PreferRoundDownWorksForSignedIntegralInputs_386) {
  // Although the template name suggests an unsigned "CarrierUInt", the public interface
  // is templated; verify behavior is observable for signed inputs too.
  EXPECT_FALSE(Policy::prefer_round_down(0));
  EXPECT_TRUE(Policy::prefer_round_down(1));
  EXPECT_FALSE(Policy::prefer_round_down(2));
  EXPECT_TRUE(Policy::prefer_round_down(3));

  // Negative odd/even (if used) should still behave consistently with parity.
  EXPECT_FALSE(Policy::prefer_round_down(-2));
  EXPECT_TRUE(Policy::prefer_round_down(-1));
}

}  // names