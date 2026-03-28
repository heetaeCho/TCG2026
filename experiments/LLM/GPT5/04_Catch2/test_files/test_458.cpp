// TimerTests_458.cpp
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

// Include the provided interface header for the SUT
// (paths may need adjusting to your project layout)
#include "catch2/catch_timer.hpp"

using namespace std::chrono_literals;

namespace {

class TimerTest_458 : public ::testing::Test {
protected:
    Catch::Timer timer;

    // Helper: sleep a bit to create observable elapsed time
    static void small_sleep(std::chrono::milliseconds d) {
        std::this_thread::sleep_for(d);
    }

    // Helper: relative tolerance check
    static ::testing::AssertionResult NearRel(double a, double b, double rel_tol) {
        if (b == 0.0) {
            return (std::abs(a) <= rel_tol) ? ::testing::AssertionSuccess()
                                            : ::testing::AssertionFailure()
                                              << "Expected |" << a << "| <= " << rel_tol << " (b == 0)";
        }
        double rel = std::abs((a - b) / b);
        if (rel <= rel_tol) return ::testing::AssertionSuccess();
        return ::testing::AssertionFailure()
               << "Relative diff " << rel << " exceeds tol " << rel_tol
               << " (a=" << a << ", b=" << b << ")";
    }
};

} // namespace

// Normal operation: after start(), elapsed times should be >= 0 across units.
TEST_F(TimerTest_458, ElapsedNonNegativeAfterStart_458) {
    timer.start();
    auto ns = timer.getElapsedNanoseconds();
    auto us = timer.getElapsedMicroseconds();
    auto ms = timer.getElapsedMilliseconds();
    auto s  = timer.getElapsedSeconds();

    EXPECT_GE(ns, static_cast<uint64_t>(0));
    EXPECT_GE(us, static_cast<uint64_t>(0));
    EXPECT_GE(ms, static_cast<unsigned int>(0));
    EXPECT_GE(s, 0.0);
}

// Normal operation: elapsed increases over time (monotonic increasing when time advances).
TEST_F(TimerTest_458, ElapsedIncreasesOverTime_458) {
    timer.start();
    auto ns1 = timer.getElapsedNanoseconds();
    auto us1 = timer.getElapsedMicroseconds();
    auto ms1 = timer.getElapsedMilliseconds();
    auto s1  = timer.getElapsedSeconds();

    small_sleep(2ms);

    auto ns2 = timer.getElapsedNanoseconds();
    auto us2 = timer.getElapsedMicroseconds();
    auto ms2 = timer.getElapsedMilliseconds();
    auto s2  = timer.getElapsedSeconds();

    EXPECT_LE(ns1, ns2);
    EXPECT_LE(us1, us2);
    EXPECT_LE(ms1, ms2);
    EXPECT_LE(s1,  s2);

    // And the increase should be observable (greater than zero) in at least some units.
    EXPECT_GT(ns2, ns1);
    EXPECT_GE(us2, us1); // microseconds may coalesce on fast systems; allow equal in rare cases
    EXPECT_GE(ms2, ms1); // same reasoning as above
    EXPECT_GT(s2, s1);
}

// Boundary: restarting the timer should reset the elapsed time baseline.
TEST_F(TimerTest_458, RestartResetsElapsed_458) {
    timer.start();
    small_sleep(30ms);
    auto before_restart_ms = timer.getElapsedMilliseconds();

    timer.start(); // restart baseline
    // After restart, elapsed should be much smaller than the pre-restart elapsed.
    small_sleep(1ms);
    auto after_restart_ms = timer.getElapsedMilliseconds();

    // Ensure we actually had non-trivial elapsed before restart.
    ASSERT_GE(before_restart_ms, static_cast<unsigned int>(20));

    // Now the new elapsed should be less than the old elapsed.
    EXPECT_LT(after_restart_ms, before_restart_ms);
}

// Normal operation: unit coherence (ns, us, ms, s) within tolerant bounds.
TEST_F(TimerTest_458, UnitCoherenceWithinTolerance_458) {
    timer.start();
    small_sleep(5ms);

    auto ns = static_cast<double>(timer.getElapsedNanoseconds());
    auto us = static_cast<double>(timer.getElapsedMicroseconds());
    auto ms = static_cast<double>(timer.getElapsedMilliseconds());
    auto s  = timer.getElapsedSeconds();

    // Convert all readings to seconds for comparison.
    double ns_in_s = ns / 1e9;
    double us_in_s = us / 1e6;
    double ms_in_s = ms / 1e3;

    // Use a generous relative tolerance to account for scheduling and rounding.
    // 20% relative tolerance is typically safe for coarse sleep intervals.
    constexpr double kRelTol = 0.20;

    EXPECT_TRUE(NearRel(ns_in_s, us_in_s, kRelTol));
    EXPECT_TRUE(NearRel(us_in_s, ms_in_s, kRelTol));
    EXPECT_TRUE(NearRel(ms_in_s, s,       kRelTol));
    EXPECT_TRUE(NearRel(ns_in_s, s,       kRelTol));
}

// Robustness: multiple successive reads should be non-decreasing (no time going backwards).
TEST_F(TimerTest_458, MultipleReadsAreNonDecreasing_458) {
    timer.start();

    auto ns1 = timer.getElapsedNanoseconds();
    auto ns2 = timer.getElapsedNanoseconds();
    auto ns3 = timer.getElapsedNanoseconds();

    EXPECT_LE(ns1, ns2);
    EXPECT_LE(ns2, ns3);
}

