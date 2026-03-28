// File: tests/normal_cdf_tests_987.cpp
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Forward declaration of the function under test (black-box style).
namespace Catch { namespace Benchmark { namespace Detail {
    double normal_cdf(double x);
}}}

namespace {
    constexpr double kTol = 1e-9; // numeric tolerance for double comparisons
    using Catch::Benchmark::Detail::normal_cdf;
}

// Normal operation: value at zero should be 0.5
TEST(NormalCdfTest_987, AtZeroIsHalf_987) {
    EXPECT_NEAR(normal_cdf(0.0), 0.5, kTol);
}

// Normal operation: check a few known reference points
TEST(NormalCdfTest_987, KnownValues_987) {
    // Reference values from standard normal CDF (double precision)
    EXPECT_NEAR(normal_cdf( 1.0), 0.8413447460685429, 1e-12);
    EXPECT_NEAR(normal_cdf(-1.0), 0.1586552539314571, 1e-12);
    EXPECT_NEAR(normal_cdf( 2.0), 0.9772498680518208, 1e-12);
    EXPECT_NEAR(normal_cdf(-2.0), 0.0227501319481792, 1e-12);
}

// Property-based observable behavior: symmetry Phi(-x) = 1 - Phi(x)
TEST(NormalCdfTest_987, SymmetryProperty_987) {
    const double xs[] = {0.1, 0.5, 1.0, 2.5, 5.0};
    for (double x : xs) {
        double p = normal_cdf(x);
        double q = normal_cdf(-x);
        EXPECT_NEAR(q, 1.0 - p, 1e-12) << "x=" << x;
    }
}

// Boundary behavior: very large magnitudes approach 0 or 1
TEST(NormalCdfTest_987, LimitsAtLargeMagnitude_987) {
    EXPECT_NEAR(normal_cdf( 10.0), 1.0, 1e-15);
    EXPECT_NEAR(normal_cdf(-10.0), 0.0, 1e-15);
}

// Monotonicity (observable via outputs): increasing x yields non-decreasing CDF
TEST(NormalCdfTest_987, MonotonicIncreasing_987) {
    const double xs[] = {-3.0, -1.0, 0.0, 1.0, 3.0};
    double prev = normal_cdf(xs[0]);
    for (size_t i = 1; i < sizeof(xs)/sizeof(xs[0]); ++i) {
        double cur = normal_cdf(xs[i]);
        // Strictly increasing for distinct x
        EXPECT_LT(prev, cur) << "x[i-1]=" << xs[i-1] << ", x[i]=" << xs[i];
        prev = cur;
    }
}

// Exceptional inputs (as observable through return): infinities and NaN
TEST(NormalCdfTest_987, InfinityAndNaNHandling_987) {
    // +inf -> 1, -inf -> 0
    EXPECT_EQ(normal_cdf(std::numeric_limits<double>::infinity()), 1.0);
    EXPECT_EQ(normal_cdf(-std::numeric_limits<double>::infinity()), 0.0);

    // NaN should propagate to NaN
    double nan_in = std::numeric_limits<double>::quiet_NaN();
    double nan_out = normal_cdf(nan_in);
    EXPECT_TRUE(std::isnan(nan_out));
}
