#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



// Test fixture for getShort function tests

class GetShortTest_1140 : public ::testing::Test {

protected:

    byte buffer[2];

};



TEST_F(GetShortTest_1140, NormalOperation_LittleEndian_1140) {

    buffer[0] = 0x34;

    buffer[1] = 0x12;

    EXPECT_EQ(getShort(buffer, littleEndian), static_cast<int16_t>(0x1234));

}



TEST_F(GetShortTest_1140, NormalOperation_BigEndian_1140) {

    buffer[0] = 0x12;

    buffer[1] = 0x34;

    EXPECT_EQ(getShort(buffer, bigEndian), static_cast<int16_t>(0x1234));

}



TEST_F(GetShortTest_1140, BoundaryCondition_ZeroValue_LittleEndian_1140) {

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    EXPECT_EQ(getShort(buffer, littleEndian), static_cast<int16_t>(0x0000));

}



TEST_F(GetShortTest_1140, BoundaryCondition_ZeroValue_BigEndian_1140) {

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    EXPECT_EQ(getShort(buffer, bigEndian), static_cast<int16_t>(0x0000));

}



TEST_F(GetShortTest_1140, BoundaryCondition_MaxValue_LittleEndian_1140) {

    buffer[0] = 0xFF;

    buffer[1] = 0x7F;

    EXPECT_EQ(getShort(buffer, littleEndian), static_cast<int16_t>(0x7FFF));

}



TEST_F(GetShortTest_1140, BoundaryCondition_MaxValue_BigEndian_1140) {

    buffer[0] = 0x7F;

    buffer[1] = 0xFF;

    EXPECT_EQ(getShort(buffer, bigEndian), static_cast<int16_t>(0x7FFF));

}



TEST_F(GetShortTest_1140, BoundaryCondition_MinValue_LittleEndian_1140) {

    buffer[0] = 0x00;

    buffer[1] = 0x80;

    EXPECT_EQ(getShort(buffer, littleEndian), static_cast<int16_t>(-32768));

}



TEST_F(GetShortTest_1140, BoundaryCondition_MinValue_BigEndian_1140) {

    buffer[0] = 0x80;

    buffer[1] = 0x00;

    EXPECT_EQ(getShort(buffer, bigEndian), static_cast<int16_t>(-32768));

}



TEST_F(GetShortTest_1140, ErrorCase_InvalidByteOrder_1140) {

    buffer[0] = 0x12;

    buffer[1] = 0x34;

    EXPECT_EQ(getShort(buffer, invalidByteOrder), static_cast<int16_t>(0x3412)); // Assuming it defaults to bigEndian

}
