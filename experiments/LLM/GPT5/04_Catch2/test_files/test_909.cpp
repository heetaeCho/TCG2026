// File: tests/EstimateClockResolution_909.tests.cpp
#include <gtest/gtest.h>
#include <chrono>

// Include the real implementation (black-box)
#include "Catch2/extras/catch_amalgamated.hpp"

namespace cb = Catch::Benchmark;
namespace cbd = Catch::Benchmark::Detail;

// ---- Detection helpers to stay compatible with different Catch2 member names ----
namespace {
    // clock resolution accessor
    template <typename T>
    auto get_clock_resolution(const T& e) -> decltype((void)e.clockResolution, e.clockResolution) {
        return e.clockResolution;
    }
    template <typename T>
    auto get_clock_resolution(const T& e) -> decltype((void)e.clock_resolution, e.clock_resolution) {
        return e.clock_resolution;
    }

    // outliers accessor
    template <typename T>
    auto get_outliers(const T& e) -> decltype((void)e.outliers, e.outliers) {
        return e.outliers;
    }
    template <typename T>
    auto get_outliers(const T& e) -> decltype((void)e.outlierClassification, e.outlierClassification) {
        return e.outlierClassification;
    }

    // Duration-to-double helper for EXPECT comparisons
    template <typename Dur>
    double to_seconds(const Dur& d) {
        using Sec = std::chrono::duration<double>;
        return std::chrono::duration_cast<Sec>(d).count();
    }
}

// ------------------------------ Tests ------------------------------

using Steady = std::chrono::steady_clock;

// Normal operation: small-but-reasonable iteration count.
TEST(EstimateClockResolution_909, ReturnsPositiveResolution_Normal_909) {
    const int iterations = 16;

    auto estimate = cbd::estimate_clock_resolution<Steady>(iterations);

    // Verify duration is positive and finite (observable return property).
    const auto res = get_clock_resolution(estimate);
    EXPECT_GT(to_seconds(res), 0.0) << "Clock resolution should be > 0 seconds";

    // Verify we also got an outlier classification object back (observable presence).
    // We do not assert its internals; we only check the expression is well-formed.
    (void)get_outliers(estimate);
}

// Boundary: iterations == 1 should still succeed and produce a sane estimate.
TEST(EstimateClockResolution_909, WorksWithSingleIteration_Boundary_909) {
    const int iterations = 1;

    auto estimate = cbd::estimate_clock_resolution<Steady>(iterations);

    const auto res = get_clock_resolution(estimate);
    EXPECT_GT(to_seconds(res), 0.0) << "Even with 1 iteration, returned resolution should be positive";
    (void)get_outliers(estimate);
}

// Boundary: a larger iteration count (still modest) should not throw and should be positive.
TEST(EstimateClockResolution_909, HandlesLargerIterationCount_Boundary_909) {
    const int iterations = 256;

    // Should not throw and should yield a positive value.
    auto estimate = cbd::estimate_clock_resolution<Steady>(iterations);

    const auto res = get_clock_resolution(estimate);
    EXPECT_GT(to_seconds(res), 0.0);
    (void)get_outliers(estimate);
}

// Sanity: two consecutive calls should be in the same ballpark (not orders of magnitude apart).
// This does NOT assume any specific algorithm — it only guards against wildly unstable results.
TEST(EstimateClockResolution_909, ConsecutiveCallsAreReasonablyConsistent_Sanity_909) {
    const int iterations = 32;

    auto e1 = cbd::estimate_clock_resolution<Steady>(iterations);
    auto e2 = cbd::estimate_clock_resolution<Steady>(iterations);

    const double r1 = to_seconds(get_clock_resolution(e1));
    const double r2 = to_seconds(get_clock_resolution(e2));

    // Both positive
    ASSERT_GT(r1, 0.0);
    ASSERT_GT(r2, 0.0);

    // Not orders of magnitude apart (very generous factor to keep test robust across platforms)
    const double ratio = (r1 > r2) ? (r1 / r2) : (r2 / r1);
    EXPECT_LT(ratio, 20.0) << "Two back-to-back estimates should be within a generous factor";
}

// Smoke: ensure the function compiles/works with system_clock as well (template surface).
TEST(EstimateClockResolution_909, AcceptsDifferentClockTypes_Smoke_909) {
    auto estimate = cbd::estimate_clock_resolution<std::chrono::system_clock>(8);
    const auto res = get_clock_resolution(estimate);
    EXPECT_GT(to_seconds(res), 0.0);
    (void)get_outliers(estimate);
}
