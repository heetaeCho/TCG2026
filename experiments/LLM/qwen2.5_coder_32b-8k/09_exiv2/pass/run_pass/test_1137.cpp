#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace {



TEST(getULongTest_1137, NormalOperation_LittleEndian_1137) {

    const uint8_t buf[] = {0x12, 0x34, 0x56, 0x78};

    EXPECT_EQ(Exiv2::getULong(buf, Exiv2::littleEndian), 0x78563412);

}



TEST(getULongTest_1137, NormalOperation_BigEndian_1137) {

    const uint8_t buf[] = {0x12, 0x34, 0x56, 0x78};

    EXPECT_EQ(Exiv2::getULong(buf, Exiv2::bigEndian), 0x12345678);

}



TEST(getULongTest_1137, BoundaryCondition_AllZeros_1137) {

    const uint8_t buf[] = {0x00, 0x00, 0x00, 0x00};

    EXPECT_EQ(Exiv2::getULong(buf, Exiv2::littleEndian), 0x00000000);

    EXPECT_EQ(Exiv2::getULong(buf, Exiv2::bigEndian), 0x00000000);

}



TEST(getULongTest_1137, BoundaryCondition_AllOnes_1137) {

    const uint8_t buf[] = {0xFF, 0xFF, 0xFF, 0xFF};

    EXPECT_EQ(Exiv2::getULong(buf, Exiv2::littleEndian), 0xFFFFFFFF);

    EXPECT_EQ(Exiv2::getULong(buf, Exiv2::bigEndian), 0xFFFFFFFF);

}



TEST(getULongTest_1137, BoundaryCondition_MaxValue_LittleEndian_1137) {

    const uint8_t buf[] = {0xFF, 0xFF, 0xFF, 0x7F};

    EXPECT_EQ(Exiv2::getULong(buf, Exiv2::littleEndian), 0x7FFFFFFF);

}



TEST(getULongTest_1137, BoundaryCondition_MaxValue_BigEndian_1137) {

    const uint8_t buf[] = {0x7F, 0xFF, 0xFF, 0xFF};

    EXPECT_EQ(Exiv2::getULong(buf, Exiv2::bigEndian), 0x7FFFFFFF);

}



TEST(getULongTest_1137, InvalidByteOrder_Ignored_1137) {

    const uint8_t buf[] = {0x12, 0x34, 0x56, 0x78};

    EXPECT_EQ(Exiv2::getULong(buf, Exiv2::invalidByteOrder), Exiv2::getULong(buf, Exiv2::bigEndian));

}



} // namespace
