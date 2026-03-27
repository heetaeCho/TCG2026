#include <gtest/gtest.h>

#define jbig2HuffmanOOB 0xfffffffe
#define jbig2HuffmanLOW 0xfffffffd
#define jbig2HuffmanEOT 0xffffffff

static inline bool isPixelOutsideAdaptiveField(int x, int y) {
    return y < -128 || y > 0 || x < -128 || (y < 0 && x > 127) || (y == 0 && x >= 0);
}

// Test Fixture
class JBIG2StreamTest_1839 : public ::testing::Test {
protected:
    // Setup and teardown if needed
    void SetUp() override {}
    void TearDown() override {}
};

// Normal Operation Test: Test when the pixel is inside the valid adaptive field
TEST_F(JBIG2StreamTest_1839, PixelInsideAdaptiveField_1839) {
    // Test pixel (x=0, y=0) inside the valid range
    EXPECT_FALSE(isPixelOutsideAdaptiveField(0, 0));  // Expected: false as it's inside the field
}

// Boundary Condition Test: Test when x or y is at the boundary values
TEST_F(JBIG2StreamTest_1839, PixelAtBoundary_1839) {
    // Test pixel at the boundary where y = -128 and x = 127 (just on the boundary of valid range)
    EXPECT_FALSE(isPixelOutsideAdaptiveField(127, -128));  // Expected: false, should still be inside the field

    // Test pixel outside the boundary with x = -128
    EXPECT_TRUE(isPixelOutsideAdaptiveField(-128, 0));  // Expected: true as it's outside
}

// Exceptional Case Test: Test the pixel outside the adaptive field
TEST_F(JBIG2StreamTest_1839, PixelOutsideAdaptiveField_1839) {
    // Test a pixel outside the field with invalid x and y
    EXPECT_TRUE(isPixelOutsideAdaptiveField(128, 1));  // Expected: true as it's outside the field
    EXPECT_TRUE(isPixelOutsideAdaptiveField(-129, -1)); // Expected: true as it's outside the field
}

// Edge Case: Check for pixel with extreme boundary values
TEST_F(JBIG2StreamTest_1839, PixelExtremeBoundary_1839) {
    // Test pixel with maximum boundary values that are still valid
    EXPECT_FALSE(isPixelOutsideAdaptiveField(127, -128));  // Expected: false as it should be valid at the boundary
    EXPECT_FALSE(isPixelOutsideAdaptiveField(-128, 0));    // Expected: false as it is within the boundary
}

// Test for exceptional case with large value (overflow boundary)
TEST_F(JBIG2StreamTest_1839, PixelOverflowBoundary_1839) {
    // Test for a pixel with values beyond the valid ranges, should be considered outside the adaptive field
    EXPECT_TRUE(isPixelOutsideAdaptiveField(99999, 99999));  // Expected: true as it exceeds all boundaries
}

// Test for interaction with Huffman constants (just as a sanity check)
TEST_F(JBIG2StreamTest_1839, TestHuffmanConstants_1839) {
    // Validate Huffman constants
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffe);  // Check if the constant matches expected
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffd); // Check if the constant matches expected
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffff); // Check if the constant matches expected
}