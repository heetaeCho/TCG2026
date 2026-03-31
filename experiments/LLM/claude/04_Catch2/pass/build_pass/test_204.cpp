#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cstring>

// Include the necessary Catch2 headers for the matchers
#include "catch2/matchers/catch_matchers_floating_point.hpp"
#include "catch2/matchers/catch_matchers.hpp"

class WithinUlpsMatcherFloatTest_204 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that exact match with 0 ULP tolerance works
TEST_F(WithinUlpsMatcherFloatTest_204, ExactMatchZeroUlp_204) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 0);
    EXPECT_TRUE(matcher.match(1.0f));
}

// Test that exact match with non-zero ULP tolerance works
TEST_F(WithinUlpsMatcherFloatTest_204, ExactMatchNonZeroUlp_204) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 5);
    EXPECT_TRUE(matcher.match(1.0f));
}

// Test within 1 ULP of a float value
TEST_F(WithinUlpsMatcherFloatTest_204, WithinOneUlp_204) {
    float target = 1.0f;
    auto matcher = Catch::Matchers::WithinULP(target, 1);
    
    // Next representable float after 1.0f
    float next = std::nextafter(target, std::numeric_limits<float>::max());
    EXPECT_TRUE(matcher.match(next));
    
    // Previous representable float before 1.0f
    float prev = std::nextafter(target, -std::numeric_limits<float>::max());
    EXPECT_TRUE(matcher.match(prev));
}

// Test outside 1 ULP of a float value
TEST_F(WithinUlpsMatcherFloatTest_204, OutsideOneUlp_204) {
    float target = 1.0f;
    auto matcher = Catch::Matchers::WithinULP(target, 0);
    
    float next = std::nextafter(target, std::numeric_limits<float>::max());
    EXPECT_FALSE(matcher.match(next));
}

// Test within multiple ULPs
TEST_F(WithinUlpsMatcherFloatTest_204, WithinMultipleUlps_204) {
    float target = 1.0f;
    auto matcher = Catch::Matchers::WithinULP(target, 5);
    
    float val = target;
    for (int i = 0; i < 5; ++i) {
        val = std::nextafter(val, std::numeric_limits<float>::max());
    }
    EXPECT_TRUE(matcher.match(val));
}

// Test just outside multiple ULPs
TEST_F(WithinUlpsMatcherFloatTest_204, JustOutsideMultipleUlps_204) {
    float target = 1.0f;
    auto matcher = Catch::Matchers::WithinULP(target, 5);
    
    float val = target;
    for (int i = 0; i < 6; ++i) {
        val = std::nextafter(val, std::numeric_limits<float>::max());
    }
    EXPECT_FALSE(matcher.match(val));
}

// Test with zero target
TEST_F(WithinUlpsMatcherFloatTest_204, ZeroTarget_204) {
    auto matcher = Catch::Matchers::WithinULP(0.0f, 0);
    EXPECT_TRUE(matcher.match(0.0f));
}

// Test negative zero vs positive zero
TEST_F(WithinUlpsMatcherFloatTest_204, NegativeZeroVsPositiveZero_204) {
    auto matcher = Catch::Matchers::WithinULP(0.0f, 0);
    EXPECT_TRUE(matcher.match(-0.0f));
}

// Test with negative values
TEST_F(WithinUlpsMatcherFloatTest_204, NegativeValues_204) {
    float target = -1.0f;
    auto matcher = Catch::Matchers::WithinULP(target, 1);
    EXPECT_TRUE(matcher.match(target));
    
    float next = std::nextafter(target, 0.0f);
    EXPECT_TRUE(matcher.match(next));
}

// Test with very small values (denormals)
TEST_F(WithinUlpsMatcherFloatTest_204, DenormalValues_204) {
    float target = std::numeric_limits<float>::denorm_min();
    auto matcher = Catch::Matchers::WithinULP(target, 1);
    EXPECT_TRUE(matcher.match(target));
}

// Test with max float
TEST_F(WithinUlpsMatcherFloatTest_204, MaxFloat_204) {
    float target = std::numeric_limits<float>::max();
    auto matcher = Catch::Matchers::WithinULP(target, 0);
    EXPECT_TRUE(matcher.match(target));
}

// Test with min positive normal float
TEST_F(WithinUlpsMatcherFloatTest_204, MinPositiveNormal_204) {
    float target = std::numeric_limits<float>::min();
    auto matcher = Catch::Matchers::WithinULP(target, 1);
    EXPECT_TRUE(matcher.match(target));
}

// Test that NaN does not match itself
TEST_F(WithinUlpsMatcherFloatTest_204, NaNDoesNotMatchItself_204) {
    float nan_val = std::numeric_limits<float>::quiet_NaN();
    auto matcher = Catch::Matchers::WithinULP(1.0f, 1000000);
    EXPECT_FALSE(matcher.match(nan_val));
}

// Test that describe returns a non-empty string
TEST_F(WithinUlpsMatcherFloatTest_204, DescribeReturnsNonEmpty_204) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 5);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test with large ULP tolerance
TEST_F(WithinUlpsMatcherFloatTest_204, LargeUlpTolerance_204) {
    float target = 1.0f;
    auto matcher = Catch::Matchers::WithinULP(target, 1000000);
    
    // Values that are significantly different should still match with large tolerance
    float val = target;
    for (int i = 0; i < 100; ++i) {
        val = std::nextafter(val, std::numeric_limits<float>::max());
    }
    EXPECT_TRUE(matcher.match(val));
}

// Test symmetry: if a matches b within N ULPs, b matches a within N ULPs
TEST_F(WithinUlpsMatcherFloatTest_204, SymmetricMatching_204) {
    float target = 1.0f;
    float other = std::nextafter(target, std::numeric_limits<float>::max());
    
    auto matcher1 = Catch::Matchers::WithinULP(target, 1);
    auto matcher2 = Catch::Matchers::WithinULP(other, 1);
    
    EXPECT_TRUE(matcher1.match(other));
    EXPECT_TRUE(matcher2.match(target));
}

// Test with different float values
TEST_F(WithinUlpsMatcherFloatTest_204, DifferentValues_204) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 0);
    EXPECT_FALSE(matcher.match(2.0f));
}

// Test negative target with ULP distance in negative direction
TEST_F(WithinUlpsMatcherFloatTest_204, NegativeTargetBothDirections_204) {
    float target = -5.0f;
    auto matcher = Catch::Matchers::WithinULP(target, 2);
    
    float next1 = std::nextafter(target, 0.0f);
    float next2 = std::nextafter(next1, 0.0f);
    EXPECT_TRUE(matcher.match(next2));
    
    float prev1 = std::nextafter(target, -std::numeric_limits<float>::max());
    float prev2 = std::nextafter(prev1, -std::numeric_limits<float>::max());
    EXPECT_TRUE(matcher.match(prev2));
}

// Test with infinity
TEST_F(WithinUlpsMatcherFloatTest_204, InfinityTarget_204) {
    float inf = std::numeric_limits<float>::infinity();
    auto matcher = Catch::Matchers::WithinULP(inf, 0);
    EXPECT_TRUE(matcher.match(inf));
}

// Test infinity does not match finite values
TEST_F(WithinUlpsMatcherFloatTest_204, InfinityDoesNotMatchFinite_204) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 100);
    float inf = std::numeric_limits<float>::infinity();
    EXPECT_FALSE(matcher.match(inf));
}
