// File: tests/totals_operator_plus_equals_309_tests.cpp
#include <gtest/gtest.h>
#include <limits>
#include "catch2/catch_totals.hpp"  // Adjust include path if needed

using Catch::Counts;
using Catch::Totals;

namespace {

// Helper to build Counts via public fields only (interface-based)
Counts MakeCounts(uint64_t passed, uint64_t failed,
                  uint64_t failedButOk, uint64_t skipped) {
    Counts c;
    c.passed = passed;
    c.failed = failed;
    c.failedButOk = failedButOk;
    c.skipped = skipped;
    return c;
}

// Helper to check equality of Counts via observable public fields
void ExpectCountsEq(const Counts& c, uint64_t passed, uint64_t failed,
                    uint64_t failedButOk, uint64_t skipped) {
    EXPECT_EQ(c.passed,      passed);
    EXPECT_EQ(c.failed,      failed);
    EXPECT_EQ(c.failedButOk, failedButOk);
    EXPECT_EQ(c.skipped,     skipped);
}

} // namespace

// Normal operation: sums each sub-count in both members (assertions & testCases)
TEST(TotalsOperatorPlusEquals_309, AddsCorrespondingCounts_309) {
    Totals a;
    a.assertions = MakeCounts(1, 2, 3, 4);
    a.testCases  = MakeCounts(5, 6, 7, 8);

    Totals b;
    b.assertions = MakeCounts(2, 3, 4, 5);
    b.testCases  = MakeCounts(1, 1, 1, 1);

    a += b;

    ExpectCountsEq(a.assertions, 1+2, 2+3, 3+4, 4+5);
    ExpectCountsEq(a.testCases,  5+1, 6+1, 7+1, 8+1);
}

// Boundary: adding a zero Totals should leave the left-hand side unchanged
TEST(TotalsOperatorPlusEquals_309, AddingZeroTotalsNoChange_309) {
    Totals a;
    a.assertions = MakeCounts(10, 0, 1, 0);
    a.testCases  = MakeCounts(0,  9, 0, 2);

    Totals zero; // default-initialized: all counts are 0 by interface defaults

    a += zero;

    ExpectCountsEq(a.assertions, 10, 0, 1, 0);
    ExpectCountsEq(a.testCases,   0, 9, 0, 2);
}

// Normal operation: chained additions behave associatively on the left operand
TEST(TotalsOperatorPlusEquals_309, ChainedAdditionAccumulates_309) {
    Totals a;
    a.assertions = MakeCounts(1, 1, 1, 1);
    a.testCases  = MakeCounts(2, 2, 2, 2);

    Totals b;
    b.assertions = MakeCounts(3, 4, 5, 6);
    b.testCases  = MakeCounts(1, 0, 1, 0);

    Totals c;
    c.assertions = MakeCounts(7, 8, 9, 10);
    c.testCases  = MakeCounts(0, 1, 0, 1);

    a += b;
    a += c;

    ExpectCountsEq(a.assertions, 1+3+7, 1+4+8, 1+5+9, 1+6+10);
    ExpectCountsEq(a.testCases,  2+1+0, 2+0+1, 2+1+0, 2+0+1);
}

// Edge case: self-addition should double each count (well-defined via interface)
TEST(TotalsOperatorPlusEquals_309, SelfAdditionDoublesValues_309) {
    Totals t;
    t.assertions = MakeCounts(2, 3, 4, 5);
    t.testCases  = MakeCounts(6, 7, 8, 9);

    // Copy expected via public fields only
    Counts a0 = t.assertions;
    Counts c0 = t.testCases;

    t += t;

    ExpectCountsEq(t.assertions, a0.passed*2, a0.failed*2, a0.failedButOk*2, a0.skipped*2);
    ExpectCountsEq(t.testCases,  c0.passed*2, c0.failed*2, c0.failedButOk*2, c0.skipped*2);
}

// Boundary: large values (stay within uint64_t range; no overflow)
TEST(TotalsOperatorPlusEquals_309, LargeValuesNoOverflow_309) {
    const uint64_t M = std::numeric_limits<uint64_t>::max();
    // Choose values that do not overflow when added
    Counts bigA = MakeCounts(M - 100, M - 200, M - 300, M - 400);
    Counts bigB = MakeCounts(50,       150,      250,      350);

    Totals a;
    a.assertions = bigA;
    a.testCases  = bigA;

    Totals b;
    b.assertions = bigB;
    b.testCases  = bigB;

    a += b;

    ExpectCountsEq(a.assertions,
                   (M - 100) + 50, (M - 200) + 150, (M - 300) + 250, (M - 400) + 350);
    ExpectCountsEq(a.testCases,
                   (M - 100) + 50, (M - 200) + 150, (M - 300) + 250, (M - 400) + 350);
}

