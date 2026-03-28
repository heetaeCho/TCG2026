#include <gtest/gtest.h>

// Function to be tested
static inline unsigned char div255(int x) {
    return (unsigned char)((x + (x >> 8) + 0x80) >> 8);
}

// Test Suite for div255 function
TEST_F(Div255Test_1576, TestNormalValue_1576) {
    // Normal value test case
    int input = 512; // A normal test value
    unsigned char result = div255(input);
    
    // Assert the expected result for the normal input
    EXPECT_EQ(result, 2); // 512 + (512 >> 8) + 0x80 = 512 + 2 + 128 = 642, 642 >> 8 = 2
}

TEST_F(Div255Test_1577, TestBoundaryValueLower_1577) {
    // Boundary test case for the lower edge of the range
    int input = 0;
    unsigned char result = div255(input);
    
    // Assert the expected result for the boundary value of 0
    EXPECT_EQ(result, 0); // 0 + (0 >> 8) + 0x80 = 128, 128 >> 8 = 0
}

TEST_F(Div255Test_1578, TestBoundaryValueUpper_1578) {
    // Boundary test case for the upper edge of the range
    int input = 255;
    unsigned char result = div255(input);
    
    // Assert the expected result for the boundary value of 255
    EXPECT_EQ(result, 1); // 255 + (255 >> 8) + 0x80 = 255 + 0 + 128 = 383, 383 >> 8 = 1
}

TEST_F(Div255Test_1579, TestNegativeValue_1579) {
    // Exceptional case: Test for a negative input value
    int input = -1;
    unsigned char result = div255(input);
    
    // Assert the expected result for the negative value
    EXPECT_EQ(result, 0); // -1 + (-1 >> 8) + 0x80 = -1 + 0 + 128 = 127, 127 >> 8 = 0
}

TEST_F(Div255Test_1580, TestLargePositiveValue_1580) {
    // Test a large positive value for handling overflow cases
    int input = 10000;
    unsigned char result = div255(input);
    
    // Assert the expected result for large input
    EXPECT_EQ(result, 39); // 10000 + (10000 >> 8) + 0x80 = 10000 + 39 + 128 = 10167, 10167 >> 8 = 39
}

TEST_F(Div255Test_1581, TestOverflowEdgeCase_1581) {
    // Test an edge case where the value is larger than 255 but not extreme
    int input = 1023;
    unsigned char result = div255(input);
    
    // Assert the expected result for the value close to the overflow limit
    EXPECT_EQ(result, 4); // 1023 + (1023 >> 8) + 0x80 = 1023 + 3 + 128 = 1154, 1154 >> 8 = 4
}

TEST_F(Div255Test_1582, TestLargeNegativeValue_1582) {
    // Test for large negative values (boundary test for large negative values)
    int input = -10000;
    unsigned char result = div255(input);
    
    // Assert the expected result for a large negative input
    EXPECT_EQ(result, 0); // -10000 + (-10000 >> 8) + 0x80 = -10000 + (-39) + 128 = -9939, -9939 >> 8 = 0
}

TEST_F(Div255Test_1583, TestSmallPositiveValue_1583) {
    // Test for a small positive value, edge case
    int input = 1;
    unsigned char result = div255(input);
    
    // Assert the expected result for a small positive input
    EXPECT_EQ(result, 0); // 1 + (1 >> 8) + 0x80 = 1 + 0 + 128 = 129, 129 >> 8 = 0
}

TEST_F(Div255Test_1584, TestOverflowFromNegativeValue_1584) {
    // Exceptional case: Test a large negative input
    int input = -255;
    unsigned char result = div255(input);
    
    // Assert the expected result for a negative boundary value
    EXPECT_EQ(result, 0); // -255 + (-255 >> 8) + 0x80 = -255 + 0 + 128 = -127, -127 >> 8 = 0
}