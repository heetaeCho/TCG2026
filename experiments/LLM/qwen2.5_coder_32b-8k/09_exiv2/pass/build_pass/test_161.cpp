#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Test fixture for ValueType<Rational> tests.

class ValueTypeRationalTest_161 : public ::testing::Test {

protected:

    ValueType<Rational> value_type;

};



TEST_F(ValueTypeRationalTest_161, ToInt64_NormalOperation_161) {

    Rational rational(5, 2);

    value_type.value_.push_back(rational);

    EXPECT_EQ(value_type.toInt64(0), 2); // 5/2 = 2.5 which is truncated to 2

}



TEST_F(ValueTypeRationalTest_161, ToInt64_BoundaryCondition_ZeroNumerator_161) {

    Rational rational(0, 3);

    value_type.value_.push_back(rational);

    EXPECT_EQ(value_type.toInt64(0), 0); // 0/3 = 0

}



TEST_F(ValueTypeRationalTest_161, ToInt64_BoundaryCondition_ZeroDenominator_161) {

    Rational rational(5, 0);

    value_type.value_.push_back(rational);

    EXPECT_THROW(value_type.toInt64(0), std::overflow_error); // Division by zero should throw

}



TEST_F(ValueTypeRationalTest_161, ToInt64_ExceptionalCase_LargeNumerator_161) {

    Rational rational(LARGE_INT, 1);

    value_type.value_.push_back(rational);

    EXPECT_EQ(value_type.toInt64(0), LARGE_INT); // Large numerator should not cause overflow

}



TEST_F(ValueTypeRationalTest_161, ToInt64_ExceptionalCase_LargeDenominator_161) {

    Rational rational(LARGE_INT, 2);

    value_type.value_.push_back(rational);

    EXPECT_EQ(value_type.toInt64(0), LARGE_INT / 2); // Large denominator should not cause overflow

}



TEST_F(ValueTypeRationalTest_161, ToInt64_OutOfRangeIndex_161) {

    Rational rational(5, 2);

    value_type.value_.push_back(rational);

    EXPECT_THROW(value_type.toInt64(1), std::out_of_range); // Accessing out-of-range index should throw

}
