// TEST_ID: 890
// File: tests/chronometer_model_elapsed_890.cpp

#include <gtest/gtest.h>
#include <chrono>

// Include the amalgamated header that provides ChronometerModel, IDuration, etc.
#include "Catch2/extras/catch_amalgamated.hpp"

namespace C = Catch::Benchmark::Detail;

template <typename Clock>
using Model = C::ChronometerModel<Clock>;

//
// Normal operation: finished > started
//
TEST(ChronometerModelTest_890, ElapsedPositiveDuration_SteadyClock_890) {
    using Clock = std::chrono::steady_clock;
    Model<Clock> m;

    // Choose values with a non-trivial difference to exercise duration_cast
    const auto t0 = Clock::time_point{std::chrono::microseconds{100}};   // 100 us
    const auto t1 = Clock::time_point{std::chrono::microseconds{1234}};  // 1234 us

    m.started  = t0;
    m.finished = t1;

    auto d = m.elapsed(); // IDuration (nanoseconds)
    EXPECT_EQ(d.count(), 1134 * 1000) << "Expected 1,134 us -> 1,134,000 ns";
}

//
// Boundary: finished == started => zero duration
//
TEST(ChronometerModelTest_890, ElapsedZeroDuration_890) {
    using Clock = std::chrono::steady_clock;
    Model<Clock> m;

    const auto t = Clock::time_point{std::chrono::nanoseconds{42}};
    m.started  = t;
    m.finished = t;

    auto d = m.elapsed();
    EXPECT_EQ(d.count(), 0) << "Zero span should yield 0 ns";
}

//
// Boundary: finished < started => negative duration (observable via public members)
//
TEST(ChronometerModelTest_890, ElapsedNegativeDuration_890) {
    using Clock = std::chrono::steady_clock;
    Model<Clock> m;

    const auto later   = Clock::time_point{std::chrono::milliseconds{10}};
    const auto earlier = Clock::time_point{std::chrono::milliseconds{7}};

    m.started  = later;    // started after
    m.finished = earlier;  // finished before

    auto d = m.elapsed();
    // The implementation does finished - started and casts to nanoseconds.
    // That yields a negative duration; assert the sign and exact magnitude.
    EXPECT_LT(d.count(), 0);
    EXPECT_EQ(d.count(), -3'000'000) << "10ms - 7ms = -3ms -> -3,000,000 ns";
}

//
// Unit conversion check: milliseconds -> nanoseconds
//
TEST(ChronometerModelTest_890, ElapsedConvertsToNanoseconds_890) {
    using Clock = std::chrono::steady_clock;
    Model<Clock> m;

    const auto t0 = Clock::time_point{std::chrono::milliseconds{0}};
    const auto t1 = Clock::time_point{std::chrono::milliseconds{2}}; // 2 ms

    m.started  = t0;
    m.finished = t1;

    auto d = m.elapsed();
    EXPECT_EQ(d.count(), 2'000'000) << "2 ms should be 2,000,000 ns";
}

//
// Template robustness: works with a different Clock (system_clock)
//
TEST(ChronometerModelTest_890, ElapsedWithSystemClock_890) {
    using Clock = std::chrono::system_clock;
    Model<Clock> m;

    const auto t0 = Clock::time_point{std::chrono::microseconds{1}};
    const auto t1 = Clock::time_point{std::chrono::microseconds{501}}; // diff = 500 us

    m.started  = t0;
    m.finished = t1;

    auto d = m.elapsed();
    EXPECT_EQ(d.count(), 500'000) << "500 us should be 500,000 ns";
}
