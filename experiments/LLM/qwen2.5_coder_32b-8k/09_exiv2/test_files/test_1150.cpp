#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace Exiv2 {

    size_t l2Data(byte* buf, int32_t l, ByteOrder byteOrder);

}



TEST(l2DataTest_1150, NormalOperation_LittleEndian_1150) {

    byte buffer[4];

    EXPECT_EQ(Exiv2::l2Data(buffer, 0x12345678, Exiv2::littleEndian), 4);

    EXPECT_EQ(buffer[0], 0x78);

    EXPECT_EQ(buffer[1], 0x56);

    EXPECT_EQ(buffer[2], 0x34);

    EXPECT_EQ(buffer[3], 0x12);

}



TEST(l2DataTest_1150, NormalOperation_BigEndian_1150) {

    byte buffer[4];

    EXPECT_EQ(Exiv2::l2Data(buffer, 0x12345678, Exiv2::bigEndian), 4);

    EXPECT_EQ(buffer[0], 0x12);

    EXPECT_EQ(buffer[1], 0x34);

    EXPECT_EQ(buffer[2], 0x56);

    EXPECT_EQ(buffer[3], 0x78);

}



TEST(l2DataTest_1150, BoundaryCondition_Zero_1150) {

    byte buffer[4];

    EXPECT_EQ(Exiv2::l2Data(buffer, 0, Exiv2::littleEndian), 4);

    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(buffer[i], 0);

    }

}



TEST(l2DataTest_1150, BoundaryCondition_MaxValue_1150) {

    byte buffer[4];

    EXPECT_EQ(Exiv2::l2Data(buffer, 0xFFFFFFFF, Exiv2::littleEndian), 4);

    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(buffer[i], 0xFF);

    }

}



TEST(l2DataTest_1150, BoundaryCondition_MinValue_1150) {

    byte buffer[4];

    EXPECT_EQ(Exiv2::l2Data(buffer, 0x00000000, Exiv2::bigEndian), 4);

    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(buffer[i], 0x00);

    }

}



TEST(l2DataTest_1150, InvalidByteOrder_1150) {

    byte buffer[4];

    EXPECT_EQ(Exiv2::l2Data(buffer, 0x12345678, Exiv2::invalidByteOrder), 4);

    // The behavior for invalidByteOrder is not defined in the code,

    // but we can check that it does not cause a crash and returns 4.

}
