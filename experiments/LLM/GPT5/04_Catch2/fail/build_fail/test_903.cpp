// File: measure_one_tests_903.cpp
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <chrono>

// Include the CUT
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {
using ClockT = std::chrono::steady_clock;
using namespace Catch::Benchmark;

// A small helper to build a stateful callable whose invocations are observable
struct CountingCallable {
    std::shared_ptr<int> counter;
    bool shouldThrow = false;

    explicit CountingCallable(std::shared_ptr<int> c, bool th = false)
        : counter(std::move(c)), shouldThrow(th) {}

    void operator()() const {
        ++(*counter);
        if (shouldThrow) {
            throw std::runtime_error("boom");
        }
    }
};
} // namespace

// --- Tests ---

// Ensures the function's interface returns TimingOf<Fun, int> for the given callable.
// This is a pure interface check that does not depend on internal behavior.
//
// TEST_ID: 903
TEST(MeasureOneTest_903, ReturnType_Is_TimingOf_903) {
    auto c = std::make_shared<int>(0);
    auto fun = CountingCallable{c, false};

    // Verify the return type only (compile-time interface check)
    using Result = decltype(Catch::Benchmark::Detail::measure_one<ClockT>(
        fun, 1, std::false_type{}));
    using Expected = Catch::Benchmark::TimingOf<decltype(fun), int>;

    static_assert(std::is_same<Result, Expected>::value,
                  "measure_one must return TimingOf<Fun, int>");
    SUCCEED(); // Reaches runtime to mark the test as executed.
}

// Boundary condition: When iters == 0, the callable should not be invoked.
// We verify via the observable side effect (counter remains 0).
//
// TEST_ID: 903
TEST(MeasureOneTest_903, ZeroIters_DoesNotInvokeCallable_903) {
    auto counter = std::make_shared<int>(0);
    CountingCallable fun{counter, /*shouldThrow*/ false};

    // Should not throw and should not invoke callable
    EXPECT_NO_THROW({
        (void)Catch::Benchmark::Detail::measure_one<ClockT>(
            fun, /*iters*/ 0, std::false_type{});
    });

    EXPECT_EQ(*counter, 0) << "Callable should not be invoked when iters == 0";
}

// Exceptional path: If the callable throws, verify that the exception propagates.
// We also check that invocation happened at least once via the observable counter.
//
// TEST_ID: 903
TEST(MeasureOneTest_903, CallableException_Propagates_903) {
    auto counter = std::make_shared<int>(0);
    CountingCallable fun{counter, /*shouldThrow*/ true};

    try {
        (void)Catch::Benchmark::Detail::measure_one<ClockT>(
            fun, /*iters*/ 1, std::false_type{});
        FAIL() << "Expected std::runtime_error to be thrown";
    } catch (const std::runtime_error& e) {
        // Exception propagated as-is (observable behavior)
        EXPECT_STREQ(e.what(), "boom");
        // And the callable was actually invoked (observable side effect)
        EXPECT_GE(*counter, 1);
    } catch (...) {
        FAIL() << "Expected std::runtime_error";
    }
}
