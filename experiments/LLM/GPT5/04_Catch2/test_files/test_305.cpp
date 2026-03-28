// File: tests/counts_tests_305.cpp

#include <gtest/gtest.h>
#include "catch2/catch_totals.hpp"

using Catch::Counts;

namespace {

// Utility to create a Counts with given fields (avoids assumptions about constructors)
Counts makeCounts(uint64_t p, uint64_t f, uint64_t fbo, uint64_t s) {
    Counts c;
    c.passed = p;
    c.failed = f;
    c.failedButOk = fbo;
    c.skipped = s;
    return c;
}

} // namespace

// --- total() ---

// Normal operation: total sums all four counters
TEST(CountsTest_305, Total_SumsAllCounts_305) {
    Counts c = makeCounts(/*passed*/3, /*failed*/2, /*failedButOk*/1, /*skipped*/4);
    EXPECT_EQ(c.total(), 3u + 2u + 1u + 4u);
}

// Boundary: total with all zeros
TEST(CountsTest_305, Total_AllZero_305) {
    Counts c = makeCounts(0, 0, 0, 0);
    EXPECT_EQ(c.total(), 0u);
}

// Boundary: total with large (but safe) values
TEST(CountsTest_305, Total_LargeValues_NoOverflow_305) {
    // Choose values that clearly fit within uint64_t without overflow when summed
    const uint64_t big = 1000000000000ULL; // 1e12
    Counts c = makeCounts(big, big, big, big);
    EXPECT_EQ(c.total(), big * 4);
}

// --- operator+= ---

// Normal operation: += accumulates field-wise and returns self-reference
TEST(CountsTest_305, PlusEqual_AccumulatesAndReturnsSelf_305) {
    Counts a = makeCounts(1, 2, 3, 4);
    Counts b = makeCounts(5, 6, 7, 8);

    Counts& ret = (a += b);

    // Check it returned a reference to self
    EXPECT_EQ(&ret, &a);

    // Check observable state through public fields
    EXPECT_EQ(a.passed,      1u + 5u);
    EXPECT_EQ(a.failed,      2u + 6u);
    EXPECT_EQ(a.failedButOk, 3u + 7u);
    EXPECT_EQ(a.skipped,     4u + 8u);
}

// Chaining: (a += b) is chainable and equivalent to sequential additions
TEST(CountsTest_305, PlusEqual_Chaining_305) {
    Counts a = makeCounts(1, 1, 1, 1);
    Counts b = makeCounts(2, 3, 5, 7);
    Counts c = makeCounts(11, 13, 17, 19);

    // Chain on b first to avoid any assumptions about evaluation order beyond operator contract
    b += c;            // update b
    a += b;            // then add the updated b into a

    EXPECT_EQ(a.passed,      1u + (2u + 11u));
    EXPECT_EQ(a.failed,      1u + (3u + 13u));
    EXPECT_EQ(a.failedButOk, 1u + (5u + 17u));
    EXPECT_EQ(a.skipped,     1u + (7u + 19u));
}

// --- operator- ---

// Normal operation: subtraction per-field where minuend >= subtrahend (to avoid unsigned underflow assumptions)
TEST(CountsTest_305, Minus_SubtractsPerField_NoUnderflow_305) {
    Counts lhs = makeCounts(10, 9, 8, 7);
    Counts rhs = makeCounts( 1, 2, 3, 4);

    Counts diff = lhs - rhs;

    // Verify observable result via public fields
    EXPECT_EQ(diff.passed,      10u - 1u);
    EXPECT_EQ(diff.failed,       9u - 2u);
    EXPECT_EQ(diff.failedButOk,  8u - 3u);
    EXPECT_EQ(diff.skipped,      7u - 4u);
}

// Identity-ish property: subtracting zero counts leaves the value unchanged
TEST(CountsTest_305, Minus_SubtractZero_IsNoOp_305) {
    Counts lhs = makeCounts(4, 3, 2, 1);
    Counts zero = makeCounts(0, 0, 0, 0);

    Counts diff = lhs - zero;

    EXPECT_EQ(diff.passed,      lhs.passed);
    EXPECT_EQ(diff.failed,      lhs.failed);
    EXPECT_EQ(diff.failedButOk, lhs.failedButOk);
    EXPECT_EQ(diff.skipped,     lhs.skipped);
}

// --- allPassed() & allOk() ---
// We only assert in unambiguous scenarios observable via the interface.

// allPassed: clearly true when there are no failures of any kind
TEST(CountsTest_305, AllPassed_TrueWhenNoFailures_305) {
    Counts c = makeCounts(/*passed*/5, /*failed*/0, /*failedButOk*/0, /*skipped*/0);
    EXPECT_TRUE(c.allPassed());
}

// allPassed: clearly false when there is at least one failed
TEST(CountsTest_305, AllPassed_FalseWhenFailedPresent_305) {
    Counts c = makeCounts(0, /*failed*/1, 0, 0);
    EXPECT_FALSE(c.allPassed());
}

// allOk: clearly true when there are zero hard failures
TEST(CountsTest_305, AllOk_TrueWhenNoHardFailures_305) {
    Counts c = makeCounts(3, /*failed*/0, /*failedButOk*/0, 2);
    EXPECT_TRUE(c.allOk());
}

// allOk: clearly false when there is at least one hard failure
TEST(CountsTest_305, AllOk_FalseWhenHardFailuresPresent_305) {
    Counts c = makeCounts(0, /*failed*/2, 0, 0);
    EXPECT_FALSE(c.allOk());
}
