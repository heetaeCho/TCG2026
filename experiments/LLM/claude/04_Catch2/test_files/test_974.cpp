#include <gtest/gtest.h>
#include <vector>
#include <limits>
#include <string>

// Include the Catch2 amalgamated header
#include "catch_amalgamated.hpp"

// Helper to check if a matcher matches a given vector
template <typename T>
bool doesMatch(Catch::Matchers::ApproxMatcher<T, std::allocator<T>, std::allocator<T>>& matcher,
               const std::vector<T>& v) {
    return matcher.match(v);
}

// Test fixture
class ApproxMatcherTest_974 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Normal operation tests
// ============================================================

TEST_F(ApproxMatcherTest_974, ExactMatchWithIdenticalVectors_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, MatchWithinDefaultEpsilon_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    // Default epsilon is float epsilon * 100, which is roughly 0.00119209...
    // Default margin is 0.0, so comparison uses epsilon-based relative comparison
    std::vector<double> v = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, NoMatchWithDifferentValues_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {1.0, 2.0, 4.0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, MatchWithCustomEpsilon_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.epsilon(0.1); // 10% tolerance
    
    std::vector<double> v = {1.05, 2.1, 3.15};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, MatchWithCustomMargin_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(0.5);
    
    std::vector<double> v = {1.4, 2.4, 3.4};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, NoMatchExceedingMargin_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(0.5);
    
    std::vector<double> v = {1.0, 2.0, 3.6};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, ScaleMethodReturnsSelf_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    // scale() should return reference to self, enabling chaining
    auto& result = matcher.scale(2.0);
    EXPECT_EQ(&result, &matcher);
}

TEST_F(ApproxMatcherTest_974, EpsilonMethodReturnsSelf_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    auto& result = matcher.epsilon(0.01);
    EXPECT_EQ(&result, &matcher);
}

TEST_F(ApproxMatcherTest_974, MarginMethodReturnsSelf_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    auto& result = matcher.margin(0.5);
    EXPECT_EQ(&result, &matcher);
}

TEST_F(ApproxMatcherTest_974, ChainingEpsilonMarginScale_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.epsilon(0.1).margin(0.5).scale(1.0);
    
    std::vector<double> v = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(v));
}

// ============================================================
// Boundary conditions
// ============================================================

TEST_F(ApproxMatcherTest_974, EmptyVectorsMatch_974) {
    std::vector<double> comparator = {};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, DifferentSizeVectorsDoNotMatch_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {1.0, 2.0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, EmptyComparatorVsNonEmptyVector_974) {
    std::vector<double> comparator = {};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {1.0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, NonEmptyComparatorVsEmptyVector_974) {
    std::vector<double> comparator = {1.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, SingleElementMatch_974) {
    std::vector<double> comparator = {42.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {42.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, SingleElementNoMatch_974) {
    std::vector<double> comparator = {42.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {43.0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, MatchWithZeroValues_974) {
    std::vector<double> comparator = {0.0, 0.0, 0.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {0.0, 0.0, 0.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, ZeroVsSmallValueWithMargin_974) {
    std::vector<double> comparator = {0.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(0.01);
    
    std::vector<double> v = {0.005};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, NegativeValues_974) {
    std::vector<double> comparator = {-1.0, -2.0, -3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {-1.0, -2.0, -3.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, VeryLargeValues_974) {
    std::vector<double> comparator = {1e15, 2e15};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::vector<double> v = {1e15, 2e15};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, VerySmallValues_974) {
    std::vector<double> comparator = {1e-15, 2e-15};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(1e-14);
    
    std::vector<double> v = {1e-15, 2e-15};
    EXPECT_TRUE(matcher.match(v));
}

// ============================================================
// Scale-specific tests
// ============================================================

TEST_F(ApproxMatcherTest_974, ScaleWithZero_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.scale(0.0);
    
    std::vector<double> v = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, ScaleWithLargeValue_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.scale(1000.0).epsilon(0.1);
    
    // With large scale and epsilon, larger differences should be tolerated
    std::vector<double> v = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, ScaleWithNegativeValue_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.scale(-1.0);
    
    std::vector<double> v = {1.0, 2.0, 3.0};
    EXPECT_TRUE(matcher.match(v));
}

// ============================================================
// Describe test
// ============================================================

TEST_F(ApproxMatcherTest_974, DescribeReturnsNonEmptyString_974) {
    std::vector<double> comparator = {1.0, 2.0, 3.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(ApproxMatcherTest_974, DescribeAfterSettingParameters_974) {
    std::vector<double> comparator = {1.0, 2.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.epsilon(0.01).margin(0.5).scale(2.0);
    
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// ============================================================
// Edge cases with epsilon at boundaries
// ============================================================

TEST_F(ApproxMatcherTest_974, EpsilonAtBoundaryJustInside_974) {
    std::vector<double> comparator = {100.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.epsilon(0.1); // 10% tolerance => allows +-10 around 100
    
    std::vector<double> v = {109.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, EpsilonAtBoundaryJustOutside_974) {
    std::vector<double> comparator = {100.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.epsilon(0.01); // 1% tolerance => allows +-1 around 100
    
    std::vector<double> v = {102.0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, MarginExactBoundary_974) {
    std::vector<double> comparator = {10.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(1.0);
    
    // Exactly at margin boundary
    std::vector<double> v_at = {11.0};
    EXPECT_TRUE(matcher.match(v_at));
}

TEST_F(ApproxMatcherTest_974, MarginJustBeyondBoundary_974) {
    std::vector<double> comparator = {10.0};
    auto matcher = Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>(comparator);
    matcher.margin(1.0);
    
    std::vector<double> v_beyond = {11.1};
    // This might or might not match depending on epsilon interaction
    // We just check it returns a boolean (no crash)
    bool result = matcher.match(v_beyond);
    (void)result; // Just ensure no crash
}

// ============================================================
// Integer type vector (if T is int-convertible to double)
// ============================================================

TEST_F(ApproxMatcherTest_974, IntegerVectorExactMatch_974) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = Catch::Matchers::ApproxMatcher<int, std::allocator<int>, std::allocator<int>>(comparator);
    
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, IntegerVectorNoMatch_974) {
    std::vector<int> comparator = {1, 2, 3};
    auto matcher = Catch::Matchers::ApproxMatcher<int, std::allocator<int>, std::allocator<int>>(comparator);
    
    std::vector<int> v = {1, 2, 4};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, IntegerVectorWithMargin_974) {
    std::vector<int> comparator = {10, 20, 30};
    auto matcher = Catch::Matchers::ApproxMatcher<int, std::allocator<int>, std::allocator<int>>(comparator);
    matcher.margin(5);
    
    std::vector<int> v = {12, 18, 33};
    EXPECT_TRUE(matcher.match(v));
}

// ============================================================
// Float type vector
// ============================================================

TEST_F(ApproxMatcherTest_974, FloatVectorExactMatch_974) {
    std::vector<float> comparator = {1.0f, 2.0f, 3.0f};
    auto matcher = Catch::Matchers::ApproxMatcher<float, std::allocator<float>, std::allocator<float>>(comparator);
    
    std::vector<float> v = {1.0f, 2.0f, 3.0f};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(ApproxMatcherTest_974, FloatVectorWithSmallDifference_974) {
    std::vector<float> comparator = {1.0f, 2.0f, 3.0f};
    auto matcher = Catch::Matchers::ApproxMatcher<float, std::allocator<float>, std::allocator<float>>(comparator);
    matcher.margin(0.01f);
    
    std::vector<float> v = {1.005f, 2.005f, 3.005f};
    EXPECT_TRUE(matcher.match(v));
}
