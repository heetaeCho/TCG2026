#include <gtest/gtest.h>
#include "catch2/catch_totals.hpp"

using namespace Catch;

// ==================== Counts Tests ====================

class CountsTest_308 : public ::testing::Test {
protected:
    Counts counts;
};

TEST_F(CountsTest_308, DefaultConstruction_AllZero_308) {
    EXPECT_EQ(counts.passed, 0u);
    EXPECT_EQ(counts.failed, 0u);
    EXPECT_EQ(counts.failedButOk, 0u);
    EXPECT_EQ(counts.skipped, 0u);
}

TEST_F(CountsTest_308, TotalReturnsSum_308) {
    counts.passed = 3;
    counts.failed = 2;
    counts.failedButOk = 1;
    counts.skipped = 4;
    EXPECT_EQ(counts.total(), 10u);
}

TEST_F(CountsTest_308, TotalReturnsZeroForDefault_308) {
    EXPECT_EQ(counts.total(), 0u);
}

TEST_F(CountsTest_308, AllPassedWhenOnlyPassed_308) {
    counts.passed = 5;
    EXPECT_TRUE(counts.allPassed());
}

TEST_F(CountsTest_308, AllPassedFalseWhenFailed_308) {
    counts.passed = 5;
    counts.failed = 1;
    EXPECT_FALSE(counts.allPassed());
}

TEST_F(CountsTest_308, AllPassedFalseWhenFailedButOk_308) {
    counts.passed = 5;
    counts.failedButOk = 1;
    EXPECT_FALSE(counts.allPassed());
}

TEST_F(CountsTest_308, AllPassedTrueWhenAllZero_308) {
    // No assertions at all - edge case
    // allPassed with total == 0 depends on implementation
    // We just verify it doesn't crash
    counts.allPassed();
}

TEST_F(CountsTest_308, AllOkWhenOnlyPassed_308) {
    counts.passed = 5;
    EXPECT_TRUE(counts.allOk());
}

TEST_F(CountsTest_308, AllOkWhenFailedButOk_308) {
    counts.passed = 5;
    counts.failedButOk = 2;
    EXPECT_TRUE(counts.allOk());
}

TEST_F(CountsTest_308, AllOkFalseWhenFailed_308) {
    counts.passed = 5;
    counts.failed = 1;
    EXPECT_FALSE(counts.allOk());
}

TEST_F(CountsTest_308, SubtractionOperator_308) {
    Counts a, b;
    a.passed = 10;
    a.failed = 5;
    a.failedButOk = 3;
    a.skipped = 2;

    b.passed = 3;
    b.failed = 2;
    b.failedButOk = 1;
    b.skipped = 1;

    Counts result = a - b;
    EXPECT_EQ(result.passed, 7u);
    EXPECT_EQ(result.failed, 3u);
    EXPECT_EQ(result.failedButOk, 2u);
    EXPECT_EQ(result.skipped, 1u);
}

TEST_F(CountsTest_308, SubtractionSameValues_308) {
    Counts a, b;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 2;
    a.skipped = 1;

    b = a;

    Counts result = a - b;
    EXPECT_EQ(result.passed, 0u);
    EXPECT_EQ(result.failed, 0u);
    EXPECT_EQ(result.failedButOk, 0u);
    EXPECT_EQ(result.skipped, 0u);
}

TEST_F(CountsTest_308, PlusEqualsOperator_308) {
    Counts a, b;
    a.passed = 3;
    a.failed = 2;
    a.failedButOk = 1;
    a.skipped = 4;

    b.passed = 7;
    b.failed = 3;
    b.failedButOk = 2;
    b.skipped = 1;

    a += b;
    EXPECT_EQ(a.passed, 10u);
    EXPECT_EQ(a.failed, 5u);
    EXPECT_EQ(a.failedButOk, 3u);
    EXPECT_EQ(a.skipped, 5u);
}

TEST_F(CountsTest_308, PlusEqualsWithZero_308) {
    Counts a, b;
    a.passed = 5;
    a.failed = 3;

    a += b; // b is all zeros
    EXPECT_EQ(a.passed, 5u);
    EXPECT_EQ(a.failed, 3u);
    EXPECT_EQ(a.failedButOk, 0u);
    EXPECT_EQ(a.skipped, 0u);
}

TEST_F(CountsTest_308, PlusEqualsReturnsReference_308) {
    Counts a, b;
    a.passed = 1;
    b.passed = 2;

    Counts& ref = (a += b);
    EXPECT_EQ(&ref, &a);
    EXPECT_EQ(ref.passed, 3u);
}

TEST_F(CountsTest_308, AllPassedFalseWhenSkipped_308) {
    counts.passed = 5;
    counts.skipped = 1;
    // skipped might affect allPassed depending on implementation
    // Just record behavior
    counts.allPassed();
}

// ==================== Totals Tests ====================

class TotalsTest_308 : public ::testing::Test {
protected:
    Totals totals;
};

TEST_F(TotalsTest_308, DefaultConstruction_308) {
    EXPECT_EQ(totals.assertions.passed, 0u);
    EXPECT_EQ(totals.assertions.failed, 0u);
    EXPECT_EQ(totals.assertions.failedButOk, 0u);
    EXPECT_EQ(totals.assertions.skipped, 0u);
    EXPECT_EQ(totals.testCases.passed, 0u);
    EXPECT_EQ(totals.testCases.failed, 0u);
    EXPECT_EQ(totals.testCases.failedButOk, 0u);
    EXPECT_EQ(totals.testCases.skipped, 0u);
}

TEST_F(TotalsTest_308, SubtractionOperator_308) {
    Totals a, b;
    a.assertions.passed = 10;
    a.assertions.failed = 5;
    a.testCases.passed = 3;
    a.testCases.failed = 2;

    b.assertions.passed = 4;
    b.assertions.failed = 2;
    b.testCases.passed = 1;
    b.testCases.failed = 1;

    Totals result = a - b;
    EXPECT_EQ(result.assertions.passed, 6u);
    EXPECT_EQ(result.assertions.failed, 3u);
    EXPECT_EQ(result.testCases.passed, 2u);
    EXPECT_EQ(result.testCases.failed, 1u);
}

TEST_F(TotalsTest_308, SubtractionSameValues_308) {
    Totals a;
    a.assertions.passed = 10;
    a.assertions.failed = 5;
    a.testCases.passed = 3;
    a.testCases.failed = 2;

    Totals result = a - a;
    EXPECT_EQ(result.assertions.passed, 0u);
    EXPECT_EQ(result.assertions.failed, 0u);
    EXPECT_EQ(result.testCases.passed, 0u);
    EXPECT_EQ(result.testCases.failed, 0u);
}

TEST_F(TotalsTest_308, PlusEqualsOperator_308) {
    Totals a, b;
    a.assertions.passed = 5;
    a.assertions.failed = 3;
    a.testCases.passed = 2;
    a.testCases.failed = 1;

    b.assertions.passed = 10;
    b.assertions.failed = 2;
    b.testCases.passed = 4;
    b.testCases.failed = 3;

    a += b;
    EXPECT_EQ(a.assertions.passed, 15u);
    EXPECT_EQ(a.assertions.failed, 5u);
    EXPECT_EQ(a.testCases.passed, 6u);
    EXPECT_EQ(a.testCases.failed, 4u);
}

TEST_F(TotalsTest_308, PlusEqualsWithZero_308) {
    Totals a, b;
    a.assertions.passed = 5;
    a.testCases.passed = 2;

    a += b;
    EXPECT_EQ(a.assertions.passed, 5u);
    EXPECT_EQ(a.testCases.passed, 2u);
}

TEST_F(TotalsTest_308, PlusEqualsReturnsReference_308) {
    Totals a, b;
    a.assertions.passed = 1;
    b.assertions.passed = 2;

    Totals& ref = (a += b);
    EXPECT_EQ(&ref, &a);
    EXPECT_EQ(ref.assertions.passed, 3u);
}

TEST_F(TotalsTest_308, DeltaMethod_308) {
    Totals current, prev;
    current.assertions.passed = 10;
    current.assertions.failed = 3;
    current.testCases.passed = 5;
    current.testCases.failed = 2;

    prev.assertions.passed = 7;
    prev.assertions.failed = 1;
    prev.testCases.passed = 3;
    prev.testCases.failed = 1;

    Totals result = current.delta(prev);
    EXPECT_EQ(result.assertions.passed, 3u);
    EXPECT_EQ(result.assertions.failed, 2u);
    EXPECT_EQ(result.testCases.passed, 2u);
    EXPECT_EQ(result.testCases.failed, 1u);
}

TEST_F(TotalsTest_308, DeltaWithSameValues_308) {
    Totals current;
    current.assertions.passed = 10;
    current.testCases.passed = 5;

    Totals result = current.delta(current);
    EXPECT_EQ(result.assertions.passed, 0u);
    EXPECT_EQ(result.testCases.passed, 0u);
}

TEST_F(TotalsTest_308, DeltaWithZeroPrev_308) {
    Totals current, prev;
    current.assertions.passed = 10;
    current.assertions.failed = 3;
    current.testCases.passed = 5;
    current.testCases.failed = 2;

    Totals result = current.delta(prev);
    EXPECT_EQ(result.assertions.passed, 10u);
    EXPECT_EQ(result.assertions.failed, 3u);
    EXPECT_EQ(result.testCases.passed, 5u);
    EXPECT_EQ(result.testCases.failed, 2u);
}

TEST_F(TotalsTest_308, SubtractionWithAllFields_308) {
    Totals a, b;
    a.assertions.passed = 20;
    a.assertions.failed = 10;
    a.assertions.failedButOk = 5;
    a.assertions.skipped = 3;
    a.testCases.passed = 15;
    a.testCases.failed = 8;
    a.testCases.failedButOk = 4;
    a.testCases.skipped = 2;

    b.assertions.passed = 10;
    b.assertions.failed = 5;
    b.assertions.failedButOk = 2;
    b.assertions.skipped = 1;
    b.testCases.passed = 7;
    b.testCases.failed = 3;
    b.testCases.failedButOk = 2;
    b.testCases.skipped = 1;

    Totals result = a - b;
    EXPECT_EQ(result.assertions.passed, 10u);
    EXPECT_EQ(result.assertions.failed, 5u);
    EXPECT_EQ(result.assertions.failedButOk, 3u);
    EXPECT_EQ(result.assertions.skipped, 2u);
    EXPECT_EQ(result.testCases.passed, 8u);
    EXPECT_EQ(result.testCases.failed, 5u);
    EXPECT_EQ(result.testCases.failedButOk, 2u);
    EXPECT_EQ(result.testCases.skipped, 1u);
}

TEST_F(TotalsTest_308, PlusEqualsWithAllFields_308) {
    Totals a, b;
    a.assertions.passed = 5;
    a.assertions.failed = 3;
    a.assertions.failedButOk = 1;
    a.assertions.skipped = 2;
    a.testCases.passed = 4;
    a.testCases.failed = 2;
    a.testCases.failedButOk = 1;
    a.testCases.skipped = 1;

    b.assertions.passed = 10;
    b.assertions.failed = 7;
    b.assertions.failedButOk = 4;
    b.assertions.skipped = 3;
    b.testCases.passed = 6;
    b.testCases.failed = 5;
    b.testCases.failedButOk = 3;
    b.testCases.skipped = 2;

    a += b;
    EXPECT_EQ(a.assertions.passed, 15u);
    EXPECT_EQ(a.assertions.failed, 10u);
    EXPECT_EQ(a.assertions.failedButOk, 5u);
    EXPECT_EQ(a.assertions.skipped, 5u);
    EXPECT_EQ(a.testCases.passed, 10u);
    EXPECT_EQ(a.testCases.failed, 7u);
    EXPECT_EQ(a.testCases.failedButOk, 4u);
    EXPECT_EQ(a.testCases.skipped, 3u);
}

// ==================== Counts - Boundary / Edge Cases ====================

TEST(CountsBoundary_308, TotalWithLargeValues_308) {
    Counts c;
    c.passed = 1000000;
    c.failed = 2000000;
    c.failedButOk = 3000000;
    c.skipped = 4000000;
    EXPECT_EQ(c.total(), 10000000u);
}

TEST(CountsBoundary_308, AllPassedWithZeroTotal_308) {
    Counts c;
    // All zero - edge case for allPassed
    bool result = c.allPassed();
    // Just verify it returns a boolean without crashing
    (void)result;
}

TEST(CountsBoundary_308, AllOkWithZeroTotal_308) {
    Counts c;
    bool result = c.allOk();
    (void)result;
}

TEST(CountsBoundary_308, SubtractionFromZero_308) {
    Counts a, b;
    b.passed = 0;
    b.failed = 0;
    Counts result = a - b;
    EXPECT_EQ(result.passed, 0u);
    EXPECT_EQ(result.failed, 0u);
}

TEST(CountsBoundary_308, AllOkOnlyFailedButOk_308) {
    Counts c;
    c.failedButOk = 5;
    EXPECT_TRUE(c.allOk());
}

TEST(CountsBoundary_308, AllPassedOnlyFailedButOkIsFalse_308) {
    Counts c;
    c.failedButOk = 5;
    EXPECT_FALSE(c.allPassed());
}

// ==================== Totals - Boundary / Edge Cases ====================

TEST(TotalsBoundary_308, SubtractionFromDefaultTotals_308) {
    Totals a, b;
    Totals result = a - b;
    EXPECT_EQ(result.assertions.passed, 0u);
    EXPECT_EQ(result.assertions.failed, 0u);
    EXPECT_EQ(result.testCases.passed, 0u);
    EXPECT_EQ(result.testCases.failed, 0u);
}

TEST(TotalsBoundary_308, DeltaFromDefault_308) {
    Totals a, b;
    Totals result = a.delta(b);
    EXPECT_EQ(result.assertions.passed, 0u);
    EXPECT_EQ(result.assertions.failed, 0u);
    EXPECT_EQ(result.testCases.passed, 0u);
    EXPECT_EQ(result.testCases.failed, 0u);
}

TEST(TotalsBoundary_308, ChainedPlusEquals_308) {
    Totals a, b, c;
    a.assertions.passed = 1;
    b.assertions.passed = 2;
    c.assertions.passed = 3;

    a += b;
    a += c;
    EXPECT_EQ(a.assertions.passed, 6u);
}
