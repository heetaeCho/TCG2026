#include <gtest/gtest.h>

#include "exiv2/value.hpp"



namespace {



class ToDataTest_140 : public ::testing::Test {

protected:

    uint8_t buffer[4];

};



TEST_F(ToDataTest_140, NormalOperation_BE_140) {

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = littleEndian; // Testing big endian conversion

    size_t bytesWritten = Exiv2::toData(buffer, value, bigEndian);

    EXPECT_EQ(bytesWritten, 4);

    EXPECT_EQ(buffer[0], 0x12);

    EXPECT_EQ(buffer[1], 0x34);

    EXPECT_EQ(buffer[2], 0x56);

    EXPECT_EQ(buffer[3], 0x78);

}



TEST_F(ToDataTest_140, NormalOperation_LE_140) {

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = littleEndian; // Testing little endian conversion

    size_t bytesWritten = Exiv2::toData(buffer, value, littleEndian);

    EXPECT_EQ(bytesWritten, 4);

    EXPECT_EQ(buffer[0], 0x78);

    EXPECT_EQ(buffer[1], 0x56);

    EXPECT_EQ(buffer[2], 0x34);

    EXPECT_EQ(buffer[3], 0x12);

}



TEST_F(ToDataTest_140, ZeroValue_140) {

    uint32_t value = 0;

    ByteOrder byteOrder = bigEndian; // Testing zero value conversion

    size_t bytesWritten = Exiv2::toData(buffer, value, bigEndian);

    EXPECT_EQ(bytesWritten, 4);

    for (size_t i = 0; i < 4; ++i) {

        EXPECT_EQ(buffer[i], 0);

    }

}



TEST_F(ToDataTest_140, MaxValue_BE_140) {

    uint32_t value = UINT32_MAX;

    ByteOrder byteOrder = bigEndian; // Testing max value conversion in big endian

    size_t bytesWritten = Exiv2::toData(buffer, value, bigEndian);

    EXPECT_EQ(bytesWritten, 4);

    EXPECT_EQ(buffer[0], 0xFF);

    EXPECT_EQ(buffer[1], 0xFF);

    EXPECT_EQ(buffer[2], 0xFF);

    EXPECT_EQ(buffer[3], 0xFF);

}



TEST_F(ToDataTest_140, MaxValue_LE_140) {

    uint32_t value = UINT32_MAX;

    ByteOrder byteOrder = littleEndian; // Testing max value conversion in little endian

    size_t bytesWritten = Exiv2::toData(buffer, value, littleEndian);

    EXPECT_EQ(bytesWritten, 4);

    EXPECT_EQ(buffer[0], 0xFF);

    EXPECT_EQ(buffer[1], 0xFF);

    EXPECT_EQ(buffer[2], 0xFF);

    EXPECT_EQ(buffer[3], 0xFF);

}



} // namespace
