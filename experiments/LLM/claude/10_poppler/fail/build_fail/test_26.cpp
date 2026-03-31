#include <gtest/gtest.h>
#include <cstring>
#include <set>
#include <algorithm>
#include <climits>

// Declaration of the function under test
extern void grandom_fill(unsigned char *buff, int size);

class GrandomFillTest_26 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that filling a buffer of size 0 does not crash or modify anything
TEST_F(GrandomFillTest_26, ZeroSizeDoesNotCrash_26) {
    unsigned char buff[4] = {0xAA, 0xBB, 0xCC, 0xDD};
    grandom_fill(buff, 0);
    // Buffer should remain unchanged
    EXPECT_EQ(buff[0], 0xAA);
    EXPECT_EQ(buff[1], 0xBB);
    EXPECT_EQ(buff[2], 0xCC);
    EXPECT_EQ(buff[3], 0xDD);
}

// Test that filling a single byte works
TEST_F(GrandomFillTest_26, SingleByteFill_26) {
    unsigned char buff[1] = {0};
    grandom_fill(buff, 1);
    // We can't predict the value, but the call should not crash
    // Value should be in valid unsigned char range (always true for unsigned char)
    EXPECT_GE(buff[0], 0);
    EXPECT_LE(buff[0], 255);
}

// Test that filling a larger buffer writes to all positions
TEST_F(GrandomFillTest_26, FillsEntireBuffer_26) {
    const int size = 256;
    unsigned char buff[size];
    std::memset(buff, 0, size);
    grandom_fill(buff, size);
    
    // It's statistically extremely unlikely that all 256 bytes remain zero
    bool allZero = true;
    for (int i = 0; i < size; ++i) {
        if (buff[i] != 0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test that values are within valid unsigned char range [0, 255]
TEST_F(GrandomFillTest_26, ValuesInValidRange_26) {
    const int size = 1024;
    unsigned char buff[size];
    grandom_fill(buff, size);
    
    for (int i = 0; i < size; ++i) {
        EXPECT_GE(static_cast<int>(buff[i]), 0);
        EXPECT_LE(static_cast<int>(buff[i]), 255);
    }
}

// Test that two consecutive calls produce different results (with very high probability)
TEST_F(GrandomFillTest_26, TwoCallsProduceDifferentResults_26) {
    const int size = 64;
    unsigned char buff1[size];
    unsigned char buff2[size];
    
    grandom_fill(buff1, size);
    grandom_fill(buff2, size);
    
    // It's statistically extremely unlikely that two 64-byte random sequences are identical
    bool identical = (std::memcmp(buff1, buff2, size) == 0);
    EXPECT_FALSE(identical);
}

// Test that the function produces some variety of values
TEST_F(GrandomFillTest_26, ProducesVarietyOfValues_26) {
    const int size = 1024;
    unsigned char buff[size];
    grandom_fill(buff, size);
    
    std::set<unsigned char> uniqueValues(buff, buff + size);
    // With 1024 random bytes, we should see a significant number of unique values
    // Statistically, we expect close to 256 unique values; at minimum we should see > 10
    EXPECT_GT(uniqueValues.size(), 10u);
}

// Test filling a moderately large buffer
TEST_F(GrandomFillTest_26, LargeBufferFill_26) {
    const int size = 4096;
    unsigned char *buff = new unsigned char[size];
    std::memset(buff, 0, size);
    
    grandom_fill(buff, size);
    
    // Check that the buffer has been modified
    bool allZero = true;
    for (int i = 0; i < size; ++i) {
        if (buff[i] != 0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
    
    delete[] buff;
}

// Test that negative size doesn't fill any bytes (boundary condition)
TEST_F(GrandomFillTest_26, NegativeSizeDoesNotFill_26) {
    unsigned char buff[4] = {0xDE, 0xAD, 0xBE, 0xEF};
    grandom_fill(buff, -1);
    // Buffer should remain unchanged since loop condition index < size is false for negative size
    EXPECT_EQ(buff[0], 0xDE);
    EXPECT_EQ(buff[1], 0xAD);
    EXPECT_EQ(buff[2], 0xBE);
    EXPECT_EQ(buff[3], 0xEF);
}

// Test filling exactly 2 bytes
TEST_F(GrandomFillTest_26, TwoByteFill_26) {
    unsigned char buff[4] = {0xFF, 0xFF, 0xAA, 0xBB};
    grandom_fill(buff, 2);
    // The first two bytes are filled (we can't predict values)
    // The last two bytes should remain unchanged
    EXPECT_EQ(buff[2], 0xAA);
    EXPECT_EQ(buff[3], 0xBB);
}

// Test multiple consecutive fills to the same buffer
TEST_F(GrandomFillTest_26, MultipleFillsSameBuffer_26) {
    const int size = 32;
    unsigned char buff[size];
    
    // Fill multiple times and verify it doesn't crash
    for (int i = 0; i < 100; ++i) {
        grandom_fill(buff, size);
    }
    
    // Just verify we can read the buffer without issues
    std::set<unsigned char> uniqueValues(buff, buff + size);
    EXPECT_GT(uniqueValues.size(), 0u);
}
