#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ToDataTest_146 : public ::testing::Test {

protected:

    byte buffer[8]; // Assuming double is 8 bytes

};



TEST_F(ToDataTest_146, NormalOperation_PositiveDouble_146) {

    ByteOrder byteOrder = littleEndian;

    double value = 123.456;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(double));

}



TEST_F(ToDataTest_146, NormalOperation_NegativeDouble_146) {

    ByteOrder byteOrder = bigEndian;

    double value = -987.654;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(double));

}



TEST_F(ToDataTest_146, BoundaryCondition_ZeroValue_146) {

    ByteOrder byteOrder = littleEndian;

    double value = 0.0;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(double));

}



TEST_F(ToDataTest_146, BoundaryCondition_MaxDouble_146) {

    ByteOrder byteOrder = bigEndian;

    double value = std::numeric_limits<double>::max();

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(double));

}



TEST_F(ToDataTest_146, BoundaryCondition_MinDouble_146) {

    ByteOrder byteOrder = littleEndian;

    double value = std::numeric_limits<double>::min();

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(double));

}



TEST_F(ToDataTest_146, BoundaryCondition_DenormalMinDouble_146) {

    ByteOrder byteOrder = bigEndian;

    double value = std::numeric_limits<double>::denorm_min();

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(double));

}



TEST_F(ToDataTest_146, BoundaryCondition_Infinity_146) {

    ByteOrder byteOrder = littleEndian;

    double value = std::numeric_limits<double>::infinity();

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(double));

}



TEST_F(ToDataTest_146, BoundaryCondition_NegativeInfinity_146) {

    ByteOrder byteOrder = bigEndian;

    double value = -std::numeric_limits<double>::infinity();

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(double));

}



TEST_F(ToDataTest_146, Exceptional_NaNValue_146) {

    ByteOrder byteOrder = littleEndian;

    double value = std::numeric_limits<double>::quiet_NaN();

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(double));

}
