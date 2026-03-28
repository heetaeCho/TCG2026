#include <gtest/gtest.h>
#include "catch2/catch_totals.hpp"

// ============================================================
// Tests for Counts::allPassed()
// ============================================================

TEST(CountsTest_306, AllPassed_AllZeros_306) {
    Catch::Counts c;
    c.passed = 0;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_TRUE(c.allPassed());
}

TEST(CountsTest_306, AllPassed_OnlyPassedNonZero_306) {
    Catch::Counts c;
    c.passed = 10;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_TRUE(c.allPassed());
}

TEST(CountsTest_306, AllPassed_FailedNonZero_306) {
    Catch::Counts c;
    c.passed = 5;
    c.failed = 1;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_306, AllPassed_FailedButOkNonZero_306) {
    Catch::Counts c;
    c.passed = 5;
    c.failed = 0;
    c.failedButOk = 1;
    c.skipped = 0;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_306, AllPassed_SkippedNonZero_306) {
    Catch::Counts c;
    c.passed = 5;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_306, AllPassed_AllNonZero_306) {
    Catch::Counts c;
    c.passed = 3;
    c.failed = 2;
    c.failedButOk = 1;
    c.skipped = 4;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_306, AllPassed_FailedAndSkippedBothNonZero_306) {
    Catch::Counts c;
    c.passed = 0;
    c.failed = 1;
    c.failedButOk = 0;
    c.skipped = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_306, AllPassed_OnlyFailedButOkAndSkipped_306) {
    Catch::Counts c;
    c.passed = 0;
    c.failed = 0;
    c.failedButOk = 1;
    c.skipped = 1;
    EXPECT_FALSE(c.allPassed());
}

// ============================================================
// Tests for Counts::allOk()
// ============================================================

TEST(CountsTest_306, AllOk_AllZeros_306) {
    Catch::Counts c;
    c.passed = 0;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_306, AllOk_OnlyPassedNonZero_306) {
    Catch::Counts c;
    c.passed = 10;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_306, AllOk_FailedNonZero_306) {
    Catch::Counts c;
    c.passed = 5;
    c.failed = 1;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_FALSE(c.allOk());
}

TEST(CountsTest_306, AllOk_FailedButOkNonZero_306) {
    Catch::Counts c;
    c.passed = 5;
    c.failed = 0;
    c.failedButOk = 3;
    c.skipped = 0;
    // failedButOk should be considered "ok"
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_306, AllOk_SkippedNonZero_306) {
    Catch::Counts c;
    c.passed = 5;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 2;
    // allOk may or may not count skipped as ok; testing observable behavior
    // Based on typical Catch2 semantics, skipped is ok
    EXPECT_TRUE(c.allOk());
}

// ============================================================
// Tests for Counts::total()
// ============================================================

TEST(CountsTest_306, Total_AllZeros_306) {
    Catch::Counts c;
    c.passed = 0;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_EQ(c.total(), 0u);
}

TEST(CountsTest_306, Total_SumOfAll_306) {
    Catch::Counts c;
    c.passed = 3;
    c.failed = 2;
    c.failedButOk = 1;
    c.skipped = 4;
    EXPECT_EQ(c.total(), 10u);
}

TEST(CountsTest_306, Total_OnlyPassed_306) {
    Catch::Counts c;
    c.passed = 42;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_EQ(c.total(), 42u);
}

TEST(CountsTest_306, Total_OnlyFailed_306) {
    Catch::Counts c;
    c.passed = 0;
    c.failed = 7;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_EQ(c.total(), 7u);
}

TEST(CountsTest_306, Total_LargeValues_306) {
    Catch::Counts c;
    c.passed = 1000000;
    c.failed = 2000000;
    c.failedButOk = 3000000;
    c.skipped = 4000000;
    EXPECT_EQ(c.total(), 10000000u);
}

// ============================================================
// Tests for Counts::operator+=
// ============================================================

TEST(CountsTest_306, OperatorPlusEquals_BasicAddition_306) {
    Catch::Counts a;
    a.passed = 1;
    a.failed = 2;
    a.failedButOk = 3;
    a.skipped = 4;

    Catch::Counts b;
    b.passed = 10;
    b.failed = 20;
    b.failedButOk = 30;
    b.skipped = 40;

    a += b;

    EXPECT_EQ(a.passed, 11u);
    EXPECT_EQ(a.failed, 22u);
    EXPECT_EQ(a.failedButOk, 33u);
    EXPECT_EQ(a.skipped, 44u);
}

TEST(CountsTest_306, OperatorPlusEquals_AddZero_306) {
    Catch::Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 1;
    a.skipped = 2;

    Catch::Counts b;
    b.passed = 0;
    b.failed = 0;
    b.failedButOk = 0;
    b.skipped = 0;

    a += b;

    EXPECT_EQ(a.passed, 5u);
    EXPECT_EQ(a.failed, 3u);
    EXPECT_EQ(a.failedButOk, 1u);
    EXPECT_EQ(a.skipped, 2u);
}

TEST(CountsTest_306, OperatorPlusEquals_ReturnsSelf_306) {
    Catch::Counts a;
    a.passed = 1;
    a.failed = 0;
    a.failedButOk = 0;
    a.skipped = 0;

    Catch::Counts b;
    b.passed = 2;
    b.failed = 0;
    b.failedButOk = 0;
    b.skipped = 0;

    Catch::Counts& ref = (a += b);
    EXPECT_EQ(&ref, &a);
    EXPECT_EQ(a.passed, 3u);
}

// ============================================================
// Tests for Counts::operator-
// ============================================================

TEST(CountsTest_306, OperatorMinus_BasicSubtraction_306) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 20;
    a.failedButOk = 30;
    a.skipped = 40;

    Catch::Counts b;
    b.passed = 1;
    b.failed = 2;
    b.failedButOk = 3;
    b.skipped = 4;

    Catch::Counts result = a - b;

    EXPECT_EQ(result.passed, 9u);
    EXPECT_EQ(result.failed, 18u);
    EXPECT_EQ(result.failedButOk, 27u);
    EXPECT_EQ(result.skipped, 36u);
}

TEST(CountsTest_306, OperatorMinus_SubtractZero_306) {
    Catch::Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 1;
    a.skipped = 2;

    Catch::Counts b;
    b.passed = 0;
    b.failed = 0;
    b.failedButOk = 0;
    b.skipped = 0;

    Catch::Counts result = a - b;

    EXPECT_EQ(result.passed, 5u);
    EXPECT_EQ(result.failed, 3u);
    EXPECT_EQ(result.failedButOk, 1u);
    EXPECT_EQ(result.skipped, 2u);
}

TEST(CountsTest_306, OperatorMinus_SubtractFromItself_306) {
    Catch::Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 1;
    a.skipped = 2;

    Catch::Counts result = a - a;

    EXPECT_EQ(result.passed, 0u);
    EXPECT_EQ(result.failed, 0u);
    EXPECT_EQ(result.failedButOk, 0u);
    EXPECT_EQ(result.skipped, 0u);
}

TEST(CountsTest_306, OperatorMinus_DoesNotModifyOriginal_306) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 20;
    a.failedButOk = 30;
    a.skipped = 40;

    Catch::Counts b;
    b.passed = 1;
    b.failed = 2;
    b.failedButOk = 3;
    b.skipped = 4;

    Catch::Counts result = a - b;

    // Original should not be modified
    EXPECT_EQ(a.passed, 10u);
    EXPECT_EQ(a.failed, 20u);
    EXPECT_EQ(a.failedButOk, 30u);
    EXPECT_EQ(a.skipped, 40u);
}

// ============================================================
// Tests for default construction
// ============================================================

TEST(CountsTest_306, DefaultConstruction_AllZero_306) {
    Catch::Counts c;
    EXPECT_EQ(c.passed, 0u);
    EXPECT_EQ(c.failed, 0u);
    EXPECT_EQ(c.failedButOk, 0u);
    EXPECT_EQ(c.skipped, 0u);
}

// ============================================================
// Boundary / Edge cases
// ============================================================

TEST(CountsTest_306, AllPassed_OnlyFailedSet_306) {
    Catch::Counts c;
    c.failed = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_306, AllPassed_OnlyFailedButOkSet_306) {
    Catch::Counts c;
    c.failedButOk = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_306, AllPassed_OnlySkippedSet_306) {
    Catch::Counts c;
    c.skipped = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_306, Total_OnlySkipped_306) {
    Catch::Counts c;
    c.skipped = 100;
    EXPECT_EQ(c.total(), 100u);
}

TEST(CountsTest_306, Total_OnlyFailedButOk_306) {
    Catch::Counts c;
    c.failedButOk = 50;
    EXPECT_EQ(c.total(), 50u);
}

TEST(CountsTest_306, OperatorPlusEquals_MultipleChained_306) {
    Catch::Counts a, b, c;
    a.passed = 1;
    b.passed = 2;
    c.passed = 3;

    a += b;
    a += c;

    EXPECT_EQ(a.passed, 6u);
}

TEST(CountsTest_306, AllOk_FailedOnly_306) {
    Catch::Counts c;
    c.failed = 1;
    EXPECT_FALSE(c.allOk());
}

TEST(CountsTest_306, AllOk_FailedAndFailedButOk_306) {
    Catch::Counts c;
    c.failed = 1;
    c.failedButOk = 1;
    EXPECT_FALSE(c.allOk());
}
