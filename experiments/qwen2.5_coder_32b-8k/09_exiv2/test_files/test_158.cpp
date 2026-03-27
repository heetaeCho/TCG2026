#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeDoubleTest_158 : public ::testing::Test {

protected:

    ValueType<double> value_type_double_;



    void SetUp() override {

        // Initialize with a sample double value

        value_type_double_ = ValueType<double>(3.14159, TypeId::doubleId);

    }

};



TEST_F(ValueTypeDoubleTest_158, ToUint32_NormalOperation_158) {

    uint32_t result = value_type_double_.toUint32(0);

    EXPECT_EQ(result, 3u); // Expect the integer part of 3.14159

}



TEST_F(ValueTypeDoubleTest_158, ToUint32_BoundaryCondition_Zero_158) {

    ValueType<double> zero_value(0.0, TypeId::doubleId);

    uint32_t result = zero_value.toUint32(0);

    EXPECT_EQ(result, 0u);

}



TEST_F(ValueTypeDoubleTest_158, ToUint32_BoundaryCondition_MaxInt_158) {

    ValueType<double> max_int_value(static_cast<double>(std::numeric_limits<uint32_t>::max()), TypeId::doubleId);

    uint32_t result = max_int_value.toUint32(0);

    EXPECT_EQ(result, std::numeric_limits<uint32_t>::max());

}



TEST_F(ValueTypeDoubleTest_158, ToUint32_BoundaryCondition_LargeValue_158) {

    ValueType<double> large_value(static_cast<double>(LARGE_INT), TypeId::doubleId);

    uint32_t result = large_value.toUint32(0);

    EXPECT_EQ(result, static_cast<uint32_t>(LARGE_INT));

}



TEST_F(ValueTypeDoubleTest_158, ToUint32_Exceptional_NegativeValue_158) {

    ValueType<double> negative_value(-3.14159, TypeId::doubleId);

    uint32_t result = negative_value.toUint32(0);

    EXPECT_EQ(result, 0u); // Expect 0 for negative values

}



TEST_F(ValueTypeDoubleTest_158, ToUint32_Exceptional_OutOfRangeIndex_158) {

    EXPECT_THROW(value_type_double_.toUint32(1), std::out_of_range);

}
