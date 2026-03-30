// File: tests/normal_quantile_tests_989.cpp

#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Forward declaration only; we treat the implementation as a black box.
namespace Catch { namespace Benchmark { namespace Detail {
    double normal_quantile(double p);
}}}

using Catch::Benchmark::Detail::normal_quantile;

namespace {

constexpr double kTightTol = 1e-12;   // For well-conditioned probabilities
constexpr double kLooseTol = 1e-10;   // Slightly looser where values are large in magnitude

} // namespace

// --- Normal operation: known quantile points ---
TEST(NormalQuantileTest_989, MidpointIsZero_989) {
    // For a standard normal, median (p=0.5) is 0
    EXPECT_NEAR(normal_quantile(0.5), 0.0, kTightTol);
}

TEST(NormalQuantileTest_989, KnownSigmaPoints_989) {
    // 1-sigma
    EXPECT_NEAR(normal_quantile(0.8413447460685429),  1.0, kTightTol);
    EXPECT_NEAR(normal_quantile(0.15865525393145707), -1.0, kTightTol);

    // 2-sigma
    EXPECT_NEAR(normal_quantile(0.9772498680518208),   2.0, kTightTol);
    EXPECT_NEAR(normal_quantile(0.02275013194817921), -2.0, kTightTol);

    // 3-sigma (allow a touch looser because magnitudes are larger)
    EXPECT_NEAR(normal_quantile(0.9986501019683699),   3.0, kLooseTol);
    EXPECT_NEAR(normal_quantile(0.0013498980316301035), -3.0, kLooseTol);
}

// --- Normal operation: symmetry & monotonicity ---
TEST(NormalQuantileTest_989, SymmetryAroundHalf_989) {
    const double ps[] = {0.1, 0.2, 0.3, 0.4};
    for (double p : ps) {
        double q  = normal_quantile(p);
        double qm = normal_quantile(1.0 - p);
        // For a symmetric distribution, Q(p) = -Q(1 - p)
        EXPECT_NEAR(q, -qm, kLooseTol) << "p=" << p;
    }
}

TEST(NormalQuantileTest_989, MonotonicIncreasingInP_989) {
    const double ps[] = {0.001, 0.01, 0.1, 0.2, 0.5, 0.8, 0.9, 0.99};
    for (size_t i = 1; i < std::size(ps); ++i) {
        double prev = normal_quantile(ps[i - 1]);
        double curr = normal_quantile(ps[i]);
        EXPECT_LT(prev, curr) << "Expected Q(" << ps[i-1] << ") < Q(" << ps[i] << ")";
    }
}

// --- Boundary conditions: exactly at the ends ---
TEST(NormalQuantileTest_989, EndsAreNotNaNAndRespectOrder_989) {
    // We do not assert exact values at p=0 or p=1 (could be +/-inf or large magnitude),
    // but we can assert sane ordering vs. nearby interior points and that results are not NaN.
    const double tiny = 1e-12;
    const double near_low  = normal_quantile(tiny);
    const double near_high = normal_quantile(1.0 - tiny);

    const double at_low  = normal_quantile(0.0);
    const double at_high = normal_quantile(1.0);

    EXPECT_FALSE(std::isnan(at_low));
    EXPECT_FALSE(std::isnan(at_high));

    // Q(0) should be <= Q(tiny); Q(1) should be >= Q(1 - tiny)
    EXPECT_LE(at_low,  near_low);
    EXPECT_GE(at_high, near_high);
}

// --- Exceptional / error cases: out-of-range inputs ---
// The implementation asserts and returns 0.0 when p is out of [0, 1].
// We cannot observe the assert in Release, but we can validate the return value.
TEST(NormalQuantileTest_989, OutOfRangeReturnsZero_989) {
    EXPECT_DOUBLE_EQ(normal_quantile(-1e-9), 0.0);
    EXPECT_DOUBLE_EQ(normal_quantile(1.0 + 1e-9), 0.0);
}

// --- Additional sanity near tails without assuming exact values ---
TEST(NormalQuantileTest_989, TailsHaveLargeMagnitude_989) {
    // Closer to 0 => large negative; closer to 1 => large positive.
    // We don't depend on specific tail constants; just relative magnitude & sign.
    double q_loose_tail  = normal_quantile(1e-6);
    double q_tight_tail  = normal_quantile(1e-12);
    double q_hi_loose    = normal_quantile(1.0 - 1e-6);
    double q_hi_tight    = normal_quantile(1.0 - 1e-12);

    EXPECT_LT(q_loose_tail, 0.0);
    EXPECT_LT(q_tight_tail, q_loose_tail); // deeper into the left tail => more negative

    EXPECT_GT(q_hi_loose, 0.0);
    EXPECT_GT(q_hi_tight, q_hi_loose);     // deeper into the right tail => more positive
}
