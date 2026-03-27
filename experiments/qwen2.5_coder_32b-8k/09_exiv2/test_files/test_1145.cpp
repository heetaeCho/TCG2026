#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace {



using namespace Exiv2;



TEST_F(Us2DataTest_1145, NormalOperationLittleEndian_1145) {

    byte buf[2];

    uint16_t value = 0xABCD;

    size_t result = us2Data(buf, value, littleEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], static_cast<byte>(0xCD));

    EXPECT_EQ(buf[1], static_cast<byte>(0xAB));

}



TEST_F(Us2DataTest_1145, NormalOperationBigEndian_1145) {

    byte buf[2];

    uint16_t value = 0xABCD;

    size_t result = us2Data(buf, value, bigEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], static_cast<byte>(0xAB));

    EXPECT_EQ(buf[1], static_cast<byte>(0xCD));

}



TEST_F(Us2DataTest_1145, BoundaryConditionZeroLittleEndian_1145) {

    byte buf[2];

    uint16_t value = 0x0000;

    size_t result = us2Data(buf, value, littleEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], static_cast<byte>(0x00));

    EXPECT_EQ(buf[1], static_cast<byte>(0x00));

}



TEST_F(Us2DataTest_1145, BoundaryConditionZeroBigEndian_1145) {

    byte buf[2];

    uint16_t value = 0x0000;

    size_t result = us2Data(buf, value, bigEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], static_cast<byte>(0x00));

    EXPECT_EQ(buf[1], static_cast<byte>(0x00));

}



TEST_F(Us2DataTest_1145, BoundaryConditionMaxValueLittleEndian_1145) {

    byte buf[2];

    uint16_t value = 0xFFFF;

    size_t result = us2Data(buf, value, littleEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], static_cast<byte>(0xFF));

    EXPECT_EQ(buf[1], static_cast<byte>(0xFF));

}



TEST_F(Us2DataTest_1145, BoundaryConditionMaxValueBigEndian_1145) {

    byte buf[2];

    uint16_t value = 0xFFFF;

    size_t result = us2Data(buf, value, bigEndian);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], static_cast<byte>(0xFF));

    EXPECT_EQ(buf[1], static_cast<byte>(0xFF));

}



TEST_F(Us2DataTest_1145, InvalidByteOrder_1145) {

    byte buf[2];

    uint16_t value = 0xABCD;

    size_t result = us2Data(buf, value, invalidByteOrder);

    EXPECT_EQ(result, 2);

    // The behavior for invalidByteOrder is not specified in the code snippet.

    // Assuming it behaves like bigEndian as a default case.

    EXPECT_EQ(buf[0], static_cast<byte>(0xAB));

    EXPECT_EQ(buf[1], static_cast<byte>(0xCD));

}



}  // namespace
