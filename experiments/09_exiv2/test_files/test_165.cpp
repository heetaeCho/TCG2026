#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeTest_165 : public ::testing::Test {

protected:

    ValueType<double> doubleValue;

    ValueType<float> floatValue;

    ValueType<int> intValue;



    ValueTypeTest_165() 

        : doubleValue(42.0, TypeId::double),

          floatValue(3.14f, TypeId::float_t),

          intValue(7, TypeId::int32) {}

};



TEST_F(ValueTypeTest_165, toFloat_NormalOperation_Double_165) {

    EXPECT_FLOAT_EQ(doubleValue.toFloat(0), 42.0f);

}



TEST_F(ValueTypeTest_165, toFloat_NormalOperation_Float_165) {

    EXPECT_FLOAT_EQ(floatValue.toFloat(0), 3.14f);

}



TEST_F(ValueTypeTest_165, toFloat_NormalOperation_Int_165) {

    EXPECT_FLOAT_EQ(intValue.toFloat(0), 7.0f);

}



TEST_F(ValueTypeTest_165, toFloat_BoundaryCondition_EmptyVector_165) {

    ValueType<int> emptyIntValue(TypeId::int32);

    EXPECT_THROW(emptyIntValue.toFloat(0), std::out_of_range);

}



TEST_F(ValueTypeTest_165, toFloat_ExceptionalCase_OutOfRange_165) {

    EXPECT_THROW(doubleValue.toFloat(1), std::out_of_range);

}
