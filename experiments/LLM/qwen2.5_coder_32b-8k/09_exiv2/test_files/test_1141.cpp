#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



// Test Fixture for getLong function

class GetLongTest_1141 : public ::testing::Test {

protected:

    byte buffer[4];

};



TEST_F(GetLongTest_1141, PutIncreasesCount_LittleEndian_1141) {

    buffer[0] = 0x12;

    buffer[1] = 0x34;

    buffer[2] = 0x56;

    buffer[3] = 0x78;

    EXPECT_EQ(getLong(buffer, littleEndian), 0x78563412);

}



TEST_F(GetLongTest_1141, PutIncreasesCount_BigEndian_1141) {

    buffer[0] = 0x12;

    buffer[1] = 0x34;

    buffer[2] = 0x56;

    buffer[3] = 0x78;

    EXPECT_EQ(getLong(buffer, bigEndian), 0x12345678);

}



TEST_F(GetLongTest_1141, BoundaryCondition_AllZeros_LittleEndian_1141) {

    for (int i = 0; i < 4; ++i) buffer[i] = 0;

    EXPECT_EQ(getLong(buffer, littleEndian), 0);

}



TEST_F(GetLongTest_1141, BoundaryCondition_AllZeros_BigEndian_1141) {

    for (int i = 0; i < 4; ++i) buffer[i] = 0;

    EXPECT_EQ(getLong(buffer, bigEndian), 0);

}



TEST_F(GetLongTest_1141, BoundaryCondition_MaxValue_LittleEndian_1141) {

    for (int i = 0; i < 4; ++i) buffer[i] = 0xFF;

    EXPECT_EQ(getLong(buffer, littleEndian), -1); // Interpreted as signed int32_t

}



TEST_F(GetLongTest_1141, BoundaryCondition_MaxValue_BigEndian_1141) {

    for (int i = 0; i < 4; ++i) buffer[i] = 0xFF;

    EXPECT_EQ(getLong(buffer, bigEndian), -1); // Interpreted as signed int32_t

}



TEST_F(GetLongTest_1141, InvalidByteOrder_1141) {

    for (int i = 0; i < 4; ++i) buffer[i] = 0x0;

    EXPECT_THROW(getLong(buffer, invalidByteOrder), std::exception);

}
