#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeTest_159 : public ::testing::Test {

protected:

    ValueType<float> float_value_type_;

};



TEST_F(ValueTypeTest_159, ToInt64_NormalOperation_159) {

    // Arrange

    float test_float = 123.456f;

    ValueType<float> vt(&test_float, sizeof(float), littleEndian, tFloat);



    // Act & Assert

    EXPECT_EQ(vt.toInt64(0), static_cast<int64_t>(test_float));

}



TEST_F(ValueTypeTest_159, ToInt64_BoundaryCondition_Zero_159) {

    // Arrange

    float test_float = 0.0f;

    ValueType<float> vt(&test_float, sizeof(float), littleEndian, tFloat);



    // Act & Assert

    EXPECT_EQ(vt.toInt64(0), static_cast<int64_t>(test_float));

}



TEST_F(ValueTypeTest_159, ToInt64_BoundaryCondition_Max_159) {

    // Arrange

    float test_float = std::numeric_limits<float>::max();

    ValueType<float> vt(&test_float, sizeof(float), littleEndian, tFloat);



    // Act & Assert

    EXPECT_EQ(vt.toInt64(0), static_cast<int64_t>(test_float));

}



TEST_F(ValueTypeTest_159, ToInt64_BoundaryCondition_Min_159) {

    // Arrange

    float test_float = std::numeric_limits<float>::lowest();

    ValueType<float> vt(&test_float, sizeof(float), littleEndian, tFloat);



    // Act & Assert

    EXPECT_EQ(vt.toInt64(0), static_cast<int64_t>(test_float));

}



TEST_F(ValueTypeTest_159, ToInt64_ExceptionalCase_OutOfRange_159) {

    // Arrange

    float test_float = std::numeric_limits<float>::max();

    ValueType<float> vt(&test_float, sizeof(float), littleEndian, tFloat);



    // Act & Assert

    EXPECT_THROW(vt.toInt64(1), std::out_of_range);

}
