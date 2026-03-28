// File: tests/counts_operator_plus_equals_test.cpp
#include <gtest/gtest.h>
#include <limits>
#include "catch2/catch_totals.hpp"

using Catch::Counts;

class CountsTest_304 : public ::testing::Test {
protected:
    Counts a{};
    Counts b{};
    Counts c{};
};

// Normal operation: verifies that all public counters are aggregated by operator+=
TEST_F(CountsTest_304, AddAggregatesAllFields_304) {
    a.passed = 1;      a.failed = 2;      a.failedButOk = 3;      a.skipped = 4;
    b.passed = 5;      b.failed = 6;      b.failedButOk = 7;      b.skipped = 8;

    a += b;

    EXPECT_EQ(a.passed,       1u + 5u);
    EXPECT_EQ(a.failed,       2u + 6u);
    EXPECT_EQ(a.failedButOk,  3u + 7u);
    EXPECT_EQ(a.skipped,      4u + 8u);
}

// Boundary condition: adding zero-valued counts should leave the left-hand side unchanged
TEST_F(CountsTest_304, AddZeroNoChange_304) {
    a.passed = 10;     a.failed = 20;     a.failedButOk = 30;     a.skipped = 40;
    // b is default-initialized to zeros

    a += b;

    EXPECT_EQ(a.passed,       10u);
    EXPECT_EQ(a.failed,       20u);
    EXPECT_EQ(a.failedButOk,  30u);
    EXPECT_EQ(a.skipped,      40u);
}

// API behavior: operator+= returns a reference to *this, enabling chaining
TEST_F(CountsTest_304, ReturnsSelfReferenceForChaining_304) {
    a.passed = 1;      a.failed = 2;      a.failedButOk = 3;      a.skipped = 4;
    b.passed = 10;     b.failed = 20;     b.failedButOk = 30;     b.skipped = 40;
    c.passed = 100;    c.failed = 200;    c.failedButOk = 300;    c.skipped = 400;

    // Verify that chaining compiles and aggregates both operands
    (a += b) += c;

    EXPECT_EQ(a.passed,       1u + 10u + 100u);
    EXPECT_EQ(a.failed,       2u + 20u + 200u);
    EXPECT_EQ(a.failedButOk,  3u + 30u + 300u);
    EXPECT_EQ(a.skipped,      4u + 40u + 400u);
}

// Edge case: self-add — observable behavior should be deterministic via the public API
TEST_F(CountsTest_304, SelfAddDoublesEachField_304) {
    a.passed = 3;      a.failed = 5;      a.failedButOk = 7;      a.skipped = 9;

    a += a;

    EXPECT_EQ(a.passed,       3u * 2u);
    EXPECT_EQ(a.failed,       5u * 2u);
    EXPECT_EQ(a.failedButOk,  7u * 2u);
    EXPECT_EQ(a.skipped,      9u * 2u);
}

// Large values (within safe range): verify arithmetic without overflow assumptions
TEST_F(CountsTest_304, LargeValuesWithinRange_304) {
    const auto half_minus_1 = std::numeric_limits<std::uint64_t>::max() / 2 - 1;

    a.passed = half_minus_1;
    a.failed = half_minus_1;
    a.failedButOk = half_minus_1;
    a.skipped = half_minus_1;

    b.passed = 1;
    b.failed = 2;
    b.failedButOk = 3;
    b.skipped = 4;

    a += b;

    EXPECT_EQ(a.passed,       half_minus_1 + 1);
    EXPECT_EQ(a.failed,       half_minus_1 + 2);
    EXPECT_EQ(a.failedButOk,  half_minus_1 + 3);
    EXPECT_EQ(a.skipped,      half_minus_1 + 4);
}
