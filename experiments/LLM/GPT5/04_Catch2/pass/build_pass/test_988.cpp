// File: tests/erfc_inv_tests_988.cpp
#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <vector>

// Forward declaration from the provided interface (no internal includes).
namespace Catch { namespace Benchmark { namespace Detail {
    double erfc_inv(double x);
}}}

namespace {
    // A tight but reasonable tolerance for double round-trips with std::erfc.
    // Adjust if your platform/libm needs a touch more wiggle room.
    constexpr double kTol = 1e-12;
}

using Catch::Benchmark::Detail::erfc_inv;

// -----------------------------
// Basic/normal behavior
// -----------------------------

TEST(ErfcInvTest_988, ReturnsZeroAtOne_988) {
    // erfc_inv(1) should be 0 exactly (maps to erf_inv(0))
    EXPECT_DOUBLE_EQ(0.0, erfc_inv(1.0));
}

TEST(ErfcInvTest_988, RoundTripThroughStdErfc_CommonPoints_988) {
    // For y in (0, 2), std::erfc(erfc_inv(y)) ~= y
    const std::vector<double> ys = {0.1, 0.2, 0.5, 1.0, 1.5, 1.9};
    for (double y : ys) {
        double z = erfc_inv(y);
        // Round-trip check: observable behavior against standard library erfc.
        EXPECT_NEAR(std::erfc(z), y, kTol) << "at y=" << y;
        // Also ensure the value returned is finite for interior points.
        EXPECT_TRUE(std::isfinite(z)) << "z should be finite for y=" << y;
    }
}

// -----------------------------
// Boundary & edge behavior
// -----------------------------

TEST(ErfcInvTest_988, DomainOutsideZeroToTwo_YieldsNaN_988) {
    // erfc maps R -> (0,2), so real inverse should be undefined outside [0,2].
    // We treat NaN as observable behavior here (no assumptions about exceptions).
    const std::vector<double> out_of_domain = {-1.0, -0.01, 2.01, 3.0};
    for (double y : out_of_domain) {
        double z = erfc_inv(y);
        EXPECT_TRUE(std::isnan(z)) << "Expected NaN for y=" << y << ", got " << z;
    }
}

TEST(ErfcInvTest_988, NearEdgesBehavesMonotoneAndFinite_988) {
    // Check relative ordering near edges without assuming exact values.
    // As y -> 0+, erfc_inv(y) grows large positive; as y -> 2-, it grows large negative.
    // We avoid extremely tiny deltas to keep things numerically stable.
    const double y_small  = 1e-6;
    const double y_mid_lo = 0.1;
    const double y_mid_hi = 1.9;
    const double y_large  = 2.0 - 1e-6;

    double z_small  = erfc_inv(y_small);
    double z_mid_lo = erfc_inv(y_mid_lo);
    double z_mid_hi = erfc_inv(y_mid_hi);
    double z_large  = erfc_inv(y_large);

    // For small y, z should be larger than at a more moderate y.
    EXPECT_GT(z_small, z_mid_lo);
    // For y near 2, z should be smaller (more negative) than at a moderate high y.
    EXPECT_LT(z_large, z_mid_hi);

    // Sanity: interior points should be finite.
    EXPECT_TRUE(std::isfinite(z_mid_lo));
    EXPECT_TRUE(std::isfinite(z_mid_hi));
}

// -----------------------------
// Functional properties (observable)
// -----------------------------

TEST(ErfcInvTest_988, SymmetryAroundOne_988) {
    // From erfc(x) + erfc(-x) = 2 (a known property), it follows
    // that erfc_inv(y) = -erfc_inv(2 - y). We verify numerically.
    const std::vector<double> ys = {0.2, 0.5, 0.8, 1.2, 1.7};
    for (double y : ys) {
        double a = erfc_inv(y);
        double b = erfc_inv(2.0 - y);
        EXPECT_NEAR(a, -b, 1e-13) << "at y=" << y;
    }
}

TEST(ErfcInvTest_988, MonotonicDecreasingOnZeroToTwo_988) {
    // erfc is strictly decreasing, so its (real) inverse is also decreasing.
    const std::vector<double> ys = {0.2, 0.4, 0.8, 1.2, 1.6};
    for (size_t i = 1; i < ys.size(); ++i) {
        double y_prev = ys[i - 1];
        double y_curr = ys[i];
        double z_prev = erfc_inv(y_prev);
        double z_curr = erfc_inv(y_curr);
        // y_prev < y_curr  =>  z_prev > z_curr
        EXPECT_GT(z_prev, z_curr) << "Expected erfc_inv to be decreasing: "
                                  << "y_prev=" << y_prev << " < y_curr=" << y_curr
                                  << " but z_prev=" << z_prev << " <= z_curr=" << z_curr;
    }
}
