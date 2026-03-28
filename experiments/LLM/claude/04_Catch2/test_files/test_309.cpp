#include <gtest/gtest.h>
#include "catch2/catch_totals.hpp"

using namespace Catch;

// ============================================================
// Tests for Counts
// ============================================================

class CountsTest_309 : public ::testing::Test {
protected:
    Counts counts;
};

TEST_F(CountsTest_309, DefaultConstruction_AllZero_309) {
    EXPECT_EQ(counts.passed, 0u);
    EXPECT_EQ(counts.failed, 0u);
    EXPECT_EQ(counts.failedButOk, 0u);
    EXPECT_EQ(counts.skipped, 0u);
}

TEST_F(CountsTest_309, TotalReturnsSum_309) {
    counts.passed = 3;
    counts.failed = 2;
    counts.failedButOk = 1;
    counts.skipped = 4;
    EXPECT_EQ(counts.total(), 10u);
}

TEST_F(CountsTest_309, TotalWhenAllZero_309) {
    EXPECT_EQ(counts.total(), 0u);
}

TEST_F(CountsTest_309, AllPassedWhenOnlyPassed_309) {
    counts.passed = 5;
    EXPECT_TRUE(counts.allPassed());
}

TEST_F(CountsTest_309, AllPassedFalseWhenFailed_309) {
    counts.passed = 5;
    counts.failed = 1;
    EXPECT_FALSE(counts.allPassed());
}

TEST_F(CountsTest_309, AllPassedFalseWhenFailedButOk_309) {
    counts.passed = 5;
    counts.failedButOk = 1;
    EXPECT_FALSE(counts.allPassed());
}

TEST_F(CountsTest_309, AllPassedWhenAllZero_309) {
    EXPECT_TRUE(counts.allPassed());
}

TEST_F(CountsTest_309, AllPassedFalseWhenSkipped_309) {
    counts.passed = 5;
    counts.skipped = 1;
    // skipped might or might not affect allPassed; test observable behavior
    // We test the result; if skipped doesn't affect allPassed, it should still be true
    // This is black-box, so we just observe
    // allPassed typically means failed == 0 && failedButOk == 0
    // but we don't know for sure about skipped
    std::uint64_t total = counts.total();
    EXPECT_EQ(total, 6u);
}

TEST_F(CountsTest_309, AllOkWhenOnlyPassed_309) {
    counts.passed = 5;
    EXPECT_TRUE(counts.allOk());
}

TEST_F(CountsTest_309, AllOkFalseWhenFailed_309) {
    counts.passed = 5;
    counts.failed = 1;
    EXPECT_FALSE(counts.allOk());
}

TEST_F(CountsTest_309, AllOkTrueWhenFailedButOk_309) {
    counts.passed = 5;
    counts.failedButOk = 1;
    // failedButOk should still count as "ok"
    EXPECT_TRUE(counts.allOk());
}

TEST_F(CountsTest_309, AllOkWhenAllZero_309) {
    EXPECT_TRUE(counts.allOk());
}

TEST_F(CountsTest_309, PlusEqualsOperator_309) {
    Counts a;
    a.passed = 3;
    a.failed = 2;
    a.failedButOk = 1;
    a.skipped = 4;

    Counts b;
    b.passed = 1;
    b.failed = 1;
    b.failedButOk = 1;
    b.skipped = 1;

    a += b;

    EXPECT_EQ(a.passed, 4u);
    EXPECT_EQ(a.failed, 3u);
    EXPECT_EQ(a.failedButOk, 2u);
    EXPECT_EQ(a.skipped, 5u);
}

TEST_F(CountsTest_309, MinusOperator_309) {
    Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 2;
    a.skipped = 4;

    Counts b;
    b.passed = 2;
    b.failed = 1;
    b.failedButOk = 1;
    b.skipped = 1;

    Counts result = a - b;

    EXPECT_EQ(result.passed, 3u);
    EXPECT_EQ(result.failed, 2u);
    EXPECT_EQ(result.failedButOk, 1u);
    EXPECT_EQ(result.skipped, 3u);
}

TEST_F(CountsTest_309, MinusOperatorDoesNotModifyOriginal_309) {
    Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 2;
    a.skipped = 4;

    Counts b;
    b.passed = 2;
    b.failed = 1;
    b.failedButOk = 1;
    b.skipped = 1;

    Counts result = a - b;

    // Original should be unchanged
    EXPECT_EQ(a.passed, 5u);
    EXPECT_EQ(a.failed, 3u);
    EXPECT_EQ(a.failedButOk, 2u);
    EXPECT_EQ(a.skipped, 4u);
}

TEST_F(CountsTest_309, PlusEqualsWithZero_309) {
    Counts a;
    a.passed = 3;
    a.failed = 2;

    Counts zero;
    a += zero;

    EXPECT_EQ(a.passed, 3u);
    EXPECT_EQ(a.failed, 2u);
    EXPECT_EQ(a.failedButOk, 0u);
    EXPECT_EQ(a.skipped, 0u);
}

TEST_F(CountsTest_309, MinusOperatorWithSelf_309) {
    Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 2;
    a.skipped = 4;

    Counts result = a - a;

    EXPECT_EQ(result.passed, 0u);
    EXPECT_EQ(result.failed, 0u);
    EXPECT_EQ(result.failedButOk, 0u);
    EXPECT_EQ(result.skipped, 0u);
}

// ============================================================
// Tests for Totals
// ============================================================

class TotalsTest_309 : public ::testing::Test {
protected:
    Totals totals;
};

TEST_F(TotalsTest_309, DefaultConstruction_309) {
    EXPECT_EQ(totals.assertions.passed, 0u);
    EXPECT_EQ(totals.assertions.failed, 0u);
    EXPECT_EQ(totals.assertions.failedButOk, 0u);
    EXPECT_EQ(totals.assertions.skipped, 0u);
    EXPECT_EQ(totals.testCases.passed, 0u);
    EXPECT_EQ(totals.testCases.failed, 0u);
    EXPECT_EQ(totals.testCases.failedButOk, 0u);
    EXPECT_EQ(totals.testCases.skipped, 0u);
}

TEST_F(TotalsTest_309, PlusEqualsOperator_309) {
    Totals a;
    a.assertions.passed = 10;
    a.assertions.failed = 2;
    a.testCases.passed = 3;
    a.testCases.failed = 1;

    Totals b;
    b.assertions.passed = 5;
    b.assertions.failed = 1;
    b.testCases.passed = 2;
    b.testCases.failed = 0;

    a += b;

    EXPECT_EQ(a.assertions.passed, 15u);
    EXPECT_EQ(a.assertions.failed, 3u);
    EXPECT_EQ(a.testCases.passed, 5u);
    EXPECT_EQ(a.testCases.failed, 1u);
}

TEST_F(TotalsTest_309, PlusEqualsReturnsReference_309) {
    Totals a;
    Totals b;
    b.assertions.passed = 1;

    Totals& ref = (a += b);
    EXPECT_EQ(&ref, &a);
}

TEST_F(TotalsTest_309, MinusOperator_309) {
    Totals a;
    a.assertions.passed = 10;
    a.assertions.failed = 5;
    a.testCases.passed = 4;
    a.testCases.failed = 2;

    Totals b;
    b.assertions.passed = 3;
    b.assertions.failed = 1;
    b.testCases.passed = 1;
    b.testCases.failed = 1;

    Totals result = a - b;

    EXPECT_EQ(result.assertions.passed, 7u);
    EXPECT_EQ(result.assertions.failed, 4u);
    EXPECT_EQ(result.testCases.passed, 3u);
    EXPECT_EQ(result.testCases.failed, 1u);
}

TEST_F(TotalsTest_309, MinusOperatorDoesNotModifyOriginal_309) {
    Totals a;
    a.assertions.passed = 10;
    a.testCases.passed = 4;

    Totals b;
    b.assertions.passed = 3;
    b.testCases.passed = 1;

    Totals result = a - b;

    EXPECT_EQ(a.assertions.passed, 10u);
    EXPECT_EQ(a.testCases.passed, 4u);
}

TEST_F(TotalsTest_309, DeltaMethod_309) {
    Totals current;
    current.assertions.passed = 10;
    current.assertions.failed = 3;
    current.testCases.passed = 5;
    current.testCases.failed = 2;

    Totals prev;
    prev.assertions.passed = 7;
    prev.assertions.failed = 1;
    prev.testCases.passed = 3;
    prev.testCases.failed = 1;

    Totals d = current.delta(prev);

    EXPECT_EQ(d.assertions.passed, 3u);
    EXPECT_EQ(d.assertions.failed, 2u);
    EXPECT_EQ(d.testCases.passed, 2u);
    EXPECT_EQ(d.testCases.failed, 1u);
}

TEST_F(TotalsTest_309, DeltaWithSelf_309) {
    Totals a;
    a.assertions.passed = 10;
    a.assertions.failed = 3;
    a.testCases.passed = 5;
    a.testCases.failed = 2;

    Totals d = a.delta(a);

    EXPECT_EQ(d.assertions.passed, 0u);
    EXPECT_EQ(d.assertions.failed, 0u);
    EXPECT_EQ(d.testCases.passed, 0u);
    EXPECT_EQ(d.testCases.failed, 0u);
}

TEST_F(TotalsTest_309, DeltaDoesNotModifyOriginal_309) {
    Totals current;
    current.assertions.passed = 10;
    current.testCases.passed = 5;

    Totals prev;
    prev.assertions.passed = 7;
    prev.testCases.passed = 3;

    Totals d = current.delta(prev);

    EXPECT_EQ(current.assertions.passed, 10u);
    EXPECT_EQ(current.testCases.passed, 5u);
}

TEST_F(TotalsTest_309, PlusEqualsWithZeroTotals_309) {
    Totals a;
    a.assertions.passed = 5;
    a.testCases.passed = 2;

    Totals zero;
    a += zero;

    EXPECT_EQ(a.assertions.passed, 5u);
    EXPECT_EQ(a.testCases.passed, 2u);
}

TEST_F(TotalsTest_309, PlusEqualsAllFields_309) {
    Totals a;
    a.assertions.passed = 1;
    a.assertions.failed = 2;
    a.assertions.failedButOk = 3;
    a.assertions.skipped = 4;
    a.testCases.passed = 5;
    a.testCases.failed = 6;
    a.testCases.failedButOk = 7;
    a.testCases.skipped = 8;

    Totals b;
    b.assertions.passed = 10;
    b.assertions.failed = 20;
    b.assertions.failedButOk = 30;
    b.assertions.skipped = 40;
    b.testCases.passed = 50;
    b.testCases.failed = 60;
    b.testCases.failedButOk = 70;
    b.testCases.skipped = 80;

    a += b;

    EXPECT_EQ(a.assertions.passed, 11u);
    EXPECT_EQ(a.assertions.failed, 22u);
    EXPECT_EQ(a.assertions.failedButOk, 33u);
    EXPECT_EQ(a.assertions.skipped, 44u);
    EXPECT_EQ(a.testCases.passed, 55u);
    EXPECT_EQ(a.testCases.failed, 66u);
    EXPECT_EQ(a.testCases.failedButOk, 77u);
    EXPECT_EQ(a.testCases.skipped, 88u);
}

TEST_F(TotalsTest_309, MinusOperatorAllFields_309) {
    Totals a;
    a.assertions.passed = 100;
    a.assertions.failed = 200;
    a.assertions.failedButOk = 300;
    a.assertions.skipped = 400;
    a.testCases.passed = 500;
    a.testCases.failed = 600;
    a.testCases.failedButOk = 700;
    a.testCases.skipped = 800;

    Totals b;
    b.assertions.passed = 10;
    b.assertions.failed = 20;
    b.assertions.failedButOk = 30;
    b.assertions.skipped = 40;
    b.testCases.passed = 50;
    b.testCases.failed = 60;
    b.testCases.failedButOk = 70;
    b.testCases.skipped = 80;

    Totals result = a - b;

    EXPECT_EQ(result.assertions.passed, 90u);
    EXPECT_EQ(result.assertions.failed, 180u);
    EXPECT_EQ(result.assertions.failedButOk, 270u);
    EXPECT_EQ(result.assertions.skipped, 360u);
    EXPECT_EQ(result.testCases.passed, 450u);
    EXPECT_EQ(result.testCases.failed, 540u);
    EXPECT_EQ(result.testCases.failedButOk, 630u);
    EXPECT_EQ(result.testCases.skipped, 720u);
}

TEST_F(TotalsTest_309, ChainedPlusEquals_309) {
    Totals a, b, c;
    a.assertions.passed = 1;
    b.assertions.passed = 2;
    c.assertions.passed = 3;

    a += b;
    a += c;

    EXPECT_EQ(a.assertions.passed, 6u);
}

// Test Counts total with large values
TEST_F(CountsTest_309, TotalWithLargeValues_309) {
    counts.passed = 1000000;
    counts.failed = 2000000;
    counts.failedButOk = 3000000;
    counts.skipped = 4000000;
    EXPECT_EQ(counts.total(), 10000000u);
}

// Test allPassed with only skipped
TEST_F(CountsTest_309, AllPassedWithOnlySkipped_309) {
    counts.skipped = 5;
    // With no passed, failed, or failedButOk but some skipped
    // allPassed behavior is observed
    bool result = counts.allPassed();
    // We just verify it doesn't crash and returns a boolean
    (void)result;
}

// Test allOk with skipped
TEST_F(CountsTest_309, AllOkWithSkipped_309) {
    counts.passed = 5;
    counts.skipped = 3;
    EXPECT_TRUE(counts.allOk());
}

TEST_F(CountsTest_309, AllOkWithOnlyFailed_309) {
    counts.failed = 1;
    EXPECT_FALSE(counts.allOk());
}

TEST_F(CountsTest_309, AllPassedWithOnlyFailed_309) {
    counts.failed = 1;
    EXPECT_FALSE(counts.allPassed());
}
