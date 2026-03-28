#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Declaration of the function under test
namespace Catch {
    float nextafter(float x, float y);
}

// Test normal operation: nextafter towards a larger value
TEST(CatchNextafterTest_637, NextafterTowardsLargerValue_637) {
    float result = Catch::nextafter(1.0f, 2.0f);
    float expected = ::nextafterf(1.0f, 2.0f);
    EXPECT_EQ(result, expected);
    EXPECT_GT(result, 1.0f);
}

// Test normal operation: nextafter towards a smaller value
TEST(CatchNextafterTest_637, NextafterTowardsSmallerValue_637) {
    float result = Catch::nextafter(1.0f, 0.0f);
    float expected = ::nextafterf(1.0f, 0.0f);
    EXPECT_EQ(result, expected);
    EXPECT_LT(result, 1.0f);
}

// Test when x equals y, should return y
TEST(CatchNextafterTest_637, NextafterSameValue_637) {
    float result = Catch::nextafter(1.0f, 1.0f);
    EXPECT_EQ(result, 1.0f);
}

// Test with zero towards positive
TEST(CatchNextafterTest_637, NextafterZeroTowardsPositive_637) {
    float result = Catch::nextafter(0.0f, 1.0f);
    float expected = ::nextafterf(0.0f, 1.0f);
    EXPECT_EQ(result, expected);
    EXPECT_GT(result, 0.0f);
}

// Test with zero towards negative
TEST(CatchNextafterTest_637, NextafterZeroTowardsNegative_637) {
    float result = Catch::nextafter(0.0f, -1.0f);
    float expected = ::nextafterf(0.0f, -1.0f);
    EXPECT_EQ(result, expected);
    EXPECT_LT(result, 0.0f);
}

// Test with negative values
TEST(CatchNextafterTest_637, NextafterNegativeValues_637) {
    float result = Catch::nextafter(-1.0f, -2.0f);
    float expected = ::nextafterf(-1.0f, -2.0f);
    EXPECT_EQ(result, expected);
    EXPECT_LT(result, -1.0f);
}

// Test with negative towards zero
TEST(CatchNextafterTest_637, NextafterNegativeTowardsZero_637) {
    float result = Catch::nextafter(-1.0f, 0.0f);
    float expected = ::nextafterf(-1.0f, 0.0f);
    EXPECT_EQ(result, expected);
    EXPECT_GT(result, -1.0f);
}

// Test boundary: max float towards infinity
TEST(CatchNextafterTest_637, NextafterMaxTowardsInfinity_637) {
    float result = Catch::nextafter(std::numeric_limits<float>::max(), std::numeric_limits<float>::infinity());
    float expected = ::nextafterf(std::numeric_limits<float>::max(), std::numeric_limits<float>::infinity());
    EXPECT_EQ(result, expected);
    EXPECT_TRUE(std::isinf(result));
}

// Test boundary: smallest positive denormalized towards zero
TEST(CatchNextafterTest_637, NextafterSmallestDenormTowardsZero_637) {
    float smallest = std::numeric_limits<float>::denorm_min();
    float result = Catch::nextafter(smallest, 0.0f);
    float expected = ::nextafterf(smallest, 0.0f);
    EXPECT_EQ(result, expected);
    EXPECT_EQ(result, 0.0f);
}

// Test with infinity
TEST(CatchNextafterTest_637, NextafterInfinityTowardsZero_637) {
    float result = Catch::nextafter(std::numeric_limits<float>::infinity(), 0.0f);
    float expected = ::nextafterf(std::numeric_limits<float>::infinity(), 0.0f);
    EXPECT_EQ(result, expected);
    EXPECT_LT(result, std::numeric_limits<float>::infinity());
}

// Test with NaN input x
TEST(CatchNextafterTest_637, NextafterNaNInput_637) {
    float nan_val = std::numeric_limits<float>::quiet_NaN();
    float result = Catch::nextafter(nan_val, 1.0f);
    EXPECT_TRUE(std::isnan(result));
}

// Test with NaN input y
TEST(CatchNextafterTest_637, NextafterNaNDirection_637) {
    float nan_val = std::numeric_limits<float>::quiet_NaN();
    float result = Catch::nextafter(1.0f, nan_val);
    EXPECT_TRUE(std::isnan(result));
}

// Test negative zero towards positive zero
TEST(CatchNextafterTest_637, NextafterNegativeZeroTowardsPositiveZero_637) {
    float result = Catch::nextafter(-0.0f, 0.0f);
    float expected = ::nextafterf(-0.0f, 0.0f);
    EXPECT_EQ(result, expected);
}

// Test positive zero towards negative zero
TEST(CatchNextafterTest_637, NextafterPositiveZeroTowardsNegativeZero_637) {
    float result = Catch::nextafter(0.0f, -0.0f);
    float expected = ::nextafterf(0.0f, -0.0f);
    EXPECT_EQ(result, expected);
}

// Test boundary: negative infinity towards zero
TEST(CatchNextafterTest_637, NextafterNegativeInfinityTowardsZero_637) {
    float result = Catch::nextafter(-std::numeric_limits<float>::infinity(), 0.0f);
    float expected = ::nextafterf(-std::numeric_limits<float>::infinity(), 0.0f);
    EXPECT_EQ(result, expected);
    EXPECT_GT(result, -std::numeric_limits<float>::infinity());
}

// Test boundary: lowest float towards negative infinity
TEST(CatchNextafterTest_637, NextafterLowestTowardsNegativeInfinity_637) {
    float result = Catch::nextafter(std::numeric_limits<float>::lowest(), -std::numeric_limits<float>::infinity());
    float expected = ::nextafterf(std::numeric_limits<float>::lowest(), -std::numeric_limits<float>::infinity());
    EXPECT_EQ(result, expected);
    EXPECT_TRUE(std::isinf(result));
}

// Test that the result matches std::nextafterf for various values
TEST(CatchNextafterTest_637, ConsistencyWithStdNextafterf_637) {
    float test_values[] = {0.5f, -0.5f, 100.0f, -100.0f, 1e-10f, -1e-10f, 1e30f, -1e30f};
    float directions[] = {1.0f, -1.0f, 0.0f};
    
    for (float x : test_values) {
        for (float y : directions) {
            float result = Catch::nextafter(x, y);
            float expected = ::nextafterf(x, y);
            EXPECT_EQ(result, expected) << "Failed for x=" << x << " y=" << y;
        }
    }
}
