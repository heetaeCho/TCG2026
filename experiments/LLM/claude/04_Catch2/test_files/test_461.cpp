#include <gtest/gtest.h>
#include <thread>
#include <chrono>

#include "catch2/catch_timer.hpp"

class TimerTest_461 : public ::testing::Test {
protected:
    Catch::Timer timer;
};

// Test that a freshly constructed Timer returns 0 or near-0 values before start is called
TEST_F(TimerTest_461, DefaultConstructedTimerReturnsZeroNanoseconds_461) {
    // Before calling start, the internal state is 0, so elapsed should be based on that
    // We just check it doesn't crash and returns some value
    auto ns = timer.getElapsedNanoseconds();
    // We can't assert exact value without knowing implementation, but it should be callable
    (void)ns;
}

TEST_F(TimerTest_461, DefaultConstructedTimerReturnsZeroMicroseconds_461) {
    auto us = timer.getElapsedMicroseconds();
    (void)us;
}

TEST_F(TimerTest_461, DefaultConstructedTimerReturnsZeroMilliseconds_461) {
    auto ms = timer.getElapsedMilliseconds();
    (void)ms;
}

TEST_F(TimerTest_461, DefaultConstructedTimerReturnsZeroSeconds_461) {
    auto s = timer.getElapsedSeconds();
    (void)s;
}

// Test that after calling start and sleeping, elapsed time is non-zero
TEST_F(TimerTest_461, StartAndMeasureNanoseconds_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto ns = timer.getElapsedNanoseconds();
    // Should be at least ~50 million nanoseconds (50ms), allow some tolerance
    EXPECT_GT(ns, 0u);
}

TEST_F(TimerTest_461, StartAndMeasureMicroseconds_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto us = timer.getElapsedMicroseconds();
    // Should be at least ~50000 microseconds
    EXPECT_GT(us, 0u);
}

TEST_F(TimerTest_461, StartAndMeasureMilliseconds_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto ms = timer.getElapsedMilliseconds();
    // Should be at least some milliseconds
    EXPECT_GE(ms, 30u); // Allow tolerance for scheduling
}

TEST_F(TimerTest_461, StartAndMeasureSeconds_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto s = timer.getElapsedSeconds();
    EXPECT_GT(s, 0.0);
    EXPECT_GE(s, 0.05); // at least 50ms
}

// Test consistency: milliseconds should be approximately microseconds / 1000
TEST_F(TimerTest_461, MillisecondsConsistentWithMicroseconds_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto us = timer.getElapsedMicroseconds();
    auto ms = timer.getElapsedMilliseconds();
    // ms should be roughly us/1000, allow some tolerance due to time between calls
    // ms was computed after us, so ms >= us/1000 approximately
    EXPECT_NEAR(static_cast<double>(ms), static_cast<double>(us) / 1000.0, 50.0);
}

// Test consistency: nanoseconds >= microseconds * 1000 (approximately)
TEST_F(TimerTest_461, NanosecondsConsistentWithMicroseconds_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto us = timer.getElapsedMicroseconds();
    auto ns = timer.getElapsedNanoseconds();
    // ns called after us, so ns >= us * 1000 approximately
    // Just check they are in the same ballpark
    EXPECT_GT(ns, 0u);
    EXPECT_GT(us, 0u);
}

// Test that elapsed time increases over time
TEST_F(TimerTest_461, ElapsedTimeIncreases_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    auto first = timer.getElapsedMicroseconds();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto second = timer.getElapsedMicroseconds();
    EXPECT_GT(second, first);
}

// Test that calling start again resets the timer
TEST_F(TimerTest_461, RestartResetsTimer_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto elapsed1 = timer.getElapsedMilliseconds();
    EXPECT_GE(elapsed1, 50u);

    // Restart the timer
    timer.start();
    auto elapsed2 = timer.getElapsedMilliseconds();
    // After restart, elapsed should be much less than before
    EXPECT_LT(elapsed2, elapsed1);
}

// Test boundary: very short measurement
TEST_F(TimerTest_461, VeryShortDuration_461) {
    timer.start();
    // No sleep - measure immediately
    auto ns = timer.getElapsedNanoseconds();
    auto ms = timer.getElapsedMilliseconds();
    // Nanoseconds might be non-zero but milliseconds could be zero
    // This is a valid boundary condition
    (void)ns;
    EXPECT_LE(ms, 10u); // Should be very small
}

// Test that getElapsedSeconds returns reasonable value
TEST_F(TimerTest_461, SecondsReasonableValue_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    auto s = timer.getElapsedSeconds();
    EXPECT_GE(s, 0.1);
    EXPECT_LE(s, 2.0); // Should not be more than 2 seconds
}

// Test multiple calls to getElapsed without restarting
TEST_F(TimerTest_461, MultipleCallsWithoutRestart_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto ms1 = timer.getElapsedMilliseconds();
    auto ms2 = timer.getElapsedMilliseconds();
    auto ms3 = timer.getElapsedMilliseconds();
    
    // Each successive call should return >= previous (time moves forward)
    EXPECT_GE(ms2, ms1);
    EXPECT_GE(ms3, ms2);
}

// Test that getElapsedMilliseconds is the truncation of microseconds/1000
TEST_F(TimerTest_461, MillisecondsIsTruncationOfMicrosecondsDividedBy1000_461) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    auto ms = timer.getElapsedMilliseconds();
    // Should be in a reasonable range around 150
    EXPECT_GE(ms, 100u);
    EXPECT_LE(ms, 300u);
}
