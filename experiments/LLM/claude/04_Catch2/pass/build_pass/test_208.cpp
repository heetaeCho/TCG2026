#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include Catch2 headers for the matchers
#include "catch2/matchers/catch_matchers_floating_point.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch::Matchers;

// Helper function to check if a matcher matches a given value
template<typename Matcher, typename T>
bool matches(const Matcher& matcher, T value) {
    return matcher.match(value);
}

// =====================================================
// Tests for WithinRel(float, float) -> WithinRelMatcher
// =====================================================

class WithinRelFloatTest_208 : public ::testing::Test {
protected:
};

// Test that WithinRel matches exact same value
TEST_F(WithinRelFloatTest_208, ExactMatch_208) {
    auto matcher = WithinRel(1.0f, 0.01f);
    EXPECT_TRUE(matcher.match(1.0f));
}

// Test that WithinRel matches value within relative tolerance
TEST_F(WithinRelFloatTest_208, WithinTolerance_208) {
    auto matcher = WithinRel(100.0f, 0.01f);
    // 1% of 100 = 1, so 100.5 should be within tolerance
    EXPECT_TRUE(matcher.match(100.5f));
}

// Test that WithinRel does not match value outside relative tolerance
TEST_F(WithinRelFloatTest_208, OutsideTolerance_208) {
    auto matcher = WithinRel(100.0f, 0.01f);
    // 1% of 100 = 1, so 102 should be outside tolerance
    EXPECT_FALSE(matcher.match(102.0f));
}

// Test WithinRel with zero target
TEST_F(WithinRelFloatTest_208, ZeroTarget_208) {
    auto matcher = WithinRel(0.0f, 0.01f);
    EXPECT_TRUE(matcher.match(0.0f));
}

// Test WithinRel with negative target
TEST_F(WithinRelFloatTest_208, NegativeTarget_208) {
    auto matcher = WithinRel(-100.0f, 0.01f);
    EXPECT_TRUE(matcher.match(-100.0f));
    EXPECT_TRUE(matcher.match(-100.5f));
}

// Test WithinRel boundary: value exactly at the edge of tolerance
TEST_F(WithinRelFloatTest_208, BoundaryTolerance_208) {
    auto matcher = WithinRel(100.0f, 0.1f);
    // 10% of 100 = 10
    // Value just inside
    EXPECT_TRUE(matcher.match(109.0f));
    // Value clearly outside
    EXPECT_FALSE(matcher.match(120.0f));
}

// Test WithinRel with very small epsilon
TEST_F(WithinRelFloatTest_208, VerySmallEpsilon_208) {
    auto matcher = WithinRel(1.0f, std::numeric_limits<float>::epsilon());
    EXPECT_TRUE(matcher.match(1.0f));
    EXPECT_FALSE(matcher.match(1.1f));
}

// Test WithinRel with large values
TEST_F(WithinRelFloatTest_208, LargeValues_208) {
    float target = 1e10f;
    auto matcher = WithinRel(target, 0.01f);
    EXPECT_TRUE(matcher.match(target));
    EXPECT_TRUE(matcher.match(target * 1.005f));
}

// Test WithinRel with very small values
TEST_F(WithinRelFloatTest_208, SmallValues_208) {
    float target = 1e-10f;
    auto matcher = WithinRel(target, 0.01f);
    EXPECT_TRUE(matcher.match(target));
}

// Test WithinRel: NaN should not match
TEST_F(WithinRelFloatTest_208, NaNDoesNotMatch_208) {
    auto matcher = WithinRel(1.0f, 0.01f);
    EXPECT_FALSE(matcher.match(std::numeric_limits<float>::quiet_NaN()));
}

// Test WithinRel: NaN target with NaN value
TEST_F(WithinRelFloatTest_208, NaNTargetNaNValue_208) {
    auto matcher = WithinRel(std::numeric_limits<float>::quiet_NaN(), 0.01f);
    // NaN != NaN typically, behavior depends on implementation
    // Just verify it doesn't crash
    matcher.match(std::numeric_limits<float>::quiet_NaN());
}

// Test WithinRel: infinity target
TEST_F(WithinRelFloatTest_208, InfinityTarget_208) {
    auto matcher = WithinRel(std::numeric_limits<float>::infinity(), 0.01f);
    EXPECT_TRUE(matcher.match(std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(matcher.match(1.0f));
}

// Test WithinRel: negative infinity
TEST_F(WithinRelFloatTest_208, NegativeInfinityTarget_208) {
    auto matcher = WithinRel(-std::numeric_limits<float>::infinity(), 0.01f);
    EXPECT_TRUE(matcher.match(-std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(matcher.match(-1.0f));
}

// Test WithinRel: describe method returns non-empty string
TEST_F(WithinRelFloatTest_208, DescribeReturnsNonEmpty_208) {
    auto matcher = WithinRel(1.0f, 0.01f);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test WithinRel with zero epsilon
TEST_F(WithinRelFloatTest_208, ZeroEpsilon_208) {
    auto matcher = WithinRel(1.0f, 0.0f);
    EXPECT_TRUE(matcher.match(1.0f));
    // With zero epsilon, only exact match (or very close due to ULP) should work
}

// Test symmetry: if a matches b within rel, then b should match a within rel
TEST_F(WithinRelFloatTest_208, SymmetryCheck_208) {
    float a = 100.0f;
    float b = 101.0f;
    float eps = 0.02f;
    auto matcherA = WithinRel(a, eps);
    auto matcherB = WithinRel(b, eps);
    // Both should have consistent behavior for relative matching
    bool aMatchesB = matcherA.match(b);
    bool bMatchesA = matcherB.match(a);
    // Note: relative matching is not always symmetric, but we test observable behavior
    // Just ensure they don't crash
    (void)aMatchesB;
    (void)bMatchesA;
}

// Test WithinRel: positive and negative zero
TEST_F(WithinRelFloatTest_208, PositiveAndNegativeZero_208) {
    auto matcher = WithinRel(0.0f, 0.01f);
    EXPECT_TRUE(matcher.match(-0.0f));
}

// Test WithinRel with default-like eps (using the two-arg version)
TEST_F(WithinRelFloatTest_208, ModerateEpsilon_208) {
    auto matcher = WithinRel(50.0f, 0.05f);
    // 5% of 50 = 2.5
    EXPECT_TRUE(matcher.match(51.0f));
    EXPECT_TRUE(matcher.match(49.0f));
    EXPECT_TRUE(matcher.match(52.0f));
    EXPECT_FALSE(matcher.match(60.0f));
    EXPECT_FALSE(matcher.match(40.0f));
}

// Test that the returned object is a WithinRelMatcher
TEST_F(WithinRelFloatTest_208, ReturnsCorrectType_208) {
    auto matcher = WithinRel(1.0f, 0.01f);
    // Verify it compiles and works as WithinRelMatcher
    WithinRelMatcher m = matcher;
    EXPECT_TRUE(m.match(1.0f));
}

// Test WithinRel with epsilon = 1.0 (100% tolerance)
TEST_F(WithinRelFloatTest_208, FullTolerance_208) {
    auto matcher = WithinRel(100.0f, 1.0f);
    // 100% relative tolerance should match a wide range
    EXPECT_TRUE(matcher.match(100.0f));
    EXPECT_TRUE(matcher.match(50.0f));
    EXPECT_TRUE(matcher.match(0.0f));
    EXPECT_TRUE(matcher.match(200.0f));
}

// Test WithinRel opposite signs
TEST_F(WithinRelFloatTest_208, OppositeSignsSmallEps_208) {
    auto matcher = WithinRel(1.0f, 0.01f);
    EXPECT_FALSE(matcher.match(-1.0f));
}
