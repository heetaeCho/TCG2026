#include <gtest/gtest.h>
#include <stdexcept>
#include "safe_op.hpp"

// Mock test class for Safe::add
class SafeAddTest_66 : public ::testing::Test {};

// Test Case 1: Normal operation with no overflow
TEST_F(SafeAddTest_66, AddNoOverflow_66) {
    // Test addition with two small numbers that should not cause overflow
    int a = 10, b = 20;
    EXPECT_NO_THROW({
        int result = Safe::add(a, b);
        EXPECT_EQ(result, 30);
    });
}

// Test Case 2: Boundary condition for integer overflow
TEST_F(SafeAddTest_66, AddOverflow_66) {
    // Test case where addition will overflow (INT_MAX + 1)
    int a = INT_MAX, b = 1;
    EXPECT_THROW({
        Safe::add(a, b);
    }, std::overflow_error);
}

// Test Case 3: Adding zero should not change the number
TEST_F(SafeAddTest_66, AddZero_66) {
    // Test adding 0 to a number
    int a = 5, b = 0;
    EXPECT_NO_THROW({
        int result = Safe::add(a, b);
        EXPECT_EQ(result, 5);
    });
}

// Test Case 4: Negative numbers should work as expected
TEST_F(SafeAddTest_66, AddNegative_66) {
    // Test adding negative numbers
    int a = -5, b = -10;
    EXPECT_NO_THROW({
        int result = Safe::add(a, b);
        EXPECT_EQ(result, -15);
    });
}

// Test Case 5: Edge case for integer limits (INT_MIN + -1 causes underflow)
TEST_F(SafeAddTest_66, AddUnderflow_66) {
    // Test case where addition will cause underflow (INT_MIN - 1)
    int a = INT_MIN, b = -1;
    EXPECT_THROW({
        Safe::add(a, b);
    }, std::overflow_error);
}