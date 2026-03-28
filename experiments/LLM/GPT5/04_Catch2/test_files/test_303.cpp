// File: tests/counts_operator_minus_tests_303.cpp
#include <gtest/gtest.h>
#include <cstdint>

// Include the provided interface
#include "catch2/catch_totals.hpp"

using Catch::Counts;

// A simple fixture to keep names consistent, though not strictly required.
class CountsTest_303 : public ::testing::Test {};

// Normal operation: element-wise subtraction across all fields.
TEST_F(CountsTest_303, SubtractBasic_303) {
    Counts a; a.passed = 10; a.failed = 4; a.failedButOk = 3; a.skipped = 7;
    Counts b; b.passed = 6;  b.failed = 1; b.failedButOk = 2; b.skipped = 5;

    Counts diff = a - b;

    EXPECT_EQ(diff.passed,       10u - 6u);
    EXPECT_EQ(diff.failed,       4u  - 1u);
    EXPECT_EQ(diff.failedButOk,  3u  - 2u);
    EXPECT_EQ(diff.skipped,      7u  - 5u);
}

// Boundary: subtracting zero does not change values.
TEST_F(CountsTest_303, SubtractZero_303) {
    Counts a; a.passed = 0; a.failed = 0; a.failedButOk = 0; a.skipped = 0;
    Counts zero; // defaults to 0 for all fields

    Counts diff = a - zero;

    EXPECT_EQ(diff.passed, 0u);
    EXPECT_EQ(diff.failed, 0u);
    EXPECT_EQ(diff.failedButOk, 0u);
    EXPECT_EQ(diff.skipped, 0u);

    // Also with nonzero 'a'
    a.passed = 5; a.failed = 1; a.failedButOk = 2; a.skipped = 9;
    diff = a - zero;
    EXPECT_EQ(diff.passed, 5u);
    EXPECT_EQ(diff.failed, 1u);
    EXPECT_EQ(diff.failedButOk, 2u);
    EXPECT_EQ(diff.skipped, 9u);
}

// Boundary: subtracting an object from itself yields zeros.
TEST_F(CountsTest_303, SubtractSelf_303) {
    Counts a; a.passed = 123; a.failed = 456; a.failedButOk = 7; a.skipped = 89;

    Counts diff = a - a;

    EXPECT_EQ(diff.passed, 0u);
    EXPECT_EQ(diff.failed, 0u);
    EXPECT_EQ(diff.failedButOk, 0u);
    EXPECT_EQ(diff.skipped, 0u);
}

// Non-mutating behavior: operator- should not modify its operands.
TEST_F(CountsTest_303, NonMutatingOperands_303) {
    Counts lhs; lhs.passed = 8; lhs.failed = 3; lhs.failedButOk = 2; lhs.skipped = 1;
    Counts rhs; rhs.passed = 5; rhs.failed = 1; rhs.failedButOk = 1; rhs.skipped = 1;

    // Keep copies to compare after the operation
    Counts lhs_before = lhs;
    Counts rhs_before = rhs;

    Counts diff = lhs - rhs;
    (void)diff; // suppress unused warning if assertions fail early

    EXPECT_EQ(lhs.passed, lhs_before.passed);
    EXPECT_EQ(lhs.failed, lhs_before.failed);
    EXPECT_EQ(lhs.failedButOk, lhs_before.failedButOk);
    EXPECT_EQ(lhs.skipped, lhs_before.skipped);

    EXPECT_EQ(rhs.passed, rhs_before.passed);
    EXPECT_EQ(rhs.failed, rhs_before.failed);
    EXPECT_EQ(rhs.failedButOk, rhs_before.failedButOk);
    EXPECT_EQ(rhs.skipped, rhs_before.skipped);
}

// Exceptional/boundary observable via unsigned wraparound: subtracting larger from smaller.
TEST_F(CountsTest_303, UnderflowWraparound_303) {
    Counts a; a.passed = 0; a.failed = 0; a.failedButOk = 0; a.skipped = 0;
    Counts b; b.passed = 1; b.failed = 2; b.failedButOk = 3; b.skipped = 4;

    Counts diff = a - b;

    // For unsigned 64-bit subtraction, underflow wraps modulo 2^64.
    // E.g., 0 - 1 == UINT64_MAX, 0 - 2 == UINT64_MAX - 1, etc.
    EXPECT_EQ(diff.passed,       std::numeric_limits<std::uint64_t>::max());
    EXPECT_EQ(diff.failed,       std::numeric_limits<std::uint64_t>::max() - 1);
    EXPECT_EQ(diff.failedButOk,  std::numeric_limits<std::uint64_t>::max() - 2);
    EXPECT_EQ(diff.skipped,      std::numeric_limits<std::uint64_t>::max() - 3);
}

// Verify 'skipped' is included in the subtraction (coverage of all fields).
TEST_F(CountsTest_303, SubtractIncludesSkipped_303) {
    Counts a; a.passed = 0; a.failed = 0; a.failedButOk = 0; a.skipped = 10;
    Counts b; b.passed = 0; b.failed = 0; b.failedButOk = 0; b.skipped = 6;

    Counts diff = a - b;

    EXPECT_EQ(diff.skipped, 4u);
    // Sanity: other fields unaffected by zero subtraction
    EXPECT_EQ(diff.passed, 0u);
    EXPECT_EQ(diff.failed, 0u);
    EXPECT_EQ(diff.failedButOk, 0u);
}
