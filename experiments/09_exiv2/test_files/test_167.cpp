#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeURationalTest_167 : public ::testing::Test {

protected:

    ValueType<URational> urationalValue;

    

    ValueTypeURationalTest_167() {

        // Initialize the value with some default URational values for testing

        URational r1(1, 2);

        URational r2(3, 4);

        urationalValue.value_.push_back(r1);

        urationalValue.value_.push_back(r2);

    }

};



TEST_F(ValueTypeURationalTest_167, toFloat_NormalOperation_167) {

    float result = urationalValue.toFloat(0);

    EXPECT_FLOAT_EQ(result, 0.5f);



    result = urationalValue.toFloat(1);

    EXPECT_FLOAT_EQ(result, 0.75f);

}



TEST_F(ValueTypeURationalTest_167, toFloat_BoundaryCondition_167) {

    URational zeroDenominator(1, 0);

    urationalValue.value_.push_back(zeroDenominator);



    float result = urationalValue.toFloat(2);

    EXPECT_FLOAT_EQ(result, 0.0f);

}



TEST_F(ValueTypeURationalTest_167, toFloat_OutOfBounds_167) {

    float result = urationalValue.toFloat(urationalValue.count());

    EXPECT_FLOAT_EQ(result, 0.0f);

}



TEST_F(ValueTypeURationalTest_167, ok_FlagCheck_167) {

    URational zeroDenominator(1, 0);

    urationalValue.value_.push_back(zeroDenominator);



    urationalValue.toFloat(2); // This should set ok_ to false

    EXPECT_FALSE(urationalValue.ok());



    urationalValue.toFloat(0); // This should reset ok_ to true

    EXPECT_TRUE(urationalValue.ok());

}
