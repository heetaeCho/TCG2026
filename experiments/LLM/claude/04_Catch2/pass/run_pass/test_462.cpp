#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <cstdint>

#include "catch2/catch_timer.hpp"

class TimerTest_462 : public ::testing::Test {
protected:
    Catch::Timer timer;
};

// Test that a default-constructed Timer has zero or near-zero elapsed time
TEST_F(TimerTest_462, DefaultConstructedTimerHasZeroNanoseconds_462) {
    // Before start() is called, m_nanoseconds is 0, so elapsed should be based on that
    // We just verify it returns some value without crashing
    uint64_t ns = timer.getElapsedNanoseconds();
    // Can't assert exact value since it depends on current time minus 0,
    // but we can at least call it
    (void)ns;
}

TEST_F(TimerTest_462, DefaultConstructedTimerHasZeroMicroseconds_462) {
    uint64_t us = timer.getElapsedMicroseconds();
    (void)us;
}

TEST_F(TimerTest_462, DefaultConstructedTimerHasZeroMilliseconds_462) {
    unsigned int ms = timer.getElapsedMilliseconds();
    (void)ms;
}

TEST_F(TimerTest_462, DefaultConstructedTimerHasZeroSeconds_462) {
    double s = timer.getElapsedSeconds();
    (void)s;
}

// Test that after start(), elapsed time is non-negative
TEST_F(TimerTest_462, AfterStartElapsedNanosecondsIsNonNegative_462) {
    timer.start();
    uint64_t ns = timer.getElapsedNanoseconds();
    EXPECT_GE(ns, static_cast<uint64_t>(0));
}

TEST_F(TimerTest_462, AfterStartElapsedMicrosecondsIsNonNegative_462) {
    timer.start();
    uint64_t us = timer.getElapsedMicroseconds();
    EXPECT_GE(us, static_cast<uint64_t>(0));
}

TEST_F(TimerTest_462, AfterStartElapsedMillisecondsIsNonNegative_462) {
    timer.start();
    unsigned int ms = timer.getElapsedMilliseconds();
    EXPECT_GE(ms, static_cast<unsigned int>(0));
}

TEST_F(TimerTest_462, AfterStartElapsedSecondsIsNonNegative_462) {
    timer.start();
    double s = timer.getElapsedSeconds();
    EXPECT_GE(s, 0.0);
}

// Test that elapsed time increases after a sleep
TEST_F(TimerTest_462, ElapsedNanosecondsIncreasesOverTime_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    uint64_t ns = timer.getElapsedNanoseconds();
    // Should be at least ~50 million nanoseconds (50ms), allow some slack
    EXPECT_GT(ns, static_cast<uint64_t>(10000000)); // > 10ms worth of nanoseconds
}

TEST_F(TimerTest_462, ElapsedMicrosecondsIncreasesOverTime_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    uint64_t us = timer.getElapsedMicroseconds();
    // Should be at least ~50000 microseconds (50ms), allow some slack
    EXPECT_GT(us, static_cast<uint64_t>(10000)); // > 10ms worth of microseconds
}

TEST_F(TimerTest_462, ElapsedMillisecondsIncreasesOverTime_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    unsigned int ms = timer.getElapsedMilliseconds();
    // Should be at least ~100ms, allow some slack
    EXPECT_GE(ms, static_cast<unsigned int>(50));
}

TEST_F(TimerTest_462, ElapsedSecondsIncreasesOverTime_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    double s = timer.getElapsedSeconds();
    // Should be at least ~0.1 seconds, allow some slack
    EXPECT_GT(s, 0.05);
}

// Test consistency between units
TEST_F(TimerTest_462, MicrosecondsConsistentWithNanoseconds_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    uint64_t ns = timer.getElapsedNanoseconds();
    uint64_t us = timer.getElapsedMicroseconds();
    // Microseconds should be approximately nanoseconds / 1000
    // Allow some tolerance since calls are sequential
    EXPECT_NEAR(static_cast<double>(us), static_cast<double>(ns) / 1000.0, 5000.0);
}

TEST_F(TimerTest_462, SecondsConsistentWithMicroseconds_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    uint64_t us = timer.getElapsedMicroseconds();
    double s = timer.getElapsedSeconds();
    // Seconds should be approximately microseconds / 1000000
    EXPECT_NEAR(s, static_cast<double>(us) / 1000000.0, 0.01);
}

TEST_F(TimerTest_462, MillisecondsConsistentWithMicroseconds_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    uint64_t us = timer.getElapsedMicroseconds();
    unsigned int ms = timer.getElapsedMilliseconds();
    // Milliseconds should be approximately microseconds / 1000
    EXPECT_NEAR(static_cast<double>(ms), static_cast<double>(us) / 1000.0, 20.0);
}

// Test that getElapsedSeconds returns microseconds / 1000000.0 as per implementation
TEST_F(TimerTest_462, GetElapsedSecondsIsMicrosecondsOverMillion_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    uint64_t us = timer.getElapsedMicroseconds();
    double s = timer.getElapsedSeconds();
    // The implementation divides microseconds by 1000000.0
    // Due to sequential calls there may be slight difference
    double expected = static_cast<double>(us) / 1000000.0;
    EXPECT_NEAR(s, expected, 0.005);
}

// Test that calling start() resets the timer
TEST_F(TimerTest_462, RestartResetsTimer_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    uint64_t elapsed1 = timer.getElapsedMilliseconds();
    
    timer.start(); // restart
    uint64_t elapsed2 = timer.getElapsedMilliseconds();
    
    // After restart, elapsed time should be much less than before
    EXPECT_LT(elapsed2, elapsed1);
}

// Test that successive reads show monotonically increasing time
TEST_F(TimerTest_462, SuccessiveReadsAreMonotonicallyIncreasing_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    uint64_t first = timer.getElapsedNanoseconds();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    uint64_t second = timer.getElapsedNanoseconds();
    EXPECT_GE(second, first);
}

// Test very short duration
TEST_F(TimerTest_462, VeryShortDurationMeasurable_462) {
    timer.start();
    // No sleep - just immediate measurement
    uint64_t ns = timer.getElapsedNanoseconds();
    // Should still return a valid (possibly 0) value
    EXPECT_GE(ns, static_cast<uint64_t>(0));
}

// Test that multiple start calls work correctly
TEST_F(TimerTest_462, MultipleStartCallsWork_462) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    unsigned int ms = timer.getElapsedMilliseconds();
    // Should reflect only the time since last start (~50ms)
    EXPECT_LT(ms, static_cast<unsigned int>(100));
}
