#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// Helper to create an ApproxMatcher easily
template <typename T>
ApproxMatcher<T, std::allocator<T>, std::allocator<T>> makeApproxMatcher(std::vector<T> const& comparator) {
    return ApproxMatcher<T, std::allocator<T>, std::allocator<T>>(comparator);
}

// Test fixture
class ApproxMatcherTest_970 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Normal operation tests
// ============================================================

TEST_F(ApproxMatcherTest_970, ExactMatchReturnTrue_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.0, 2.0, 3.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, EmptyVectorsMatch_970) {
    std::vector<double> comparator = {};
    std::vector<double> target = {};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, SingleElementExactMatch_970) {
    std::vector<double> comparator = {42.0};
    std::vector<double> target = {42.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, ApproximatelyEqualWithinDefaultEpsilon_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    // Default Approx epsilon is typically around 1e-12 relative
    std::vector<double> target = {1.0 + 1e-15, 2.0 + 1e-15, 3.0 + 1e-15};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST_F(ApproxMatcherTest_970, DifferentSizesReturnFalse_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.0, 2.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, TargetLargerThanComparatorReturnFalse_970) {
    std::vector<double> comparator = {1.0, 2.0};
    std::vector<double> target = {1.0, 2.0, 3.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, EmptyComparatorNonEmptyTargetReturnFalse_970) {
    std::vector<double> comparator = {};
    std::vector<double> target = {1.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, NonEmptyComparatorEmptyTargetReturnFalse_970) {
    std::vector<double> comparator = {1.0};
    std::vector<double> target = {};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// ============================================================
// Mismatch tests
// ============================================================

TEST_F(ApproxMatcherTest_970, ClearMismatchReturnFalse_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.0, 2.0, 4.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, FirstElementMismatchReturnFalse_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {100.0, 2.0, 3.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, AllElementsMismatchReturnFalse_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {10.0, 20.0, 30.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}

// ============================================================
// Epsilon/Margin/Scale tests
// ============================================================

TEST_F(ApproxMatcherTest_970, CustomEpsilonAllowsLargerDifference_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.1, 2.2, 3.3};
    auto matcher = makeApproxMatcher(comparator);
    matcher.epsilon(0.15); // 15% relative
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, CustomEpsilonTooSmallReturnFalse_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.1, 2.2, 3.3};
    auto matcher = makeApproxMatcher(comparator);
    matcher.epsilon(0.01); // 1% relative - too small
    EXPECT_FALSE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, CustomMarginAllowsAbsoluteDifference_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.5, 2.5, 3.5};
    auto matcher = makeApproxMatcher(comparator);
    matcher.margin(0.6);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, CustomMarginTooSmallReturnFalse_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.5, 2.5, 3.5};
    auto matcher = makeApproxMatcher(comparator);
    matcher.margin(0.1);
    EXPECT_FALSE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, ChainEpsilonAndMargin_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.05, 2.05, 3.05};
    auto matcher = makeApproxMatcher(comparator);
    matcher.epsilon(0.001).margin(0.1);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, ScaleChaining_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.0, 2.0, 3.0};
    auto matcher = makeApproxMatcher(comparator);
    matcher.scale(10.0);
    EXPECT_TRUE(matcher.match(target));
}

// ============================================================
// describe() tests
// ============================================================

TEST_F(ApproxMatcherTest_970, DescribeReturnsNonEmptyString_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = makeApproxMatcher(comparator);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(ApproxMatcherTest_970, DescribeEmptyVectorReturnsNonEmptyString_970) {
    std::vector<double> comparator = {};
    auto matcher = makeApproxMatcher(comparator);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// ============================================================
// Edge cases with special floating point values
// ============================================================

TEST_F(ApproxMatcherTest_970, ZeroValuesMatch_970) {
    std::vector<double> comparator = {0.0, 0.0, 0.0};
    std::vector<double> target = {0.0, 0.0, 0.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, NegativeValuesExactMatch_970) {
    std::vector<double> comparator = {-1.0, -2.0, -3.0};
    std::vector<double> target = {-1.0, -2.0, -3.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, NegativeValuesMismatch_970) {
    std::vector<double> comparator = {-1.0, -2.0, -3.0};
    std::vector<double> target = {1.0, 2.0, 3.0};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, VeryLargeValuesMatch_970) {
    std::vector<double> comparator = {1e15, 2e15, 3e15};
    std::vector<double> target = {1e15, 2e15, 3e15};
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, VerySmallValuesWithMarginMatch_970) {
    std::vector<double> comparator = {1e-15, 2e-15, 3e-15};
    std::vector<double> target = {1e-15 + 1e-20, 2e-15 + 1e-20, 3e-15 + 1e-20};
    auto matcher = makeApproxMatcher(comparator);
    matcher.margin(1e-14);
    EXPECT_TRUE(matcher.match(target));
}

// ============================================================
// Integer type tests (if T is int convertible to double)
// ============================================================

TEST_F(ApproxMatcherTest_970, IntegerVectorsExactMatch_970) {
    std::vector<int> comparator = {1, 2, 3};
    std::vector<int> target = {1, 2, 3};
    ApproxMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, IntegerVectorsMismatch_970) {
    std::vector<int> comparator = {1, 2, 3};
    std::vector<int> target = {1, 2, 4};
    ApproxMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, FloatVectorsMatch_970) {
    std::vector<float> comparator = {1.0f, 2.0f, 3.0f};
    std::vector<float> target = {1.0f, 2.0f, 3.0f};
    ApproxMatcher<float, std::allocator<float>, std::allocator<float>> matcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

// ============================================================
// Method chaining returns reference tests
// ============================================================

TEST_F(ApproxMatcherTest_970, MethodChainingWorks_970) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    std::vector<double> target = {1.05, 2.05, 3.05};
    auto matcher = makeApproxMatcher(comparator);
    // All three methods chained
    matcher.epsilon(0.1).margin(0.1).scale(1.0);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, LargeVectorMatch_970) {
    std::vector<double> comparator(1000, 1.0);
    std::vector<double> target(1000, 1.0);
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_TRUE(matcher.match(target));
}

TEST_F(ApproxMatcherTest_970, LargeVectorSingleMismatch_970) {
    std::vector<double> comparator(1000, 1.0);
    std::vector<double> target(1000, 1.0);
    target[999] = 100.0; // Single mismatch at end
    auto matcher = makeApproxMatcher(comparator);
    EXPECT_FALSE(matcher.match(target));
}
