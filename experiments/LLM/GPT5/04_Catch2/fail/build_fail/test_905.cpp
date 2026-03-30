// File: tests/run_for_at_least_tests_905.cpp
#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

#include <type_traits>
#include <chrono>

namespace my_test {

// --- Test probes (only observable via the external collaborator we provide) ---
struct Probe {
    // Not callable with Chronometer (is_callable<Fun(Chronometer)>() should be false)
    int operator()() const { return 123; }
};

struct ChronoProbe {
    // Callable with Chronometer (is_callable<Fun(Chronometer)>() should be true)
    int operator()(Catch::Benchmark::Chronometer) const { return 456; }
};

// Fake timing object with just the members used by run_for_at_least:
//   - .elapsed  (for comparison)
//   - .result   (returned via CATCH_MOVE into the final aggregate)
struct FakeTiming {
    Catch::Benchmark::Detail::IDuration elapsed;
    int result;
};

// ADL-visible test double for the external collaborator `measure_one`.
// We constrain it so it only participates for our probes, avoiding ambiguity
// with Catch2's real overloads.
template <typename Clock, typename Fun,
          std::enable_if_t<
              std::is_same_v<std::decay_t<Fun>, my_test::Probe> ||
              std::is_same_v<std::decay_t<Fun>, my_test::ChronoProbe>,
              int> = 0>
inline FakeTiming measure_one(Fun&& /*fun*/,
                              int iters,
                              auto /*callable_tag*/) {
    using ID = Catch::Benchmark::Detail::IDuration;
    // Deterministic behavior: elapsed grows with iters; result encodes iters.
    // (No assumptions about internal logic; this is just our collaborator's behavior.)
    return FakeTiming{ ID{iters}, iters * 10 };
}

// Dummy clock type (type parameter only; not used by our test double).
struct DummyClock {};

} // namespace my_test

// ---- Test fixture ----
class RunForAtLeastTest_905 : public ::testing::Test {
protected:
    using ID = Catch::Benchmark::Detail::IDuration;
    template <typename Fun>
    auto call_run_for_at_least(ID how_long, int initial_iterations, Fun&& fun) {
        return Catch::Benchmark::Detail::run_for_at_least<my_test::DummyClock>(
            how_long, initial_iterations, std::forward<Fun>(fun));
    }
};

// Normal operation: returns immediately when initial iterations already meet threshold
TEST_F(RunForAtLeastTest_905, ReturnsWhenInitialMeets_905) {
    // With our test-double, elapsed == iters
    const ID how_long{8};
    const int initial_iters = 16; // Already >= how_long
    auto timing = call_run_for_at_least(how_long, initial_iters, my_test::Probe{});

    // Observable expectations:
    // - It should keep the initial iterations (no doubling needed)
    // - Returned result should be what our collaborator provided for that iters
    EXPECT_GE(timing.elapsed, how_long);
    EXPECT_EQ(timing.samples, initial_iters); // 'samples' is the iteration count in TimingOf
    EXPECT_EQ(timing.result, initial_iters * 10);
}

// Normal operation: doubles iterations until threshold is reached
TEST_F(RunForAtLeastTest_905, DoublesUntilMeets_905) {
    // elapsed == iters (from our collaborator). Start at 1, target 8 => iters: 1 -> 2 -> 4 -> 8
    const ID how_long{8};
    const int initial_iters = 1;

    auto timing = call_run_for_at_least(how_long, initial_iters, my_test::Probe{});

    EXPECT_GE(timing.elapsed, how_long);
    EXPECT_EQ(timing.samples, 8);          // first power-of-two >= 8
    EXPECT_EQ(timing.result, 8 * 10);      // collaborator encodes iters as result
}

// Boundary: exact threshold match should be accepted
TEST_F(RunForAtLeastTest_905, ExactThresholdMatch_905) {
    const ID how_long{32};
    const int initial_iters = 32;

    auto timing = call_run_for_at_least(how_long, initial_iters, my_test::Probe{});

    EXPECT_EQ(timing.samples, 32);
    EXPECT_GE(timing.elapsed, how_long);
    EXPECT_EQ(timing.result, 320);
}

// Exceptional case: if threshold cannot be met before hitting the hard cap, it throws
TEST_F(RunForAtLeastTest_905, ThrowsWhenExceedsIterationCap_905) {
    // Loop condition is while (iters < (1 << 30)).
    // With elapsed == iters, asking for >= 1<<30 ensures we never satisfy the condition
    // before the loop exits and triggers throw_optimized_away_error().
    const auto too_long = my_test::RunForAtLeastTest_905::ID{ (1u << 30) };
    const int initial_iters = 1;

    EXPECT_ANY_THROW({
        (void)call_run_for_at_least(too_long, initial_iters, my_test::Probe{});
    });
}

// Verifies behavior when Fun is callable with Chronometer (trait flips).
// (We do not rely on any internal detail; we just ensure the call still works.)
TEST_F(RunForAtLeastTest_905, WorksWhenCallableWithChronometer_905) {
    // Same deterministic collaborator behavior applies (elapsed == iters),
    // but the is_callable trait should evaluate to true for this Fun.
    const ID how_long{4};
    const int initial_iters = 1;

    auto timing = call_run_for_at_least(how_long, initial_iters, my_test::ChronoProbe{});

    // 1 -> 2 -> 4
    EXPECT_EQ(timing.samples, 4);
    EXPECT_GE(timing.elapsed, how_long);
    EXPECT_EQ(timing.result, 40);
}
