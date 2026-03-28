// Timer_test_459.cpp
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

// Assuming the Timer interface is available under this header path.
// If your project exposes a different include, adjust as needed.
#include "catch2/catch_timer.hpp"

using Catch::Timer;

class TimerTest_459 : public ::testing::Test {
protected:
    Timer timer;
};

// Verifies that right after start(), elapsed time is near-zero (non-negative and small).
TEST_F(TimerTest_459, StartsNearZero_459) {
    timer.start();

    // Check across all units for basic sanity.
    auto ns = timer.getElapsedNanoseconds();
    auto us = timer.getElapsedMicroseconds();
    auto ms = timer.getElapsedMilliseconds();
    auto s  = timer.getElapsedSeconds();

    // Non-negative in all units
    EXPECT_GE(ns, 0u);
    EXPECT_GE(us, 0u);
    EXPECT_GE(ms, 0u);
    EXPECT_GE(s, 0.0);

    // Immediately after start, elapsed should be small.
    // Use a generous upper bound to avoid CI flakiness on slow machines.
    EXPECT_LT(ms, 100u);
    EXPECT_LT(s, 0.2);
}

// Verifies that elapsed time increases as wall time passes.
TEST_F(TimerTest_459, IncreasesOverTime_459) {
    timer.start();

    auto t0_ns = timer.getElapsedNanoseconds();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    auto t1_ns = timer.getElapsedNanoseconds();

    EXPECT_LE(t0_ns, t1_ns);
}

// Verifies cross-unit consistency within generous tolerances
// (we only check observable outputs, not internal conversions).
TEST_F(TimerTest_459, CrossUnitConsistency_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    const uint64_t ns = timer.getElapsedNanoseconds();
    const uint64_t us = timer.getElapsedMicroseconds();
    const unsigned ms = timer.getElapsedMilliseconds();
    const double   s  = timer.getElapsedSeconds();

    // Convert everything to seconds for comparison.
    const double sec_from_ns = static_cast<double>(ns) / 1e9;
    const double sec_from_us = static_cast<double>(us) / 1e6;
    const double sec_from_ms = static_cast<double>(ms) / 1e3;

    // All should be within a small window of each other (allowing rounding & scheduler jitter).
    const double max_sec = std::max({sec_from_ns, sec_from_us, sec_from_ms, s});
    const double min_sec = std::min({sec_from_ns, sec_from_us, sec_from_ms, s});
    EXPECT_LE(max_sec - min_sec, 0.05); // 50ms tolerance
}

// Verifies a lower bound after a known sleep (observable behavior, not exact).
TEST_F(TimerTest_459, MillisecondLowerBoundAfterSleep_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    const unsigned ms = timer.getElapsedMilliseconds();

    // Should be at least close to the sleep duration; use a conservative lower bound
    // to tolerate platform scheduling variance.
    EXPECT_GE(ms, 10u);
}

// Verifies that calling start() again resets the baseline (observable via decreased elapsed).
TEST_F(TimerTest_459, RestartResetsElapsed_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    const unsigned before_restart_ms = timer.getElapsedMilliseconds();

    // Restart and elapsed should drop to a small value.
    timer.start();
    const unsigned after_restart_ms = timer.getElapsedMilliseconds();

    EXPECT_LT(after_restart_ms, before_restart_ms);
    EXPECT_LT(after_restart_ms, 100u);
}
