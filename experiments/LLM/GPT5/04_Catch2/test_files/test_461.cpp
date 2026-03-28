// File: tests/timer_getElapsedMilliseconds_461_test.cpp

#include <gtest/gtest.h>
#include <cstdint>

// Include the public interface (as provided)
#include "catch2/catch_timer.hpp"

using Catch::Timer;

// A simple fixture in case future setup/teardown is needed
class TimerGetMsTest_461 : public ::testing::Test {
protected:
    Timer t;
};

// [461] Verifies that getElapsedMilliseconds() equals floor(getElapsedMicroseconds()/1000)
// This directly reflects the provided implementation in catch_timer.cpp.
TEST_F(TimerGetMsTest_461, MillisecondsDerivedFromMicroseconds_461) {
    t.start();
    // Read both values as "atomically" as we can (back-to-back) to minimize drift.
    const uint64_t us = t.getElapsedMicroseconds();
    const unsigned int ms = t.getElapsedMilliseconds();

    EXPECT_EQ(ms, static_cast<unsigned int>(us / 1000));
}

// [461] Verifies truncation semantics: ms*1000 <= us < (ms+1)*1000
// This asserts floor-division behavior without depending on any absolute time.
TEST_F(TimerGetMsTest_461, TruncationBoundsHold_461) {
    t.start();
    const uint64_t us = t.getElapsedMicroseconds();
    const unsigned int ms = t.getElapsedMilliseconds();

    // Lower bound (no rounding up)
    EXPECT_LE(static_cast<uint64_t>(ms) * 1000ULL, us);

    // Upper bound (strictly less than next millisecond)
    EXPECT_LT(us, (static_cast<uint64_t>(ms) + 1ULL) * 1000ULL);
}

// [461] getElapsedMilliseconds() should be monotonic non-decreasing as time passes.
// We avoid sleeps to keep tests fast & stable; a small busy loop is sufficient to
// allow measurable time to pass on most systems, but we only require non-decrease.
TEST_F(TimerGetMsTest_461, MonotonicNonDecreasing_461) {
    t.start();
    const unsigned int ms1 = t.getElapsedMilliseconds();

    // Small, deterministic busy work to advance the clock a bit
    volatile uint64_t sink = 0;
    for (int i = 0; i < 100000; ++i) { sink += static_cast<uint64_t>(i); }

    const unsigned int ms2 = t.getElapsedMilliseconds();

    EXPECT_LE(ms1, ms2) << "Elapsed milliseconds should not go backwards.";
}
