#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Forward declaration of the function under test
namespace Catch {
namespace Benchmark {
namespace Detail {
double normal_quantile(double p);
}
}
}

using Catch::Benchmark::Detail::normal_quantile;

class NormalQuantileTest_989 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-6;
};

// Test that p = 0.5 returns 0 (median of standard normal distribution)
TEST_F(NormalQuantileTest_989, MedianReturnsZero_989) {
    double result = normal_quantile(0.5);
    EXPECT_NEAR(result, 0.0, kTolerance);
}

// Test that p = 0 returns a very negative value (negative infinity or large negative)
TEST_F(NormalQuantileTest_989, PZeroReturnsNegativeExtreme_989) {
    double result = normal_quantile(0.0);
    // At p=0, the quantile should be -infinity or a very large negative number
    EXPECT_LE(result, -1e10);
}

// Test that p = 1 returns a very positive value (positive infinity or large positive)
TEST_F(NormalQuantileTest_989, POneReturnsPositiveExtreme_989) {
    double result = normal_quantile(1.0);
    // At p=1, the quantile should be +infinity or a very large positive number
    EXPECT_GE(result, 1e10);
}

// Test that p < 0 returns 0 (error case)
TEST_F(NormalQuantileTest_989, NegativePReturnsZero_989) {
    double result = normal_quantile(-0.1);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test that p > 1 returns 0 (error case)
TEST_F(NormalQuantileTest_989, PGreaterThanOneReturnsZero_989) {
    double result = normal_quantile(1.1);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test that p < 0.5 returns a negative value
TEST_F(NormalQuantileTest_989, PLessThanHalfReturnsNegative_989) {
    double result = normal_quantile(0.25);
    EXPECT_LT(result, 0.0);
}

// Test that p > 0.5 returns a positive value
TEST_F(NormalQuantileTest_989, PGreaterThanHalfReturnsPositive_989) {
    double result = normal_quantile(0.75);
    EXPECT_GT(result, 0.0);
}

// Test symmetry: quantile(p) == -quantile(1-p)
TEST_F(NormalQuantileTest_989, SymmetryAroundMedian_989) {
    double p = 0.25;
    double q1 = normal_quantile(p);
    double q2 = normal_quantile(1.0 - p);
    EXPECT_NEAR(q1, -q2, kTolerance);
}

// Test symmetry at another point
TEST_F(NormalQuantileTest_989, SymmetryAtTenPercent_989) {
    double q1 = normal_quantile(0.1);
    double q2 = normal_quantile(0.9);
    EXPECT_NEAR(q1, -q2, kTolerance);
}

// Test known quantile value: p = 0.975 should give approximately 1.96
TEST_F(NormalQuantileTest_989, KnownQuantile975_989) {
    double result = normal_quantile(0.975);
    EXPECT_NEAR(result, 1.959964, 1e-3);
}

// Test known quantile value: p = 0.025 should give approximately -1.96
TEST_F(NormalQuantileTest_989, KnownQuantile025_989) {
    double result = normal_quantile(0.025);
    EXPECT_NEAR(result, -1.959964, 1e-3);
}

// Test known quantile value: p = 0.8413 should give approximately 1.0
TEST_F(NormalQuantileTest_989, KnownQuantileApproxOne_989) {
    double result = normal_quantile(0.8413447);
    EXPECT_NEAR(result, 1.0, 1e-3);
}

// Test known quantile value: p = 0.1587 should give approximately -1.0
TEST_F(NormalQuantileTest_989, KnownQuantileApproxNegOne_989) {
    double result = normal_quantile(0.1586553);
    EXPECT_NEAR(result, -1.0, 1e-3);
}

// Test monotonicity: larger p should give larger quantile
TEST_F(NormalQuantileTest_989, MonotonicityIncreasing_989) {
    double prev = normal_quantile(0.01);
    for (double p = 0.1; p <= 0.99; p += 0.1) {
        double curr = normal_quantile(p);
        EXPECT_GT(curr, prev) << "Failed monotonicity at p = " << p;
        prev = curr;
    }
}

// Test very small p value
TEST_F(NormalQuantileTest_989, VerySmallP_989) {
    double result = normal_quantile(0.001);
    EXPECT_LT(result, -3.0);
}

// Test very large p value close to 1
TEST_F(NormalQuantileTest_989, VeryLargeP_989) {
    double result = normal_quantile(0.999);
    EXPECT_GT(result, 3.0);
}

// Test boundary: p exactly 0
TEST_F(NormalQuantileTest_989, BoundaryPZero_989) {
    // Should not crash, should return a valid (possibly infinite) result
    double result = normal_quantile(0.0);
    EXPECT_FALSE(std::isnan(result));
}

// Test boundary: p exactly 1
TEST_F(NormalQuantileTest_989, BoundaryPOne_989) {
    // Should not crash, should return a valid (possibly infinite) result
    double result = normal_quantile(1.0);
    EXPECT_FALSE(std::isnan(result));
}

// Test p = -1 returns 0 (out of range)
TEST_F(NormalQuantileTest_989, LargeNegativePReturnsZero_989) {
    double result = normal_quantile(-1.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test p = 2 returns 0 (out of range)
TEST_F(NormalQuantileTest_989, LargePositivePReturnsZero_989) {
    double result = normal_quantile(2.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test known quantile: p = 0.95 should give approximately 1.6449
TEST_F(NormalQuantileTest_989, KnownQuantile95_989) {
    double result = normal_quantile(0.95);
    EXPECT_NEAR(result, 1.6449, 1e-3);
}

// Test known quantile: p = 0.99 should give approximately 2.3263
TEST_F(NormalQuantileTest_989, KnownQuantile99_989) {
    double result = normal_quantile(0.99);
    EXPECT_NEAR(result, 2.3263, 1e-3);
}
