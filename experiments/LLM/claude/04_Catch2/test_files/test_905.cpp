#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
#include <thread>
#include <functional>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark;
using namespace Catch::Benchmark::Detail;

// Type aliases for convenience
using ClockType = std::chrono::steady_clock;
using Duration = std::chrono::nanoseconds;

// ============================================================================
// Test Fixture
// ============================================================================
class RunForAtLeastTest_905 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Helper functions used in tests
// ============================================================================

// A simple callable that takes an int (iteration count) and returns a value
// It simulates some work that takes a measurable amount of time.
static int simple_int_fun(int iterations) {
    volatile int sum = 0;
    for (int i = 0; i < iterations; ++i) {
        sum += i;
    }
    return sum;
}

// A callable that takes a Chronometer - used to test the other overload path
struct ChronometerCallable {
    void operator()(Chronometer meter) const {
        meter.measure([](int i) { return i * 2; });
    }
};

// A fast function that completes almost instantly per iteration
static int fast_fun(int iterations) {
    volatile int x = 0;
    for (int i = 0; i < iterations; ++i) {
        x = i;
    }
    return static_cast<int>(x);
}

// A function that takes a noticeable amount of time per iteration
static int slow_fun(int iterations) {
    volatile int sum = 0;
    for (int i = 0; i < iterations; ++i) {
        // Burn some CPU time
        for (int j = 0; j < 1000; ++j) {
            sum += j;
        }
    }
    return sum;
}

// ============================================================================
// Tests
// ============================================================================

// Test that run_for_at_least returns a result with elapsed >= how_long
TEST_F(RunForAtLeastTest_905, ElapsedTimeIsAtLeastHowLong_905) {
    auto how_long = std::chrono::milliseconds(1);
    auto result = run_for_at_least<ClockType>(
        how_long, 1, [](int iters) -> int {
            volatile int sum = 0;
            for (int i = 0; i < iters; ++i) {
                for (int j = 0; j < 100; ++j) {
                    sum += j;
                }
            }
            return sum;
        });

    EXPECT_GE(result.elapsed, how_long);
}

// Test that the returned iterations count is >= the initial iterations
TEST_F(RunForAtLeastTest_905, IterationsAreAtLeastInitial_905) {
    auto how_long = std::chrono::milliseconds(1);
    int initial = 1;
    auto result = run_for_at_least<ClockType>(
        how_long, initial, [](int iters) -> int {
            volatile int sum = 0;
            for (int i = 0; i < iters; ++i) {
                for (int j = 0; j < 100; ++j) {
                    sum += j;
                }
            }
            return sum;
        });

    EXPECT_GE(result.iterations, initial);
}

// Test with initial_iterations = 1 and a very short how_long
TEST_F(RunForAtLeastTest_905, ShortDurationWithSmallInitial_905) {
    auto how_long = std::chrono::nanoseconds(1);
    auto result = run_for_at_least<ClockType>(
        how_long, 1, [](int iters) -> int {
            return iters;
        });

    EXPECT_GE(result.elapsed, how_long);
    EXPECT_GE(result.iterations, 1);
}

// Test with a lambda that returns a non-trivial result
TEST_F(RunForAtLeastTest_905, ResultIsPreserved_905) {
    auto how_long = std::chrono::nanoseconds(1);
    auto result = run_for_at_least<ClockType>(
        how_long, 1, [](int iters) -> int {
            return 42;
        });

    // The result should be what the function returned
    EXPECT_EQ(result.result, 42);
}

// Test that iterations double when the function is very fast and how_long is moderate
TEST_F(RunForAtLeastTest_905, IterationsIncreaseForFastFunction_905) {
    auto how_long = std::chrono::milliseconds(10);
    int initial = 1;
    auto result = run_for_at_least<ClockType>(
        how_long, initial, [](int iters) -> int {
            volatile int x = 0;
            for (int i = 0; i < iters; ++i) x = i;
            return static_cast<int>(x);
        });

    // Since the function is fast, iterations should have been doubled several times
    EXPECT_GT(result.iterations, initial);
}

// Test with a slow function that satisfies the time requirement on the first attempt
TEST_F(RunForAtLeastTest_905, SlowFunctionSatisfiesImmediately_905) {
    auto how_long = std::chrono::nanoseconds(1);
    int initial = 1;
    auto result = run_for_at_least<ClockType>(
        how_long, initial, [](int iters) -> int {
            // Even one iteration of this will take more than 1ns
            volatile int sum = 0;
            for (int i = 0; i < iters; ++i) {
                for (int j = 0; j < 10000; ++j) {
                    sum += j;
                }
            }
            return sum;
        });

    // Should complete with the initial iteration count
    EXPECT_EQ(result.iterations, initial);
}

// Test with larger initial iterations
TEST_F(RunForAtLeastTest_905, LargerInitialIterations_905) {
    auto how_long = std::chrono::nanoseconds(1);
    int initial = 100;
    auto result = run_for_at_least<ClockType>(
        how_long, initial, [](int iters) -> int {
            return iters;
        });

    EXPECT_GE(result.iterations, initial);
}

// Test that iterations are always a power-of-two multiple of the initial
TEST_F(RunForAtLeastTest_905, IterationsArePowerOfTwoMultipleOfInitial_905) {
    auto how_long = std::chrono::milliseconds(5);
    int initial = 1;
    auto result = run_for_at_least<ClockType>(
        how_long, initial, [](int iters) -> int {
            volatile int x = 0;
            for (int i = 0; i < iters; ++i) x = i;
            return static_cast<int>(x);
        });

    // iterations should be initial * 2^k for some k >= 0
    int iters = result.iterations;
    EXPECT_GE(iters, initial);
    // Check that iters / initial is a power of 2
    int ratio = iters / initial;
    EXPECT_EQ(iters, ratio * initial);
    EXPECT_TRUE((ratio & (ratio - 1)) == 0) << "Ratio " << ratio << " is not a power of 2";
}

// Test with zero-duration how_long - should return immediately
TEST_F(RunForAtLeastTest_905, ZeroDuration_905) {
    auto how_long = std::chrono::nanoseconds(0);
    int initial = 1;
    auto result = run_for_at_least<ClockType>(
        how_long, initial, [](int iters) -> int {
            return iters * 3;
        });

    EXPECT_GE(result.elapsed, how_long);
    EXPECT_GE(result.iterations, initial);
}

// Test with a function returning a different type (double)
TEST_F(RunForAtLeastTest_905, FunctionReturningDouble_905) {
    auto how_long = std::chrono::nanoseconds(1);
    auto result = run_for_at_least<ClockType>(
        how_long, 1, [](int iters) -> double {
            return 3.14 * iters;
        });

    EXPECT_GE(result.elapsed, how_long);
    EXPECT_GT(result.result, 0.0);
}

// Test with a function returning a string
TEST_F(RunForAtLeastTest_905, FunctionReturningString_905) {
    auto how_long = std::chrono::nanoseconds(1);
    auto result = run_for_at_least<ClockType>(
        how_long, 1, [](int iters) -> std::string {
            return std::string("result_") + std::to_string(iters);
        });

    EXPECT_GE(result.elapsed, how_long);
    EXPECT_FALSE(result.result.empty());
}

// Test that using std::function works
TEST_F(RunForAtLeastTest_905, StdFunctionCallable_905) {
    auto how_long = std::chrono::nanoseconds(1);
    std::function<int(int)> fun = [](int iters) -> int { return iters + 1; };
    auto result = run_for_at_least<ClockType>(
        how_long, 1, std::move(fun));

    EXPECT_GE(result.elapsed, how_long);
    EXPECT_GE(result.iterations, 1);
}

// Test with system_clock as alternative clock type
TEST_F(RunForAtLeastTest_905, SystemClockWorks_905) {
    using SysClock = std::chrono::system_clock;
    auto how_long = std::chrono::nanoseconds(1);
    auto result = run_for_at_least<SysClock>(
        how_long, 1, [](int iters) -> int {
            return iters;
        });

    EXPECT_GE(result.elapsed, how_long);
}

// Test with high_resolution_clock
TEST_F(RunForAtLeastTest_905, HighResolutionClockWorks_905) {
    using HRClock = std::chrono::high_resolution_clock;
    auto how_long = std::chrono::nanoseconds(1);
    auto result = run_for_at_least<HRClock>(
        how_long, 1, [](int iters) -> int {
            return iters;
        });

    EXPECT_GE(result.elapsed, how_long);
}

// Test that elapsed, result, and iterations fields are all populated
TEST_F(RunForAtLeastTest_905, AllFieldsPopulated_905) {
    auto how_long = std::chrono::milliseconds(1);
    auto result = run_for_at_least<ClockType>(
        how_long, 1, [](int iters) -> int {
            volatile int sum = 0;
            for (int i = 0; i < iters; ++i) {
                sum += i;
            }
            return sum;
        });

    EXPECT_GE(result.elapsed.count(), 0);
    EXPECT_GE(result.iterations, 1);
    // result.result is some int value - just check it's accessible
    (void)result.result;
}

// Test with initial_iterations that is already large enough
TEST_F(RunForAtLeastTest_905, LargeInitialSatisfiesImmediately_905) {
    auto how_long = std::chrono::nanoseconds(1);
    int initial = 1000000;
    auto result = run_for_at_least<ClockType>(
        how_long, initial, [](int iters) -> int {
            volatile int sum = 0;
            for (int i = 0; i < iters; ++i) sum += i;
            return sum;
        });

    // With 1M iterations, even a trivial loop should take more than 1ns
    EXPECT_EQ(result.iterations, initial);
}

// Test consistency: running the same benchmark twice should give similar iteration counts
TEST_F(RunForAtLeastTest_905, ConsistentResults_905) {
    auto how_long = std::chrono::milliseconds(5);
    auto fun = [](int iters) -> int {
        volatile int sum = 0;
        for (int i = 0; i < iters; ++i) {
            for (int j = 0; j < 10; ++j) {
                sum += j;
            }
        }
        return sum;
    };

    auto result1 = run_for_at_least<ClockType>(how_long, 1, fun);
    auto result2 = run_for_at_least<ClockType>(how_long, 1, fun);

    // Both should have completed with reasonable iteration counts
    // They might differ by a factor of 2 since iterations double
    EXPECT_GE(result1.iterations, 1);
    EXPECT_GE(result2.iterations, 1);
    // The ratio should be within a factor of 4 (two doublings difference)
    if (result1.iterations > result2.iterations) {
        EXPECT_LE(result1.iterations / result2.iterations, 4);
    } else {
        EXPECT_LE(result2.iterations / result1.iterations, 4);
    }
}
