#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <cmath>

// Include the Catch2 amalgamated header
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Helper to check if a matcher matches a given vector
template <typename Matcher, typename T, typename Alloc>
bool doesMatch(const Matcher& matcher, const std::vector<T, Alloc>& v) {
    return matcher.match(v);
}

class ApproxMatcherTest_971 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that identical vectors match
TEST_F(ApproxMatcherTest_971, IdenticalVectorsMatch_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test that vectors with different sizes do not match
TEST_F(ApproxMatcherTest_971, DifferentSizeVectorsDoNotMatch_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {1.0, 2.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test that vectors with different sizes (target larger) do not match
TEST_F(ApproxMatcherTest_971, TargetLargerDoesNotMatch_971) {
    std::vector<double> comparator = {1.0, 2.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {1.0, 2.0, 3.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test that empty vectors match
TEST_F(ApproxMatcherTest_971, EmptyVectorsMatch_971) {
    std::vector<double> comparator = {};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {};
    EXPECT_TRUE(matcher.match(target));
}

// Test that values within default epsilon match
TEST_F(ApproxMatcherTest_971, ValuesWithinDefaultEpsilonMatch_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    // Default epsilon in Catch::Approx is typically std::numeric_limits<float>::epsilon()*100
    std::vector<double> target = {1.0, 2.0, 3.0 + 1e-10};
    EXPECT_TRUE(matcher.match(target));
}

// Test that values far apart do not match with default settings
TEST_F(ApproxMatcherTest_971, ValuesFarApartDoNotMatch_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {1.0, 2.0, 4.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test custom epsilon makes approximate values match
TEST_F(ApproxMatcherTest_971, CustomEpsilonAllowsLargerDifference_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.epsilon(0.5); // 50% relative tolerance
    
    std::vector<double> target = {1.0, 2.0, 3.5};
    EXPECT_TRUE(matcher.match(target));
}

// Test custom margin allows absolute differences
TEST_F(ApproxMatcherTest_971, CustomMarginAllowsAbsoluteDifference_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(2.0);
    
    std::vector<double> target = {1.0, 2.0, 5.0}; // diff of 2.0, within margin
    EXPECT_TRUE(matcher.match(target));
}

// Test that margin does not allow differences beyond the margin
TEST_F(ApproxMatcherTest_971, MarginRejectsBeyondMarginDifference_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(0.5);
    
    std::vector<double> target = {1.0, 2.0, 4.0}; // diff of 1.0, beyond margin of 0.5
    EXPECT_FALSE(matcher.match(target));
}

// Test that describe contains "is approx"
TEST_F(ApproxMatcherTest_971, DescribeContainsIsApprox_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::string desc = matcher.describe();
    EXPECT_NE(desc.find("is approx"), std::string::npos);
}

// Test describe contains the comparator values
TEST_F(ApproxMatcherTest_971, DescribeContainsComparatorValues_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::string desc = matcher.describe();
    // The description should contain stringified version of the comparator
    EXPECT_FALSE(desc.empty());
    EXPECT_NE(desc.find("1.0"), std::string::npos);
}

// Test epsilon chaining returns reference to self
TEST_F(ApproxMatcherTest_971, EpsilonReturnsSelfForChaining_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    auto& result = matcher.epsilon(0.1);
    EXPECT_EQ(&result, &matcher);
}

// Test margin chaining returns reference to self
TEST_F(ApproxMatcherTest_971, MarginReturnsSelfForChaining_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    auto& result = matcher.margin(0.1);
    EXPECT_EQ(&result, &matcher);
}

// Test scale chaining returns reference to self
TEST_F(ApproxMatcherTest_971, ScaleReturnsSelfForChaining_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    auto& result = matcher.scale(2.0);
    EXPECT_EQ(&result, &matcher);
}

// Test chaining multiple settings
TEST_F(ApproxMatcherTest_971, ChainingMultipleSettings_971) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    matcher.epsilon(0.01).margin(0.5).scale(1.0);
    
    std::vector<double> target = {1.0, 2.0, 3.4}; // within margin of 0.5
    EXPECT_TRUE(matcher.match(target));
}

// Test single element vectors that match
TEST_F(ApproxMatcherTest_971, SingleElementVectorMatch_971) {
    std::vector<double> comparator = {42.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {42.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test single element vectors that don't match
TEST_F(ApproxMatcherTest_971, SingleElementVectorNoMatch_971) {
    std::vector<double> comparator = {42.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {100.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test with integer-like doubles (zero)
TEST_F(ApproxMatcherTest_971, ZeroValuesMatch_971) {
    std::vector<double> comparator = {0.0, 0.0, 0.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {0.0, 0.0, 0.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test with zero comparator and small target values - epsilon is relative so small absolute values near zero need margin
TEST_F(ApproxMatcherTest_971, ZeroComparatorSmallTargetWithoutMarginFails_971) {
    std::vector<double> comparator = {0.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    // Relative epsilon against 0 won't help for non-zero target
    std::vector<double> target = {0.5};
    EXPECT_FALSE(matcher.match(target));
}

// Test with zero comparator and small target values with margin
TEST_F(ApproxMatcherTest_971, ZeroComparatorSmallTargetWithMarginSucceeds_971) {
    std::vector<double> comparator = {0.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(1.0);
    
    std::vector<double> target = {0.5};
    EXPECT_TRUE(matcher.match(target));
}

// Test negative values match
TEST_F(ApproxMatcherTest_971, NegativeValuesMatch_971) {
    std::vector<double> comparator = {-1.0, -2.0, -3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {-1.0, -2.0, -3.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test negative values don't match when far apart
TEST_F(ApproxMatcherTest_971, NegativeValuesFarApartDoNotMatch_971) {
    std::vector<double> comparator = {-1.0, -2.0, -3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {-1.0, -2.0, -30.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test with large vectors
TEST_F(ApproxMatcherTest_971, LargeVectorsMatch_971) {
    std::vector<double> comparator(1000, 1.0);
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target(1000, 1.0);
    EXPECT_TRUE(matcher.match(target));
}

// Test with large vectors where one element differs
TEST_F(ApproxMatcherTest_971, LargeVectorsOneElementDiffers_971) {
    std::vector<double> comparator(1000, 1.0);
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target(1000, 1.0);
    target[500] = 100.0;
    EXPECT_FALSE(matcher.match(target));
}

// Test with float type
TEST_F(ApproxMatcherTest_971, FloatVectorsMatch_971) {
    std::vector<float> comparator = {1.0f, 2.0f, 3.0f};
    auto matcher = Catch::Matchers::ApproxMatcher<float, std::allocator<float>, std::allocator<float>>(comparator);
    
    std::vector<float> target = {1.0f, 2.0f, 3.0f};
    EXPECT_TRUE(matcher.match(target));
}

// Test with int type (convertible to double)
TEST_F(ApproxMatcherTest_971, IntVectorsMatch_971) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = Catch::Matchers::ApproxMatcher<int, std::allocator<int>, std::allocator<int>>(comparator);
    
    std::vector<int> target = {1, 2, 3};
    EXPECT_TRUE(matcher.match(target));
}

// Test empty comparator with non-empty target
TEST_F(ApproxMatcherTest_971, EmptyComparatorNonEmptyTargetDoesNotMatch_971) {
    std::vector<double> comparator = {};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> target = {1.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test very small epsilon with very close values
TEST_F(ApproxMatcherTest_971, VerySmallEpsilonVeryCloseValues_971) {
    std::vector<double> comparator = {1.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.epsilon(1e-15);
    
    std::vector<double> target = {1.0 + 1e-16};
    EXPECT_TRUE(matcher.match(target));
}
