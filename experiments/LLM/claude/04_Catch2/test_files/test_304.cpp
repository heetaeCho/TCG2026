#include <gtest/gtest.h>
#include "catch2/catch_totals.hpp"

// ===== Counts Tests =====

// --- Default Construction ---

TEST(CountsTest_304, DefaultConstructionAllZero_304) {
    Catch::Counts c;
    EXPECT_EQ(c.passed, 0u);
    EXPECT_EQ(c.failed, 0u);
    EXPECT_EQ(c.failedButOk, 0u);
    EXPECT_EQ(c.skipped, 0u);
}

// --- total() ---

TEST(CountsTest_304, TotalReturnsZeroForDefault_304) {
    Catch::Counts c;
    EXPECT_EQ(c.total(), 0u);
}

TEST(CountsTest_304, TotalReturnsSumOfAllFields_304) {
    Catch::Counts c;
    c.passed = 3;
    c.failed = 2;
    c.failedButOk = 1;
    c.skipped = 4;
    EXPECT_EQ(c.total(), 10u);
}

TEST(CountsTest_304, TotalWithOnlyPassed_304) {
    Catch::Counts c;
    c.passed = 5;
    EXPECT_EQ(c.total(), 5u);
}

TEST(CountsTest_304, TotalWithOnlyFailed_304) {
    Catch::Counts c;
    c.failed = 7;
    EXPECT_EQ(c.total(), 7u);
}

TEST(CountsTest_304, TotalWithOnlyFailedButOk_304) {
    Catch::Counts c;
    c.failedButOk = 3;
    EXPECT_EQ(c.total(), 3u);
}

TEST(CountsTest_304, TotalWithOnlySkipped_304) {
    Catch::Counts c;
    c.skipped = 9;
    EXPECT_EQ(c.total(), 9u);
}

// --- allPassed() ---

TEST(CountsTest_304, AllPassedWhenDefaultIsTrue_304) {
    Catch::Counts c;
    // No failed, no failedButOk => should be considered all passed
    // (depends on implementation; zero total might be considered all passed)
    // We test observable behavior
    EXPECT_TRUE(c.allPassed());
}

TEST(CountsTest_304, AllPassedWhenOnlyPassed_304) {
    Catch::Counts c;
    c.passed = 10;
    EXPECT_TRUE(c.allPassed());
}

TEST(CountsTest_304, AllPassedFalseWhenFailed_304) {
    Catch::Counts c;
    c.passed = 5;
    c.failed = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_304, AllPassedFalseWhenFailedButOk_304) {
    Catch::Counts c;
    c.passed = 5;
    c.failedButOk = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_304, AllPassedFalseWhenSkipped_304) {
    Catch::Counts c;
    c.passed = 5;
    c.skipped = 1;
    // Skipped tests mean not all passed
    EXPECT_FALSE(c.allPassed());
}

TEST(CountsTest_304, AllPassedFalseWhenOnlyFailed_304) {
    Catch::Counts c;
    c.failed = 3;
    EXPECT_FALSE(c.allPassed());
}

// --- allOk() ---

TEST(CountsTest_304, AllOkWhenDefault_304) {
    Catch::Counts c;
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_304, AllOkWhenOnlyPassed_304) {
    Catch::Counts c;
    c.passed = 10;
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_304, AllOkFalseWhenFailed_304) {
    Catch::Counts c;
    c.passed = 5;
    c.failed = 1;
    EXPECT_FALSE(c.allOk());
}

TEST(CountsTest_304, AllOkWhenFailedButOk_304) {
    Catch::Counts c;
    c.passed = 5;
    c.failedButOk = 2;
    // failedButOk should still be considered "ok"
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_304, AllOkWhenOnlyFailedButOk_304) {
    Catch::Counts c;
    c.failedButOk = 3;
    EXPECT_TRUE(c.allOk());
}

TEST(CountsTest_304, AllOkFalseWhenFailedAndFailedButOk_304) {
    Catch::Counts c;
    c.failed = 1;
    c.failedButOk = 2;
    EXPECT_FALSE(c.allOk());
}

TEST(CountsTest_304, AllOkWithSkipped_304) {
    Catch::Counts c;
    c.passed = 5;
    c.skipped = 2;
    EXPECT_TRUE(c.allOk());
}

// --- operator+= ---

TEST(CountsTest_304, PlusEqualsAddsAllFields_304) {
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

TEST(CountsTest_304, PlusEqualsWithZero_304) {
    Catch::Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 1;
    a.skipped = 2;

    Catch::Counts zero;
    a += zero;

    EXPECT_EQ(a.passed, 5u);
    EXPECT_EQ(a.failed, 3u);
    EXPECT_EQ(a.failedButOk, 1u);
    EXPECT_EQ(a.skipped, 2u);
}

TEST(CountsTest_304, PlusEqualsReturnsSelf_304) {
    Catch::Counts a;
    a.passed = 1;

    Catch::Counts b;
    b.passed = 2;

    Catch::Counts& result = (a += b);
    EXPECT_EQ(&result, &a);
    EXPECT_EQ(result.passed, 3u);
}

TEST(CountsTest_304, PlusEqualsChaining_304) {
    Catch::Counts a, b, c;
    a.passed = 1;
    b.passed = 2;
    c.passed = 3;

    a += b += c;

    EXPECT_EQ(b.passed, 5u);
    EXPECT_EQ(a.passed, 6u);
}

TEST(CountsTest_304, PlusEqualsDoesNotModifyOther_304) {
    Catch::Counts a;
    a.passed = 1;

    Catch::Counts b;
    b.passed = 10;

    a += b;

    EXPECT_EQ(b.passed, 10u);
    EXPECT_EQ(b.failed, 0u);
    EXPECT_EQ(b.failedButOk, 0u);
    EXPECT_EQ(b.skipped, 0u);
}

// --- operator- ---

TEST(CountsTest_304, SubtractAllFields_304) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 20;
    a.failedButOk = 30;
    a.skipped = 40;

    Catch::Counts b;
    b.passed = 3;
    b.failed = 5;
    b.failedButOk = 7;
    b.skipped = 9;

    Catch::Counts result = a - b;

    EXPECT_EQ(result.passed, 7u);
    EXPECT_EQ(result.failed, 15u);
    EXPECT_EQ(result.failedButOk, 23u);
    EXPECT_EQ(result.skipped, 31u);
}

TEST(CountsTest_304, SubtractZero_304) {
    Catch::Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 1;
    a.skipped = 2;

    Catch::Counts zero;
    Catch::Counts result = a - zero;

    EXPECT_EQ(result.passed, 5u);
    EXPECT_EQ(result.failed, 3u);
    EXPECT_EQ(result.failedButOk, 1u);
    EXPECT_EQ(result.skipped, 2u);
}

TEST(CountsTest_304, SubtractFromZero_304) {
    Catch::Counts zero;
    Catch::Counts b;
    b.passed = 1;

    // Subtracting from zero with unsigned - this may wrap around
    // Testing observable behavior
    Catch::Counts result = zero - b;
    // For uint64_t, 0 - 1 wraps to max value
    EXPECT_EQ(result.passed, static_cast<std::uint64_t>(0) - static_cast<std::uint64_t>(1));
}

TEST(CountsTest_304, SubtractDoesNotModifyOperands_304) {
    Catch::Counts a;
    a.passed = 10;
    a.failed = 20;

    Catch::Counts b;
    b.passed = 3;
    b.failed = 5;

    Catch::Counts result = a - b;

    // Original operands unchanged
    EXPECT_EQ(a.passed, 10u);
    EXPECT_EQ(a.failed, 20u);
    EXPECT_EQ(b.passed, 3u);
    EXPECT_EQ(b.failed, 5u);
}

TEST(CountsTest_304, SubtractSameValues_304) {
    Catch::Counts a;
    a.passed = 5;
    a.failed = 3;
    a.failedButOk = 2;
    a.skipped = 1;

    Catch::Counts result = a - a;

    EXPECT_EQ(result.passed, 0u);
    EXPECT_EQ(result.failed, 0u);
    EXPECT_EQ(result.failedButOk, 0u);
    EXPECT_EQ(result.skipped, 0u);
}

// --- Interaction between methods ---

TEST(CountsTest_304, TotalAfterPlusEquals_304) {
    Catch::Counts a;
    a.passed = 1;
    a.failed = 1;

    Catch::Counts b;
    b.passed = 2;
    b.failed = 2;

    a += b;
    EXPECT_EQ(a.total(), 6u);
}

TEST(CountsTest_304, AllPassedAfterAddingFailure_304) {
    Catch::Counts a;
    a.passed = 10;
    EXPECT_TRUE(a.allPassed());

    Catch::Counts b;
    b.failed = 1;
    a += b;
    EXPECT_FALSE(a.allPassed());
}

TEST(CountsTest_304, AllOkAfterAddingFailedButOk_304) {
    Catch::Counts a;
    a.passed = 10;
    EXPECT_TRUE(a.allOk());

    Catch::Counts b;
    b.failedButOk = 1;
    a += b;
    EXPECT_TRUE(a.allOk());
}

TEST(CountsTest_304, AllOkAfterAddingFailed_304) {
    Catch::Counts a;
    a.passed = 10;
    EXPECT_TRUE(a.allOk());

    Catch::Counts b;
    b.failed = 1;
    a += b;
    EXPECT_FALSE(a.allOk());
}

// --- Large values ---

TEST(CountsTest_304, LargeValues_304) {
    Catch::Counts c;
    c.passed = 1000000;
    c.failed = 2000000;
    c.failedButOk = 3000000;
    c.skipped = 4000000;
    EXPECT_EQ(c.total(), 10000000u);
}

TEST(CountsTest_304, PlusEqualsLargeValues_304) {
    Catch::Counts a;
    a.passed = 999999999;

    Catch::Counts b;
    b.passed = 1;

    a += b;
    EXPECT_EQ(a.passed, 1000000000u);
}
