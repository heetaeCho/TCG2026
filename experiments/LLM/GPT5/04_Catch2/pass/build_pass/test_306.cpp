// File: counts_allPassed_tests_306.cpp
#include <gtest/gtest.h>
#include <cstdint>

// Include the production header as given in the prompt
#include "catch2/catch_totals.hpp"

using Catch::Counts;

namespace {

// Helper to make a Counts with explicit fields.
Counts MakeCounts(std::uint64_t passed,
                  std::uint64_t failed,
                  std::uint64_t failedButOk,
                  std::uint64_t skipped) {
    Counts c;
    c.passed = passed;
    c.failed = failed;
    c.failedButOk = failedButOk;
    c.skipped = skipped;
    return c;
}

} // namespace

// Normal operation: all zero -> true
TEST(CountsTest_306, AllZero_ReturnsTrue_306) {
    Counts c = MakeCounts(0, 0, 0, 0);
    EXPECT_TRUE(c.allPassed());
}

// Normal operation: non-zero failed -> false
TEST(CountsTest_306, NonZeroFailed_ReturnsFalse_306) {
    Counts c = MakeCounts(0, 1, 0, 0);
    EXPECT_FALSE(c.allPassed());
}

// Normal operation: non-zero failedButOk -> false
TEST(CountsTest_306, NonZeroFailedButOk_ReturnsFalse_306) {
    Counts c = MakeCounts(0, 0, 1, 0);
    EXPECT_FALSE(c.allPassed());
}

// Normal operation: non-zero skipped -> false
TEST(CountsTest_306, NonZeroSkipped_ReturnsFalse_306) {
    Counts c = MakeCounts(0, 0, 0, 1);
    EXPECT_FALSE(c.allPassed());
}

// Boundary/behavioral detail from interface: passed should not affect result
TEST(CountsTest_306, PassedNonZero_OthersZero_StillTrue_306) {
    Counts c = MakeCounts(42, 0, 0, 0);
    EXPECT_TRUE(c.allPassed());
}

// Boundary: very large values (uint64 max) -> false
TEST(CountsTest_306, LargeValuesInFailedFields_ReturnsFalse_306) {
    constexpr std::uint64_t U = std::numeric_limits<std::uint64_t>::max();
    Counts c1 = MakeCounts(0, U, 0, 0);
    Counts c2 = MakeCounts(0, 0, U, 0);
    Counts c3 = MakeCounts(0, 0, 0, U);
    EXPECT_FALSE(c1.allPassed());
    EXPECT_FALSE(c2.allPassed());
    EXPECT_FALSE(c3.allPassed());
}

// Const-correctness / no side effects observable via public interface
TEST(CountsTest_306, CallingAllPassedDoesNotMutateState_306) {
    Counts c = MakeCounts(7, 0, 0, 0);
    // Snapshot before
    Counts before = c;
    // Call const method
    (void)c.allPassed();
    // Verify no public fields changed
    EXPECT_EQ(before.passed, c.passed);
    EXPECT_EQ(before.failed, c.failed);
    EXPECT_EQ(before.failedButOk, c.failedButOk);
    EXPECT_EQ(before.skipped, c.skipped);
}
