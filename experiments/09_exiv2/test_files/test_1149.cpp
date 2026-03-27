#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



TEST(s2DataTest_1149, NormalOperation_LittleEndian_1149) {

    byte buf[2];

    size_t result = s2Data(buf, 0x1234, littleEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], 0x34);

    EXPECT_EQ(buf[1], 0x12);

}



TEST(s2DataTest_1149, NormalOperation_BigEndian_1149) {

    byte buf[2];

    size_t result = s2Data(buf, 0x1234, bigEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], 0x12);

    EXPECT_EQ(buf[1], 0x34);

}



TEST(s2DataTest_1149, BoundaryCondition_Zero_LittleEndian_1149) {

    byte buf[2];

    size_t result = s2Data(buf, 0, littleEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], 0x00);

    EXPECT_EQ(buf[1], 0x00);

}



TEST(s2DataTest_1149, BoundaryCondition_Zero_BigEndian_1149) {

    byte buf[2];

    size_t result = s2Data(buf, 0, bigEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], 0x00);

    EXPECT_EQ(buf[1], 0x00);

}



TEST(s2DataTest_1149, BoundaryCondition_MaxValue_LittleEndian_1149) {

    byte buf[2];

    size_t result = s2Data(buf, 0xFFFF, littleEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], 0xFF);

    EXPECT_EQ(buf[1], 0xFF);

}



TEST(s2DataTest_1149, BoundaryCondition_MaxValue_BigEndian_1149) {

    byte buf[2];

    size_t result = s2Data(buf, 0xFFFF, bigEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], 0xFF);

    EXPECT_EQ(buf[1], 0xFF);

}



TEST(s2DataTest_1149, BoundaryCondition_NegativeValue_LittleEndian_1149) {

    byte buf[2];

    size_t result = s2Data(buf, -1, littleEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], 0xFF);

    EXPECT_EQ(buf[1], 0xFF);

}



TEST(s2DataTest_1149, BoundaryCondition_NegativeValue_BigEndian_1149) {

    byte buf[2];

    size_t result = s2Data(buf, -1, bigEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], 0xFF);

    EXPECT_EQ(buf[1], 0xFF);

}



TEST(s2DataTest_1149, InvalidByteOrder_1149) {

    byte buf[2];

    size_t result = s2Data(buf, 0x1234, invalidByteOrder);

    // Assuming the function handles invalid byte order by defaulting to one of the valid orders

    EXPECT_EQ(result, 2);

}
