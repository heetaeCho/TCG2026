// TimerTest_460.cpp
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

// Include the provided interface header
#include "catch2/catch_timer.hpp"

// Test fixture (kept simple for clarity)
class TimerTest_460 : public ::testing::Test {
protected:
    Catch::Timer timer_;
};

// [Normal] getElapsedMicroseconds equals getElapsedNanoseconds / 1000 (integer division)
TEST_F(TimerTest_460, MicrosecondsMatchesNanosecondsDivision_460) {
    timer_.start();

    // Allow a tiny bit of time to pass so elapsed is non-trivial but still small
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

    const uint64_t ns = timer_.getElapsedNanoseconds();
    const uint64_t us = timer_.getElapsedMicroseconds();

    // Observable relation based solely on public methods
    EXPECT_EQ(us, ns / 1000);
}

// [Normal] Elapsed time reported in microseconds should be monotonic non-decreasing
TEST_F(TimerTest_460, ElapsedIsMonotonic_460) {
    timer_.start();

    const uint64_t first_us = timer_.getElapsedMicroseconds();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    const uint64_t second_us = timer_.getElapsedMicroseconds();

    EXPECT_LE(first_us, second_us);
}

// [Boundary/Behavior] start() restarts the timer (observable drop in elapsed)
TEST_F(TimerTest_460, StartResetsElapsed_460) {
    timer_.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    const uint64_t before_restart_us = timer_.getElapsedMicroseconds();

    // Restart and confirm elapsed is (observably) much smaller than before
    timer_.start();
    const uint64_t after_restart_us_immediate = timer_.getElapsedMicroseconds();

    // The restarted elapsed should be <= the pre-restart elapsed,
    // and typically much smaller. We require strictly smaller to
    // detect the reset effect via the public API.
    EXPECT_LT(after_restart_us_immediate, before_restart_us);
}

// [Boundary] The remainder after converting back to nanoseconds is < 1000
// (i.e., ns = us*1000 + remainder, remainder in [0, 999])
TEST_F(TimerTest_460, NanosecondsRemainderUnderThousand_460) {
    timer_.start();

    // Let some time pass to avoid purely zero durations on very fast systems
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    const uint64_t ns = timer_.getElapsedNanoseconds();
    const uint64_t us = timer_.getElapsedMicroseconds();

    // Using only public methods; no internal state assumptions.
    const uint64_t remainder = ns - us * 1000;
    EXPECT_LT(remainder, static_cast<uint64_t>(1000));
}
