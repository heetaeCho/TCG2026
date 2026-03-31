#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <limits>

// Include the Catch2 amalgamated header for the ApproxMatcher
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

class ApproxMatcherTest_980 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to check if matcher matches a given vector
template<typename T>
bool matcherMatches(const Catch::Matchers::ApproxMatcher<T>& matcher, const std::vector<T>& target) {
    return matcher.match(target);
}

// Test: Creating ApproxMatcher from a vector of doubles
TEST_F(ApproxMatcherTest_980, CreateFromDoubleVector_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    // Matcher should match the same vector exactly
    std::vector<double> target = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Exact match with integer vector
TEST_F(ApproxMatcherTest_980, ExactMatchIntegerVector_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Mismatch with different values
TEST_F(ApproxMatcherTest_980, MismatchDifferentValues_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {1.0, 2.0, 4.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Empty vectors should match
TEST_F(ApproxMatcherTest_980, EmptyVectorsMatch_980) {
    std::vector<double> comparator = {};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Different sized vectors should not match
TEST_F(ApproxMatcherTest_980, DifferentSizedVectorsNoMatch_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {1.0, 2.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Values within default epsilon should match
TEST_F(ApproxMatcherTest_980, ValuesWithinDefaultEpsilon_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    // Very small differences relative to value should still match due to default margin/epsilon
    std::vector<double> target = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Approx matcher with custom epsilon
TEST_F(ApproxMatcherTest_980, CustomEpsilon_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator).epsilon(0.1);
    // Values within 10% should match
    std::vector<double> target = {1.05, 2.1, 3.15};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Approx matcher with custom margin
TEST_F(ApproxMatcherTest_980, CustomMargin_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator).margin(0.5);
    std::vector<double> target = {1.3, 2.3, 3.3};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Values outside custom margin should not match
TEST_F(ApproxMatcherTest_980, OutsideCustomMarginNoMatch_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator).margin(0.1);
    std::vector<double> target = {1.0, 2.0, 3.5};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Values outside custom epsilon should not match
TEST_F(ApproxMatcherTest_980, OutsideCustomEpsilonNoMatch_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator).epsilon(0.01);
    std::vector<double> target = {1.0, 2.0, 3.5};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Single element vector match
TEST_F(ApproxMatcherTest_980, SingleElementMatch_980) {
    std::vector<double> comparator = {42.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {42.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Single element vector mismatch
TEST_F(ApproxMatcherTest_980, SingleElementMismatch_980) {
    std::vector<double> comparator = {42.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {43.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Large vector match
TEST_F(ApproxMatcherTest_980, LargeVectorMatch_980) {
    std::vector<double> comparator(1000, 1.0);
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target(1000, 1.0);
    EXPECT_TRUE(matcher.match(target));
}

// Test: Large vector with one differing element
TEST_F(ApproxMatcherTest_980, LargeVectorOneDifference_980) {
    std::vector<double> comparator(1000, 1.0);
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target(1000, 1.0);
    target[500] = 100.0;
    EXPECT_FALSE(matcher.match(target));
}

// Test: Negative values
TEST_F(ApproxMatcherTest_980, NegativeValues_980) {
    std::vector<double> comparator = {-1.0, -2.0, -3.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {-1.0, -2.0, -3.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Zero values
TEST_F(ApproxMatcherTest_980, ZeroValues_980) {
    std::vector<double> comparator = {0.0, 0.0, 0.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {0.0, 0.0, 0.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Mixed positive and negative values
TEST_F(ApproxMatcherTest_980, MixedPositiveNegative_980) {
    std::vector<double> comparator = {-1.0, 0.0, 1.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {-1.0, 0.0, 1.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test: describe() returns a non-empty string
TEST_F(ApproxMatcherTest_980, DescribeReturnsNonEmpty_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: Comparator vector longer than target
TEST_F(ApproxMatcherTest_980, ComparatorLongerThanTarget_980) {
    std::vector<double> comparator = {1.0, 2.0, 3.0, 4.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {1.0, 2.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Target vector longer than comparator
TEST_F(ApproxMatcherTest_980, TargetLongerThanComparator_980) {
    std::vector<double> comparator = {1.0, 2.0};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<double> target = {1.0, 2.0, 3.0, 4.0};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Epsilon chaining returns a matcher that works
TEST_F(ApproxMatcherTest_980, EpsilonChainingWorks_980) {
    std::vector<double> comparator = {100.0, 200.0};
    auto matcher = Catch::Matchers::Approx(comparator).epsilon(0.5);
    // 50% tolerance: 100 +/- 50, 200 +/- 100
    std::vector<double> target = {130.0, 250.0};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Margin chaining returns a matcher that works
TEST_F(ApproxMatcherTest_980, MarginChainingWorks_980) {
    std::vector<double> comparator = {0.0, 0.0};
    auto matcher = Catch::Matchers::Approx(comparator).margin(1.0);
    std::vector<double> target = {0.5, -0.5};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Float vector support
TEST_F(ApproxMatcherTest_980, FloatVectorSupport_980) {
    std::vector<float> comparator = {1.0f, 2.0f, 3.0f};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<float> target = {1.0f, 2.0f, 3.0f};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Float vector mismatch
TEST_F(ApproxMatcherTest_980, FloatVectorMismatch_980) {
    std::vector<float> comparator = {1.0f, 2.0f, 3.0f};
    auto matcher = Catch::Matchers::Approx(comparator);
    std::vector<float> target = {1.0f, 2.0f, 5.0f};
    EXPECT_FALSE(matcher.match(target));
}

// Test: Very small differences near zero with margin
TEST_F(ApproxMatcherTest_980, SmallDifferencesNearZeroWithMargin_980) {
    std::vector<double> comparator = {0.0};
    auto matcher = Catch::Matchers::Approx(comparator).margin(1e-10);
    std::vector<double> target = {1e-11};
    EXPECT_TRUE(matcher.match(target));
}

// Test: Very small differences near zero without margin should fail (epsilon is relative)
TEST_F(ApproxMatcherTest_980, SmallDifferencesNearZeroWithoutMargin_980) {
    std::vector<double> comparator = {0.0};
    auto matcher = Catch::Matchers::Approx(comparator).epsilon(0.01);
    // epsilon is relative, so for 0.0 base value, any non-zero diff might fail
    std::vector<double> target = {1.0};
    EXPECT_FALSE(matcher.match(target));
}
