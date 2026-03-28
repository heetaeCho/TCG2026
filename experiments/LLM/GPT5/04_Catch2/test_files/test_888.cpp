// File: tests/chronometer_model_test_888.cpp

#include <gtest/gtest.h>

// Include the real amalgamated header from your tree
#include "Catch2/extras/catch_amalgamated.hpp"

// Minimal controllable clock for tests.
// It matches the required Clock interface: defines time_point and static now().
struct FakeClock {
    using rep        = long long;
    using period     = std::nano;
    using duration   = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<FakeClock>;

    static void set_now(rep ns) { now_value = ns; }
    static time_point now()     { return time_point(duration(now_value)); }

    static inline rep now_value = 0;
};

// Convenience aliases to the types from the Catch2 namespace (as declared in your Known deps)
namespace C = Catch::Benchmark::Detail;

class ChronometerModelTest_888 : public ::testing::Test {
protected:
    using Chrono = C::ChronometerModel<FakeClock>;
    Chrono chrono_;
};

// Normal operation: start() captures the current time from Clock::now()
TEST_F(ChronometerModelTest_888, StartSetsStarted_888) {
    FakeClock::set_now(1'000);                // ns
    chrono_.start();
    // Public field: verify observable effect
    EXPECT_EQ(chrono_.started, FakeClock::time_point(FakeClock::duration(1'000)));
}

// Normal operation: finish() captures the current time from Clock::now()
TEST_F(ChronometerModelTest_888, FinishSetsFinished_888) {
    FakeClock::set_now(2'000);
    chrono_.finish();
    // Public field: verify observable effect
    EXPECT_EQ(chrono_.finished, FakeClock::time_point(FakeClock::duration(2'000)));
}

// Normal operation: elapsed() reflects the duration between start and finish
TEST_F(ChronometerModelTest_888, ElapsedBetweenStartAndFinish_888) {
    FakeClock::set_now(10'000);
    chrono_.start();

    FakeClock::set_now(25'000);
    chrono_.finish();

    auto elapsed = chrono_.elapsed(); // IDuration (per provided interface)
    // Convert to nanoseconds for comparison via chrono cast
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    EXPECT_EQ(ns, 15'000);
}

// Boundary: starting twice should update the recorded start time to the latest Clock::now()
TEST_F(ChronometerModelTest_888, StartTwiceUpdatesStartTime_888) {
    FakeClock::set_now(5'000);
    chrono_.start();

    FakeClock::set_now(8'000);
    chrono_.start(); // call again

    EXPECT_EQ(chrono_.started, FakeClock::time_point(FakeClock::duration(8'000)));
}

// Boundary: zero-duration case when start and finish happen at the same clock value
TEST_F(ChronometerModelTest_888, ZeroDurationWhenStartEqualsFinish_888) {
    FakeClock::set_now(42'000);
    chrono_.start();
    // finish at the same timestamp
    FakeClock::set_now(42'000);
    chrono_.finish();

    auto elapsed = chrono_.elapsed();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    EXPECT_EQ(ns, 0);
}
