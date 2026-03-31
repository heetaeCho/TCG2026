#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
#include <thread>
#include <atomic>
#include <vector>
#include <cmath>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark;
using namespace Catch::Benchmark::Detail;

namespace {

// A simple fake clock that increments by a fixed amount each call
struct FakeClock {
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<FakeClock, duration>;
    static constexpr bool is_steady = true;

    static std::atomic<rep>& counter() {
        static std::atomic<rep> c{0};
        return c;
    }

    static rep& increment() {
        static rep inc = 100; // 100 nanoseconds per call
        return inc;
    }

    static time_point now() {
        auto val = counter().fetch_add(increment());
        return time_point(duration(val));
    }

    static void reset(rep start_val = 0, rep inc = 100) {
        counter().store(start_val);
        increment() = inc;
    }
};

// A clock with very fast resolution (small increment)
struct FastClock {
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<FastClock, duration>;
    static constexpr bool is_steady = true;

    static std::atomic<rep>& counter() {
        static std::atomic<rep> c{0};
        return c;
    }

    static time_point now() {
        // Each call increments by 10 nanoseconds
        auto val = counter().fetch_add(10);
        return time_point(duration(val));
    }

    static void reset(rep start_val = 0) {
        counter().store(start_val);
    }
};

// A clock with larger increment to simulate slower clock
struct SlowClock {
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<SlowClock, duration>;
    static constexpr bool is_steady = true;

    static std::atomic<rep>& counter() {
        static std::atomic<rep> c{0};
        return c;
    }

    static time_point now() {
        // Each call increments by 1000 nanoseconds (1 microsecond)
        auto val = counter().fetch_add(1000);
        return time_point(duration(val));
    }

    static void reset(rep start_val = 0) {
        counter().store(start_val);
    }
};

} // anonymous namespace

class EstimateClockCostTest_910 : public ::testing::Test {
protected:
    void SetUp() override {
        FakeClock::reset();
        FastClock::reset();
        SlowClock::reset();
    }
};

// Test that estimate_clock_cost returns a result with a non-negative mean
TEST_F(EstimateClockCostTest_910, ReturnsMeanIsNonNegative_910) {
    FakeClock::reset(0, 100);
    FDuration resolution(std::chrono::nanoseconds(100));
    auto result = estimate_clock_cost<FakeClock>(resolution);
    EXPECT_GE(result.mean.count(), 0.0);
}

// Test that the result contains valid outlier classification
TEST_F(EstimateClockCostTest_910, ReturnsValidOutlierClassification_910) {
    FakeClock::reset(0, 100);
    FDuration resolution(std::chrono::nanoseconds(100));
    auto result = estimate_clock_cost<FakeClock>(resolution);
    // OutlierClassification should have non-negative fields
    EXPECT_GE(result.outliers.samples_seen, 0);
}

// Test with a fast clock (small resolution)
TEST_F(EstimateClockCostTest_910, FastClockProducesResult_910) {
    FastClock::reset();
    FDuration resolution(std::chrono::nanoseconds(10));
    auto result = estimate_clock_cost<FastClock>(resolution);
    EXPECT_GE(result.mean.count(), 0.0);
}

// Test with a slow clock (larger resolution)
TEST_F(EstimateClockCostTest_910, SlowClockProducesResult_910) {
    SlowClock::reset();
    FDuration resolution(std::chrono::nanoseconds(1000));
    auto result = estimate_clock_cost<SlowClock>(resolution);
    EXPECT_GE(result.mean.count(), 0.0);
}

// Test with very small resolution (boundary condition)
TEST_F(EstimateClockCostTest_910, VerySmallResolutionProducesResult_910) {
    FakeClock::reset(0, 50);
    FDuration resolution(std::chrono::nanoseconds(1));
    auto result = estimate_clock_cost<FakeClock>(resolution);
    EXPECT_GE(result.mean.count(), 0.0);
}

// Test with larger resolution value
TEST_F(EstimateClockCostTest_910, LargerResolutionProducesResult_910) {
    FakeClock::reset(0, 500);
    FDuration resolution(std::chrono::microseconds(100));
    auto result = estimate_clock_cost<FakeClock>(resolution);
    EXPECT_GE(result.mean.count(), 0.0);
}

// Test that mean is finite (not NaN or infinity)
TEST_F(EstimateClockCostTest_910, MeanIsFinite_910) {
    FakeClock::reset(0, 200);
    FDuration resolution(std::chrono::nanoseconds(200));
    auto result = estimate_clock_cost<FakeClock>(resolution);
    EXPECT_TRUE(std::isfinite(result.mean.count()));
}

// Test that outliers total is consistent
TEST_F(EstimateClockCostTest_910, OutliersTotalIsConsistent_910) {
    FakeClock::reset(0, 150);
    FDuration resolution(std::chrono::nanoseconds(150));
    auto result = estimate_clock_cost<FakeClock>(resolution);
    
    int total_classified = result.outliers.low_mild + result.outliers.low_severe +
                           result.outliers.high_mild + result.outliers.high_severe;
    EXPECT_GE(result.outliers.samples_seen, total_classified);
}

// Test that the function works with resolution equal to zero edge
TEST_F(EstimateClockCostTest_910, ZeroResolutionHandled_910) {
    FakeClock::reset(0, 100);
    // Very tiny resolution - the time_limit will be very small but should still work
    FDuration resolution(std::chrono::nanoseconds(0));
    // This might produce 0 samples via ceil(0/elapsed), but let's see the behavior
    // The function should still return without crashing
    auto result = estimate_clock_cost<FakeClock>(resolution);
    // Just verify it doesn't crash and returns something
    EXPECT_TRUE(std::isfinite(result.mean.count()) || std::isnan(result.mean.count()));
}

// Test consistent results with same clock configuration
TEST_F(EstimateClockCostTest_910, DeterministicClockGivesConsistentResults_910) {
    FakeClock::reset(0, 100);
    FDuration resolution(std::chrono::nanoseconds(100));
    auto result1 = estimate_clock_cost<FakeClock>(resolution);

    FakeClock::reset(0, 100);
    auto result2 = estimate_clock_cost<FakeClock>(resolution);

    // With a deterministic fake clock reset to the same state, results should be identical
    EXPECT_DOUBLE_EQ(result1.mean.count(), result2.mean.count());
}

// Test that all outlier fields are non-negative
TEST_F(EstimateClockCostTest_910, OutlierFieldsNonNegative_910) {
    FakeClock::reset(0, 100);
    FDuration resolution(std::chrono::nanoseconds(500));
    auto result = estimate_clock_cost<FakeClock>(resolution);
    
    EXPECT_GE(result.outliers.low_mild, 0);
    EXPECT_GE(result.outliers.low_severe, 0);
    EXPECT_GE(result.outliers.high_mild, 0);
    EXPECT_GE(result.outliers.high_severe, 0);
    EXPECT_GE(result.outliers.samples_seen, 0);
}
