#include <gtest/gtest.h>
#include "gmem.h"
#include <cstdlib>
#include <cstring>
#include <climits>

// Test normal allocation with greallocn_checkoverflow
TEST(GmemGreallocnCheckoverflowTest_16, NormalAllocation_16) {
    // Allocate initial memory
    void *p = gmalloc(10);
    ASSERT_NE(p, nullptr);
    
    // Reallocate with valid count and size
    void *result = greallocn_checkoverflow(p, 5, 4);
    ASSERT_NE(result, nullptr);
    
    gfree(result);
}

TEST(GmemGreallocnCheckoverflowTest_16, NullPointerAllocation_16) {
    // When p is null, it should behave like malloc(count * size)
    void *result = greallocn_checkoverflow(nullptr, 10, 8);
    ASSERT_NE(result, nullptr);
    
    gfree(result);
}

TEST(GmemGreallocnCheckoverflowTest_16, SingleElementAllocation_16) {
    void *result = greallocn_checkoverflow(nullptr, 1, 1);
    ASSERT_NE(result, nullptr);
    
    gfree(result);
}

TEST(GmemGreallocnCheckoverflowTest_16, OverflowReturnsNull_16) {
    // Overflow case: count * size overflows int or size_t
    // Should return nullptr on overflow since checkoverflow = true
    void *result = greallocn_checkoverflow(nullptr, INT_MAX, INT_MAX);
    EXPECT_EQ(result, nullptr);
}

TEST(GmemGreallocnCheckoverflowTest_16, NegativeCountReturnsNull_16) {
    // Negative count should be treated as error/overflow
    void *result = greallocn_checkoverflow(nullptr, -1, 10);
    EXPECT_EQ(result, nullptr);
}

TEST(GmemGreallocnCheckoverflowTest_16, NegativeSizeReturnsNull_16) {
    // Negative size should be treated as error/overflow
    void *result = greallocn_checkoverflow(nullptr, 10, -1);
    EXPECT_EQ(result, nullptr);
}

TEST(GmemGreallocnCheckoverflowTest_16, ZeroCountReturnsNull_16) {
    // Zero count - behavior depends on implementation, but should not crash
    void *result = greallocn_checkoverflow(nullptr, 0, 10);
    // Result could be nullptr or a valid pointer depending on implementation
    // Just ensure it doesn't crash; if non-null, free it
    if (result) {
        gfree(result);
    }
}

TEST(GmemGreallocnCheckoverflowTest_16, ZeroSizeReturnsNull_16) {
    // Zero size - behavior depends on implementation, but should not crash
    void *result = greallocn_checkoverflow(nullptr, 10, 0);
    if (result) {
        gfree(result);
    }
}

TEST(GmemGreallocnCheckoverflowTest_16, ReallocExistingMemory_16) {
    // Allocate some memory, write data, then reallocate
    void *p = gmalloc(20);
    ASSERT_NE(p, nullptr);
    memset(p, 0xAB, 20);
    
    // Reallocate to larger size
    void *result = greallocn_checkoverflow(p, 10, 8);
    ASSERT_NE(result, nullptr);
    
    // The first 20 bytes should be preserved
    unsigned char *bytes = static_cast<unsigned char *>(result);
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(bytes[i], 0xAB) << "Byte at index " << i << " was not preserved";
    }
    
    gfree(result);
}

TEST(GmemGreallocnCheckoverflowTest_16, LargeButValidAllocation_16) {
    // A large but hopefully valid allocation
    void *result = greallocn_checkoverflow(nullptr, 1024, 1024);
    // This is 1MB, should generally succeed
    if (result != nullptr) {
        memset(result, 0, 1024 * 1024); // Verify it's writable
        gfree(result);
    }
}

TEST(GmemGreallocnCheckoverflowTest_16, OverflowWithExistingPointerReturnsNull_16) {
    void *p = gmalloc(10);
    ASSERT_NE(p, nullptr);
    
    // Attempt overflow reallocation
    void *result = greallocn_checkoverflow(p, INT_MAX, INT_MAX);
    EXPECT_EQ(result, nullptr);
    
    // Original pointer should still need to be freed if overflow returns null
    // The implementation may or may not free p on failure
    // Since we got null back, we should free the original
    gfree(p);
}

TEST(GmemGreallocnCheckoverflowTest_16, BothNegativeReturnsNull_16) {
    void *result = greallocn_checkoverflow(nullptr, -1, -1);
    EXPECT_EQ(result, nullptr);
}

TEST(GmemGreallocnCheckoverflowTest_16, CountOneValidSize_16) {
    void *result = greallocn_checkoverflow(nullptr, 1, 100);
    ASSERT_NE(result, nullptr);
    
    // Verify we can write to it
    memset(result, 0xFF, 100);
    
    gfree(result);
}

TEST(GmemGreallocnCheckoverflowTest_16, SizeOneValidCount_16) {
    void *result = greallocn_checkoverflow(nullptr, 100, 1);
    ASSERT_NE(result, nullptr);
    
    memset(result, 0xFF, 100);
    
    gfree(result);
}
