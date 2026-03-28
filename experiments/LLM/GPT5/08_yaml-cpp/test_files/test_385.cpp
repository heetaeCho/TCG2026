// TEST_ID: 385
// File: dragonbox_policy_binary_to_decimal_rounding_do_not_care_test.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

// Try common include paths used by yaml-cpp builds.
#if __has_include("contrib/dragonbox.h")
#include "contrib/dragonbox.h"
#elif __has_include("yaml-cpp/contrib/dragonbox.h")
#include "yaml-cpp/contrib/dragonbox.h"
#elif __has_include("src/contrib/dragonbox.h")
#include "src/contrib/dragonbox.h"
#else
// If this fails, adjust the include path in your build/test target.
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"
#endif

namespace {

using Policy = YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::do_not_care_t;

TEST(DragonboxDoNotCarePolicyTest_385, PreferRoundDownIsNoexcept_385) {
  // Verify the function is callable and noexcept for a representative type.
  EXPECT_TRUE(noexcept(Policy::prefer_round_down(std::uint32_t{0})));
}

TEST(DragonboxDoNotCarePolicyTest_385, PreferRoundDownReturnTypeIsBool_385) {
  static_assert(std::is_same_v<decltype(Policy::prefer_round_down(std::uint32_t{0})), bool>,
                "prefer_round_down should return bool");
  SUCCEED();
}

TEST(DragonboxDoNotCarePolicyTest_385, PreferRoundDownIsConstexprEvaluatable_385) {
  // Verify compile-time evaluation works (constexpr + deterministic value).
  static_assert(Policy::prefer_round_down(std::uint32_t{0}) == false, "Expected false");
  static_assert(Policy::prefer_round_down(std::uint64_t{123}) == false, "Expected false");
  SUCCEED();
}

TEST(DragonboxDoNotCarePolicyTest_385, PreferRoundDownReturnsFalseForZero_385) {
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{0}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint64_t{0}));
}

TEST(DragonboxDoNotCarePolicyTest_385, PreferRoundDownReturnsFalseForTypicalValues_385) {
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{1}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{42}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint64_t{123456789ULL}));
}

TEST(DragonboxDoNotCarePolicyTest_385, PreferRoundDownReturnsFalseForMaxValues_385) {
  EXPECT_FALSE(Policy::prefer_round_down(std::numeric_limits<std::uint8_t>::max()));
  EXPECT_FALSE(Policy::prefer_round_down(std::numeric_limits<std::uint32_t>::max()));
  EXPECT_FALSE(Policy::prefer_round_down(std::numeric_limits<std::uint64_t>::max()));
}

TEST(DragonboxDoNotCarePolicyTest_385, PreferRoundDownAcceptsDifferentUnsignedCarrierTypes_385) {
  // Boundary/compat: ensure template accepts multiple unsigned integer types.
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<unsigned short>(7)));
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<unsigned int>(8)));
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<unsigned long>(9)));
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<unsigned long long>(10)));
}

}  // namespace