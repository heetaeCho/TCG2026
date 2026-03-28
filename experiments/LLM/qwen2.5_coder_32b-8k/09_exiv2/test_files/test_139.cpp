#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



namespace {



TEST(ToDataTest_139, NormalOperationWithLittleEndian_139) {

    uint8_t buffer[2];

    ByteOrder byteOrder = littleEndian;

    uint16_t value = 0x1234;

    size_t bytesWritten = Exiv2::toData(buffer, value, byteOrder);

    EXPECT_EQ(bytesWritten, 2u);

    EXPECT_EQ(buffer[0], 0x34);

    EXPECT_EQ(buffer[1], 0x12);

}



TEST(ToDataTest_139, NormalOperationWithBigEndian_139) {

    uint8_t buffer[2];

    ByteOrder byteOrder = bigEndian;

    uint16_t value = 0x1234;

    size_t bytesWritten = Exiv2::toData(buffer, value, byteOrder);

    EXPECT_EQ(bytesWritten, 2u);

    EXPECT_EQ(buffer[0], 0x12);

    EXPECT_EQ(buffer[1], 0x34);

}



TEST(ToDataTest_139, BoundaryConditionZeroValue_139) {

    uint8_t buffer[2];

    ByteOrder byteOrder = littleEndian;

    uint16_t value = 0x0000;

    size_t bytesWritten = Exiv2::toData(buffer, value, byteOrder);

    EXPECT_EQ(bytesWritten, 2u);

    EXPECT_EQ(buffer[0], 0x00);

    EXPECT_EQ(buffer[1], 0x00);

}



TEST(ToDataTest_139, BoundaryConditionMaxValue_139) {

    uint8_t buffer[2];

    ByteOrder byteOrder = bigEndian;

    uint16_t value = 0xFFFF;

    size_t bytesWritten = Exiv2::toData(buffer, value, byteOrder);

    EXPECT_EQ(bytesWritten, 2u);

    EXPECT_EQ(buffer[0], 0xFF);

    EXPECT_EQ(buffer[1], 0xFF);

}



}  // namespace
