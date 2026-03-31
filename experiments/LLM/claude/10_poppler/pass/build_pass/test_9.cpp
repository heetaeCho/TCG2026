#include <gtest/gtest.h>
#include <cstdlib>
#include <cstddef>
#include "gmem.h"

// Test that gmalloc with size 0 returns nullptr
TEST(GmallocTest_9, ZeroSizeReturnsNull_9) {
    void *p = gmalloc(0);
    EXPECT_EQ(p, nullptr);
}

// Test that gmalloc with size 0 and checkoverflow=true returns nullptr
TEST(GmallocTest_9, ZeroSizeWithCheckOverflowReturnsNull_9) {
    void *p = gmalloc(0, true);
    EXPECT_EQ(p, nullptr);
}

// Test that gmalloc with size 0 and checkoverflow=false returns nullptr
TEST(GmallocTest_9, ZeroSizeWithCheckOverflowFalseReturnsNull_9) {
    void *p = gmalloc(0, false);
    EXPECT_EQ(p, nullptr);
}

// Test that gmalloc with a small valid size returns a non-null pointer
TEST(GmallocTest_9, SmallSizeReturnsNonNull_9) {
    void *p = gmalloc(1);
    EXPECT_NE(p, nullptr);
    std::free(p);
}

// Test that gmalloc with a typical size returns a non-null pointer
TEST(GmallocTest_9, TypicalSizeReturnsNonNull_9) {
    void *p = gmalloc(1024);
    EXPECT_NE(p, nullptr);
    std::free(p);
}

// Test that gmalloc with a larger size returns a non-null pointer
TEST(GmallocTest_9, LargerSizeReturnsNonNull_9) {
    void *p = gmalloc(1024 * 1024);
    EXPECT_NE(p, nullptr);
    std::free(p);
}

// Test that gmalloc with checkoverflow=true and a valid size returns non-null
TEST(GmallocTest_9, ValidSizeWithCheckOverflowTrueReturnsNonNull_9) {
    void *p = gmalloc(256, true);
    EXPECT_NE(p, nullptr);
    std::free(p);
}

// Test that gmalloc with checkoverflow=false and a valid size returns non-null
TEST(GmallocTest_9, ValidSizeWithCheckOverflowFalseReturnsNonNull_9) {
    void *p = gmalloc(256, false);
    EXPECT_NE(p, nullptr);
    std::free(p);
}

// Test that the returned pointer from gmalloc is writable
TEST(GmallocTest_9, AllocatedMemoryIsWritable_9) {
    size_t size = 128;
    void *p = gmalloc(size);
    ASSERT_NE(p, nullptr);
    // Write to the allocated memory to verify it's usable
    std::memset(p, 0xAB, size);
    unsigned char *bytes = static_cast<unsigned char *>(p);
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(bytes[i], 0xAB);
    }
    std::free(p);
}

// Test that gmalloc with size 1 returns valid pointer
TEST(GmallocTest_9, Size1ReturnsNonNull_9) {
    void *p = gmalloc(1);
    EXPECT_NE(p, nullptr);
    std::free(p);
}

// Test that multiple allocations return different pointers
TEST(GmallocTest_9, MultipleAllocationsReturnDifferentPointers_9) {
    void *p1 = gmalloc(64);
    void *p2 = gmalloc(64);
    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);
    EXPECT_NE(p1, p2);
    std::free(p1);
    std::free(p2);
}

// Test that default checkoverflow parameter is false (valid allocation works)
TEST(GmallocTest_9, DefaultCheckOverflowParameter_9) {
    void *p = gmalloc(512);
    EXPECT_NE(p, nullptr);
    std::free(p);
}

// Test boundary: size = 1 byte with checkoverflow true
TEST(GmallocTest_9, SingleByteWithCheckOverflow_9) {
    void *p = gmalloc(1, true);
    EXPECT_NE(p, nullptr);
    std::free(p);
}

// Test that gmalloc with checkoverflow=true returns nullptr on failure
// (We test with an absurdly large size that should fail)
TEST(GmallocTest_9, HugeAllocationWithCheckOverflowReturnsNull_9) {
    // Try to allocate an extremely large amount that should fail
    // SIZE_MAX should be too large for any system to allocate
    void *p = gmalloc(SIZE_MAX, true);
    EXPECT_EQ(p, nullptr);
}

// Test gmalloc with a moderately large but feasible allocation
TEST(GmallocTest_9, ModerateLargeAllocation_9) {
    void *p = gmalloc(10 * 1024 * 1024); // 10 MB
    EXPECT_NE(p, nullptr);
    if (p) {
        std::free(p);
    }
}
