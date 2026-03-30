// totals_operator_minus_test_308.cpp
#include <gtest/gtest.h>
#include <cstdint>

// Headers under test (use your actual include paths)
#include "catch2/catch_totals.hpp"

using Catch::Counts;
using Catch::Totals;

// Small helper to build Totals from two Counts
static Totals MakeTotals(const Counts& assertions, const Counts& testCases) {
    Totals t;
    t.assertions = assertions;
    t.testCases  = testCases;
    return t;
}

// Verifies that Totals::operator- returns a Totals whose fields equal
// the per-field results of Counts::operator- on corresponding members.
TEST(TotalsOperatorMinusTest_308, SubtractsAssertionsAndTestCases_308) {
    Counts a_assert{}; a_assert.passed = 5; a_assert.failed = 2; a_assert.failedButOk = 1; a_assert.skipped = 3;
    Counts a_cases{};  a_cases.passed  = 2; a_cases.failed  = 1; a_cases.failedButOk  = 0; a_cases.skipped  = 0;

    Counts b_assert{}; b_assert.passed = 1; b_assert.failed = 1; b_assert.failedButOk = 0; b_assert.skipped = 1;
    Counts b_cases{};  b_cases.passed  = 1; b_cases.failed  = 0; b_cases.failedButOk  = 0; b_cases.skipped  = 0;

    Totals A = MakeTotals(a_assert, a_cases);
    Totals B = MakeTotals(b_assert, b_cases);

    Totals diff = A - B;

    Counts expectedAssertions = a_assert - b_assert;
    Counts expectedTestCases  = a_cases  - b_cases;

    EXPECT_EQ(diff.assertions.passed,      expectedAssertions.passed);
    EXPECT_EQ(diff.assertions.failed,      expectedAssertions.failed);
    EXPECT_EQ(diff.assertions.failedButOk, expectedAssertions.failedButOk);
    EXPECT_EQ(diff.assertions.skipped,     expectedAssertions.skipped);

    EXPECT_EQ(diff.testCases.passed,       expectedTestCases.passed);
    EXPECT_EQ(diff.testCases.failed,       expectedTestCases.failed);
    EXPECT_EQ(diff.testCases.failedButOk,  expectedTestCases.failedButOk);
    EXPECT_EQ(diff.testCases.skipped,      expectedTestCases.skipped);
}

// Boundary: zero totals. Ensures neutral element behavior is delegated exactly
// to Counts::operator- for both members.
TEST(TotalsOperatorMinusTest_308, ZeroMinusZero_308) {
    Counts zeroA{}; // all zeros by default
    Counts zeroB{};

    Totals A = MakeTotals(zeroA, zeroA);
    Totals B = MakeTotals(zeroB, zeroB);

    Totals diff = A - B;

    Counts expectedAssertions = zeroA - zeroB;
    Counts expectedTestCases  = zeroA - zeroB;

    EXPECT_EQ(diff.assertions.passed,      expectedAssertions.passed);
    EXPECT_EQ(diff.assertions.failed,      expectedAssertions.failed);
    EXPECT_EQ(diff.assertions.failedButOk, expectedAssertions.failedButOk);
    EXPECT_EQ(diff.assertions.skipped,     expectedAssertions.skipped);

    EXPECT_EQ(diff.testCases.passed,       expectedTestCases.passed);
    EXPECT_EQ(diff.testCases.failed,       expectedTestCases.failed);
    EXPECT_EQ(diff.testCases.failedButOk,  expectedTestCases.failedButOk);
    EXPECT_EQ(diff.testCases.skipped,      expectedTestCases.skipped);
}

// Independence: changing only assertions in the subtrahend affects only
// the assertions part of the result (and vice versa for testCases).
TEST(TotalsOperatorMinusTest_308, MixedFieldsIndependently_308) {
    Counts a_assert{}; a_assert.passed = 10;
    Counts a_cases{};  a_cases.failed  = 7;

    Counts b_assert{}; b_assert.passed = 3;   // only assertions differ
    Counts b_cases{};  /* leave testCases zero */;

    Totals A = MakeTotals(a_assert, a_cases);
    Totals B = MakeTotals(b_assert, b_cases);

    Totals diff = A - B;

    Counts expectedAssertions = a_assert - b_assert;
    Counts expectedTestCases  = a_cases  - b_cases;

    // Assertions part follows a_assert - b_assert
    EXPECT_EQ(diff.assertions.passed,      expectedAssertions.passed);
    EXPECT_EQ(diff.assertions.failed,      expectedAssertions.failed);
    EXPECT_EQ(diff.assertions.failedButOk, expectedAssertions.failedButOk);
    EXPECT_EQ(diff.assertions.skipped,     expectedAssertions.skipped);

    // testCases part is unaffected by b_assert and follows a_cases - b_cases
    EXPECT_EQ(diff.testCases.passed,       expectedTestCases.passed);
    EXPECT_EQ(diff.testCases.failed,       expectedTestCases.failed);
    EXPECT_EQ(diff.testCases.failedButOk,  expectedTestCases.failedButOk);
    EXPECT_EQ(diff.testCases.skipped,      expectedTestCases.skipped);
}

// Large values / potential underflow paths: we do not assert specific arithmetic,
// only that Totals::operator- mirrors Counts::operator- outcomes for each member.
TEST(TotalsOperatorMinusTest_308, LargeNumbersDelegation_308) {
    Counts bigA{}; bigA.passed = UINT64_C(1'000'000'000'000); bigA.failed = 0; bigA.failedButOk = 5; bigA.skipped = 2;
    Counts bigB{}; bigB.passed = UINT64_C(999'999'999'999);  bigB.failed = 7; bigB.failedButOk = 10; bigB.skipped = 3;

    Counts bigCA{}; bigCA.passed = UINT64_C(500'000'000'000); bigCA.failed = 4; bigCA.failedButOk = 0; bigCA.skipped = 0;
    Counts bigCB{}; bigCB.passed = UINT64_C(600'000'000'000); bigCB.failed = 1; bigCB.failedButOk = 0; bigCB.skipped = 5;

    Totals A = MakeTotals(bigA,  bigCA);
    Totals B = MakeTotals(bigB,  bigCB);

    Totals diff = A - B;

    Counts expectedAssertions = bigA  - bigB;
    Counts expectedTestCases  = bigCA - bigCB;

    EXPECT_EQ(diff.assertions.passed,      expectedAssertions.passed);
    EXPECT_EQ(diff.assertions.failed,      expectedAssertions.failed);
    EXPECT_EQ(diff.assertions.failedButOk, expectedAssertions.failedButOk);
    EXPECT_EQ(diff.assertions.skipped,     expectedAssertions.skipped);

    EXPECT_EQ(diff.testCases.passed,       expectedTestCases.passed);
    EXPECT_EQ(diff.testCases.failed,       expectedTestCases.failed);
    EXPECT_EQ(diff.testCases.failedButOk,  expectedTestCases.failedButOk);
    EXPECT_EQ(diff.testCases.skipped,      expectedTestCases.skipped);
}
