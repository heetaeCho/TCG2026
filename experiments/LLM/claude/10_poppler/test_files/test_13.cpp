#include <gtest/gtest.h>
#include "gmem.h"
#include <climits>
#include <cstring>

// Test normal allocation with valid count and size
TEST(GmallocnCheckoverflowTest_13, NormalAllocation_13) {
    void *ptr = gmallocn_checkoverflow(10, sizeof(int));
    ASSERT_NE(ptr, nullptr);
    // Verify we can actually write to the allocated memory
    memset(ptr, 0, 10 * sizeof(int));
    gfree(ptr);
}

// Test allocation with count of 1
TEST(GmallocnCheckoverflowTest_13, SingleElementAllocation_13) {
    void *ptr = gmallocn_checkoverflow(1, sizeof(double));
    ASSERT_NE(ptr, nullptr);
    memset(ptr, 0, sizeof(double));
    gfree(ptr);
}

// Test allocation with size of 1
TEST(GmallocnCheckoverflowTest_13, SingleByteSize_13) {
    void *ptr = gmallocn_checkoverflow(100, 1);
    ASSERT_NE(ptr, nullptr);
    memset(ptr, 'A', 100);
    gfree(ptr);
}

// Test allocation with count of 0 - boundary condition
TEST(GmallocnCheckoverflowTest_13, ZeroCount_13) {
    // With checkoverflow (true), zero count should not crash
    // It may return nullptr or a valid pointer depending on implementation
    void *ptr = gmallocn_checkoverflow(0, sizeof(int));
    // We just verify it doesn't crash; free if non-null
    if (ptr) {
        gfree(ptr);
    }
}

// Test allocation with size of 0 - boundary condition
TEST(GmallocnCheckoverflowTest_13, ZeroSize_13) {
    void *ptr = gmallocn_checkoverflow(10, 0);
    if (ptr) {
        gfree(ptr);
    }
}

// Test overflow condition - should return nullptr instead of crashing
TEST(GmallocnCheckoverflowTest_13, OverflowReturnsNull_13) {
    // Very large values that would overflow when multiplied
    void *ptr = gmallocn_checkoverflow(INT_MAX, INT_MAX);
    EXPECT_EQ(ptr, nullptr);
}

// Test negative count - should return nullptr on overflow check
TEST(GmallocnCheckoverflowTest_13, NegativeCountReturnsNull_13) {
    void *ptr = gmallocn_checkoverflow(-1, sizeof(int));
    EXPECT_EQ(ptr, nullptr);
}

// Test negative size - should return nullptr on overflow check
TEST(GmallocnCheckoverflowTest_13, NegativeSizeReturnsNull_13) {
    void *ptr = gmallocn_checkoverflow(10, -1);
    EXPECT_EQ(ptr, nullptr);
}

// Test both negative - should return nullptr on overflow check
TEST(GmallocnCheckoverflowTest_13, BothNegativeReturnsNull_13) {
    void *ptr = gmallocn_checkoverflow(-1, -1);
    EXPECT_EQ(ptr, nullptr);
}

// Test large but valid allocation
TEST(GmallocnCheckoverflowTest_13, LargeValidAllocation_13) {
    void *ptr = gmallocn_checkoverflow(1024, sizeof(char));
    ASSERT_NE(ptr, nullptr);
    memset(ptr, 0, 1024);
    gfree(ptr);
}

// Test that allocated memory is writable
TEST(GmallocnCheckoverflowTest_13, AllocatedMemoryIsWritable_13) {
    int count = 5;
    void *ptr = gmallocn_checkoverflow(count, sizeof(int));
    ASSERT_NE(ptr, nullptr);
    int *intPtr = static_cast<int *>(ptr);
    for (int i = 0; i < count; i++) {
        intPtr[i] = i * 42;
    }
    for (int i = 0; i < count; i++) {
        EXPECT_EQ(intPtr[i], i * 42);
    }
    gfree(ptr);
}

// Test near-overflow boundary
TEST(GmallocnCheckoverflowTest_13, NearOverflowBoundary_13) {
    // INT_MAX / 2 * 3 should overflow
    void *ptr = gmallocn_checkoverflow(INT_MAX / 2, 3);
    // This should return nullptr due to overflow
    EXPECT_EQ(ptr, nullptr);
}

// Test count=1, size=1 minimal allocation
TEST(GmallocnCheckoverflowTest_13, MinimalAllocation_13) {
    void *ptr = gmallocn_checkoverflow(1, 1);
    ASSERT_NE(ptr, nullptr);
    *static_cast<char *>(ptr) = 'X';
    EXPECT_EQ(*static_cast<char *>(ptr), 'X');
    gfree(ptr);
}
