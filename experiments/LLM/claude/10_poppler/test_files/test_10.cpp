#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
#include "gmem.h"

// Test normal allocation with a reasonable size
TEST(GmallocCheckoverflowTest_10, NormalAllocation_10) {
    void *ptr = gmalloc_checkoverflow(100);
    ASSERT_NE(ptr, nullptr);
    // Verify we can write to and read from the allocated memory
    memset(ptr, 0xAB, 100);
    unsigned char *bytes = static_cast<unsigned char *>(ptr);
    EXPECT_EQ(bytes[0], 0xAB);
    EXPECT_EQ(bytes[99], 0xAB);
    gfree(ptr);
}

// Test allocation of size zero
TEST(GmallocCheckoverflowTest_10, ZeroSizeAllocation_10) {
    // Allocating zero bytes: behavior may return nullptr or a valid pointer
    // depending on implementation, but it should not crash
    void *ptr = gmalloc_checkoverflow(0);
    // Either nullptr or a valid pointer is acceptable for zero-size allocation
    // Just free it if non-null
    if (ptr != nullptr) {
        gfree(ptr);
    }
}

// Test allocation of size 1
TEST(GmallocCheckoverflowTest_10, SingleByteAllocation_10) {
    void *ptr = gmalloc_checkoverflow(1);
    ASSERT_NE(ptr, nullptr);
    unsigned char *bytes = static_cast<unsigned char *>(ptr);
    bytes[0] = 0xFF;
    EXPECT_EQ(bytes[0], 0xFF);
    gfree(ptr);
}

// Test allocation of a larger block
TEST(GmallocCheckoverflowTest_10, LargeAllocation_10) {
    size_t size = 1024 * 1024; // 1 MB
    void *ptr = gmalloc_checkoverflow(size);
    ASSERT_NE(ptr, nullptr);
    // Write to first and last byte to verify accessibility
    memset(ptr, 0, size);
    unsigned char *bytes = static_cast<unsigned char *>(ptr);
    bytes[0] = 1;
    bytes[size - 1] = 2;
    EXPECT_EQ(bytes[0], 1);
    EXPECT_EQ(bytes[size - 1], 2);
    gfree(ptr);
}

// Test that an extremely large allocation returns nullptr (overflow check)
TEST(GmallocCheckoverflowTest_10, OverflowReturnsNull_10) {
    // Request an absurdly large amount of memory that should fail
    // The _checkoverflow variant should return nullptr instead of aborting
    size_t hugeSize = static_cast<size_t>(-1); // SIZE_MAX
    void *ptr = gmalloc_checkoverflow(hugeSize);
    EXPECT_EQ(ptr, nullptr);
}

// Test multiple allocations and frees (no double-free or corruption)
TEST(GmallocCheckoverflowTest_10, MultipleAllocationsAndFrees_10) {
    const int count = 100;
    void *ptrs[count];
    for (int i = 0; i < count; i++) {
        ptrs[i] = gmalloc_checkoverflow(64);
        ASSERT_NE(ptrs[i], nullptr);
        memset(ptrs[i], i & 0xFF, 64);
    }
    for (int i = 0; i < count; i++) {
        unsigned char *bytes = static_cast<unsigned char *>(ptrs[i]);
        EXPECT_EQ(bytes[0], static_cast<unsigned char>(i & 0xFF));
        gfree(ptrs[i]);
    }
}

// Test allocation with a near-overflow size (SIZE_MAX - small value)
TEST(GmallocCheckoverflowTest_10, NearOverflowReturnsNull_10) {
    size_t nearMaxSize = static_cast<size_t>(-1) - 16;
    void *ptr = gmalloc_checkoverflow(nearMaxSize);
    EXPECT_EQ(ptr, nullptr);
}

// Test that returned pointer is usable for writing various data types
TEST(GmallocCheckoverflowTest_10, WriteAndReadDifferentTypes_10) {
    void *ptr = gmalloc_checkoverflow(sizeof(int) * 10);
    ASSERT_NE(ptr, nullptr);
    int *intPtr = static_cast<int *>(ptr);
    for (int i = 0; i < 10; i++) {
        intPtr[i] = i * 42;
    }
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(intPtr[i], i * 42);
    }
    gfree(ptr);
}
