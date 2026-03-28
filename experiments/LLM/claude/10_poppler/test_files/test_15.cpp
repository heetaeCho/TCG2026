#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
#include "gmem.h"

// Test normal allocation with valid count and size
TEST(GreallocnTest_15, NormalAllocation_15) {
    void *p = greallocn(nullptr, 10, sizeof(int));
    ASSERT_NE(p, nullptr);
    // Verify we can write to the allocated memory
    memset(p, 0, 10 * sizeof(int));
    gfree(p);
}

// Test that count == 0 frees memory and returns nullptr
TEST(GreallocnTest_15, CountZeroFreesAndReturnsNull_15) {
    void *p = greallocn(nullptr, 5, sizeof(int));
    ASSERT_NE(p, nullptr);
    void *result = greallocn(p, 0, sizeof(int));
    EXPECT_EQ(result, nullptr);
}

// Test count == 0 with nullptr input
TEST(GreallocnTest_15, CountZeroWithNullptrReturnsNull_15) {
    void *result = greallocn(nullptr, 0, sizeof(int));
    EXPECT_EQ(result, nullptr);
}

// Test reallocation - expanding existing memory
TEST(GreallocnTest_15, ReallocExpandsMemory_15) {
    void *p = greallocn(nullptr, 5, sizeof(int));
    ASSERT_NE(p, nullptr);
    int *ip = static_cast<int *>(p);
    for (int i = 0; i < 5; i++) {
        ip[i] = i + 1;
    }
    void *q = greallocn(p, 10, sizeof(int));
    ASSERT_NE(q, nullptr);
    int *iq = static_cast<int *>(q);
    // Original data should be preserved
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(iq[i], i + 1);
    }
    gfree(q);
}

// Test negative count with checkoverflow=true returns nullptr
TEST(GreallocnTest_15, NegativeCountWithCheckOverflowReturnsNull_15) {
    void *result = greallocn(nullptr, -1, sizeof(int), true);
    EXPECT_EQ(result, nullptr);
}

// Test negative count with checkoverflow=true frees input pointer
TEST(GreallocnTest_15, NegativeCountWithCheckOverflowFreesInput_15) {
    void *p = greallocn(nullptr, 10, sizeof(int));
    ASSERT_NE(p, nullptr);
    void *result = greallocn(p, -5, sizeof(int), true);
    EXPECT_EQ(result, nullptr);
}

// Test size <= 0 with checkoverflow=true returns nullptr
TEST(GreallocnTest_15, ZeroSizeWithCheckOverflowReturnsNull_15) {
    void *result = greallocn(nullptr, 10, 0, true);
    EXPECT_EQ(result, nullptr);
}

// Test negative size with checkoverflow=true returns nullptr
TEST(GreallocnTest_15, NegativeSizeWithCheckOverflowReturnsNull_15) {
    void *result = greallocn(nullptr, 10, -1, true);
    EXPECT_EQ(result, nullptr);
}

// Test overflow condition with checkoverflow=true returns nullptr
TEST(GreallocnTest_15, OverflowWithCheckOverflowReturnsNull_15) {
    // Use very large values that would overflow when multiplied
    void *result = greallocn(nullptr, INT_MAX, INT_MAX, true);
    EXPECT_EQ(result, nullptr);
}

// Test allocation with count=1 and size=1 (minimum valid allocation)
TEST(GreallocnTest_15, MinimumValidAllocation_15) {
    void *p = greallocn(nullptr, 1, 1);
    ASSERT_NE(p, nullptr);
    // Should be able to write one byte
    *static_cast<char *>(p) = 'A';
    EXPECT_EQ(*static_cast<char *>(p), 'A');
    gfree(p);
}

// Test allocation with larger counts
TEST(GreallocnTest_15, LargerAllocation_15) {
    void *p = greallocn(nullptr, 1000, sizeof(double));
    ASSERT_NE(p, nullptr);
    double *dp = static_cast<double *>(p);
    for (int i = 0; i < 1000; i++) {
        dp[i] = static_cast<double>(i);
    }
    for (int i = 0; i < 1000; i++) {
        EXPECT_DOUBLE_EQ(dp[i], static_cast<double>(i));
    }
    gfree(p);
}

// Test reallocation shrinking memory
TEST(GreallocnTest_15, ReallocShrinksMemory_15) {
    void *p = greallocn(nullptr, 100, sizeof(int));
    ASSERT_NE(p, nullptr);
    int *ip = static_cast<int *>(p);
    for (int i = 0; i < 100; i++) {
        ip[i] = i;
    }
    void *q = greallocn(p, 10, sizeof(int));
    ASSERT_NE(q, nullptr);
    int *iq = static_cast<int *>(q);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(iq[i], i);
    }
    gfree(q);
}

// Test that negative count with checkoverflow=true and existing pointer frees and returns null
TEST(GreallocnTest_15, NegativeCountCheckOverflowFreesExistingPointer_15) {
    void *p = greallocn(nullptr, 5, sizeof(int));
    ASSERT_NE(p, nullptr);
    void *result = greallocn(p, -1, sizeof(int), true);
    EXPECT_EQ(result, nullptr);
}

// Test overflow with large count and size, checkoverflow=true, with existing allocation
TEST(GreallocnTest_15, OverflowWithExistingPointerCheckOverflow_15) {
    void *p = greallocn(nullptr, 5, sizeof(int));
    ASSERT_NE(p, nullptr);
    void *result = greallocn(p, INT_MAX, INT_MAX, true);
    EXPECT_EQ(result, nullptr);
}

// Test with count=1 (no multiplication overflow possible)
TEST(GreallocnTest_15, CountOneNoOverflow_15) {
    void *p = greallocn(nullptr, 1, sizeof(long long));
    ASSERT_NE(p, nullptr);
    *static_cast<long long *>(p) = 123456789LL;
    EXPECT_EQ(*static_cast<long long *>(p), 123456789LL);
    gfree(p);
}

// Test default checkoverflow parameter (should be false by default)
TEST(GreallocnTest_15, DefaultCheckOverflowIsFalse_15) {
    // Normal case should work the same with default parameter
    void *p = greallocn(nullptr, 10, sizeof(int));
    ASSERT_NE(p, nullptr);
    gfree(p);
}

// Test negative count without checkoverflow aborts (death test)
TEST(GreallocnDeathTest_15, NegativeCountWithoutCheckOverflowAborts_15) {
    EXPECT_DEATH(greallocn(nullptr, -1, sizeof(int), false), "");
}

// Test zero size without checkoverflow aborts (death test)
TEST(GreallocnDeathTest_15, ZeroSizeWithoutCheckOverflowAborts_15) {
    EXPECT_DEATH(greallocn(nullptr, 10, 0, false), "");
}

// Test negative size without checkoverflow aborts (death test)
TEST(GreallocnDeathTest_15, NegativeSizeWithoutCheckOverflowAborts_15) {
    EXPECT_DEATH(greallocn(nullptr, 10, -1, false), "");
}

// Test overflow without checkoverflow aborts (death test)
TEST(GreallocnDeathTest_15, OverflowWithoutCheckOverflowAborts_15) {
    EXPECT_DEATH(greallocn(nullptr, INT_MAX, INT_MAX, false), "");
}
