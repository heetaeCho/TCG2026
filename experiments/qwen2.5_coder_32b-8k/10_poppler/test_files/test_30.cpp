#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "goo/gstrtod.h"



// Test fixture for gatof function

class GatofTest_30 : public ::testing::Test {

protected:

    // No additional setup or teardown needed for this simple function

};



// Test normal operation with a valid number

TEST_F(GatofTest_30, ValidNumberConversion_30) {

    EXPECT_EQ(gatof("123.45"), 123.45);

}



// Test boundary condition with zero

TEST_F(GatofTest_30, ZeroConversion_30) {

    EXPECT_EQ(gatof("0"), 0.0);

}



// Test negative number conversion

TEST_F(GatofTest_30, NegativeNumberConversion_30) {

    EXPECT_EQ(gatof("-123.45"), -123.45);

}



// Test large positive number conversion

TEST_F(GatofTest_30, LargePositiveNumberConversion_30) {

    EXPECT_EQ(gatof("9876543210.123456"), 9876543210.123456);

}



// Test large negative number conversion

TEST_F(GatofTest_30, LargeNegativeNumberConversion_30) {

    EXPECT_EQ(gatof("-9876543210.123456"), -9876543210.123456);

}



// Test scientific notation conversion

TEST_F(GatofTest_30, ScientificNotationConversion_30) {

    EXPECT_EQ(gatof("1.23e10"), 12300000000.0);

}



// Test scientific notation with negative exponent

TEST_F(GatofTest_30, ScientificNotationNegativeExponentConversion_30) {

    EXPECT_EQ(gatof("1.23e-10"), 0.000000000123);

}



// Test invalid input (non-numeric string)

TEST_F(GatofTest_30, InvalidInputConversion_30) {

    EXPECT_EQ(gatof("abc"), 0.0);

}



// Test empty string input

TEST_F(GatofTest_30, EmptyStringConversion_30) {

    EXPECT_EQ(gatof(""), 0.0);

}
