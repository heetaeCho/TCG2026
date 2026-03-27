#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/types.cpp"



namespace Exiv2 {



class GetFloatTest_1143 : public ::testing::Test {

protected:

    byte buffer[4];

};



TEST_F(GetFloatTest_1143, NormalOperation_LittleEndian_1143) {

    // Arrange

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    buffer[2] = 0x80;

    buffer[3] = 0x3F; // Represents the float value 1.0 in little-endian



    // Act

    float result = getFloat(buffer, littleEndian);



    // Assert

    EXPECT_FLOAT_EQ(result, 1.0f);

}



TEST_F(GetFloatTest_1143, NormalOperation_BigEndian_1143) {

    // Arrange

    buffer[0] = 0x3F;

    buffer[1] = 0x80;

    buffer[2] = 0x00;

    buffer[3] = 0x00; // Represents the float value 1.0 in big-endian



    // Act

    float result = getFloat(buffer, bigEndian);



    // Assert

    EXPECT_FLOAT_EQ(result, 1.0f);

}



TEST_F(GetFloatTest_1143, BoundaryCondition_ZeroValue_LittleEndian_1143) {

    // Arrange

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    buffer[2] = 0x00;

    buffer[3] = 0x00; // Represents the float value 0.0 in little-endian



    // Act

    float result = getFloat(buffer, littleEndian);



    // Assert

    EXPECT_FLOAT_EQ(result, 0.0f);

}



TEST_F(GetFloatTest_1143, BoundaryCondition_ZeroValue_BigEndian_1143) {

    // Arrange

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    buffer[2] = 0x00;

    buffer[3] = 0x00; // Represents the float value 0.0 in big-endian



    // Act

    float result = getFloat(buffer, bigEndian);



    // Assert

    EXPECT_FLOAT_EQ(result, 0.0f);

}



TEST_F(GetFloatTest_1143, BoundaryCondition_MaxValue_LittleEndian_1143) {

    // Arrange

    buffer[0] = 0xFF;

    buffer[1] = 0x7F;

    buffer[2] = 0xFF;

    buffer[3] = 0x7F; // Represents the float value 3.402823e+38 in little-endian



    // Act

    float result = getFloat(buffer, littleEndian);



    // Assert

    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::max());

}



TEST_F(GetFloatTest_1143, BoundaryCondition_MaxValue_BigEndian_1143) {

    // Arrange

    buffer[0] = 0x7F;

    buffer[1] = 0xFF;

    buffer[2] = 0x7F;

    buffer[3] = 0xFF; // Represents the float value 3.402823e+38 in big-endian



    // Act

    float result = getFloat(buffer, bigEndian);



    // Assert

    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::max());

}



TEST_F(GetFloatTest_1143, BoundaryCondition_MinValue_LittleEndian_1143) {

    // Arrange

    buffer[0] = 0x01;

    buffer[1] = 0x80;

    buffer[2] = 0x00;

    buffer[3] = 0x00; // Represents the float value -1.175494e-38 in little-endian



    // Act

    float result = getFloat(buffer, littleEndian);



    // Assert

    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::min());

}



TEST_F(GetFloatTest_1143, BoundaryCondition_MinValue_BigEndian_1143) {

    // Arrange

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    buffer[2] = 0x80;

    buffer[3] = 0x01; // Represents the float value -1.175494e-38 in big-endian



    // Act

    float result = getFloat(buffer, bigEndian);



    // Assert

    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::min());

}



TEST_F(GetFloatTest_1143, ExceptionalCase_NaN_LittleEndian_1143) {

    // Arrange

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    buffer[2] = 0xF8;

    buffer[3] = 0x7F; // Represents a NaN value in little-endian



    // Act

    float result = getFloat(buffer, littleEndian);



    // Assert

    EXPECT_TRUE(std::isnan(result));

}



TEST_F(GetFloatTest_1143, ExceptionalCase_NaN_BigEndian_1143) {

    // Arrange

    buffer[0] = 0x7F;

    buffer[1] = 0xF8;

    buffer[2] = 0x00;

    buffer[3] = 0x00; // Represents a NaN value in big-endian



    // Act

    float result = getFloat(buffer, bigEndian);



    // Assert

    EXPECT_TRUE(std::isnan(result));

}



TEST_F(GetFloatTest_1143, ExceptionalCase_PositiveInfinity_LittleEndian_1143) {

    // Arrange

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    buffer[2] = 0x80;

    buffer[3] = 0x7F; // Represents positive infinity in little-endian



    // Act

    float result = getFloat(buffer, littleEndian);



    // Assert

    EXPECT_TRUE(std::isinf(result) && result > 0);

}



TEST_F(GetFloatTest_1143, ExceptionalCase_PositiveInfinity_BigEndian_1143) {

    // Arrange

    buffer[0] = 0x7F;

    buffer[1] = 0x80;

    buffer[2] = 0x00;

    buffer[3] = 0x00; // Represents positive infinity in big-endian



    // Act

    float result = getFloat(buffer, bigEndian);



    // Assert

    EXPECT_TRUE(std::isinf(result) && result > 0);

}



TEST_F(GetFloatTest_1143, ExceptionalCase_NegativeInfinity_LittleEndian_1143) {

    // Arrange

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    buffer[2] = 0x80;

    buffer[3] = 0xFF; // Represents negative infinity in little-endian



    // Act

    float result = getFloat(buffer, littleEndian);



    // Assert

    EXPECT_TRUE(std::isinf(result) && result < 0);

}



TEST_F(GetFloatTest_1143, ExceptionalCase_NegativeInfinity_BigEndian_1143) {

    // Arrange

    buffer[0] = 0xFF;

    buffer[1] = 0x80;

    buffer[2] = 0x00;

    buffer[3] = 0x00; // Represents negative infinity in big-endian



    // Act

    float result = getFloat(buffer, bigEndian);



    // Assert

    EXPECT_TRUE(std::isinf(result) && result < 0);

}



}  // namespace Exiv2
