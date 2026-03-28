// File: tests/estimate_clock_cost_test_910.cpp

#include <gtest/gtest.h>

// Include the amalgamated header that defines:
// - Catch::Benchmark::Detail::estimate_clock_cost
// - Catch::Benchmark::FDuration
// - Catch::Benchmark::Detail::{mean, classify_outliers, run_for_at_least, measure}
// - Catch::Benchmark::Detail::EnvironmentEstimate
#include "Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark;

namespace {

// A controllable steady "clock" that advances by a fixed step on every now().
// This lets us make the time measured by Catch2 deterministic and fast.
struct FakeClock {
    using duration   = FDuration;
    using rep        = duration::rep;
    using period     = duration::period;
    using time_point = std::chrono::time_point<FakeClock, duration>;
    static constexpr bool is_steady = true;

    static void set_step(duration d) { step_ = d; }
    static void reset() { current_ = duration::zero(); }

    static time_point now() {
        current_ += step_;
        return time_point(current_);
    }

    // Expose the configured step so tests can compare against it.
    static duration step() { return step_; }

private:
    static inline duration step_{std::chrono::microseconds(100)}; // default 100 µs
    static inline duration current_{duration::zero()};
};

// Helper: compute relative error (non-negative).
template <typename Duration>
double rel_error(Duration observed, Duration expected) {
    const double e = expected.count();
    const double o = observed.count();
    if (e == 0.0) return (o == 0.0) ? 0.0 : 1.0;
    return std::abs(o - e) / std::abs(e);
}

} // namespace

// Test fixture: reset the fake clock before each test.
class EstimateClockCostTest_910 : public ::testing::Test {
protected:
    void SetUp() override {
        FakeClock::reset();
    }
};

// [Normal operation] The estimated mean per-Clock::now() should be
// close to the configured FakeClock step.
TEST_F(EstimateClockCostTest_910, MeanRoughlyEqualsPerNowCost_910) {
    FakeClock::set_step(std::chrono::microseconds(50)); // 50 µs per now()
    // 'resolution' only affects sample count; choose any reasonable value.
    const auto resolution = std::chrono::nanoseconds(100);

    auto result = Catch::Benchmark::Detail::estimate_clock_cost<FakeClock>(resolution);

    // Observable behavior: result.mean is a per-iteration (i.e., per now()) cost.
    // Allow a generous tolerance because other framework overhead may exist.
    const auto expected = FakeClock::step();
    const double tol = 0.30; // 30% relative tolerance
    EXPECT_LE(rel_error(result.mean, expected), tol)
        << "mean=" << result.mean.count() << " vs step=" << expected.count();
}

// [Scaling behavior] If the cost of Clock::now() doubles, the estimated mean
// should approximately double as well.
TEST_F(EstimateClockCostTest_910, MeanScalesWithClockStep_910) {
    const auto base = std::chrono::microseconds(20);
    const auto dbl  = base * 2;

    // Run with base step
    FakeClock::set_step(base);
    auto r1 = Catch::Benchmark::Detail::estimate_clock_cost<FakeClock>(std::chrono::nanoseconds(100));

    // Reset the fake clock timeline and run with doubled step
    FakeClock::reset();
    FakeClock::set_step(dbl);
    auto r2 = Catch::Benchmark::Detail::estimate_clock_cost<FakeClock>(std::chrono::nanoseconds(100));

    // Compare ratio r2.mean / r1.mean to 2.0 within tolerance
    const double ratio = r2.mean.count() / r1.mean.count();
    const double tol_ratio = 0.30; // 30% tolerance on scaling
    EXPECT_NEAR(ratio, 2.0, 2.0 * tol_ratio) << "ratio=" << ratio;
}

// [Boundary-ish / stability] Changing 'resolution' (which influences sample count)
// should not significantly change the estimated per-call mean.
TEST_F(EstimateClockCostTest_910, MeanStableAcrossDifferentResolutions_910) {
    FakeClock::set_step(std::chrono::microseconds(80));

    // Very small resolution => potentially more samples (bounded by time limit)
    auto r_small = Catch::Benchmark::Detail::estimate_clock_cost<FakeClock>(std::chrono::nanoseconds(1));

    // Very large resolution => time limit likely capped by 1s global, but observable output (mean) should remain similar
    auto r_large = Catch::Benchmark::Detail::estimate_clock_cost<FakeClock>(std::chrono::seconds(5));

    // Both should be close to the per-now step, and also close to each other.
    const auto expected = FakeClock::step();
    const double tol_mean = 0.35; // allow some slack
    EXPECT_LE(rel_error(r_small.mean, expected), tol_mean);
    EXPECT_LE(rel_error(r_large.mean, expected), tol_mean);

    // Additionally, small vs large should not diverge wildly
    const double rel_between = std::abs(r_small.mean.count() - r_large.mean.count()) /
                               std::max(std::abs(r_small.mean.count()), std::abs(r_large.mean.count()));
    EXPECT_LE(rel_between, 0.35);
}

// [Basic sanity] The function returns an outlier classification along with the mean.
// We don't assert its internal fields (black-box), only that a call succeeds and
// the mean is a finite, non-negative duration.
TEST_F(EstimateClockCostTest_910, ReturnsFiniteNonNegativeMeanAndOutliers_910) {
    FakeClock::set_step(std::chrono::microseconds(30));
    auto result = Catch::Benchmark::Detail::estimate_clock_cost<FakeClock>(std::chrono::microseconds(10));

    // Non-negative & finite mean check
    EXPECT_GE(result.mean.count(), 0.0);
    EXPECT_TRUE(std::isfinite(result.mean.count()));
    // We intentionally do not inspect result.outliers internals (black-box).
}
