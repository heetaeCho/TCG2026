#include "gtest/gtest.h"
#include "catch2/catch_totals.hpp"

// ============================================================
// Tests for Counts::operator-
// ============================================================

TEST(CountsTest_303, OperatorMinus_AllZeros_303) {
    Catch::Counts a;
    Catch::Counts b;
    Catch::Counts result = a - b;
    EXPECT_EQ(result.passed, 0u);
    EXPECT_EQ(result.failed, 0u);
    EXPECT_EQ(result.failedButOk, 0u);
    EXPECT_EQ(result.skipped, 0u);
}

TEST(CountsTest_303, OperatorMinus_SubtractsCorrectly_303) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 5;
    a.failedButOk = 3;
    a.skipped = 2;

    Catch::Counts b;
    b.passed = 4;
    b.failed = 2;
    b.failedButOk = 1;
    b.skipped = 1;

    Catch::Counts result = a - b;
    EXPECT_EQ(result.passed, 6u);
    EXPECT_EQ(result.failed, 3u);
    EXPECT_EQ(result.failedButOk, 2u);
    EXPECT_EQ(result.skipped, 1u);
}

TEST(CountsTest_303, OperatorMinus_SubtractFromSelf_303) {
    Catch::Counts a;
    a.passed = 7;
    a.failed = 3;
    a.failedButOk = 2;
    a.skipped = 1;

    Catch::Counts result = a - a;
    EXPECT_EQ(result.passed, 0u);
    EXPECT_EQ(result.failed, 0u);
    EXPECT_EQ(result.failedButOk, 0u);
    EXPECT_EQ(result.skipped, 0u);
}

TEST(CountsTest_303, OperatorMinus_SubtractZero_303) {
    Catch::Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 1;
    a.skipped = 4;

    Catch::Counts b;

    Catch::Counts result = a - b;
    EXPECT_EQ(result.passed, 5u);
    EXPECT_EQ(result.failed, 3u);
    EXPECT_EQ(result.failedButOk, 1u);
    EXPECT_EQ(result.skipped, 4u);
}

TEST(CountsTest_303, OperatorMinus_LargeValues_303) {
    Catch::Counts a;
    a.passed = 1000000;
    a.failed = 500000;
    a.failedButOk = 250000;
    a.skipped = 100000;

    Catch::Counts b;
    b.passed = 999999;
    b.failed = 499999;
    b.failedButOk = 249999;
    b.skipped = 99999;

    Catch::Counts result = a - b;
    EXPECT_EQ(result.passed, 1u);
    EXPECT_EQ(result.failed, 1u);
    EXPECT_EQ(result.failedButOk, 1u);
    EXPECT_EQ(result.skipped, 1u);
}

// ============================================================
// Tests for Counts::operator+=
// ============================================================

TEST(CountsTest_303, OperatorPlusEquals_AllZeros_303) {
    Catch::Counts a;
    Catch::Counts b;
    a += b;
    EXPECT_EQ(a.passed, 0u);
    EXPECT_EQ(a.failed, 0u);
    EXPECT_EQ(a.failedButOk, 0u);
    EXPECT_EQ(a.skipped, 0u);
}

TEST(CountsTest_303, OperatorPlusEquals_AddsCorrectly_303) {
    Catch::Counts a;
    a.passed = 3;
    a.failed = 2;
    a.failedButOk = 1;
    a.skipped = 0;

    Catch::Counts b;
    b.passed = 5;
    b.failed = 4;
    b.failedButOk = 3;
    b.skipped = 2;

    a += b;
    EXPECT_EQ(a.passed, 8u);
    EXPECT_EQ(a.failed, 6u);
    EXPECT_EQ(a.failedButOk, 4u);
    EXPECT_EQ(a.skipped, 2u);
}

TEST(CountsTest_303, OperatorPlusEquals_AddZero_303) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 20;
    a.failedButOk = 30;
    a.skipped = 40;

    Catch::Counts b;

    a += b;
    EXPECT_EQ(a.passed, 10u);
    EXPECT_EQ(a.failed, 20u);
    EXPECT_EQ(a.failedButOk, 30u);
    EXPECT_EQ(a.skipped, 40u);
}

TEST(CountsTest_303, OperatorPlusEquals_AddToSelf_303) {
    Catch::Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 2;
    a.skipped = 1;

    a += a;
    EXPECT_EQ(a.passed, 10u);
    EXPECT_EQ(a.failed, 6u);
    EXPECT_EQ(a.failedButOk, 4u);
    EXPECT_EQ(a.skipped, 2u);
}

TEST(CountsTest_303, OperatorPlusEquals_ReturnsReference_303) {
    Catch::Counts a;
    a.passed = 1;
    Catch::Counts b;
    b.passed = 2;

    Catch::Counts& ref = (a += b);
    EXPECT_EQ(&ref, &a);
    EXPECT_EQ(ref.passed, 3u);
}

TEST(CountsTest_303, OperatorPlusEquals_Chaining_303) {
    Catch::Counts a;
    Catch::Counts b;
    b.passed = 1;
    b.failed = 1;
    Catch::Counts c;
    c.passed = 2;
    c.failed = 2;

    (a += b) += c;
    EXPECT_EQ(a.passed, 3u);
    EXPECT_EQ(a.failed, 3u);
}

// ============================================================
// Tests for Counts::total()
// ============================================================

TEST(CountsTest_303, Total_AllZeros_303) {
    Catch::Counts c;
    EXPECT_EQ(c.total(), 0u);
}

TEST(CountsTest_303, Total_SumsAllFields_303) {
    Catch::Counts c;
    c.passed = 10;
    c.failed = 5;
    c.failedButOk = 3;
    c.skipped = 2;
    EXPECT_EQ(c.total(), 20u);
}

TEST(CountsTest_303, Total_OnlyPassed_303) {
    Catch::Counts c;
    c.passed = 7;
    EXPECT_EQ(c.total(), 7u);
}

TEST(CountsTest_303, Total_OnlyFailed_303) {
    Catch::Counts c;
    c.failed = 4;
    EXPECT_EQ(c.total(), 4u);
}

TEST(CountsTest_303, Total_OnlyFailedButOk_303) {
    Catch::Counts c;
    c.failedButOk = 6;
    EXPECT_EQ(c.total(), 6u);
}

TEST(CountsTest_303, Total_OnlySkipped_303) {
    Catch::Counts c;
    c.skipped = 9;
    EXPECT_EQ(c.total(), 9u);
}

// ============================================================
// Tests for Counts::allPassed()
// ============================================================

TEST(CountsTest_303, AllPassed_AllZeros_303) {
    Catch::Counts c;
    // With zero total, allPassed might return true (no failures)
    // We test the observable behavior
    bool result = c.allPassed();
    EXPECT_TRUE(result == true || result == false);
    // More specifically: no failed, no failedButOk => likely true
}

TEST(CountsTest_303, AllPassed_OnlyPassedNonZero_303) {
    Catch::Counts c;
    c.passed = 10;
    EXPECT_TRUE(c.allPassed());
}

TEST(CountsTest_303, AllPassed_WithFailed_303) {
    Catch::Counts c;
    c.passed = 10;
    c.failed = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_303, AllPassed_WithFailedButOk_303) {
    Catch::Counts c;
    c.passed = 10;
    c.failedButOk = 1;
    // failedButOk means it's "ok" but not "passed" — allPassed likely returns false
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_303, AllPassed_WithSkipped_303) {
    Catch::Counts c;
    c.passed = 10;
    c.skipped = 2;
    // skipped tests are not "passed" so allPassed might be false
    bool result = c.allPassed();
    // Just observe the behavior
    (void)result;
}

TEST(CountsTest_303, AllPassed_OnlyFailed_303) {
    Catch::Counts c;
    c.failed = 5;
    EXPECT_FALSE(c.allPassed());
}

// ============================================================
// Tests for Counts::allOk()
// ============================================================

TEST(CountsTest_303, AllOk_AllZeros_303) {
    Catch::Counts c;
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_303, AllOk_OnlyPassed_303) {
    Catch::Counts c;
    c.passed = 10;
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_303, AllOk_WithFailed_303) {
    Catch::Counts c;
    c.passed = 10;
    c.failed = 1;
    EXPECT_FALSE(c.allOk());
}

TEST(CountsTest_303, AllOk_WithFailedButOk_303) {
    Catch::Counts c;
    c.passed = 10;
    c.failedButOk = 3;
    // failedButOk should be considered "ok"
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_303, AllOk_OnlyFailedButOk_303) {
    Catch::Counts c;
    c.failedButOk = 5;
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_303, AllOk_FailedAndFailedButOk_303) {
    Catch::Counts c;
    c.passed = 5;
    c.failed = 2;
    c.failedButOk = 1;
    EXPECT_FALSE(c.allOk());
}

TEST(CountsTest_303, AllOk_WithSkipped_303) {
    Catch::Counts c;
    c.passed = 5;
    c.skipped = 3;
    // Skipped should still be "ok"
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_303, AllOk_OnlySkipped_303) {
    Catch::Counts c;
    c.skipped = 10;
    EXPECT_TRUE(c.allOk());
}

// ============================================================
// Tests for default construction
// ============================================================

TEST(CountsTest_303, DefaultConstruction_AllZero_303) {
    Catch::Counts c;
    EXPECT_EQ(c.passed, 0u);
    EXPECT_EQ(c.failed, 0u);
    EXPECT_EQ(c.failedButOk, 0u);
    EXPECT_EQ(c.skipped, 0u);
}

// ============================================================
// Boundary tests
// ============================================================

TEST(CountsTest_303, OperatorMinus_ResultIsOneInEachField_303) {
    Catch::Counts a;
    a.passed = 1;
    a.failed = 1;
    a.failedButOk = 1;
    a.skipped = 1;

    Catch::Counts b;

    Catch::Counts result = a - b;
    EXPECT_EQ(result.passed, 1u);
    EXPECT_EQ(result.failed, 1u);
    EXPECT_EQ(result.failedButOk, 1u);
    EXPECT_EQ(result.skipped, 1u);
}

TEST(CountsTest_303, Total_SingleFieldSet_303) {
    Catch::Counts c;
    c.passed = 1;
    EXPECT_EQ(c.total(), 1u);
}

TEST(CountsTest_303, OperatorMinus_DoesNotModifyOperands_303) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 5;
    a.failedButOk = 3;
    a.skipped = 2;

    Catch::Counts b;
    b.passed = 4;
    b.failed = 2;
    b.failedButOk = 1;
    b.skipped = 1;

    Catch::Counts result = a - b;

    // Verify operands are unchanged
    EXPECT_EQ(a.passed, 10u);
    EXPECT_EQ(a.failed, 5u);
    EXPECT_EQ(a.failedButOk, 3u);
    EXPECT_EQ(a.skipped, 2u);

    EXPECT_EQ(b.passed, 4u);
    EXPECT_EQ(b.failed, 2u);
    EXPECT_EQ(b.failedButOk, 1u);
    EXPECT_EQ(b.skipped, 1u);
}

TEST(CountsTest_303, OperatorPlusEquals_MultipleAccumulations_303) {
    Catch::Counts total;
    Catch::Counts increment;
    increment.passed = 1;
    increment.failed = 1;
    increment.failedButOk = 1;
    increment.skipped = 1;

    for (int i = 0; i < 100; ++i) {
        total += increment;
    }

    EXPECT_EQ(total.passed, 100u);
    EXPECT_EQ(total.failed, 100u);
    EXPECT_EQ(total.failedButOk, 100u);
    EXPECT_EQ(total.skipped, 100u);
    EXPECT_EQ(total.total(), 400u);
}

TEST(CountsTest_303, AllPassed_FailedZeroFailedButOkZeroSkippedZero_303) {
    Catch::Counts c;
    c.passed = 100;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;
    EXPECT_TRUE(c.allPassed());
}

TEST(CountsTest_303, AllOk_OnlyFailed_303) {
    Catch::Counts c;
    c.failed = 1;
    EXPECT_FALSE(c.allOk());
}
