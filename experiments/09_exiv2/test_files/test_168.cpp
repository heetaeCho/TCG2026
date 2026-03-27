#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeTest_168 : public ::testing::Test {

protected:

    ValueType<int> valueInt;

    ValueType<float> valueFloat;

    ValueType<Rational> valueRational;



    ValueTypeTest_168()

        : valueInt(TypeId::int1),

          valueFloat(TypeId::float1),

          valueRational(TypeId::rational1) {}

};



TEST_F(ValueTypeTest_168, toRational_NormalOperation_168) {

    Rational expected(42, 1);

    valueInt.value_.push_back(42);

    EXPECT_EQ(expected, valueInt.toRational(0));

}



TEST_F(ValueTypeTest_168, toRational_BoundaryCondition_EmptyList_168) {

    EXPECT_THROW(valueInt.toRational(0), std::out_of_range);

}



TEST_F(ValueTypeTest_168, toRational_BoundaryCondition_OutOfRange_168) {

    valueInt.value_.push_back(42);

    EXPECT_THROW(valueInt.toRational(1), std::out_of_range);

}



TEST_F(ValueTypeTest_168, toRational_FloatConversion_168) {

    Rational expected(3, 1);

    valueFloat.value_.push_back(3.0f);

    EXPECT_EQ(expected, valueFloat.toRational(0));

}



TEST_F(ValueTypeTest_168, toRational_RationalDirect_168) {

    Rational expected(5, 2);

    valueRational.value_.push_back(Rational(5, 2));

    EXPECT_EQ(expected, valueRational.toRational(0));

}
