#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Declaration of the function under test
namespace Catch {
namespace Benchmark {
namespace Detail {
double normal_cdf(double x);
}
}
}

using Catch::Benchmark::Detail::normal_cdf;

class NormalCdfTest_987 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-10;
};

// Test that CDF at x=0 returns 0.5 (the median of the standard normal)
TEST_F(NormalCdfTest_987, AtZeroReturnsHalf_987) {
    double result = normal_cdf(0.0);
    EXPECT_NEAR(result, 0.5, kTolerance);
}

// Test that CDF at x=1 returns approximately 0.8413
TEST_F(NormalCdfTest_987, AtOneReturnsExpectedValue_987) {
    double result = normal_cdf(1.0);
    EXPECT_NEAR(result, 0.8413447460685429, 1e-10);
}

// Test that CDF at x=-1 returns approximately 0.1587
TEST_F(NormalCdfTest_987, AtNegativeOneReturnsExpectedValue_987) {
    double result = normal_cdf(-1.0);
    EXPECT_NEAR(result, 0.15865525393145702, 1e-10);
}

// Test symmetry: CDF(x) + CDF(-x) = 1
TEST_F(NormalCdfTest_987, SymmetryProperty_987) {
    double x = 1.5;
    double cdf_pos = normal_cdf(x);
    double cdf_neg = normal_cdf(-x);
    EXPECT_NEAR(cdf_pos + cdf_neg, 1.0, kTolerance);
}

// Test symmetry at various points
TEST_F(NormalCdfTest_987, SymmetryAtMultiplePoints_987) {
    std::vector<double> test_values = {0.1, 0.5, 1.0, 2.0, 3.0, 4.0};
    for (double x : test_values) {
        EXPECT_NEAR(normal_cdf(x) + normal_cdf(-x), 1.0, kTolerance)
            << "Symmetry failed for x = " << x;
    }
}

// Test that CDF at x=2 returns approximately 0.9772
TEST_F(NormalCdfTest_987, AtTwoReturnsExpectedValue_987) {
    double result = normal_cdf(2.0);
    EXPECT_NEAR(result, 0.9772498680518208, 1e-10);
}

// Test that CDF at x=-2 returns approximately 0.0228
TEST_F(NormalCdfTest_987, AtNegativeTwoReturnsExpectedValue_987) {
    double result = normal_cdf(-2.0);
    EXPECT_NEAR(result, 0.022750131948179195, 1e-10);
}

// Test that CDF at x=3 returns approximately 0.99865
TEST_F(NormalCdfTest_987, AtThreeReturnsExpectedValue_987) {
    double result = normal_cdf(3.0);
    EXPECT_NEAR(result, 0.9986501019683699, 1e-10);
}

// Test that CDF at x=-3 returns approximately 0.00135
TEST_F(NormalCdfTest_987, AtNegativeThreeReturnsExpectedValue_987) {
    double result = normal_cdf(-3.0);
    EXPECT_NEAR(result, 0.0013498980316300946, 1e-10);
}

// Test monotonicity: CDF should be non-decreasing
TEST_F(NormalCdfTest_987, MonotonicallyIncreasing_987) {
    double prev = normal_cdf(-10.0);
    for (double x = -9.0; x <= 10.0; x += 0.5) {
        double curr = normal_cdf(x);
        EXPECT_GE(curr, prev) << "Monotonicity violated at x = " << x;
        prev = curr;
    }
}

// Test that CDF approaches 1 for large positive values
TEST_F(NormalCdfTest_987, ApproachesOneForLargePositive_987) {
    double result = normal_cdf(10.0);
    EXPECT_NEAR(result, 1.0, 1e-10);
}

// Test that CDF approaches 0 for large negative values
TEST_F(NormalCdfTest_987, ApproachesZeroForLargeNegative_987) {
    double result = normal_cdf(-10.0);
    EXPECT_NEAR(result, 0.0, 1e-10);
}

// Test that CDF is always in range [0, 1]
TEST_F(NormalCdfTest_987, ResultAlwaysInUnitInterval_987) {
    std::vector<double> test_values = {-100.0, -10.0, -5.0, -1.0, 0.0, 1.0, 5.0, 10.0, 100.0};
    for (double x : test_values) {
        double result = normal_cdf(x);
        EXPECT_GE(result, 0.0) << "CDF below 0 at x = " << x;
        EXPECT_LE(result, 1.0) << "CDF above 1 at x = " << x;
    }
}

// Test with small positive value
TEST_F(NormalCdfTest_987, SmallPositiveValue_987) {
    double result = normal_cdf(0.01);
    EXPECT_GT(result, 0.5);
    EXPECT_NEAR(result, 0.50398936298, 1e-8);
}

// Test with small negative value
TEST_F(NormalCdfTest_987, SmallNegativeValue_987) {
    double result = normal_cdf(-0.01);
    EXPECT_LT(result, 0.5);
    EXPECT_NEAR(result, 0.49601063702, 1e-8);
}

// Test at x=0.5
TEST_F(NormalCdfTest_987, AtHalfReturnsExpectedValue_987) {
    double result = normal_cdf(0.5);
    EXPECT_NEAR(result, 0.6914624612740131, 1e-10);
}

// Test at x=-0.5
TEST_F(NormalCdfTest_987, AtNegativeHalfReturnsExpectedValue_987) {
    double result = normal_cdf(-0.5);
    EXPECT_NEAR(result, 0.3085375387259869, 1e-10);
}

// Test very large positive value
TEST_F(NormalCdfTest_987, VeryLargePositiveValue_987) {
    double result = normal_cdf(37.0);
    EXPECT_EQ(result, 1.0);
}

// Test very large negative value
TEST_F(NormalCdfTest_987, VeryLargeNegativeValue_987) {
    double result = normal_cdf(-37.0);
    EXPECT_EQ(result, 0.0);
}

// Test at 1.96 (common z-score for 95% confidence)
TEST_F(NormalCdfTest_987, At196ReturnsExpectedValue_987) {
    double result = normal_cdf(1.96);
    EXPECT_NEAR(result, 0.9750021048517796, 1e-10);
}

// Test at 2.576 (common z-score for 99% confidence)
TEST_F(NormalCdfTest_987, At2576ReturnsExpectedValue_987) {
    double result = normal_cdf(2.576);
    EXPECT_NEAR(result, 0.9950015, 1e-5);
}

// Test with positive infinity
TEST_F(NormalCdfTest_987, PositiveInfinity_987) {
    double result = normal_cdf(std::numeric_limits<double>::infinity());
    EXPECT_EQ(result, 1.0);
}

// Test with negative infinity
TEST_F(NormalCdfTest_987, NegativeInfinity_987) {
    double result = normal_cdf(-std::numeric_limits<double>::infinity());
    EXPECT_EQ(result, 0.0);
}

// Test with NaN input (should return NaN)
TEST_F(NormalCdfTest_987, NaNInput_987) {
    double result = normal_cdf(std::numeric_limits<double>::quiet_NaN());
    EXPECT_TRUE(std::isnan(result));
}

// Test that result at fractional value is reasonable
TEST_F(NormalCdfTest_987, FractionalValue_987) {
    double result = normal_cdf(0.674);
    // 0.674 is approximately the 75th percentile z-score
    EXPECT_NEAR(result, 0.74986, 1e-4);
}
