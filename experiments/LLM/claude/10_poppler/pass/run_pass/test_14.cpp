#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
#include "gmem.h"

// Test normal allocation with valid parameters
TEST(Gmallocn3Test_14, NormalAllocation_14) {
    void *ptr = gmallocn3(2, 3, 4);
    ASSERT_NE(ptr, nullptr);
    // Should be able to write to the allocated memory (2*3*4 = 24 bytes)
    memset(ptr, 0, 24);
    gfree(ptr);
}

// Test that width=0 returns nullptr
TEST(Gmallocn3Test_14, WidthZeroReturnsNull_14) {
    void *ptr = gmallocn3(0, 3, 4);
    EXPECT_EQ(ptr, nullptr);
}

// Test that height=0 returns nullptr
TEST(Gmallocn3Test_14, HeightZeroReturnsNull_14) {
    void *ptr = gmallocn3(2, 0, 4);
    EXPECT_EQ(ptr, nullptr);
}

// Test that both width and height being 0 returns nullptr
TEST(Gmallocn3Test_14, WidthAndHeightZeroReturnsNull_14) {
    void *ptr = gmallocn3(0, 0, 4);
    EXPECT_EQ(ptr, nullptr);
}

// Test with all dimensions being 1
TEST(Gmallocn3Test_14, AllOnesAllocation_14) {
    void *ptr = gmallocn3(1, 1, 1);
    ASSERT_NE(ptr, nullptr);
    memset(ptr, 0, 1);
    gfree(ptr);
}

// Test negative width with checkoverflow=true returns nullptr
TEST(Gmallocn3Test_14, NegativeWidthCheckOverflowReturnsNull_14) {
    void *ptr = gmallocn3(-1, 3, 4, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test negative height with checkoverflow=true returns nullptr
TEST(Gmallocn3Test_14, NegativeHeightCheckOverflowReturnsNull_14) {
    void *ptr = gmallocn3(2, -1, 4, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test size=0 with checkoverflow=true returns nullptr (size <= 0 triggers error path)
TEST(Gmallocn3Test_14, SizeZeroCheckOverflowReturnsNull_14) {
    void *ptr = gmallocn3(2, 3, 0, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test negative size with checkoverflow=true returns nullptr
TEST(Gmallocn3Test_14, NegativeSizeCheckOverflowReturnsNull_14) {
    void *ptr = gmallocn3(2, 3, -1, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test overflow in width*height with checkoverflow=true
TEST(Gmallocn3Test_14, OverflowWidthTimesHeightCheckOverflow_14) {
    // INT_MAX * 2 should overflow
    void *ptr = gmallocn3(INT_MAX, 2, 1, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test overflow in (width*height)*size with checkoverflow=true
TEST(Gmallocn3Test_14, OverflowCountTimesSizeCheckOverflow_14) {
    void *ptr = gmallocn3(1000, 1000, INT_MAX, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test large but valid allocation
TEST(Gmallocn3Test_14, LargeValidAllocation_14) {
    void *ptr = gmallocn3(100, 100, 1);
    ASSERT_NE(ptr, nullptr);
    memset(ptr, 0, 10000);
    gfree(ptr);
}

// Test default checkoverflow parameter (should be false by default)
TEST(Gmallocn3Test_14, DefaultCheckOverflowIsFalse_14) {
    // Width=0 returns nullptr regardless of checkoverflow
    void *ptr = gmallocn3(0, 5, 4);
    EXPECT_EQ(ptr, nullptr);
}

// Test with width=1, height=1, size=1 (minimum valid allocation)
TEST(Gmallocn3Test_14, MinimumValidAllocation_14) {
    void *ptr = gmallocn3(1, 1, 1, false);
    ASSERT_NE(ptr, nullptr);
    unsigned char *byte_ptr = static_cast<unsigned char *>(ptr);
    byte_ptr[0] = 0xFF;
    EXPECT_EQ(byte_ptr[0], 0xFF);
    gfree(ptr);
}

// Test moderate allocation and verify memory is writable
TEST(Gmallocn3Test_14, ModerateAllocationWritable_14) {
    int width = 10;
    int height = 20;
    int size = 4;
    void *ptr = gmallocn3(width, height, size);
    ASSERT_NE(ptr, nullptr);
    // Total bytes: 10*20*4 = 800
    memset(ptr, 0xAB, 800);
    unsigned char *byte_ptr = static_cast<unsigned char *>(ptr);
    EXPECT_EQ(byte_ptr[0], 0xAB);
    EXPECT_EQ(byte_ptr[799], 0xAB);
    gfree(ptr);
}

// Test both negative width and height with checkoverflow=true
TEST(Gmallocn3Test_14, BothNegativeCheckOverflow_14) {
    void *ptr = gmallocn3(-1, -1, 4, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test large overflow scenario with checkoverflow=true
TEST(Gmallocn3Test_14, LargeOverflowCheckOverflow_14) {
    void *ptr = gmallocn3(INT_MAX, INT_MAX, INT_MAX, true);
    EXPECT_EQ(ptr, nullptr);
}

// Test that negative width with checkoverflow=false aborts
TEST(Gmallocn3Test_14, NegativeWidthNoCheckOverflowAborts_14) {
    EXPECT_DEATH(gmallocn3(-1, 3, 4, false), "");
}

// Test that negative height with checkoverflow=false aborts
TEST(Gmallocn3Test_14, NegativeHeightNoCheckOverflowAborts_14) {
    EXPECT_DEATH(gmallocn3(2, -1, 4, false), "");
}

// Test that size<=0 with checkoverflow=false aborts
TEST(Gmallocn3Test_14, SizeZeroNoCheckOverflowAborts_14) {
    EXPECT_DEATH(gmallocn3(2, 3, 0, false), "");
}

// Test overflow without checkoverflow aborts
TEST(Gmallocn3Test_14, OverflowNoCheckOverflowAborts_14) {
    EXPECT_DEATH(gmallocn3(INT_MAX, INT_MAX, INT_MAX, false), "");
}
