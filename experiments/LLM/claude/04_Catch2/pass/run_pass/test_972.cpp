#include <gtest/gtest.h>
#include <vector>
#include <limits>
#include <cmath>

// Include the necessary Catch2 headers
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// Helper to check if a matcher matches a given vector
template <typename T>
bool doesMatch(const ApproxMatcher<T, std::allocator<T>, std::allocator<T>>& matcher, const std::vector<T>& v) {
    return matcher.match(v);
}

class ApproxMatcherTest_972 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that identical vectors match with default settings
TEST_F(ApproxMatcherTest_972, IdenticalVectorsMatch_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.0, 2.0, 3.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test that vectors with values within default epsilon match
TEST_F(ApproxMatcherTest_972, ValuesWithinDefaultEpsilonMatch_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    double eps = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    std::vector<double> target = {1.0 + 1.0 * eps * 0.5, 2.0, 3.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test that vectors with very different values do not match
TEST_F(ApproxMatcherTest_972, VeryDifferentValuesDoNotMatch_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {10.0, 20.0, 30.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// Test that different-sized vectors do not match
TEST_F(ApproxMatcherTest_972, DifferentSizedVectorsDoNotMatch_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.0, 2.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// Test that empty vectors match
TEST_F(ApproxMatcherTest_972, EmptyVectorsMatch_972) {
    std::vector<double> comparator = {};
    std::vector<double> target = {};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test epsilon setter - setting a large epsilon allows more tolerance
TEST_F(ApproxMatcherTest_972, EpsilonIncreasesTolerance_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.1, 2.2, 3.3};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    // Default epsilon should not match these
    EXPECT_FALSE(matcher.match(target));
    
    // With a large epsilon, they should match
    auto matcher2 = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher2.epsilon(0.5);
    EXPECT_TRUE(matcher2.match(target));
}

// Test margin setter - setting a margin allows absolute tolerance
TEST_F(ApproxMatcherTest_972, MarginIncreasesAbsoluteTolerance_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.05, 2.05, 3.05};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_FALSE(matcher.match(target));
    
    auto matcher2 = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher2.margin(0.1);
    EXPECT_TRUE(matcher2.match(target));
}

// Test scale setter returns reference for chaining
TEST_F(ApproxMatcherTest_972, ScaleReturnsSelfForChaining_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    auto& ref = matcher.scale(1.0);
    EXPECT_EQ(&ref, &matcher);
}

// Test epsilon returns reference for chaining
TEST_F(ApproxMatcherTest_972, EpsilonReturnsSelfForChaining_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    auto& ref = matcher.epsilon(0.01);
    EXPECT_EQ(&ref, &matcher);
}

// Test margin returns reference for chaining
TEST_F(ApproxMatcherTest_972, MarginReturnsSelfForChaining_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    auto& ref = matcher.margin(0.01);
    EXPECT_EQ(&ref, &matcher);
}

// Test chaining epsilon and margin together
TEST_F(ApproxMatcherTest_972, ChainingEpsilonAndMargin_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.05, 2.05, 3.05};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.epsilon(0.01).margin(0.1);
    EXPECT_TRUE(matcher.match(target));
}

// Test describe returns a non-empty string
TEST_F(ApproxMatcherTest_972, DescribeReturnsNonEmptyString_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test single element vectors match
TEST_F(ApproxMatcherTest_972, SingleElementVectorsMatch_972) {
    std::vector<double> comparator = {42.0};
    std::vector<double> target = {42.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test single element vectors with slightly different values
TEST_F(ApproxMatcherTest_972, SingleElementSlightDifference_972) {
    std::vector<double> comparator = {100.0};
    std::vector<double> target = {100.001};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(0.01);
    EXPECT_TRUE(matcher.match(target));
}

// Test with zero values
TEST_F(ApproxMatcherTest_972, ZeroValuesMatch_972) {
    std::vector<double> comparator = {0.0, 0.0, 0.0};
    std::vector<double> target = {0.0, 0.0, 0.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test that zero values with small differences need margin (epsilon-based tolerance is 0 for value 0)
TEST_F(ApproxMatcherTest_972, ZeroValuesWithSmallDifferenceNeedMargin_972) {
    std::vector<double> comparator = {0.0};
    std::vector<double> target = {0.001};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    // Without margin, near-zero epsilon * 0 = 0, so this shouldn't match
    EXPECT_FALSE(matcher.match(target));
    
    auto matcher2 = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher2.margin(0.01);
    EXPECT_TRUE(matcher2.match(target));
}

// Test with negative values
TEST_F(ApproxMatcherTest_972, NegativeValuesMatch_972) {
    std::vector<double> comparator = {-1.0, -2.0, -3.0};
    std::vector<double> target = {-1.0, -2.0, -3.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test with negative values approximately equal
TEST_F(ApproxMatcherTest_972, NegativeValuesApproxMatch_972) {
    std::vector<double> comparator = {-1.0, -2.0, -3.0};
    std::vector<double> target = {-1.05, -2.05, -3.05};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(0.1);
    EXPECT_TRUE(matcher.match(target));
}

// Test with large vectors
TEST_F(ApproxMatcherTest_972, LargeVectorsMatch_972) {
    std::vector<double> comparator(1000, 1.0);
    std::vector<double> target(1000, 1.0);
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test that one element mismatch causes failure
TEST_F(ApproxMatcherTest_972, OneElementMismatchCausesFailure_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.0, 2.0, 300.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// Test with float type
TEST_F(ApproxMatcherTest_972, FloatTypeVectorsMatch_972) {
    std::vector<float> comparator = {1.0f, 2.0f, 3.0f};
    std::vector<float> target = {1.0f, 2.0f, 3.0f};
    
    auto matcher = ApproxMatcher<float, std::allocator<float>, std::allocator<float>>(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// Test setting very small epsilon
TEST_F(ApproxMatcherTest_972, VerySmallEpsilonReducesTolerance_972) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    double tinyDiff = 1e-10;
    std::vector<double> target = {1.0 + tinyDiff, 2.0 + tinyDiff, 3.0 + tinyDiff};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.epsilon(1e-15);
    // Even with tiny epsilon, the diff might be within margin or not - 
    // but with default margin 0 and very small epsilon, very tiny diff should fail
    // Actually tinyDiff/value could still be larger than epsilon
    // 1e-10 / 1.0 = 1e-10 > 1e-15, so should not match
    EXPECT_FALSE(matcher.match(target));
}

// Test that comparator is empty but target is not
TEST_F(ApproxMatcherTest_972, EmptyComparatorNonEmptyTargetDoNotMatch_972) {
    std::vector<double> comparator = {};
    std::vector<double> target = {1.0};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// Test with very large values
TEST_F(ApproxMatcherTest_972, VeryLargeValuesMatch_972) {
    std::vector<double> comparator = {1e15, 2e15};
    std::vector<double> target = {1e15, 2e15};
    
    auto matcher = ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    EXPECT_TRUE(matcher.match(target));
}
