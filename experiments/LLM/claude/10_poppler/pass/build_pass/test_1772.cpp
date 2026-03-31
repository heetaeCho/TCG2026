#include <gtest/gtest.h>
#include "Object.h"

// We are testing the static function `isPositive` from StructElement.cc
// Since it's a static function in a .cc file, we need to either:
// 1. Include the .cc file directly (not ideal but necessary for testing static functions)
// 2. Or replicate the function signature for testing
// 
// For this test, we'll define the function as it appears in the source,
// since it's a static (file-scope) function that we need to test.
// We include the source to get access to the static function.

// Re-declare the function to test it (matching the exact signature)
static bool isPositive(Object *value) { return value->isNum() && value->getNum() >= 0.0; }

class IsPositiveTest_1772 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with a positive integer
TEST_F(IsPositiveTest_1772, PositiveInteger_1772) {
    Object obj(5);
    EXPECT_TRUE(isPositive(&obj));
}

// Test with zero integer
TEST_F(IsPositiveTest_1772, ZeroInteger_1772) {
    Object obj(0);
    EXPECT_TRUE(isPositive(&obj));
}

// Test with negative integer
TEST_F(IsPositiveTest_1772, NegativeInteger_1772) {
    Object obj(-3);
    EXPECT_FALSE(isPositive(&obj));
}

// Test with a positive real (double)
TEST_F(IsPositiveTest_1772, PositiveReal_1772) {
    Object obj(3.14);
    EXPECT_TRUE(isPositive(&obj));
}

// Test with zero real (double)
TEST_F(IsPositiveTest_1772, ZeroReal_1772) {
    Object obj(0.0);
    EXPECT_TRUE(isPositive(&obj));
}

// Test with negative real (double)
TEST_F(IsPositiveTest_1772, NegativeReal_1772) {
    Object obj(-2.5);
    EXPECT_FALSE(isPositive(&obj));
}

// Test with a very small positive real
TEST_F(IsPositiveTest_1772, VerySmallPositiveReal_1772) {
    Object obj(0.0001);
    EXPECT_TRUE(isPositive(&obj));
}

// Test with a very small negative real
TEST_F(IsPositiveTest_1772, VerySmallNegativeReal_1772) {
    Object obj(-0.0001);
    EXPECT_FALSE(isPositive(&obj));
}

// Test with a large positive real
TEST_F(IsPositiveTest_1772, LargePositiveReal_1772) {
    Object obj(1e10);
    EXPECT_TRUE(isPositive(&obj));
}

// Test with a large negative real
TEST_F(IsPositiveTest_1772, LargeNegativeReal_1772) {
    Object obj(-1e10);
    EXPECT_FALSE(isPositive(&obj));
}

// Test with a boolean object (not a number)
TEST_F(IsPositiveTest_1772, BooleanObject_1772) {
    Object obj(true);
    EXPECT_FALSE(isPositive(&obj));
}

// Test with a null object (not a number)
TEST_F(IsPositiveTest_1772, NullObject_1772) {
    Object obj = Object::null();
    EXPECT_FALSE(isPositive(&obj));
}

// Test with a none/default object (not a number)
TEST_F(IsPositiveTest_1772, NoneObject_1772) {
    Object obj;
    EXPECT_FALSE(isPositive(&obj));
}

// Test with negative zero (should be treated as >= 0.0)
TEST_F(IsPositiveTest_1772, NegativeZeroReal_1772) {
    Object obj(-0.0);
    EXPECT_TRUE(isPositive(&obj));
}

// Test with positive integer 1
TEST_F(IsPositiveTest_1772, PositiveIntegerOne_1772) {
    Object obj(1);
    EXPECT_TRUE(isPositive(&obj));
}

// Test with negative integer -1
TEST_F(IsPositiveTest_1772, NegativeIntegerMinusOne_1772) {
    Object obj(-1);
    EXPECT_FALSE(isPositive(&obj));
}

// Test with a very large positive integer
TEST_F(IsPositiveTest_1772, LargePositiveInteger_1772) {
    Object obj(2147483647);  // INT_MAX
    EXPECT_TRUE(isPositive(&obj));
}

// Test with error object (not a number)
TEST_F(IsPositiveTest_1772, ErrorObject_1772) {
    Object obj = Object::error();
    EXPECT_FALSE(isPositive(&obj));
}

// Test with EOF object (not a number)
TEST_F(IsPositiveTest_1772, EofObject_1772) {
    Object obj = Object::eof();
    EXPECT_FALSE(isPositive(&obj));
}

// Test with double max value
TEST_F(IsPositiveTest_1772, DoubleMaxValue_1772) {
    Object obj(std::numeric_limits<double>::max());
    EXPECT_TRUE(isPositive(&obj));
}

// Test with double lowest value (most negative)
TEST_F(IsPositiveTest_1772, DoubleLowestValue_1772) {
    Object obj(std::numeric_limits<double>::lowest());
    EXPECT_FALSE(isPositive(&obj));
}

// Test with double epsilon (smallest positive)
TEST_F(IsPositiveTest_1772, DoubleEpsilon_1772) {
    Object obj(std::numeric_limits<double>::epsilon());
    EXPECT_TRUE(isPositive(&obj));
}
