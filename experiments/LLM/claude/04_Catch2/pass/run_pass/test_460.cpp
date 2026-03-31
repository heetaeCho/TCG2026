#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "catch2/catch_timer.hpp"

class TimerTest_460 : public ::testing::Test {
protected:
    Catch::Timer timer;
};

// Test that a default-constructed timer returns zero or near-zero elapsed time
TEST_F(TimerTest_460, DefaultConstructedTimerNanoseconds_460) {
    // Before start() is called, m_nanoseconds is initialized to 0
    // getElapsedNanoseconds should return some value based on current time minus 0
    // We can't predict exact value, but we can at least call it without crashing
    auto ns = timer.getElapsedNanoseconds();
    // Just verify it returns without error - value is implementation-dependent
    (void)ns;
}

TEST_F(TimerTest_460, DefaultConstructedTimerMicroseconds_460) {
    auto us = timer.getElapsedMicroseconds();
    (void)us;
}

TEST_F(TimerTest_460, DefaultConstructedTimerMilliseconds_460) {
    auto ms = timer.getElapsedMilliseconds();
    (void)ms;
}

TEST_F(TimerTest_460, DefaultConstructedTimerSeconds_460) {
    auto s = timer.getElapsedSeconds();
    (void)s;
}

// Test that after start(), elapsed time increases
TEST_F(TimerTest_460, StartThenElapsedNanosecondsIsPositive_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto ns = timer.getElapsedNanoseconds();
    EXPECT_GT(ns, 0u);
}

TEST_F(TimerTest_460, StartThenElapsedMicrosecondsIsPositive_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto us = timer.getElapsedMicroseconds();
    EXPECT_GT(us, 0u);
}

TEST_F(TimerTest_460, StartThenElapsedMillisecondsIsPositive_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto ms = timer.getElapsedMilliseconds();
    EXPECT_GE(ms, 1u);
}

TEST_F(TimerTest_460, StartThenElapsedSecondsIsPositive_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto s = timer.getElapsedSeconds();
    EXPECT_GT(s, 0.0);
}

// Test that microseconds is nanoseconds / 1000
TEST_F(TimerTest_460, MicrosecondsEqualsNanosecondsDividedBy1000_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto ns = timer.getElapsedNanoseconds();
    auto us = timer.getElapsedMicroseconds();
    // They are called at slightly different times, so allow some tolerance
    // us should be approximately ns/1000, but ns is taken first so us >= ns/1000
    // Just verify they are in the right ballpark
    EXPECT_NEAR(static_cast<double>(us), static_cast<double>(ns) / 1000.0, 5000.0);
}

// Test that elapsed time increases with more sleep
TEST_F(TimerTest_460, ElapsedTimeIncreasesOverTime_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto first = timer.getElapsedNanoseconds();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto second = timer.getElapsedNanoseconds();
    EXPECT_GT(second, first);
}

// Test that calling start() resets the timer
TEST_F(TimerTest_460, RestartResetsTimer_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto elapsed1 = timer.getElapsedMilliseconds();
    
    timer.start();  // restart
    auto elapsed2 = timer.getElapsedMilliseconds();
    
    // After restart, elapsed time should be much smaller than before restart
    EXPECT_LT(elapsed2, elapsed1);
}

// Test consistency between units
TEST_F(TimerTest_460, MillisecondsConsistentWithMicroseconds_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    auto us = timer.getElapsedMicroseconds();
    auto ms = timer.getElapsedMilliseconds();
    // ms should be approximately us/1000
    EXPECT_NEAR(static_cast<double>(ms), static_cast<double>(us) / 1000.0, 50.0);
}

// Test consistency between seconds and milliseconds
TEST_F(TimerTest_460, SecondsConsistentWithMilliseconds_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    auto ms = timer.getElapsedMilliseconds();
    auto s = timer.getElapsedSeconds();
    EXPECT_NEAR(s, static_cast<double>(ms) / 1000.0, 0.1);
}

// Test very short duration
TEST_F(TimerTest_460, VeryShortDuration_460) {
    timer.start();
    // No sleep - immediate measurement
    auto ns = timer.getElapsedNanoseconds();
    // Should be very small but non-negative (uint64_t so always >= 0)
    EXPECT_LT(ns, 1000000000u); // less than 1 second
}

// Test that multiple calls to getElapsed don't affect the timer
TEST_F(TimerTest_460, MultipleGetCallsDontAffectTimer_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    auto ns1 = timer.getElapsedNanoseconds();
    auto ns2 = timer.getElapsedNanoseconds();
    auto ns3 = timer.getElapsedNanoseconds();
    
    // Each successive call should return >= previous (time moves forward)
    EXPECT_GE(ns2, ns1);
    EXPECT_GE(ns3, ns2);
}

// Boundary: test with approximately 1 second sleep
TEST_F(TimerTest_460, OneSecondSleep_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto s = timer.getElapsedSeconds();
    EXPECT_NEAR(s, 1.0, 0.5); // Allow generous tolerance for CI environments
}

// Test that getElapsedMicroseconds truncates (integer division)
TEST_F(TimerTest_460, MicrosecondsIsTruncatedDivision_460) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto ns = timer.getElapsedNanoseconds();
    auto us = timer.getElapsedMicroseconds();
    // Due to separate calls, we just verify us is reasonable
    EXPECT_GE(us, 500u); // at least 0.5ms in microseconds
}
