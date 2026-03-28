#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <limits>

// Include the Catch2 amalgamated header
#include "catch_amalgamated.hpp"

// Helper to check if a matcher matches a given vector
template <typename T>
bool doesMatch(const Catch::Matchers::ApproxMatcher<T, std::allocator<T>, std::allocator<T>>& matcher,
               const std::vector<T>& v) {
    return matcher.match(v);
}

class ApproxMatcherTest_973 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that identical vectors match with default settings
TEST_F(ApproxMatcherTest_973, ExactMatchDefaultSettings_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.0, 2.0, 3.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test that vectors with small differences match within default epsilon
TEST_F(ApproxMatcherTest_973, SmallDifferencesWithinDefaultEpsilon_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    // Default epsilon is float epsilon * 100, so small relative differences should match
    double eps = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    std::vector<double> target = {1.0 + 1.0 * eps * 0.5, 2.0, 3.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test that vectors with large differences do not match with default settings
TEST_F(ApproxMatcherTest_973, LargeDifferencesDoNotMatchDefault_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.5, 2.5, 3.5};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_FALSE(matcher.match(target));
}

// Test that different sized vectors do not match
TEST_F(ApproxMatcherTest_973, DifferentSizedVectorsDoNotMatch_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.0, 2.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_FALSE(matcher.match(target));
}

// Test that empty vectors match each other
TEST_F(ApproxMatcherTest_973, EmptyVectorsMatch_973) {
    std::vector<double> comparator = {};
    std::vector<double> target = {};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test that empty comparator does not match non-empty target
TEST_F(ApproxMatcherTest_973, EmptyComparatorDoesNotMatchNonEmpty_973) {
    std::vector<double> comparator = {};
    std::vector<double> target = {1.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_FALSE(matcher.match(target));
}

// Test margin method allows larger absolute differences
TEST_F(ApproxMatcherTest_973, MarginAllowsLargerDifferences_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.4, 2.4, 3.4};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    matcher.margin(0.5);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test margin method - values outside margin do not match
TEST_F(ApproxMatcherTest_973, MarginDoesNotMatchOutsideRange_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.6, 2.0, 3.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    matcher.margin(0.5);
    
    EXPECT_FALSE(matcher.match(target));
}

// Test epsilon method adjusts relative tolerance
TEST_F(ApproxMatcherTest_973, EpsilonAdjustsRelativeTolerance_973) {
    std::vector<double> comparator = {100.0, 200.0};
    // 10% relative difference
    std::vector<double> target = {110.0, 220.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    // Default epsilon won't match 10% difference
    EXPECT_FALSE(matcher.match(target));
    
    // Create new matcher with larger epsilon
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher2(comparator);
    matcher2.epsilon(0.11); // 11% tolerance
    EXPECT_TRUE(matcher2.match(target));
}

// Test scale method
TEST_F(ApproxMatcherTest_973, ScaleAdjustsTolerance_973) {
    std::vector<double> comparator = {1.0, 2.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    matcher.scale(10.0);
    
    // With a larger scale, the absolute tolerance derived from epsilon should be larger
    // The formula for Approx is: margin OR epsilon*(scale + abs(value))
    // With scale=10, epsilon * (10 + 1) should be larger than epsilon * (0 + 1)
    double eps = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double tolerance_with_scale = eps * (10.0 + 1.0);
    std::vector<double> target = {1.0 + tolerance_with_scale * 0.9, 2.0};
    
    EXPECT_TRUE(matcher.match(target));
}

// Test chaining margin returns reference to self
TEST_F(ApproxMatcherTest_973, MarginReturnsReference_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    auto& ref = matcher.margin(0.5);
    
    // Verify the reference is the same object
    EXPECT_EQ(&ref, &matcher);
}

// Test chaining epsilon returns reference to self
TEST_F(ApproxMatcherTest_973, EpsilonReturnsReference_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    auto& ref = matcher.epsilon(0.01);
    
    EXPECT_EQ(&ref, &matcher);
}

// Test chaining scale returns reference to self
TEST_F(ApproxMatcherTest_973, ScaleReturnsReference_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    auto& ref = matcher.scale(1.0);
    
    EXPECT_EQ(&ref, &matcher);
}

// Test method chaining works (fluent interface)
TEST_F(ApproxMatcherTest_973, FluentInterfaceChaining_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.3, 2.3, 3.3};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    matcher.margin(0.5).epsilon(0.01).scale(1.0);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test describe returns a non-empty string
TEST_F(ApproxMatcherTest_973, DescribeReturnsNonEmptyString_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test with single element vectors
TEST_F(ApproxMatcherTest_973, SingleElementVectorsMatch_973) {
    std::vector<double> comparator = {42.0};
    std::vector<double> target = {42.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test with single element vectors that don't match
TEST_F(ApproxMatcherTest_973, SingleElementVectorsDoNotMatch_973) {
    std::vector<double> comparator = {42.0};
    std::vector<double> target = {43.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_FALSE(matcher.match(target));
}

// Test with zero values
TEST_F(ApproxMatcherTest_973, ZeroValuesMatch_973) {
    std::vector<double> comparator = {0.0, 0.0};
    std::vector<double> target = {0.0, 0.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test with zero values and small margin
TEST_F(ApproxMatcherTest_973, ZeroValuesWithMargin_973) {
    std::vector<double> comparator = {0.0};
    std::vector<double> target = {0.001};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    // Default epsilon is relative, so 0 * epsilon = 0 tolerance for zero values
    EXPECT_FALSE(matcher.match(target));
    
    // With margin it should match
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher2(comparator);
    matcher2.margin(0.01);
    EXPECT_TRUE(matcher2.match(target));
}

// Test with negative values
TEST_F(ApproxMatcherTest_973, NegativeValuesMatch_973) {
    std::vector<double> comparator = {-1.0, -2.0, -3.0};
    std::vector<double> target = {-1.0, -2.0, -3.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test with negative values within margin
TEST_F(ApproxMatcherTest_973, NegativeValuesWithinMargin_973) {
    std::vector<double> comparator = {-1.0, -2.0};
    std::vector<double> target = {-1.3, -2.3};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    matcher.margin(0.5);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test with large vectors
TEST_F(ApproxMatcherTest_973, LargeVectorsExactMatch_973) {
    std::vector<double> comparator(1000, 1.0);
    std::vector<double> target(1000, 1.0);
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test that only one element being different causes failure
TEST_F(ApproxMatcherTest_973, OneElementDifferentCausesFailure_973) {
    std::vector<double> comparator = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> target = {1.0, 2.0, 3.0, 4.0, 999.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_FALSE(matcher.match(target));
}

// Test margin with zero margin (should be same as default for absolute tolerance)
TEST_F(ApproxMatcherTest_973, ZeroMarginBehavesLikeDefault_973) {
    std::vector<double> comparator = {1.0, 2.0};
    std::vector<double> target = {1.0, 2.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    matcher.margin(0.0);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test with float-typed vectors
TEST_F(ApproxMatcherTest_973, FloatVectorsMatch_973) {
    std::vector<float> comparator = {1.0f, 2.0f, 3.0f};
    std::vector<float> target = {1.0f, 2.0f, 3.0f};
    
    Catch::Matchers::ApproxMatcher<float, std::allocator<float>, std::allocator<float>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test boundary: margin exactly at the difference
TEST_F(ApproxMatcherTest_973, MarginExactlyAtBoundary_973) {
    std::vector<double> comparator = {1.0};
    std::vector<double> target = {1.5};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    matcher.margin(0.5);
    
    // At exactly the margin boundary, should match (Approx uses <=)
    EXPECT_TRUE(matcher.match(target));
}

// Test describe changes with margin setting
TEST_F(ApproxMatcherTest_973, DescribeWithMarginSetting_973) {
    std::vector<double> comparator = {1.0, 2.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    matcher.margin(0.5);
    
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test with very large values
TEST_F(ApproxMatcherTest_973, VeryLargeValuesMatch_973) {
    std::vector<double> comparator = {1e15, 2e15};
    std::vector<double> target = {1e15, 2e15};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test with very small values
TEST_F(ApproxMatcherTest_973, VerySmallValuesMatch_973) {
    std::vector<double> comparator = {1e-15, 2e-15};
    std::vector<double> target = {1e-15, 2e-15};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_TRUE(matcher.match(target));
}

// Test non-empty comparator vs empty target
TEST_F(ApproxMatcherTest_973, NonEmptyComparatorEmptyTarget_973) {
    std::vector<double> comparator = {1.0};
    std::vector<double> target = {};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);
    
    EXPECT_FALSE(matcher.match(target));
}

// Test epsilon boundary
TEST_F(ApproxMatcherTest_973, EpsilonBoundaryTest_973) {
    std::vector<double> comparator = {100.0};
    // 1% of 100 = 1.0
    std::vector<double> target_within = {101.0};
    std::vector<double> target_outside = {102.0};
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher1(comparator);
    matcher1.epsilon(0.01);
    EXPECT_TRUE(matcher1.match(target_within));
    
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher2(comparator);
    matcher2.epsilon(0.01);
    EXPECT_FALSE(matcher2.match(target_outside));
}
