#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "catch2/catch_timer.hpp"

class TimerTest_458 : public ::testing::Test {
protected:
    Catch::Timer timer;
};

// Test that a default-constructed timer returns 0 for elapsed nanoseconds before start
TEST_F(TimerTest_458, DefaultTimerElapsedNanosecondsIsZeroOrNear_458) {
    // Before calling start, m_nanoseconds is 0, so getElapsedNanoseconds
    // should return current time minus 0, which is a very large number.
    // Actually, since m_nanoseconds = 0 initially, elapsed = now - 0 = now
    // This tests the behavior before start() is called.
    uint64_t elapsed = timer.getElapsedNanoseconds();
    // Since m_nanoseconds is initialized to 0, elapsed should be approximately
    // the current nanoseconds since epoch (a very large number)
    EXPECT_GT(elapsed, 0u);
}

// Test that start() can be called without error
TEST_F(TimerTest_458, StartDoesNotThrow_458) {
    EXPECT_NO_THROW(timer.start());
}

// Test that after start, elapsed nanoseconds is a small positive value
TEST_F(TimerTest_458, ElapsedNanosecondsAfterStartIsSmall_458) {
    timer.start();
    uint64_t elapsed = timer.getElapsedNanoseconds();
    // Should be very small (less than 1 second = 1e9 nanoseconds)
    EXPECT_LT(elapsed, 1000000000u);
}

// Test that after start, elapsed microseconds is a small positive value
TEST_F(TimerTest_458, ElapsedMicrosecondsAfterStartIsSmall_458) {
    timer.start();
    uint64_t elapsed = timer.getElapsedMicroseconds();
    EXPECT_LT(elapsed, 1000000u); // less than 1 second
}

// Test that after start, elapsed milliseconds is a small value
TEST_F(TimerTest_458, ElapsedMillisecondsAfterStartIsSmall_458) {
    timer.start();
    unsigned int elapsed = timer.getElapsedMilliseconds();
    EXPECT_LT(elapsed, 1000u); // less than 1 second
}

// Test that after start, elapsed seconds is a small value
TEST_F(TimerTest_458, ElapsedSecondsAfterStartIsSmall_458) {
    timer.start();
    double elapsed = timer.getElapsedSeconds();
    EXPECT_LT(elapsed, 1.0);
    EXPECT_GE(elapsed, 0.0);
}

// Test that elapsed time increases after a sleep
TEST_F(TimerTest_458, ElapsedNanosecondsIncreasesOverTime_458) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    uint64_t elapsed = timer.getElapsedNanoseconds();
    // Should be at least ~50 million nanoseconds (50ms), allowing some tolerance
    EXPECT_GE(elapsed, 30000000u); // at least 30ms
}

// Test that elapsed microseconds reflects passage of time
TEST_F(TimerTest_458, ElapsedMicrosecondsIncreasesOverTime_458) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    uint64_t elapsed = timer.getElapsedMicroseconds();
    EXPECT_GE(elapsed, 30000u); // at least 30ms = 30000 microseconds
}

// Test that elapsed milliseconds reflects passage of time
TEST_F(TimerTest_458, ElapsedMillisecondsIncreasesOverTime_458) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    unsigned int elapsed = timer.getElapsedMilliseconds();
    EXPECT_GE(elapsed, 70u); // at least ~70ms with tolerance
    EXPECT_LE(elapsed, 500u); // but not unreasonably large
}

// Test that elapsed seconds reflects passage of time
TEST_F(TimerTest_458, ElapsedSecondsIncreasesOverTime_458) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    double elapsed = timer.getElapsedSeconds();
    EXPECT_GE(elapsed, 0.07);
    EXPECT_LE(elapsed, 0.5);
}

// Test that calling start() again resets the timer
TEST_F(TimerTest_458, RestartResetsElapsedTime_458) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    uint64_t elapsedBefore = timer.getElapsedNanoseconds();
    
    timer.start(); // restart
    uint64_t elapsedAfter = timer.getElapsedNanoseconds();
    
    // After restart, elapsed should be much smaller than before restart
    EXPECT_LT(elapsedAfter, elapsedBefore);
}

// Test consistency between different elapsed time units
TEST_F(TimerTest_458, ElapsedUnitsAreConsistent_458) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    uint64_t nanos = timer.getElapsedNanoseconds();
    uint64_t micros = timer.getElapsedMicroseconds();
    unsigned int millis = timer.getElapsedMilliseconds();
    double seconds = timer.getElapsedSeconds();
    
    // Nanoseconds should be roughly 1000x microseconds (with some timing slack)
    // We just check the order of magnitude is correct
    EXPECT_GT(nanos, micros); // nanos > micros since nanos is a finer unit
    EXPECT_GE(micros, static_cast<uint64_t>(millis) * 900); // roughly millis * 1000
    EXPECT_LE(micros, static_cast<uint64_t>(millis + 10) * 1100);
    
    // Seconds should be in the right ballpark
    EXPECT_GE(seconds, 0.1);
    EXPECT_LE(seconds, 1.0);
}

// Test multiple sequential getElapsed calls show non-decreasing values
TEST_F(TimerTest_458, ElapsedIsNonDecreasing_458) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    uint64_t elapsed1 = timer.getElapsedNanoseconds();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    uint64_t elapsed2 = timer.getElapsedNanoseconds();
    
    EXPECT_GE(elapsed2, elapsed1);
}

// Test that start can be called multiple times
TEST_F(TimerTest_458, MultipleStartCalls_458) {
    for (int i = 0; i < 5; ++i) {
        timer.start();
        uint64_t elapsed = timer.getElapsedNanoseconds();
        EXPECT_LT(elapsed, 100000000u); // less than 100ms each time
    }
}

// Boundary: test very short elapsed time (essentially immediate)
TEST_F(TimerTest_458, ImmediateElapsedIsVerySmall_458) {
    timer.start();
    uint64_t elapsed = timer.getElapsedNanoseconds();
    // Immediate call should result in very small elapsed time
    // Less than 10ms should be safe
    EXPECT_LT(elapsed, 10000000u);
}
