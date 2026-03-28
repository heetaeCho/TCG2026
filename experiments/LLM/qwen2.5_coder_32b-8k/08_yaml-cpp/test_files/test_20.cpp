#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"



// Test Fixture for FloatPrecision function

class FloatPrecisionTest_20 : public ::testing::Test {

protected:

    // No setup or teardown needed as this is a simple function test

};



// Test case to verify normal operation of FloatPrecision

TEST_F(FloatPrecisionTest_20, NormalOperation_20) {

    YAML::_Precision precision = YAML::FloatPrecision(5);

    EXPECT_EQ(precision.value, 5);

}



// Test case to verify boundary condition with zero

TEST_F(FloatPrecisionTest_20, BoundaryZero_20) {

    YAML::_Precision precision = YAML::FloatPrecision(0);

    EXPECT_EQ(precision.value, 0);

}



// Test case to verify boundary condition with a negative number

TEST_F(FloatPrecisionTest_20, BoundaryNegative_20) {

    YAML::_Precision precision = YAML::FloatPrecision(-3);

    EXPECT_EQ(precision.value, -3);

}



// Test case to verify boundary condition with a large positive number

TEST_F(FloatPrecisionTest_20, BoundaryLargePositive_20) {

    YAML::_Precision precision = YAML::FloatPrecision(100);

    EXPECT_EQ(precision.value, 100);

}

```


