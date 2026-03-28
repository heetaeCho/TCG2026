#include <gtest/gtest.h>
#include <cstdint>
#include <cstddef>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

// Define test Info templates for different tiers
template <std::size_t Tier>
struct TestInfo;

// Tier 0: supports range [-100, 100]
template <>
struct TestInfo<0> {
    static constexpr std::int_least32_t min_exponent = -100;
    static constexpr std::int_least32_t max_exponent = 100;
};

// Tier 1: supports range [-50, 50]
template <>
struct TestInfo<1> {
    static constexpr std::int_least32_t min_exponent = -50;
    static constexpr std::int_least32_t max_exponent = 50;
};

// Tier 2: supports range [0, 0] (single point)
template <>
struct TestInfo<2> {
    static constexpr std::int_least32_t min_exponent = 0;
    static constexpr std::int_least32_t max_exponent = 0;
};

// Tier 3: supports range [-1000, 1000] (wide range)
template <>
struct TestInfo<3> {
    static constexpr std::int_least32_t min_exponent = -1000;
    static constexpr std::int_least32_t max_exponent = 1000;
};

using namespace YAML::jkj::dragonbox::detail::log;

// Test fixture
class IsInRangeTest_316 : public ::testing::Test {};

// Normal operation: range exactly matches supported range
TEST_F(IsInRangeTest_316, ExactMatch_316) {
    constexpr bool result = is_in_range<TestInfo, -100, 100, 0>(0);
    EXPECT_TRUE(result);
}

// Normal operation: range is strictly within supported range
TEST_F(IsInRangeTest_316, StrictlyWithinRange_316) {
    constexpr bool result = is_in_range<TestInfo, -50, 50, 0>(0);
    EXPECT_TRUE(result);
}

// Normal operation: range is within tier 1 supported range
TEST_F(IsInRangeTest_316, WithinTier1Range_316) {
    constexpr bool result = is_in_range<TestInfo, -30, 30, 1>(0);
    EXPECT_TRUE(result);
}

// Boundary: min_exponent equals supported min_exponent
TEST_F(IsInRangeTest_316, MinExponentAtBoundary_316) {
    constexpr bool result = is_in_range<TestInfo, -100, 50, 0>(0);
    EXPECT_TRUE(result);
}

// Boundary: max_exponent equals supported max_exponent
TEST_F(IsInRangeTest_316, MaxExponentAtBoundary_316) {
    constexpr bool result = is_in_range<TestInfo, -50, 100, 0>(0);
    EXPECT_TRUE(result);
}

// Out of range: min_exponent below supported min
TEST_F(IsInRangeTest_316, MinExponentBelowSupported_316) {
    constexpr bool result = is_in_range<TestInfo, -101, 50, 0>(0);
    EXPECT_FALSE(result);
}

// Out of range: max_exponent above supported max
TEST_F(IsInRangeTest_316, MaxExponentAboveSupported_316) {
    constexpr bool result = is_in_range<TestInfo, -50, 101, 0>(0);
    EXPECT_FALSE(result);
}

// Out of range: both min and max outside supported range
TEST_F(IsInRangeTest_316, BothOutsideRange_316) {
    constexpr bool result = is_in_range<TestInfo, -200, 200, 0>(0);
    EXPECT_FALSE(result);
}

// Single point range: zero within tier 2
TEST_F(IsInRangeTest_316, SinglePointInRange_316) {
    constexpr bool result = is_in_range<TestInfo, 0, 0, 2>(0);
    EXPECT_TRUE(result);
}

// Single point range: nonzero outside tier 2
TEST_F(IsInRangeTest_316, SinglePointOutOfRange_316) {
    constexpr bool result = is_in_range<TestInfo, 1, 1, 2>(0);
    EXPECT_FALSE(result);
}

// Negative single point outside tier 2
TEST_F(IsInRangeTest_316, NegativeSinglePointOutOfRange_316) {
    constexpr bool result = is_in_range<TestInfo, -1, -1, 2>(0);
    EXPECT_FALSE(result);
}

// Wide supported range: large query within range
TEST_F(IsInRangeTest_316, WideRangeWithinSupported_316) {
    constexpr bool result = is_in_range<TestInfo, -999, 999, 3>(0);
    EXPECT_TRUE(result);
}

// Wide supported range: exact boundary
TEST_F(IsInRangeTest_316, WideRangeExactBoundary_316) {
    constexpr bool result = is_in_range<TestInfo, -1000, 1000, 3>(0);
    EXPECT_TRUE(result);
}

// Wide supported range: just outside
TEST_F(IsInRangeTest_316, WideRangeJustOutside_316) {
    constexpr bool result = is_in_range<TestInfo, -1001, 1000, 3>(0);
    EXPECT_FALSE(result);
}

// Tier 1: range exceeds supported max
TEST_F(IsInRangeTest_316, Tier1ExceedsMax_316) {
    constexpr bool result = is_in_range<TestInfo, -50, 51, 1>(0);
    EXPECT_FALSE(result);
}

// Tier 1: range exact match
TEST_F(IsInRangeTest_316, Tier1ExactMatch_316) {
    constexpr bool result = is_in_range<TestInfo, -50, 50, 1>(0);
    EXPECT_TRUE(result);
}

// Verify constexpr evaluation at compile time
TEST_F(IsInRangeTest_316, ConstexprEvaluation_316) {
    static_assert(is_in_range<TestInfo, -100, 100, 0>(0) == true, "Should be in range");
    static_assert(is_in_range<TestInfo, -101, 100, 0>(0) == false, "Should not be in range");
    static_assert(is_in_range<TestInfo, -100, 101, 0>(0) == false, "Should not be in range");
    SUCCEED();
}

// Test with min_exponent equal to max_exponent at supported boundary
TEST_F(IsInRangeTest_316, MinEqualsMaxAtSupportedMin_316) {
    constexpr bool result = is_in_range<TestInfo, -100, -100, 0>(0);
    EXPECT_TRUE(result);
}

TEST_F(IsInRangeTest_316, MinEqualsMaxAtSupportedMax_316) {
    constexpr bool result = is_in_range<TestInfo, 100, 100, 0>(0);
    EXPECT_TRUE(result);
}

} // namespace
