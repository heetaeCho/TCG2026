// File: timer_getElapsedSeconds_test.cpp
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

// SUT headers
#include "catch2/catch_timer.hpp"

using Catch::Timer;

// Helper: small sleeps to create observable elapsed time without being flaky
static void SleepForMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// [Normal operation] After start, elapsed seconds should be small but >= 0
TEST(TimerTest_462, ReturnsReasonableAfterStart_462) {
    Timer t;
    t.start();

    // Immediately after start, elapsed time should be near zero but non-negative.
    const double s0 = t.getElapsedSeconds();
    EXPECT_GE(s0, 0.0);

    // After ~50ms, elapsed time should be within a reasonable bound.
    SleepForMs(50);
    const double s1 = t.getElapsedSeconds();

    // Expect at least ~40ms and less than 0.5s to keep test robust across platforms.
    EXPECT_GE(s1, 0.040);
    EXPECT_LT(s1, 0.500);
}

// [Boundary-ish / monotonicity] Multiple reads should be non-decreasing over time
TEST(TimerTest_462, MonotonicIncrease_462) {
    Timer t;
    t.start();

    const double s0 = t.getElapsedSeconds();
    SleepForMs(10);
    const double s1 = t.getElapsedSeconds();
    SleepForMs(10);
    const double s2 = t.getElapsedSeconds();

    EXPECT_LE(s0, s1);
    EXPECT_LE(s1, s2);
}

// [External interaction verification via public API agreement]
// getElapsedSeconds should agree with getElapsedMicroseconds within a small tolerance
// because getElapsedSeconds is defined as microseconds / 1'000'000 via the public API.
TEST(TimerTest_462, ConsistentWithMicroseconds_462) {
    Timer t;
    t.start();

    SleepForMs(20);

    // Read both values; they are taken at slightly different instants, so allow slack.
    const double secs = t.getElapsedSeconds();
    const uint64_t micros = t.getElapsedMicroseconds();

    // Convert seconds to microseconds and compare with a tolerance to account for
    // the time between calls and scheduling jitter.
    const double secs_to_micros = secs * 1'000'000.0;

    // Allow up to 20ms jitter between the two readings.
    const double tolerance_us = 20'000.0;

    EXPECT_NEAR(secs_to_micros, static_cast<double>(micros), tolerance_us);
}
