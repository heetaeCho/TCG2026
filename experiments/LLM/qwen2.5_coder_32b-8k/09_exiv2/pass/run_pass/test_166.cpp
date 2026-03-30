#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeRationalTest_166 : public ::testing::Test {

protected:

    ValueType<Rational> valueRational;

};



TEST_F(ValueTypeRationalTest_166, ToFloat_NormalOperation_166) {

    Rational rational(3, 4);

    valueRational.value_.push_back(rational);

    EXPECT_FLOAT_EQ(valueRational.toFloat(0), 0.75f);

}



TEST_F(ValueTypeRationalTest_166, ToFloat_BoundaryCondition_ZeroDenominator_166) {

    Rational rational(3, 0);

    valueRational.value_.push_back(rational);

    EXPECT_FLOAT_EQ(valueRational.toFloat(0), 0.0f);

}



TEST_F(ValueTypeRationalTest_166, ToFloat_ExceptionalCase_EmptyVector_166) {

    EXPECT_FLOAT_EQ(valueRational.toFloat(0), 0.0f);

}



TEST_F(ValueTypeRationalTest_166, ToFloat_BoundaryCondition_LargeNumbers_166) {

    Rational rational(LARGE_INT, 1);

    valueRational.value_.push_back(rational);

    EXPECT_FLOAT_EQ(valueRational.toFloat(0), static_cast<float>(LARGE_INT));

}



TEST_F(ValueTypeRationalTest_166, ToFloat_BoundaryCondition_SmallNumbers_166) {

    Rational rational(1, LARGE_INT);

    valueRational.value_.push_back(rational);

    EXPECT_FLOAT_EQ(valueRational.toFloat(0), 1.0f / static_cast<float>(LARGE_INT));

}
