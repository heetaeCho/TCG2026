#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace Exiv2 {

    double getDouble(const byte* buf, ByteOrder byteOrder);

}



TEST(getDoubleTest_1144, NormalOperation_LittleEndian_1144) {

    uint8_t buffer[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f}; // Represents 1.0 in little-endian

    double result = Exiv2::getDouble(buffer, Exiv2::littleEndian);

    EXPECT_DOUBLE_EQ(result, 1.0);

}



TEST(getDoubleTest_1144, NormalOperation_BigEndian_1144) {

    uint8_t buffer[] = {0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Represents 1.0 in big-endian

    double result = Exiv2::getDouble(buffer, Exiv2::bigEndian);

    EXPECT_DOUBLE_EQ(result, 1.0);

}



TEST(getDoubleTest_1144, BoundaryCondition_Zero_LittleEndian_1144) {

    uint8_t buffer[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Represents 0.0 in little-endian

    double result = Exiv2::getDouble(buffer, Exiv2::littleEndian);

    EXPECT_DOUBLE_EQ(result, 0.0);

}



TEST(getDoubleTest_1144, BoundaryCondition_Zero_BigEndian_1144) {

    uint8_t buffer[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Represents 0.0 in big-endian

    double result = Exiv2::getDouble(buffer, Exiv2::bigEndian);

    EXPECT_DOUBLE_EQ(result, 0.0);

}



TEST(getDoubleTest_1144, BoundaryCondition_MaxValue_LittleEndian_1144) {

    uint8_t buffer[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x7f}; // Represents DBL_MAX in little-endian

    double result = Exiv2::getDouble(buffer, Exiv2::littleEndian);

    EXPECT_DOUBLE_EQ(result, DBL_MAX);

}



TEST(getDoubleTest_1144, BoundaryCondition_MaxValue_BigEndian_1144) {

    uint8_t buffer[] = {0x7f, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; // Represents DBL_MAX in big-endian

    double result = Exiv2::getDouble(buffer, Exiv2::bigEndian);

    EXPECT_DOUBLE_EQ(result, DBL_MAX);

}



TEST(getDoubleTest_1144, BoundaryCondition_MinValue_LittleEndian_1144) {

    uint8_t buffer[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff}; // Represents -DBL_MAX in little-endian

    double result = Exiv2::getDouble(buffer, Exiv2::littleEndian);

    EXPECT_DOUBLE_EQ(result, -DBL_MAX);

}



TEST(getDoubleTest_1144, BoundaryCondition_MinValue_BigEndian_1144) {

    uint8_t buffer[] = {0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff}; // Represents -DBL_MAX in big-endian

    double result = Exiv2::getDouble(buffer, Exiv2::bigEndian);

    EXPECT_DOUBLE_EQ(result, -DBL_MAX);

}



TEST(getDoubleTest_1144, InvalidByteOrder_DefaultsToBigEndian_1144) {

    uint8_t buffer[] = {0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Represents 1.0 in big-endian

    double result = Exiv2::getDouble(buffer, static_cast<Exiv2::ByteOrder>(99)); // Invalid byte order

    EXPECT_DOUBLE_EQ(result, 1.0);

}
