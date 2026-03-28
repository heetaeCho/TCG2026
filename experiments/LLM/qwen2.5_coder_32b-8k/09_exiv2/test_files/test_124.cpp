#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class ValueTest_124 : public ::testing::Test {

protected:

    void SetUp() override {

        value = Value::create(TypeId::asciiString);

    }



    UniquePtr value;

};



TEST_F(ValueTest_124, TypeId_ReturnsCorrectType_124) {

    EXPECT_EQ(value->typeId(), TypeId::asciiString);

}



TEST_F(ValueTest_124, Ok_ReturnsTrueByDefault_124) {

    EXPECT_TRUE(value->ok());

}



TEST_F(ValueTest_124, Read_Buffer_ReturnsZeroForValidInput_124) {

    byte buf[] = { 'H', 'e', 'l', 'l', 'o' };

    size_t len = sizeof(buf);

    ByteOrder byteOrder = littleEndian;

    EXPECT_EQ(value->read(buf, len, byteOrder), 0);

}



TEST_F(ValueTest_124, Read_String_ReturnsZeroForValidInput_124) {

    std::string buf = "Hello";

    EXPECT_EQ(value->read(buf), 0);

}



TEST_F(ValueTest_124, SetDataArea_ValidBuffer_ReturnsZero_124) {

    byte buf[] = { 'H', 'e', 'l', 'l', 'o' };

    size_t len = sizeof(buf);

    EXPECT_EQ(value->setDataArea(buf, len), 0);

}



TEST_F(ValueTest_124, Copy_ValidBuffer_ReturnsSize_124) {

    byte dest[6];

    ByteOrder byteOrder = littleEndian;

    value->read(reinterpret_cast<const byte*>("Hello"), 5, byteOrder);

    EXPECT_EQ(value->copy(dest, byteOrder), 5);

}



TEST_F(ValueTest_124, Count_ReturnsZeroByDefault_124) {

    EXPECT_EQ(value->count(), 0);

}



TEST_F(ValueTest_124, Size_ReturnsZeroByDefault_124) {

    EXPECT_EQ(value->size(), 0);

}



TEST_F(ValueTest_124, ToString_Default_ReturnsEmptyString_124) {

    EXPECT_EQ(value->toString(), "");

}



TEST_F(ValueTest_124, ToString_Index_OutOfBounds_ReturnsEmptyString_124) {

    EXPECT_EQ(value->toString(10), "");

}



TEST_F(ValueTest_124, ToInt64_Default_ReturnsZero_124) {

    EXPECT_EQ(value->toInt64(0), 0);

}



TEST_F(ValueTest_124, ToUint32_Default_ReturnsZero_124) {

    EXPECT_EQ(value->toUint32(0), 0);

}



TEST_F(ValueTest_124, ToFloat_Default_ReturnsZero_124) {

    EXPECT_FLOAT_EQ(value->toFloat(0), 0.0f);

}



TEST_F(ValueTest_124, ToRational_Default_ReturnsZeroOverOne_124) {

    Rational r = value->toRational(0);

    EXPECT_EQ(r.first, 0);

    EXPECT_EQ(r.second, 1);

}



TEST_F(ValueTest_124, SizeDataArea_Default_ReturnsZero_124) {

    EXPECT_EQ(value->sizeDataArea(), 0);

}



TEST_F(ValueTest_124, DataArea_Default_ReturnsEmptyBuffer_124) {

    DataBuf data = value->dataArea();

    EXPECT_EQ(data.pData_, nullptr);

    EXPECT_EQ(data.size_, 0);

}
