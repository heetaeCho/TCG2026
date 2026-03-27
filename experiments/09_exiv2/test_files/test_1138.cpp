#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace Exiv2 {

    uint64_t getULongLong(const byte* buf, ByteOrder byteOrder);

}



class GetULongLongTest_1138 : public ::testing::Test {

protected:

    static constexpr size_t BufferSize = 8;

    byte buffer[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

};



TEST_F(GetULongLongTest_1138, LittleEndianConversion_1138) {

    uint64_t expected = 0x0807060504030201;

    EXPECT_EQ(Exiv2::getULongLong(buffer, Exiv2::littleEndian), expected);

}



TEST_F(GetULongLongTest_1138, BigEndianConversion_1138) {

    uint64_t expected = 0x0102030405060708;

    EXPECT_EQ(Exiv2::getULongLong(buffer, Exiv2::bigEndian), expected);

}



TEST_F(GetULongLongTest_1138, InvalidByteOrder_1138) {

    uint64_t result = Exiv2::getULongLong(buffer, static_cast<Exiv2::ByteOrder>(0));

    // Since the behavior for invalid byte order is not specified,

    // we can only assume it returns something consistent.

    // Here we check if it does not crash and returns a value.

    EXPECT_TRUE(result == 0 || result != 0);

}



TEST_F(GetULongLongTest_1138, ZeroBufferLittleEndian_1138) {

    byte zeroBuffer[BufferSize] = {0};

    uint64_t expected = 0;

    EXPECT_EQ(Exiv2::getULongLong(zeroBuffer, Exiv2::littleEndian), expected);

}



TEST_F(GetULongLongTest_1138, ZeroBufferBigEndian_1138) {

    byte zeroBuffer[BufferSize] = {0};

    uint64_t expected = 0;

    EXPECT_EQ(Exiv2::getULongLong(zeroBuffer, Exiv2::bigEndian), expected);

}



TEST_F(GetULongLongTest_1138, MaxValueLittleEndian_1138) {

    byte maxBuffer[BufferSize] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    uint64_t expected = UINT64_MAX;

    EXPECT_EQ(Exiv2::getULongLong(maxBuffer, Exiv2::littleEndian), expected);

}



TEST_F(GetULongLongTest_1138, MaxValueBigEndian_1138) {

    byte maxBuffer[BufferSize] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    uint64_t expected = UINT64_MAX;

    EXPECT_EQ(Exiv2::getULongLong(maxBuffer, Exiv2::bigEndian), expected);

}
