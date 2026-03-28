// File: ./TestProjects/yaml-cpp/test/dragonbox_toward_zero_rounding_test_389.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "contrib/dragonbox.h"

namespace {

using TowardZeroPolicy =
    YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::toward_zero;

TEST(TowardZeroRoundingPolicyTest_389, PreferRoundDownAlwaysTrueForUint32_389) {
  EXPECT_TRUE(TowardZeroPolicy::prefer_round_down<std::uint32_t>(0u));
  EXPECT_TRUE(TowardZeroPolicy::prefer_round_down<std::uint32_t>(1u));
  EXPECT_TRUE(TowardZeroPolicy::prefer_round_down<std::uint32_t>(
      std::numeric_limits<std::uint32_t>::max()));
}

TEST(TowardZeroRoundingPolicyTest_389, PreferRoundDownAlwaysTrueForUint64_389) {
  EXPECT_TRUE(TowardZeroPolicy::prefer_round_down<std::uint64_t>(0ull));
  EXPECT_TRUE(TowardZeroPolicy::prefer_round_down<std::uint64_t>(42ull));
  EXPECT_TRUE(TowardZeroPolicy::prefer_round_down<std::uint64_t>(
      std::numeric_limits<std::uint64_t>::max()));
}

TEST(TowardZeroRoundingPolicyTest_389, PreferRoundDownIsNoexcept_389) {
  static_assert(noexcept(TowardZeroPolicy::prefer_round_down<std::uint32_t>(0u)),
                "prefer_round_down(uint32_t) must be noexcept");
  static_assert(
      noexcept(TowardZeroPolicy::prefer_round_down<std::uint64_t>(0ull)),
      "prefer_round_down(uint64_t) must be noexcept");

  // Also verify at runtime (not required, but makes the intent explicit).
  EXPECT_TRUE(noexcept(TowardZeroPolicy::prefer_round_down<std::uint32_t>(0u)));
  EXPECT_TRUE(noexcept(TowardZeroPolicy::prefer_round_down<std::uint64_t>(0ull)));
}

TEST(TowardZeroRoundingPolicyTest_389, PreferRoundDownIsUsableInConstantEvaluation_389) {
  constexpr bool v0 = TowardZeroPolicy::prefer_round_down<std::uint32_t>(0u);
  constexpr bool v1 = TowardZeroPolicy::prefer_round_down<std::uint64_t>(123ull);

  static_assert(v0, "prefer_round_down must be constexpr-usable and true");
  static_assert(v1, "prefer_round_down must be constexpr-usable and true");

  EXPECT_TRUE(v0);
  EXPECT_TRUE(v1);
}

}  // namespace