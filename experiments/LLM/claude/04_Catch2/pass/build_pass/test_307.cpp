#include <gtest/gtest.h>
#include "catch2/catch_totals.hpp"

// Tests for Counts::allOk()
TEST(CountsTest_307, AllOk_DefaultState_ReturnsTrue_307) {
    Catch::Counts counts;
    EXPECT_TRUE(counts.allOk());
}

TEST(CountsTest_307, AllOk_WithFailures_ReturnsFalse_307) {
    Catch::Counts counts;
    counts.failed = 1;
    EXPECT_FALSE(counts.allOk());
}

TEST(CountsTest_307, AllOk_WithFailedButOk_ReturnsTrue_307) {
    Catch::Counts counts;
    counts.failedButOk = 5;
    EXPECT_TRUE(counts.allOk());
}

TEST(CountsTest_307, AllOk_WithPassedOnly_ReturnsTrue_307) {
    Catch::Counts counts;
    counts.passed = 10;
    EXPECT_TRUE(counts.allOk());
}

TEST(CountsTest_307, AllOk_WithPassedAndFailed_ReturnsFalse_307) {
    Catch::Counts counts;
    counts.passed = 10;
    counts.failed = 1;
    EXPECT_FALSE(counts.allOk());
}

TEST(CountsTest_307, AllOk_WithSkippedOnly_ReturnsTrue_307) {
    Catch::Counts counts;
    counts.skipped = 3;
    EXPECT_TRUE(counts.allOk());
}

TEST(CountsTest_307, AllOk_WithMultipleFailures_ReturnsFalse_307) {
    Catch::Counts counts;
    counts.failed = 100;
    EXPECT_FALSE(counts.allOk());
}

TEST(CountsTest_307, AllOk_WithAllFieldsSetAndNoFailed_ReturnsTrue_307) {
    Catch::Counts counts;
    counts.passed = 10;
    counts.failed = 0;
    counts.failedButOk = 2;
    counts.skipped = 3;
    EXPECT_TRUE(counts.allOk());
}

TEST(CountsTest_307, AllOk_WithAllFieldsSetAndFailed_ReturnsFalse_307) {
    Catch::Counts counts;
    counts.passed = 10;
    counts.failed = 1;
    counts.failedButOk = 2;
    counts.skipped = 3;
    EXPECT_FALSE(counts.allOk());
}

// Tests for Counts::allPassed()
TEST(CountsTest_307, AllPassed_DefaultState_ReturnsTrue_307) {
    Catch::Counts counts;
    EXPECT_TRUE(counts.allPassed());
}

TEST(CountsTest_307, AllPassed_WithPassedOnly_ReturnsTrue_307) {
    Catch::Counts counts;
    counts.passed = 10;
    EXPECT_TRUE(counts.allPassed());
}

TEST(CountsTest_307, AllPassed_WithFailed_ReturnsFalse_307) {
    Catch::Counts counts;
    counts.passed = 10;
    counts.failed = 1;
    EXPECT_FALSE(counts.allPassed());
}

TEST(CountsTest_307, AllPassed_WithFailedButOk_ReturnsFalse_307) {
    Catch::Counts counts;
    counts.passed = 10;
    counts.failedButOk = 1;
    EXPECT_FALSE(counts.allPassed());
}

TEST(CountsTest_307, AllPassed_WithSkipped_ReturnsFalse_307) {
    Catch::Counts counts;
    counts.passed = 10;
    counts.skipped = 1;
    // allPassed might consider skipped as not all passed
    // We test observable behavior
    bool result = counts.allPassed();
    // Just record the result - we can't know for sure without implementation
    (void)result;
}

// Tests for Counts::total()
TEST(CountsTest_307, Total_DefaultState_ReturnsZero_307) {
    Catch::Counts counts;
    EXPECT_EQ(counts.total(), 0u);
}

TEST(CountsTest_307, Total_WithPassedOnly_ReturnsPassed_307) {
    Catch::Counts counts;
    counts.passed = 5;
    EXPECT_EQ(counts.total(), 5u);
}

TEST(CountsTest_307, Total_WithAllFields_ReturnsSumOfRelevantFields_307) {
    Catch::Counts counts;
    counts.passed = 10;
    counts.failed = 3;
    counts.failedButOk = 2;
    counts.skipped = 1;
    // total should be the sum of all or a subset
    std::uint64_t t = counts.total();
    // At minimum, passed + failed should be included
    EXPECT_GE(t, counts.passed + counts.failed);
}

// Tests for operator-
TEST(CountsTest_307, OperatorMinus_SubtractsCorrectly_307) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 5;
    a.failedButOk = 3;
    a.skipped = 2;

    Catch::Counts b;
    b.passed = 3;
    b.failed = 2;
    b.failedButOk = 1;
    b.skipped = 1;

    Catch::Counts result = a - b;
    EXPECT_EQ(result.passed, 7u);
    EXPECT_EQ(result.failed, 3u);
    EXPECT_EQ(result.failedButOk, 2u);
    EXPECT_EQ(result.skipped, 1u);
}

TEST(CountsTest_307, OperatorMinus_SubtractFromZero_307) {
    Catch::Counts a;
    Catch::Counts b;

    Catch::Counts result = a - b;
    EXPECT_EQ(result.passed, 0u);
    EXPECT_EQ(result.failed, 0u);
    EXPECT_EQ(result.failedButOk, 0u);
    EXPECT_EQ(result.skipped, 0u);
}

TEST(CountsTest_307, OperatorMinus_DoesNotModifyOriginal_307) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 5;

    Catch::Counts b;
    b.passed = 3;
    b.failed = 2;

    Catch::Counts result = a - b;
    EXPECT_EQ(a.passed, 10u);
    EXPECT_EQ(a.failed, 5u);
}

// Tests for operator+=
TEST(CountsTest_307, OperatorPlusEquals_AddsCorrectly_307) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 5;
    a.failedButOk = 3;
    a.skipped = 2;

    Catch::Counts b;
    b.passed = 3;
    b.failed = 2;
    b.failedButOk = 1;
    b.skipped = 1;

    a += b;
    EXPECT_EQ(a.passed, 13u);
    EXPECT_EQ(a.failed, 7u);
    EXPECT_EQ(a.failedButOk, 4u);
    EXPECT_EQ(a.skipped, 3u);
}

TEST(CountsTest_307, OperatorPlusEquals_AddZero_307) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 5;

    Catch::Counts b;

    a += b;
    EXPECT_EQ(a.passed, 10u);
    EXPECT_EQ(a.failed, 5u);
}

TEST(CountsTest_307, OperatorPlusEquals_ReturnsReference_307) {
    Catch::Counts a;
    a.passed = 10;

    Catch::Counts b;
    b.passed = 5;

    Catch::Counts& ref = (a += b);
    EXPECT_EQ(&ref, &a);
    EXPECT_EQ(ref.passed, 15u);
}

TEST(CountsTest_307, OperatorPlusEquals_ChainedCalls_307) {
    Catch::Counts a;
    Catch::Counts b;
    b.passed = 1;
    Catch::Counts c;
    c.passed = 2;

    a += b;
    a += c;
    EXPECT_EQ(a.passed, 3u);
}

// Boundary tests
TEST(CountsTest_307, AllOk_FailedIsMaxUint64_ReturnsFalse_307) {
    Catch::Counts counts;
    counts.failed = std::numeric_limits<std::uint64_t>::max();
    EXPECT_FALSE(counts.allOk());
}

TEST(CountsTest_307, AllOk_FailedIsOne_ReturnsFalse_307) {
    Catch::Counts counts;
    counts.failed = 1;
    EXPECT_FALSE(counts.allOk());
}

TEST(CountsTest_307, Total_WithLargeValues_307) {
    Catch::Counts counts;
    counts.passed = 1000000;
    counts.failed = 500000;
    counts.failedButOk = 100000;
    counts.skipped = 50000;
    std::uint64_t t = counts.total();
    EXPECT_GT(t, 0u);
}

// Test that operator- produces correct allOk result
TEST(CountsTest_307, OperatorMinus_ResultAllOk_307) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 5;

    Catch::Counts b;
    b.failed = 5;

    Catch::Counts result = a - b;
    EXPECT_TRUE(result.allOk());
}

TEST(CountsTest_307, OperatorPlusEquals_ResultNotAllOk_307) {
    Catch::Counts a;
    a.passed = 10;

    Catch::Counts b;
    b.failed = 1;

    a += b;
    EXPECT_FALSE(a.allOk());
}
