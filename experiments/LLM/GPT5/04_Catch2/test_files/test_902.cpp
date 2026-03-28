// File: test_measure_902.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/extras/catch_amalgamated.hpp"
#include <chrono>
#include <memory>
#include <stdexcept>
#include <string>

using ::testing::Eq;
using ::testing::Ge;

namespace {

// A controllable clock to make duration deterministic.
struct TestClock {
    using duration   = std::chrono::nanoseconds;
    using rep        = duration::rep;
    using period     = duration::period;
    using time_point = std::chrono::time_point<TestClock, duration>;
    static constexpr bool is_steady = true;

    // First call -> t=100ns, second call -> t=250ns, so delta=150ns
    static int call_index;
    static time_point now() {
        const auto t = (call_index++ == 0) ? duration{100} : duration{250};
        return time_point{t};
    }

    static void reset() { call_index = 0; }
};
int TestClock::call_index = 0;

} // namespace

// Basic happy path: function is invoked, result is captured, iterations == 1, duration matches TestClock.
TEST(MeasureTest_902, ReturnsResultAndIterationsAreOne_902) {
    using namespace Catch::Benchmark::Detail;

    TestClock::reset();
    int side_effect = 0;
    auto fun = [&](){ side_effect = 123; return 42; };

    auto t = measure<TestClock>(fun);

    // Observable effects/values only:
    EXPECT_THAT(side_effect, Eq(123));                      // fun executed
    EXPECT_THAT(t.result, Eq(42));                          // result forwarded
    EXPECT_THAT(t.iterations, Eq(1));                       // iterations fixed at 1
    EXPECT_THAT(t.elapsed, Eq(TestClock::duration{150}));   // 250ns - 100ns
}

// Perfect forwarding of lvalue reference: fun mutates the argument; mutation is observable post-call.
TEST(MeasureTest_902, ForwardsLvalueReferenceAndAppliesMutation_902) {
    using namespace Catch::Benchmark::Detail;

    TestClock::reset();
    int x = 7;
    auto fun = [](int& ref) -> int { ref += 5; return ref; };

    auto t = measure<TestClock>(fun, x);

    EXPECT_THAT(x, Eq(12));                 // observable side effect on lvalue arg
    EXPECT_THAT(t.result, Eq(12));          // return value reflects mutation
    EXPECT_THAT(t.iterations, Eq(1));
    EXPECT_THAT(t.elapsed, Eq(TestClock::duration{150}));
}

// Perfect forwarding of rvalue/move-only argument: move-only value is consumed.
TEST(MeasureTest_902, ForwardsMoveOnlyArgument_902) {
    using namespace Catch::Benchmark::Detail;

    struct MoveOnly {
        std::unique_ptr<int> p;
        explicit MoveOnly(int v) : p(new int(v)) {}
        MoveOnly(MoveOnly&&) noexcept = default;
        MoveOnly& operator=(MoveOnly&&) noexcept = default;
        MoveOnly(const MoveOnly&)            = delete;
        MoveOnly& operator=(const MoveOnly&) = delete;
    };

    auto fun = [](MoveOnly m) {
        // Consume the unique_ptr and compute something from it
        int v = m.p ? *m.p : -999;
        return std::string("v=") + std::to_string(v);
    };

    TestClock::reset();
    MoveOnly mo{55};
    auto t = measure<TestClock>(fun, std::move(mo));

    // We cannot inspect 'mo' internals (moved-from state) except that it's still valid as an object.
    // We only assert on the observable result value and timing/iterations.
    EXPECT_THAT(t.result, Eq(std::string("v=55")));
    EXPECT_THAT(t.iterations, Eq(1));
    EXPECT_THAT(t.elapsed, Eq(TestClock::duration{150}));
}

// Move-only callable is supported and invoked once.
TEST(MeasureTest_902, InvokesMoveOnlyCallable_902) {
    using namespace Catch::Benchmark::Detail;

    struct MoveOnlyCallable {
        int* counter;
        explicit MoveOnlyCallable(int& c) : counter(&c) {}
        MoveOnlyCallable(MoveOnlyCallable&&) noexcept = default;
        MoveOnlyCallable& operator=(MoveOnlyCallable&&) noexcept = default;
        MoveOnlyCallable(const MoveOnlyCallable&)            = delete;
        MoveOnlyCallable& operator=(const MoveOnlyCallable&) = delete;

        int operator()() {
            ++(*counter);
            return 77;
        }
    };

    int calls = 0;
    TestClock::reset();
    auto t = measure<TestClock>(MoveOnlyCallable{calls});

    EXPECT_THAT(calls, Eq(1));                  // callable invoked exactly once
    EXPECT_THAT(t.result, Eq(77));
    EXPECT_THAT(t.iterations, Eq(1));
    EXPECT_THAT(t.elapsed, Eq(TestClock::duration{150}));
}

// Exceptions from the fun propagate out of measure (observable via EXPECT_THROW).
TEST(MeasureTest_902, PropagatesExceptions_902) {
    using namespace Catch::Benchmark::Detail;

    struct MyError : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    auto throwing = []() -> int {
        throw MyError("boom");
    };

    TestClock::reset();
    EXPECT_THROW(
        (void)measure<TestClock>(throwing),
        MyError
    );
}

// Sanity: elapsed is non-negative even with a normal steady clock (no strict value check).
TEST(MeasureTest_902, ElapsedIsNonNegativeWithSteadyClock_902) {
    using namespace Catch::Benchmark::Detail;

    // Use a real steady clock here; we only assert non-negativity and iterations==1.
    auto fun = [] { return 1; };
    auto t = measure<std::chrono::steady_clock>(fun);

    EXPECT_THAT(t.result, Eq(1));
    EXPECT_THAT(t.iterations, Eq(1));
    // The only observable property we can safely assert is that the duration is >= 0.
    EXPECT_THAT(t.elapsed.count(), Ge(0LL));
}
