// File: tests/benchmark_warmup_tests_908.cpp

#include <gtest/gtest.h>
#include <chrono>
#include "Catch2/extras/catch_amalgamated.hpp"

namespace C = Catch::Benchmark::Detail;

//
// Test notes (black-box):
// - warmup<Clock>() returns an int (iterations count) from an internal run.
// - We don't assume how it's computed; we only check observable properties:
//   * It returns without throwing.
//   * The returned iteration count is >= 0 (sane, non-negative).
//   * It completes in a reasonable time window (should not hang).
// - We avoid asserting equality across clocks or identical values across runs,
//   because that would depend on internal details.
//
class WarmupTests_908 : public ::testing::Test {};

// Normal operation with steady_clock
TEST_F(WarmupTests_908, SteadyClock_ReturnsNonNegative_908) {
    // Act
    int iterations = C::warmup<std::chrono::steady_clock>();

    // Assert
    // Observable behavior: should be a sane, non-negative iteration count.
    EXPECT_GE(iterations, 0);
}

// Normal operation with high_resolution_clock
TEST_F(WarmupTests_908, HighResClock_ReturnsNonNegative_908) {
    int iterations = C::warmup<std::chrono::high_resolution_clock>();
    EXPECT_GE(iterations, 0);
}

// Normal operation with system_clock (less ideal for benchmarking,
// but still a standard clock type—this checks template robustness)
TEST_F(WarmupTests_908, SystemClock_ReturnsNonNegative_908) {
    int iterations = C::warmup<std::chrono::system_clock>();
    EXPECT_GE(iterations, 0);
}

// Boundary/robustness: The call should complete in a reasonable time.
// We do not assert exact timing—just that it does not take excessively long.
// This guards against accidental hangs/regressions observable at the interface.
TEST_F(WarmupTests_908, CompletesWithinReasonableTime_908) {
    using namespace std::chrono;

    const auto start = steady_clock::now();

    // Act
    (void)C::warmup<std::chrono::steady_clock>();

    const auto end   = steady_clock::now();
    const auto took  = duration_cast<milliseconds>(end - start);

    // Assert a generous upper bound that should easily pass under normal conditions.
    // We avoid strict lower/upper bounds to not encode implementation details.
    EXPECT_LT(took, seconds(5)) << "warmup() took too long and might be hanging/regressed";
}

// Smoke: Multiple invocations should be safe and return sane values.
// We do not assert equality across calls (to avoid relying on internal logic).
TEST_F(WarmupTests_908, MultipleInvocationsRemainSane_908) {
    int a = C::warmup<std::chrono::steady_clock>();
    int b = C::warmup<std::chrono::steady_clock>();

    EXPECT_GE(a, 0);
    EXPECT_GE(b, 0);
}
