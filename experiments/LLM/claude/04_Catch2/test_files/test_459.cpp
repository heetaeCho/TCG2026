#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "catch2/catch_timer.hpp"

class TimerTest_459 : public ::testing::Test {
protected:
    Catch::Timer timer;
};

// Test that a default-constructed timer exists and can be used
TEST_F(TimerTest_459, DefaultConstruction_459) {
    // Timer should be constructible without issues
    Catch::Timer t;
    // No crash means success
}

// Test that start() can be called without error
TEST_F(TimerTest_459, StartDoesNotThrow_459) {
    EXPECT_NO_THROW(timer.start());
}

// Test that getElapsedNanoseconds returns a value after start
TEST_F(TimerTest_459, GetElapsedNanosecondsAfterStart_459) {
    timer.start();
    // Small sleep to ensure some time passes
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    uint64_t elapsed = timer.getElapsedNanoseconds();
    // At least some nanoseconds should have elapsed
    EXPECT_GT(elapsed, 0u);
}

// Test that getElapsedMicroseconds returns a value after start
TEST_F(TimerTest_459, GetElapsedMicrosecondsAfterStart_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    uint64_t elapsed = timer.getElapsedMicroseconds();
    // At least some microseconds should have elapsed (10ms = 10000us)
    EXPECT_GT(elapsed, 0u);
}

// Test that getElapsedMilliseconds returns a value after start
TEST_F(TimerTest_459, GetElapsedMillisecondsAfterStart_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    unsigned int elapsed = timer.getElapsedMilliseconds();
    // Should have at least some milliseconds elapsed
    EXPECT_GE(elapsed, 10u);  // Allow some slack for scheduling
}

// Test that getElapsedSeconds returns a value after start
TEST_F(TimerTest_459, GetElapsedSecondsAfterStart_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    double elapsed = timer.getElapsedSeconds();
    // Should be at least close to 0.1 seconds
    EXPECT_GT(elapsed, 0.0);
    EXPECT_GE(elapsed, 0.05);  // Allow slack
}

// Test that elapsed time increases over time
TEST_F(TimerTest_459, ElapsedTimeIncreasesOverTime_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    uint64_t first = timer.getElapsedNanoseconds();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    uint64_t second = timer.getElapsedNanoseconds();
    EXPECT_GT(second, first);
}

// Test that calling start again resets the timer
TEST_F(TimerTest_459, RestartResetsTimer_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    uint64_t beforeRestart = timer.getElapsedNanoseconds();
    
    timer.start();  // Restart
    // Immediately after restart, elapsed should be much smaller
    uint64_t afterRestart = timer.getElapsedNanoseconds();
    EXPECT_LT(afterRestart, beforeRestart);
}

// Test consistency between different time units
TEST_F(TimerTest_459, TimeUnitConsistency_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    uint64_t nanos = timer.getElapsedNanoseconds();
    uint64_t micros = timer.getElapsedMicroseconds();
    unsigned int millis = timer.getElapsedMilliseconds();
    double seconds = timer.getElapsedSeconds();
    
    // Nanoseconds should be roughly 1000x microseconds
    // Allow for time passing between calls
    EXPECT_GT(nanos, 0u);
    EXPECT_GT(micros, 0u);
    
    // Microseconds should be approximately nanos / 1000 (with some tolerance for time between calls)
    // micros was measured after nanos, so micros*1000 could be >= nanos
    // Just check order of magnitude
    EXPECT_NEAR(static_cast<double>(micros), static_cast<double>(nanos) / 1000.0, static_cast<double>(nanos) * 0.1);
    
    // Millis should be roughly micros / 1000
    EXPECT_GE(millis, 50u);  // At least 50ms given 100ms sleep
    
    // Seconds should be positive and roughly 0.1
    EXPECT_GT(seconds, 0.05);
    EXPECT_LT(seconds, 1.0);  // Shouldn't be more than 1 second
}

// Test very short elapsed time
TEST_F(TimerTest_459, VeryShortElapsedTime_459) {
    timer.start();
    // Immediately get elapsed - should be very small but non-negative (uint64_t)
    uint64_t elapsed = timer.getElapsedNanoseconds();
    // Just verify it doesn't wrap around (i.e., it's a reasonable small value)
    // Since it's uint64_t, any value is >= 0
    // It should be less than, say, 1 second worth of nanoseconds
    EXPECT_LT(elapsed, 1000000000u);  // Less than 1 second
}

// Test getElapsedMilliseconds returns unsigned int (boundary behavior)
TEST_F(TimerTest_459, MillisecondsIsUnsignedInt_459) {
    timer.start();
    unsigned int millis = timer.getElapsedMilliseconds();
    // Immediately after start, should be 0 or very small
    EXPECT_LT(millis, 1000u);
}

// Test multiple elapsed queries without restart
TEST_F(TimerTest_459, MultipleQueriesWithoutRestart_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    
    uint64_t e1 = timer.getElapsedNanoseconds();
    uint64_t e2 = timer.getElapsedNanoseconds();
    uint64_t e3 = timer.getElapsedNanoseconds();
    
    // Each subsequent call should return >= the previous
    EXPECT_GE(e2, e1);
    EXPECT_GE(e3, e2);
}

// Test that getElapsedSeconds returns a double with sub-second precision
TEST_F(TimerTest_459, SecondsHasSubSecondPrecision_459) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    double seconds = timer.getElapsedSeconds();
    
    // Should be between 0.1 and 0.5 (allowing for scheduling delays)
    EXPECT_GE(seconds, 0.1);
    EXPECT_LT(seconds, 0.5);
    
    // Should not be a whole number (has fractional part)
    // This verifies sub-second precision
    double fractional = seconds - static_cast<int>(seconds);
    EXPECT_GT(fractional, 0.0);
}
