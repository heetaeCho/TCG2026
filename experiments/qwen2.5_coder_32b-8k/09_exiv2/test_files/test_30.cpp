#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace {



using namespace Exiv2;



class GetUShortTest_30 : public ::testing::Test {

protected:

    Slice<uint8_t> buffer;

};



TEST_F(GetUShortTest_30, LittleEndianOrder_30) {

    buffer = {0x12, 0x34};

    EXPECT_EQ(getUShort(buffer, littleEndian), 0x3412);

}



TEST_F(GetUShortTest_30, BigEndianOrder_30) {

    buffer = {0x12, 0x34};

    EXPECT_EQ(getUShort(buffer, bigEndian), 0x1234);

}



TEST_F(GetUShortTest_30, ZeroValue_30) {

    buffer = {0x00, 0x00};

    EXPECT_EQ(getUShort(buffer, littleEndian), 0x0000);

    EXPECT_EQ(getUShort(buffer, bigEndian), 0x0000);

}



TEST_F(GetUShortTest_30, MaxValue_30) {

    buffer = {0xFF, 0xFF};

    EXPECT_EQ(getUShort(buffer, littleEndian), 0xFFFF);

    EXPECT_EQ(getUShort(buffer, bigEndian), 0xFFFF);

}



TEST_F(GetUShortTest_30, SingleByteNonZero_30) {

    buffer = {0x01, 0x00};

    EXPECT_EQ(getUShort(buffer, littleEndian), 0x0001);

    EXPECT_EQ(getUShort(buffer, bigEndian), 0x0100);



    buffer = {0x00, 0x01};

    EXPECT_EQ(getUShort(buffer, littleEndian), 0x0100);

    EXPECT_EQ(getUShort(buffer, bigEndian), 0x0001);

}



TEST_F(GetUShortTest_30, InvalidByteOrder_30) {

    buffer = {0x12, 0x34};

    EXPECT_THROW(getUShort(buffer, invalidByteOrder), std::exception); // Assuming this throws an exception for invalid byte order

}



}  // namespace
