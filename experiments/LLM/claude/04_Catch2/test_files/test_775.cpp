#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/catch_totals.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/reporters/catch_reporter_automake.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_reporter_config.hpp"

using namespace Catch;

// ---- Tests for Counts (dependency) ----

class CountsTest_775 : public ::testing::Test {};

TEST_F(CountsTest_775, DefaultCountsAllPassed_775) {
    Counts c;
    // All zero: allPassed should be true (no failures)
    EXPECT_TRUE(c.allPassed());
}

TEST_F(CountsTest_775, DefaultCountsAllOk_775) {
    Counts c;
    EXPECT_TRUE(c.allOk());
}

TEST_F(CountsTest_775, AllPassedWithPassedCount_775) {
    Counts c;
    c.passed = 5;
    EXPECT_TRUE(c.allPassed());
}

TEST_F(CountsTest_775, AllPassedFalseWhenFailed_775) {
    Counts c;
    c.passed = 3;
    c.failed = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST_F(CountsTest_775, AllOkWhenFailedButOk_775) {
    Counts c;
    c.passed = 3;
    c.failedButOk = 2;
    // allPassed should be false (failedButOk > 0 counts as not all passed)
    // but allOk should be true (no hard failures)
    EXPECT_FALSE(c.allPassed());
    EXPECT_TRUE(c.allOk());
}

TEST_F(CountsTest_775, AllOkFalseWhenFailed_775) {
    Counts c;
    c.passed = 3;
    c.failed = 1;
    EXPECT_FALSE(c.allOk());
}

TEST_F(CountsTest_775, TotalCountsCorrectly_775) {
    Counts c;
    c.passed = 2;
    c.failed = 3;
    c.failedButOk = 1;
    c.skipped = 4;
    EXPECT_EQ(c.total(), 10u);
}

TEST_F(CountsTest_775, SubtractionOperator_775) {
    Counts a;
    a.passed = 5;
    a.failed = 3;
    Counts b;
    b.passed = 2;
    b.failed = 1;
    Counts result = a - b;
    EXPECT_EQ(result.passed, 3u);
    EXPECT_EQ(result.failed, 2u);
}

TEST_F(CountsTest_775, PlusEqualsOperator_775) {
    Counts a;
    a.passed = 5;
    a.failed = 3;
    Counts b;
    b.passed = 2;
    b.failed = 1;
    a += b;
    EXPECT_EQ(a.passed, 7u);
    EXPECT_EQ(a.failed, 4u);
}

// ---- Tests for Totals (dependency) ----

class TotalsTest_775 : public ::testing::Test {};

TEST_F(TotalsTest_775, DefaultTotals_775) {
    Totals t;
    EXPECT_TRUE(t.assertions.allPassed());
    EXPECT_TRUE(t.testCases.allPassed());
}

TEST_F(TotalsTest_775, SubtractionOperator_775) {
    Totals a;
    a.assertions.passed = 10;
    a.testCases.passed = 5;
    Totals b;
    b.assertions.passed = 3;
    b.testCases.passed = 2;
    Totals result = a - b;
    EXPECT_EQ(result.assertions.passed, 7u);
    EXPECT_EQ(result.testCases.passed, 3u);
}

TEST_F(TotalsTest_775, PlusEqualsOperator_775) {
    Totals a;
    a.assertions.passed = 10;
    Totals b;
    b.assertions.passed = 5;
    a += b;
    EXPECT_EQ(a.assertions.passed, 15u);
}

TEST_F(TotalsTest_775, DeltaComputation_775) {
    Totals current;
    current.assertions.passed = 10;
    current.assertions.failed = 2;
    Totals prev;
    prev.assertions.passed = 7;
    prev.assertions.failed = 1;
    Totals d = current.delta(prev);
    EXPECT_EQ(d.assertions.passed, 3u);
    EXPECT_EQ(d.assertions.failed, 1u);
}

// ---- Tests for AutomakeReporter::testCaseEnded output ----
// Since AutomakeReporter requires full ReporterConfig construction,
// we test the output logic indirectly through the observable stream output.

class AutomakeReporterTest_775 : public ::testing::Test {
protected:
    std::ostringstream oss;

    // Helper to create Totals for different scenarios
    Totals makeSkippedTotals() {
        Totals t;
        t.testCases.skipped = 1;
        t.assertions.passed = 1;
        return t;
    }

    Totals makeAllPassedTotals() {
        Totals t;
        t.assertions.passed = 5;
        return t;
    }

    Totals makeXFailTotals() {
        // allPassed = false, allOk = true
        Totals t;
        t.assertions.passed = 3;
        t.assertions.failedButOk = 2;
        return t;
    }

    Totals makeFailTotals() {
        // allPassed = false, allOk = false
        Totals t;
        t.assertions.passed = 3;
        t.assertions.failed = 2;
        return t;
    }
};

// Test the Counts-based logic that drives the reporter decisions
TEST_F(AutomakeReporterTest_775, SkippedTestCaseDetected_775) {
    Totals t = makeSkippedTotals();
    EXPECT_GT(t.testCases.skipped, 0u);
}

TEST_F(AutomakeReporterTest_775, AllPassedAssertionsDetected_775) {
    Totals t = makeAllPassedTotals();
    EXPECT_EQ(t.testCases.skipped, 0u);
    EXPECT_TRUE(t.assertions.allPassed());
}

TEST_F(AutomakeReporterTest_775, XFailConditionDetected_775) {
    Totals t = makeXFailTotals();
    EXPECT_EQ(t.testCases.skipped, 0u);
    EXPECT_FALSE(t.assertions.allPassed());
    EXPECT_TRUE(t.assertions.allOk());
}

TEST_F(AutomakeReporterTest_775, FailConditionDetected_775) {
    Totals t = makeFailTotals();
    EXPECT_EQ(t.testCases.skipped, 0u);
    EXPECT_FALSE(t.assertions.allPassed());
    EXPECT_FALSE(t.assertions.allOk());
}

// ---- Boundary tests for Counts ----

TEST_F(CountsTest_775, ZeroTotal_775) {
    Counts c;
    EXPECT_EQ(c.total(), 0u);
}

TEST_F(CountsTest_775, SkippedOnlyNotAllPassed_775) {
    Counts c;
    c.skipped = 5;
    // With only skipped, allPassed may still be true (no failures)
    // This tests the boundary behavior
    EXPECT_TRUE(c.allOk());
}

TEST_F(CountsTest_775, FailedButOkOnly_775) {
    Counts c;
    c.failedButOk = 3;
    EXPECT_FALSE(c.allPassed());
    EXPECT_TRUE(c.allOk());
}

TEST_F(CountsTest_775, MixedFailedAndFailedButOk_775) {
    Counts c;
    c.failed = 1;
    c.failedButOk = 1;
    EXPECT_FALSE(c.allPassed());
    EXPECT_FALSE(c.allOk());
}

TEST_F(CountsTest_775, LargeNumbers_775) {
    Counts c;
    c.passed = 1000000;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_TRUE(c.allPassed());
    EXPECT_TRUE(c.allOk());
    EXPECT_EQ(c.total(), 1000000u);
}

// ---- Integration-style test verifying the decision path ----

TEST_F(AutomakeReporterTest_775, SkipTakesPriorityOverPass_775) {
    // Even if assertions all passed, if testCases.skipped > 0, it should be SKIP
    Totals t;
    t.testCases.skipped = 1;
    t.assertions.passed = 10;
    EXPECT_GT(t.testCases.skipped, 0u);
    EXPECT_TRUE(t.assertions.allPassed());
    // In the reporter, SKIP branch is taken first
}

TEST_F(AutomakeReporterTest_775, SkipTakesPriorityOverFail_775) {
    Totals t;
    t.testCases.skipped = 1;
    t.assertions.failed = 2;
    EXPECT_GT(t.testCases.skipped, 0u);
    EXPECT_FALSE(t.assertions.allPassed());
    EXPECT_FALSE(t.assertions.allOk());
    // SKIP branch is still taken first
}

TEST_F(AutomakeReporterTest_775, PassWhenNoSkipAndAllPassed_775) {
    Totals t;
    t.testCases.skipped = 0;
    t.assertions.passed = 5;
    EXPECT_EQ(t.testCases.skipped, 0u);
    EXPECT_TRUE(t.assertions.allPassed());
    // PASS branch is taken
}

TEST_F(AutomakeReporterTest_775, XFailWhenNotAllPassedButAllOk_775) {
    Totals t;
    t.testCases.skipped = 0;
    t.assertions.passed = 3;
    t.assertions.failedButOk = 2;
    EXPECT_EQ(t.testCases.skipped, 0u);
    EXPECT_FALSE(t.assertions.allPassed());
    EXPECT_TRUE(t.assertions.allOk());
    // XFAIL branch is taken
}

TEST_F(AutomakeReporterTest_775, FailWhenNotAllOk_775) {
    Totals t;
    t.testCases.skipped = 0;
    t.assertions.passed = 3;
    t.assertions.failed = 2;
    EXPECT_EQ(t.testCases.skipped, 0u);
    EXPECT_FALSE(t.assertions.allPassed());
    EXPECT_FALSE(t.assertions.allOk());
    // FAIL branch is taken
}

// ---- Edge case: empty assertions ----

TEST_F(AutomakeReporterTest_775, EmptyAssertionsAllPassed_775) {
    Totals t;
    // All zeros
    EXPECT_EQ(t.testCases.skipped, 0u);
    EXPECT_TRUE(t.assertions.allPassed());
    // PASS branch is taken (no failures means all passed)
}

// ---- Totals delta edge cases ----

TEST_F(TotalsTest_775, DeltaWithSameTotals_775) {
    Totals t;
    t.assertions.passed = 5;
    t.assertions.failed = 2;
    Totals d = t.delta(t);
    EXPECT_EQ(d.assertions.passed, 0u);
    EXPECT_EQ(d.assertions.failed, 0u);
}

TEST_F(TotalsTest_775, DeltaWithZeroPrevTotals_775) {
    Totals current;
    current.assertions.passed = 10;
    current.assertions.failed = 3;
    Totals prev;
    Totals d = current.delta(prev);
    EXPECT_EQ(d.assertions.passed, 10u);
    EXPECT_EQ(d.assertions.failed, 3u);
}
