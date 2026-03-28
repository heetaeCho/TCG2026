#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Test;



class ToDataTest_143 : public Test {

protected:

    byte buffer[4];

};



TEST_F(ToDataTest_143, NormalOperation_LittleEndian_143) {

    int32_t value = 0x12345678;

    ByteOrder byteOrder = littleEndian;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 4u);

    EXPECT_EQ(buffer[0], 0x78);

    EXPECT_EQ(buffer[1], 0x56);

    EXPECT_EQ(buffer[2], 0x34);

    EXPECT_EQ(buffer[3], 0x12);

}



TEST_F(ToDataTest_143, NormalOperation_BigEndian_143) {

    int32_t value = 0x12345678;

    ByteOrder byteOrder = bigEndian;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 4u);

    EXPECT_EQ(buffer[0], 0x12);

    EXPECT_EQ(buffer[1], 0x34);

    EXPECT_EQ(buffer[2], 0x56);

    EXPECT_EQ(buffer[3], 0x78);

}



TEST_F(ToDataTest_143, ZeroValue_LittleEndian_143) {

    int32_t value = 0;

    ByteOrder byteOrder = littleEndian;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 4u);

    for (size_t i = 0; i < 4; ++i) {

        EXPECT_EQ(buffer[i], 0);

    }

}



TEST_F(ToDataTest_143, ZeroValue_BigEndian_143) {

    int32_t value = 0;

    ByteOrder byteOrder = bigEndian;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 4u);

    for (size_t i = 0; i < 4; ++i) {

        EXPECT_EQ(buffer[i], 0);

    }

}



TEST_F(ToDataTest_143, MaxValue_LittleEndian_143) {

    int32_t value = std::numeric_limits<int32_t>::max();

    ByteOrder byteOrder = littleEndian;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 4u);

    EXPECT_EQ(buffer[0], 0xFF);

    EXPECT_EQ(buffer[1], 0xFF);

    EXPECT_EQ(buffer[2], 0xFF);

    EXPECT_EQ(buffer[3], 0x7F);

}



TEST_F(ToDataTest_143, MaxValue_BigEndian_143) {

    int32_t value = std::numeric_limits<int32_t>::max();

    ByteOrder byteOrder = bigEndian;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 4u);

    EXPECT_EQ(buffer[0], 0x7F);

    EXPECT_EQ(buffer[1], 0xFF);

    EXPECT_EQ(buffer[2], 0xFF);

    EXPECT_EQ(buffer[3], 0xFF);

}



TEST_F(ToDataTest_143, MinValue_LittleEndian_143) {

    int32_t value = std::numeric_limits<int32_t>::min();

    ByteOrder byteOrder = littleEndian;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 4u);

    EXPECT_EQ(buffer[0], 0x00);

    EXPECT_EQ(buffer[1], 0x00);

    EXPECT_EQ(buffer[2], 0x00);

    EXPECT_EQ(buffer[3], 0x80);

}



TEST_F(ToDataTest_143, MinValue_BigEndian_143) {

    int32_t value = std::numeric_limits<int32_t>::min();

    ByteOrder byteOrder = bigEndian;

    size_t result = toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 4u);

    EXPECT_EQ(buffer[0], 0x80);

    EXPECT_EQ(buffer[1], 0x00);

    EXPECT_EQ(buffer[2], 0x00);

    EXPECT_EQ(buffer[3], 0x00);

}
