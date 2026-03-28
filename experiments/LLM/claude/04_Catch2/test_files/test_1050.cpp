#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cstdint>

// Include necessary Catch2 headers
#include "catch2/matchers/catch_matchers_floating_point.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;
using Catch::Matchers::Detail::FloatingPointKind;

// ============================================================================
// Construction Tests
// ============================================================================

TEST(WithinUlpsMatcherConstructionTest_1050, ConstructWithDoubleTypeAndSmallUlps_1050) {
    // Normal construction with Double type and small ULP value
    EXPECT_NO_THROW(WithinUlpsMatcher(1.0, 5, FloatingPointKind::Double));
}

TEST(WithinUlpsMatcherConstructionTest_1050, ConstructWithDoubleTypeAndZeroUlps_1050) {
    // Boundary: zero ULPs with Double type
    EXPECT_NO_THROW(WithinUlpsMatcher(1.0, 0, FloatingPointKind::Double));
}

TEST(WithinUlpsMatcherConstructionTest_1050, ConstructWithDoubleTypeAndLargeUlps_1050) {
    // Double type should allow very large ULP values (beyond uint32_t max)
    uint64_t largeUlps = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) + 1;
    EXPECT_NO_THROW(WithinUlpsMatcher(1.0, largeUlps, FloatingPointKind::Double));
}

TEST(WithinUlpsMatcherConstructionTest_1050, ConstructWithFloatTypeAndSmallUlps_1050) {
    // Normal construction with Float type and small ULP value
    EXPECT_NO_THROW(WithinUlpsMatcher(1.0f, 5, FloatingPointKind::Float));
}

TEST(WithinUlpsMatcherConstructionTest_1050, ConstructWithFloatTypeAndZeroUlps_1050) {
    // Boundary: zero ULPs with Float type
    EXPECT_NO_THROW(WithinUlpsMatcher(1.0f, 0, FloatingPointKind::Float));
}

TEST(WithinUlpsMatcherConstructionTest_1050, ConstructWithFloatTypeAndMaxUint32MinusOneUlps_1050) {
    // Boundary: Float type with ULP just below uint32_t max
    uint64_t ulps = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) - 1;
    EXPECT_NO_THROW(WithinUlpsMatcher(1.0f, ulps, FloatingPointKind::Float));
}

TEST(WithinUlpsMatcherConstructionTest_1050, ConstructWithFloatTypeAndTooLargeUlpsThrows_1050) {
    // Error case: Float type with ULP >= uint32_t max should throw
    uint64_t tooLargeUlps = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max());
    EXPECT_ANY_THROW(WithinUlpsMatcher(1.0f, tooLargeUlps, FloatingPointKind::Float));
}

TEST(WithinUlpsMatcherConstructionTest_1050, ConstructWithFloatTypeAndWayTooLargeUlpsThrows_1050) {
    // Error case: Float type with ULP well beyond uint32_t max
    uint64_t wayTooLargeUlps = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) + 100;
    EXPECT_ANY_THROW(WithinUlpsMatcher(1.0f, wayTooLargeUlps, FloatingPointKind::Float));
}

// ============================================================================
// Match Tests - Double Type
// ============================================================================

TEST(WithinUlpsMatcherMatchTest_1050, ExactMatchDouble_1050) {
    // Exact same value should match with 0 ULPs
    WithinUlpsMatcher matcher(1.0, 0, FloatingPointKind::Double);
    double value = 1.0;
    EXPECT_TRUE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, ExactMatchDoubleWithPositiveUlps_1050) {
    // Exact same value should match with any ULP tolerance
    WithinUlpsMatcher matcher(1.0, 10, FloatingPointKind::Double);
    double value = 1.0;
    EXPECT_TRUE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, ZeroMatchesZeroDouble_1050) {
    // Zero should match zero
    WithinUlpsMatcher matcher(0.0, 0, FloatingPointKind::Double);
    double value = 0.0;
    EXPECT_TRUE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, NegativeZeroMatchesPositiveZeroDouble_1050) {
    // -0.0 and 0.0 should be close enough with some ULP tolerance
    WithinUlpsMatcher matcher(0.0, 1, FloatingPointKind::Double);
    double value = -0.0;
    EXPECT_TRUE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, OneUlpApartDoubleWithOneUlpTolerance_1050) {
    // Values that are exactly 1 ULP apart should match with 1 ULP tolerance
    double target = 1.0;
    double nextVal = std::nextafter(target, std::numeric_limits<double>::infinity());
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(nextVal));
}

TEST(WithinUlpsMatcherMatchTest_1050, OneUlpApartDoubleWithZeroUlpTolerance_1050) {
    // Values that are exactly 1 ULP apart should NOT match with 0 ULP tolerance
    double target = 1.0;
    double nextVal = std::nextafter(target, std::numeric_limits<double>::infinity());
    WithinUlpsMatcher matcher(target, 0, FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(nextVal));
}

TEST(WithinUlpsMatcherMatchTest_1050, TwoUlpsApartDoubleWithOneUlpTolerance_1050) {
    // Values 2 ULPs apart should NOT match with 1 ULP tolerance
    double target = 1.0;
    double nextVal = std::nextafter(target, std::numeric_limits<double>::infinity());
    nextVal = std::nextafter(nextVal, std::numeric_limits<double>::infinity());
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(nextVal));
}

TEST(WithinUlpsMatcherMatchTest_1050, TwoUlpsApartDoubleWithTwoUlpTolerance_1050) {
    // Values 2 ULPs apart should match with 2 ULP tolerance
    double target = 1.0;
    double nextVal = std::nextafter(target, std::numeric_limits<double>::infinity());
    nextVal = std::nextafter(nextVal, std::numeric_limits<double>::infinity());
    WithinUlpsMatcher matcher(target, 2, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(nextVal));
}

TEST(WithinUlpsMatcherMatchTest_1050, LargelyDifferentValuesDouble_1050) {
    // Very different values should not match even with moderate ULP tolerance
    WithinUlpsMatcher matcher(1.0, 10, FloatingPointKind::Double);
    double value = 2.0;
    EXPECT_FALSE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, NegativeValuesMatchDouble_1050) {
    // Negative exact match
    WithinUlpsMatcher matcher(-5.0, 0, FloatingPointKind::Double);
    double value = -5.0;
    EXPECT_TRUE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, NegativeOneUlpApartDouble_1050) {
    // Negative values 1 ULP apart
    double target = -1.0;
    double nextVal = std::nextafter(target, -std::numeric_limits<double>::infinity());
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(nextVal));
}

TEST(WithinUlpsMatcherMatchTest_1050, NaNDoesNotMatchDouble_1050) {
    // NaN should not match any value
    WithinUlpsMatcher matcher(1.0, 1000000, FloatingPointKind::Double);
    double value = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, TargetNaNDoesNotMatchDouble_1050) {
    // If target is NaN, nothing should match
    WithinUlpsMatcher matcher(std::numeric_limits<double>::quiet_NaN(), 1000000, FloatingPointKind::Double);
    double value = 1.0;
    EXPECT_FALSE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, InfinityMatchesInfinityDouble_1050) {
    // Infinity should match itself
    double inf = std::numeric_limits<double>::infinity();
    WithinUlpsMatcher matcher(inf, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(inf));
}

// ============================================================================
// Match Tests - Float Type (passed as double)
// ============================================================================

TEST(WithinUlpsMatcherMatchTest_1050, ExactMatchFloat_1050) {
    float target = 1.0f;
    WithinUlpsMatcher matcher(static_cast<double>(target), 0, FloatingPointKind::Float);
    double value = static_cast<double>(target);
    EXPECT_TRUE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, OneUlpApartFloat_1050) {
    float target = 1.0f;
    float nextVal = std::nextafter(target, std::numeric_limits<float>::infinity());
    WithinUlpsMatcher matcher(static_cast<double>(target), 1, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(static_cast<double>(nextVal)));
}

TEST(WithinUlpsMatcherMatchTest_1050, OneUlpApartFloatZeroTolerance_1050) {
    float target = 1.0f;
    float nextVal = std::nextafter(target, std::numeric_limits<float>::infinity());
    WithinUlpsMatcher matcher(static_cast<double>(target), 0, FloatingPointKind::Float);
    EXPECT_FALSE(matcher.match(static_cast<double>(nextVal)));
}

// ============================================================================
// Describe Tests
// ============================================================================

TEST(WithinUlpsMatcherDescribeTest_1050, DescribeReturnsNonEmptyString_1050) {
    WithinUlpsMatcher matcher(1.0, 5, FloatingPointKind::Double);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST(WithinUlpsMatcherDescribeTest_1050, DescribeContainsUlpInfo_1050) {
    WithinUlpsMatcher matcher(1.0, 5, FloatingPointKind::Double);
    std::string description = matcher.describe();
    // The description should mention ULP in some form
    EXPECT_NE(description.find("ULP"), std::string::npos);
}

TEST(WithinUlpsMatcherDescribeTest_1050, DescribeForFloatType_1050) {
    WithinUlpsMatcher matcher(1.0f, 3, FloatingPointKind::Float);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// ============================================================================
// Symmetry Tests
// ============================================================================

TEST(WithinUlpsMatcherSymmetryTest_1050, MatchIsSymmetricDouble_1050) {
    double a = 1.0;
    double b = std::nextafter(a, std::numeric_limits<double>::infinity());
    
    WithinUlpsMatcher matcherA(a, 1, FloatingPointKind::Double);
    WithinUlpsMatcher matcherB(b, 1, FloatingPointKind::Double);
    
    EXPECT_EQ(matcherA.match(b), matcherB.match(a));
}

// ============================================================================
// Boundary on ULP tolerance for float
// ============================================================================

TEST(WithinUlpsMatcherConstructionTest_1050, FloatWithUlpsJustBelowUint32Max_1050) {
    uint64_t ulps = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) - 1;
    EXPECT_NO_THROW(WithinUlpsMatcher(1.0f, ulps, FloatingPointKind::Float));
}

TEST(WithinUlpsMatcherConstructionTest_1050, FloatWithUlpsExactlyUint32Max_1050) {
    // uint32_t max should trigger the enforcement for float
    uint64_t ulps = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max());
    EXPECT_ANY_THROW(WithinUlpsMatcher(1.0f, ulps, FloatingPointKind::Float));
}

TEST(WithinUlpsMatcherConstructionTest_1050, DoubleWithUlpsExactlyUint32MaxAllowed_1050) {
    // Double type should allow ULP values at uint32_t max
    uint64_t ulps = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max());
    EXPECT_NO_THROW(WithinUlpsMatcher(1.0, ulps, FloatingPointKind::Double));
}

TEST(WithinUlpsMatcherConstructionTest_1050, DoubleWithUlpsMaxUint64_1050) {
    // Double type with maximum uint64_t ULP should be constructible
    uint64_t ulps = std::numeric_limits<uint64_t>::max();
    EXPECT_NO_THROW(WithinUlpsMatcher(1.0, ulps, FloatingPointKind::Double));
}

// ============================================================================
// Special floating point values
// ============================================================================

TEST(WithinUlpsMatcherMatchTest_1050, PositiveInfinityDoesNotMatchFiniteDouble_1050) {
    WithinUlpsMatcher matcher(1.0, 1000000, FloatingPointKind::Double);
    double value = std::numeric_limits<double>::infinity();
    EXPECT_FALSE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, NegativeInfinityDoesNotMatchFiniteDouble_1050) {
    WithinUlpsMatcher matcher(1.0, 1000000, FloatingPointKind::Double);
    double value = -std::numeric_limits<double>::infinity();
    EXPECT_FALSE(matcher.match(value));
}

TEST(WithinUlpsMatcherMatchTest_1050, NegativeInfinityMatchesItself_1050) {
    double negInf = -std::numeric_limits<double>::infinity();
    WithinUlpsMatcher matcher(negInf, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(negInf));
}

TEST(WithinUlpsMatcherMatchTest_1050, PositiveAndNegativeInfinityDoNotMatch_1050) {
    double posInf = std::numeric_limits<double>::infinity();
    double negInf = -std::numeric_limits<double>::infinity();
    WithinUlpsMatcher matcher(posInf, std::numeric_limits<uint64_t>::max(), FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(negInf));
}

TEST(WithinUlpsMatcherMatchTest_1050, SmallestDenormalizedDouble_1050) {
    double target = std::numeric_limits<double>::denorm_min();
    WithinUlpsMatcher matcher(target, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(target));
}

TEST(WithinUlpsMatcherMatchTest_1050, MaxDoubleExactMatch_1050) {
    double target = std::numeric_limits<double>::max();
    WithinUlpsMatcher matcher(target, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(target));
}
