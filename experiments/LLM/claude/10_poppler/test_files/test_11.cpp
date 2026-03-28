#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
#include "gmem.h"

class GMemReallocTest_11 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up is handled in individual tests
    }
};

// Test that grealloc with size 0 frees memory and returns nullptr
TEST_F(GMemReallocTest_11, SizeZeroReturnsNullptr_11) {
    void *p = std::malloc(100);
    ASSERT_NE(p, nullptr);
    void *result = grealloc(p, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that grealloc with size 0 and null pointer returns nullptr
TEST_F(GMemReallocTest_11, SizeZeroNullPtrReturnsNullptr_11) {
    void *result = grealloc(nullptr, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that grealloc with null pointer and non-zero size allocates new memory (acts like malloc)
TEST_F(GMemReallocTest_11, NullPtrNonZeroSizeAllocates_11) {
    void *result = grealloc(nullptr, 64);
    EXPECT_NE(result, nullptr);
    std::free(result);
}

// Test that grealloc with existing pointer and non-zero size reallocates memory
TEST_F(GMemReallocTest_11, ExistingPtrReallocates_11) {
    void *p = std::malloc(32);
    ASSERT_NE(p, nullptr);
    std::memset(p, 'A', 32);

    void *result = grealloc(p, 128);
    EXPECT_NE(result, nullptr);

    // Verify that original data is preserved
    unsigned char *bytes = static_cast<unsigned char *>(result);
    for (int i = 0; i < 32; i++) {
        EXPECT_EQ(bytes[i], 'A');
    }
    std::free(result);
}

// Test that grealloc with small allocation works correctly
TEST_F(GMemReallocTest_11, SmallAllocation_11) {
    void *result = grealloc(nullptr, 1);
    EXPECT_NE(result, nullptr);
    std::free(result);
}

// Test that grealloc preserves data when shrinking
TEST_F(GMemReallocTest_11, ShrinkPreservesData_11) {
    void *p = std::malloc(256);
    ASSERT_NE(p, nullptr);
    std::memset(p, 'B', 256);

    void *result = grealloc(p, 64);
    EXPECT_NE(result, nullptr);

    unsigned char *bytes = static_cast<unsigned char *>(result);
    for (int i = 0; i < 64; i++) {
        EXPECT_EQ(bytes[i], 'B');
    }
    std::free(result);
}

// Test that grealloc with size 0 and checkoverflow=true returns nullptr
TEST_F(GMemReallocTest_11, SizeZeroCheckOverflowReturnsNullptr_11) {
    void *p = std::malloc(50);
    ASSERT_NE(p, nullptr);
    void *result = grealloc(p, 0, true);
    EXPECT_EQ(result, nullptr);
}

// Test that grealloc with size 0 and checkoverflow=false returns nullptr
TEST_F(GMemReallocTest_11, SizeZeroNoCheckOverflowReturnsNullptr_11) {
    void *p = std::malloc(50);
    ASSERT_NE(p, nullptr);
    void *result = grealloc(p, 0, false);
    EXPECT_EQ(result, nullptr);
}

// Test normal allocation with checkoverflow=true
TEST_F(GMemReallocTest_11, NormalAllocationCheckOverflow_11) {
    void *result = grealloc(nullptr, 128, true);
    EXPECT_NE(result, nullptr);
    std::free(result);
}

// Test normal allocation with checkoverflow=false (default)
TEST_F(GMemReallocTest_11, NormalAllocationNoCheckOverflow_11) {
    void *result = grealloc(nullptr, 128, false);
    EXPECT_NE(result, nullptr);
    std::free(result);
}

// Test that grealloc can handle a moderately large allocation
TEST_F(GMemReallocTest_11, LargeAllocation_11) {
    void *result = grealloc(nullptr, 1024 * 1024); // 1MB
    EXPECT_NE(result, nullptr);
    std::free(result);
}

// Test realloc from null to some size, then realloc to larger size
TEST_F(GMemReallocTest_11, SequentialGrowth_11) {
    void *p = grealloc(nullptr, 16);
    ASSERT_NE(p, nullptr);
    std::memset(p, 'C', 16);

    void *p2 = grealloc(p, 64);
    ASSERT_NE(p2, nullptr);

    unsigned char *bytes = static_cast<unsigned char *>(p2);
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(bytes[i], 'C');
    }

    void *p3 = grealloc(p2, 256);
    ASSERT_NE(p3, nullptr);

    bytes = static_cast<unsigned char *>(p3);
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(bytes[i], 'C');
    }
    std::free(p3);
}

// Test that the default value of checkoverflow is false (implicitly tested by normal usage)
TEST_F(GMemReallocTest_11, DefaultCheckOverflowParam_11) {
    // Just verify that calling without the third parameter works the same as false
    void *result1 = grealloc(nullptr, 32);
    EXPECT_NE(result1, nullptr);
    std::free(result1);

    void *result2 = grealloc(nullptr, 32, false);
    EXPECT_NE(result2, nullptr);
    std::free(result2);
}

// Test realloc to same size
TEST_F(GMemReallocTest_11, ReallocSameSize_11) {
    void *p = std::malloc(100);
    ASSERT_NE(p, nullptr);
    std::memset(p, 'D', 100);

    void *result = grealloc(p, 100);
    EXPECT_NE(result, nullptr);

    unsigned char *bytes = static_cast<unsigned char *>(result);
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(bytes[i], 'D');
    }
    std::free(result);
}

// Test that writing to allocated memory works
TEST_F(GMemReallocTest_11, WriteToAllocatedMemory_11) {
    void *result = grealloc(nullptr, 512);
    ASSERT_NE(result, nullptr);

    // Should be able to write to the entire allocated region without issues
    std::memset(result, 0xFF, 512);

    unsigned char *bytes = static_cast<unsigned char *>(result);
    for (int i = 0; i < 512; i++) {
        EXPECT_EQ(bytes[i], 0xFF);
    }
    std::free(result);
}
