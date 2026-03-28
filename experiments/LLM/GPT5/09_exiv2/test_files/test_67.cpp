#include <gtest/gtest.h>
#include <limits>
#include "safe_op.hpp"  // Include the header for the Safe::abs function

// TEST_ID 67
// Test for normal positive integer
TEST_F(SafeAbsTest_67, Abs_PositiveNumber_67) {
    EXPECT_EQ(Safe::abs(10), 10);  // Absolute of a positive number should return the number itself
}

// TEST_ID 68
// Test for normal negative integer
TEST_F(SafeAbsTest_68, Abs_NegativeNumber_68) {
    EXPECT_EQ(Safe::abs(-10), 10);  // Absolute of a negative number should return its positive counterpart
}

// TEST_ID 69
// Test for zero (edge case)
TEST_F(SafeAbsTest_69, Abs_Zero_69) {
    EXPECT_EQ(Safe::abs(0), 0);  // Absolute of zero should return zero
}

// TEST_ID 70
// Test for large positive number (within the range of the type)
TEST_F(SafeAbsTest_70, Abs_LargePositiveNumber_70) {
    EXPECT_EQ(Safe::abs(1000000), 1000000);  // Large positive number should return the number itself
}

// TEST_ID 71
// Test for large negative number (within the range of the type)
TEST_F(SafeAbsTest_71, Abs_LargeNegativeNumber_71) {
    EXPECT_EQ(Safe::abs(-1000000), 1000000);  // Large negative number should return its positive counterpart
}

// TEST_ID 72
// Test for edge case with the minimum value of a signed integer
TEST_F(SafeAbsTest_72, Abs_SignedMin_72) {
    EXPECT_EQ(Safe::abs(std::numeric_limits<int>::min()), std::numeric_limits<int>::max());  // Abs of INT_MIN should return INT_MAX
}

// TEST_ID 73
// Test for edge case with the maximum value of an unsigned integer
TEST_F(SafeAbsTest_73, Abs_UnsignedMax_73) {
    EXPECT_EQ(Safe::abs(std::numeric_limits<unsigned int>::max()), std::numeric_limits<unsigned int>::max());  // Abs of unsigned int max should return the value itself
}

// TEST_ID 74
// Test for edge case with a floating point number
TEST_F(SafeAbsTest_74, Abs_FloatingPoint_74) {
    EXPECT_EQ(Safe::abs(-3.14), 3.14);  // Abs of negative floating point should return positive value
}

// TEST_ID 75
// Test for the maximum value of a signed integer (just below the overflow limit)
TEST_F(SafeAbsTest_75, Abs_SignedMax_75) {
    EXPECT_EQ(Safe::abs(std::numeric_limits<int>::max()), std::numeric_limits<int>::max());  // Abs of INT_MAX should return INT_MAX
}

// TEST_ID 76
// Test for small signed integer value
TEST_F(SafeAbsTest_76, Abs_SmallSignedValue_76) {
    EXPECT_EQ(Safe::abs(-1), 1);  // Small negative signed number should return positive 1
}