// File: ./TestProjects/yaml-cpp/test/dragonbox_to_odd_rounding_policy_test_387.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::to_odd_t;

// Compile-time checks (observable via the interface: constexpr + noexcept).
static_assert(to_odd_t::prefer_round_down(0u), "0 is even -> prefer_round_down should be true");
static_assert(!to_odd_t::prefer_round_down(1u), "1 is odd -> prefer_round_down should be false");
static_assert(noexcept(to_odd_t::prefer_round_down(0u)), "prefer_round_down must be noexcept");

TEST(ToOddRoundingPolicyTest_387, PreferRoundDownEvenReturnsTrue_387) {
  EXPECT_TRUE(to_odd_t::prefer_round_down(0u));
  EXPECT_TRUE(to_odd_t::prefer_round_down(2u));
  EXPECT_TRUE(to_odd_t::prefer_round_down(42u));
}

TEST(ToOddRoundingPolicyTest_387, PreferRoundDownOddReturnsFalse_387) {
  EXPECT_FALSE(to_odd_t::prefer_round_down(1u));
  EXPECT_FALSE(to_odd_t::prefer_round_down(3u));
  EXPECT_FALSE(to_odd_t::prefer_round_down(99u));
}

TEST(ToOddRoundingPolicyTest_387, WorksForDifferentUnsignedCarrierTypes_387) {
  EXPECT_TRUE(to_odd_t::prefer_round_down(static_cast<std::uint8_t>(10)));
  EXPECT_FALSE(to_odd_t::prefer_round_down(static_cast<std::uint8_t>(11)));

  EXPECT_TRUE(to_odd_t::prefer_round_down(static_cast<std::uint16_t>(65000)));
  EXPECT_FALSE(to_odd_t::prefer_round_down(static_cast<std::uint16_t>(65001)));

  EXPECT_TRUE(to_odd_t::prefer_round_down(static_cast<std::uint32_t>(0xFFFFFFFEu)));
  EXPECT_FALSE(to_odd_t::prefer_round_down(static_cast<std::uint32_t>(0xFFFFFFFFu)));

  EXPECT_TRUE(to_odd_t::prefer_round_down(static_cast<std::uint64_t>(18446744073709551614ull)));
  EXPECT_FALSE(to_odd_t::prefer_round_down(static_cast<std::uint64_t>(18446744073709551615ull)));
}

TEST(ToOddRoundingPolicyTest_387, BoundaryValuesForStandardUnsignedTypes_387) {
  // For unsigned max: true if even, false if odd.
  {
    constexpr unsigned umax = std::numeric_limits<unsigned>::max();
    if ((umax % 2u) == 0u) {
      EXPECT_TRUE(to_odd_t::prefer_round_down(umax));
    } else {
      EXPECT_FALSE(to_odd_t::prefer_round_down(umax));
    }
  }

  {
    constexpr std::uint64_t u64max = std::numeric_limits<std::uint64_t>::max();
    // For uint64_t, max is all 1s => odd.
    EXPECT_FALSE(to_odd_t::prefer_round_down(u64max));
    EXPECT_TRUE(to_odd_t::prefer_round_down(u64max - 1));
  }
}

TEST(ToOddRoundingPolicyTest_387, AcceptsSignedIntegralCarrierTypes_387) {
  // The template accepts any CarrierUInt; verify behavior is consistent for signed integers too.
  EXPECT_TRUE(to_odd_t::prefer_round_down(0));
  EXPECT_TRUE(to_odd_t::prefer_round_down(2));
  EXPECT_FALSE(to_odd_t::prefer_round_down(1));

  // Negative values: -2 is even, -1 is odd in terms of divisibility by 2.
  EXPECT_TRUE(to_odd_t::prefer_round_down(-2));
  EXPECT_FALSE(to_odd_t::prefer_round_down(-1));
}

}  // namespace