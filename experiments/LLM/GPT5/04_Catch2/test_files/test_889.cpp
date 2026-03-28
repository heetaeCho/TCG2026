// File: tests/chronometer_model_finish_889_tests.cpp

#include <gtest/gtest.h>

#include "Catch2/extras/catch_amalgamated.hpp"
#include <chrono>

namespace {

// A controllable clock to make now() deterministic in tests.
// This is an external collaborator provided via the template parameter.
// We do NOT simulate any ChronometerModel internals.
struct FakeClock {
    using rep        = long long;
    using period     = std::nano;
    using duration   = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<FakeClock>;

    static time_point now() { return current_; }

    static void SetNow(const time_point& tp) { current_ = tp; }

private:
    static time_point current_;
};

FakeClock::time_point FakeClock::current_{ FakeClock::time_point{} };

} // namespace

// Type under test
using ChronoModel = Catch::Benchmark::Detail::ChronometerModel<FakeClock>;

//
// NOTE about test scope:
// - We verify only WHAT is visible/observable through the public interface.
// - We do not rely on any private/internal state or inferred behavior.
// - We use the public members/methods available in the provided interface.
//

//------------------------------------------------------------------------------
// Normal operation: finish() sets `finished` to `Clock::now()`
//------------------------------------------------------------------------------
TEST(ChronometerModelTest_889, FinishSetsFinishedToNow_889) {
    ChronoModel model;

    // Arrange: pick a deterministic timestamp
    const auto t1 = FakeClock::time_point{ FakeClock::duration{123456789} };
    FakeClock::SetNow(t1);

    // Act
    model.finish();

    // Assert: `finished` reflects the clock's now() at the moment of finish()
    // We assert equality against the public member `finished`.
    EXPECT_EQ(model.finished, t1);
}

//------------------------------------------------------------------------------
// Boundary-ish: calling finish() without calling start() first
// Still must set `finished` to `Clock::now()` (observable via public member)
//------------------------------------------------------------------------------
TEST(ChronometerModelTest_889, FinishWithoutStartStillSetsFinished_889) {
    ChronoModel model;

    const auto t = FakeClock::time_point{ FakeClock::duration{42} };
    FakeClock::SetNow(t);

    model.finish();

    EXPECT_EQ(model.finished, t);
}

//------------------------------------------------------------------------------
// Repeated calls: subsequent finish() updates `finished` to the *new* now()
//------------------------------------------------------------------------------
TEST(ChronometerModelTest_889, FinishCanBeCalledMultipleTimes_UpdatesFinished_889) {
    ChronoModel model;

    const auto t1 = FakeClock::time_point{ FakeClock::duration{1000} };
    const auto t2 = FakeClock::time_point{ FakeClock::duration{2000} };
    const auto t3 = FakeClock::time_point{ FakeClock::duration{3000} };

    FakeClock::SetNow(t1);
    model.finish();
    EXPECT_EQ(model.finished, t1);

    FakeClock::SetNow(t2);
    model.finish();
    EXPECT_EQ(model.finished, t2);

    FakeClock::SetNow(t3);
    model.finish();
    EXPECT_EQ(model.finished, t3);
}

//------------------------------------------------------------------------------
// Integration with start()/elapsed() via public interface only:
// If start() captures `Clock::now()` and finish() sets finished to `Clock::now()`,
// then elapsed() should reflect the difference (observable).
// We do not re-implement internal logic; we only assert visible outcomes.
//------------------------------------------------------------------------------
TEST(ChronometerModelTest_889, ElapsedReflectsStartToFinishInterval_889) {
    ChronoModel model;

    const auto t_start  = FakeClock::time_point{ FakeClock::duration{10'000} };
    const auto t_finish = FakeClock::time_point{ FakeClock::duration{25'000} };

    // Start at t_start
    FakeClock::SetNow(t_start);
    model.start();

    // Finish at t_finish
    FakeClock::SetNow(t_finish);
    model.finish();

    // elapsed() is part of the public interface; we assert it matches the interval.
    // We avoid assuming exact underlying type of IDuration beyond being duration-like.
    auto elapsed = model.elapsed();

    // Convert both to nanoseconds if possible by using std::chrono semantics.
    // If IDuration is already a chrono::duration, count() should be comparable.
    using ns = std::chrono::nanoseconds;
    const auto expected_ns = (t_finish - t_start).count();

    // Compare via counts to avoid type/precision assumptions.
    EXPECT_EQ(std::chrono::duration_cast<ns>(elapsed).count(), expected_ns);
}

//------------------------------------------------------------------------------
// Edge case: zero interval (start and finish at same "now") should yield 0
//------------------------------------------------------------------------------
TEST(ChronometerModelTest_889, ElapsedZeroWhenStartEqualsFinish_889) {
    ChronoModel model;

    const auto t = FakeClock::time_point{ FakeClock::duration{777'777} };

    FakeClock::SetNow(t);
    model.start();

    FakeClock::SetNow(t);
    model.finish();

    using ns = std::chrono::nanoseconds;
    EXPECT_EQ(std::chrono::duration_cast<ns>(model.elapsed()).count(), 0);
}

