#include <gtest/gtest.h>
#include <cstdlib>
#include <cstdio>
#include "gmem.h"

// Test normal allocation with valid count and size
TEST(GmallocnTest_12, NormalAllocation_12) {
    void *ptr = gmallocn(10, 4);
    ASSERT_NE(ptr, nullptr);
    // Verify we can write to the allocated memory
    memset(ptr, 0, 40);
    gfree(ptr);
}

// Test that count of 0 returns nullptr
TEST(GmallocnTest_12, ZeroCountReturnsNull_12) {
    void *ptr = gmallocn(0, 4);
    EXPECT_EQ(ptr, nullptr);
}

// Test that count of 0 returns nullptr even with checkoverflow true
TEST(GmallocnTest_12, ZeroCountReturnsNullWithCheckOverflow_12) {
    void *ptr = gmallocn(0, 4, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test that count of 0 returns nullptr regardless of size
TEST(GmallocnTest_12, ZeroCountReturnsNullAnySize_12) {
    void *ptr = gmallocn(0, 0);
    EXPECT_EQ(ptr, nullptr);
}

// Test allocation with count=1 and size=1 (minimum valid allocation)
TEST(GmallocnTest_12, MinimumValidAllocation_12) {
    void *ptr = gmallocn(1, 1);
    ASSERT_NE(ptr, nullptr);
    gfree(ptr);
}

// Test allocation with larger sizes
TEST(GmallocnTest_12, LargerAllocation_12) {
    void *ptr = gmallocn(100, 8);
    ASSERT_NE(ptr, nullptr);
    memset(ptr, 0, 800);
    gfree(ptr);
}

// Test negative count with checkoverflow=true returns nullptr
TEST(GmallocnTest_12, NegativeCountWithCheckOverflowReturnsNull_12) {
    void *ptr = gmallocn(-1, 4, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test size of 0 with checkoverflow=true returns nullptr (size <= 0 triggers error path)
TEST(GmallocnTest_12, ZeroSizeWithCheckOverflowReturnsNull_12) {
    void *ptr = gmallocn(10, 0, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test negative size with checkoverflow=true returns nullptr
TEST(GmallocnTest_12, NegativeSizeWithCheckOverflowReturnsNull_12) {
    void *ptr = gmallocn(10, -1, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test overflow case with checkoverflow=true returns nullptr
TEST(GmallocnTest_12, OverflowWithCheckOverflowReturnsNull_12) {
    void *ptr = gmallocn(INT_MAX, INT_MAX, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test large count that would overflow with checkoverflow=true
TEST(GmallocnTest_12, LargeCountOverflowCheckOverflow_12) {
    void *ptr = gmallocn(INT_MAX / 2 + 1, 4, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test negative count with checkoverflow=false causes abort (death test)
TEST(GmallocnDeathTest_12, NegativeCountWithoutCheckOverflowAborts_12) {
    EXPECT_DEATH(gmallocn(-1, 4, false), ".*");
}

// Test size of 0 without checkoverflow causes abort (death test)
TEST(GmallocnDeathTest_12, ZeroSizeWithoutCheckOverflowAborts_12) {
    EXPECT_DEATH(gmallocn(10, 0, false), ".*");
}

// Test negative size without checkoverflow causes abort (death test)
TEST(GmallocnDeathTest_12, NegativeSizeWithoutCheckOverflowAborts_12) {
    EXPECT_DEATH(gmallocn(10, -1, false), ".*");
}

// Test overflow without checkoverflow causes abort (death test)
TEST(GmallocnDeathTest_12, OverflowWithoutCheckOverflowAborts_12) {
    EXPECT_DEATH(gmallocn(INT_MAX, INT_MAX, false), ".*");
}

// Test default checkoverflow parameter (should be false, so it aborts)
TEST(GmallocnDeathTest_12, DefaultCheckOverflowAborts_12) {
    EXPECT_DEATH(gmallocn(-1, 4), ".*");
}

// Test allocation of count=1 size=1 with checkoverflow true
TEST(GmallocnTest_12, SmallAllocationWithCheckOverflow_12) {
    void *ptr = gmallocn(1, 1, true);
    ASSERT_NE(ptr, nullptr);
    gfree(ptr);
}

// Test that allocated memory is writable
TEST(GmallocnTest_12, AllocatedMemoryIsWritable_12) {
    int count = 50;
    int size = sizeof(int);
    void *ptr = gmallocn(count, size);
    ASSERT_NE(ptr, nullptr);
    int *arr = static_cast<int *>(ptr);
    for (int i = 0; i < count; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < count; i++) {
        EXPECT_EQ(arr[i], i);
    }
    gfree(ptr);
}

// Test boundary: count and size just below overflow threshold
TEST(GmallocnTest_12, BoundaryNoOverflow_12) {
    // A small allocation that should not overflow
    void *ptr = gmallocn(1024, 4, true);
    ASSERT_NE(ptr, nullptr);
    gfree(ptr);
}

// Test with count=1 and large valid size
TEST(GmallocnTest_12, CountOneWithLargeSize_12) {
    void *ptr = gmallocn(1, 4096, true);
    ASSERT_NE(ptr, nullptr);
    gfree(ptr);
}
