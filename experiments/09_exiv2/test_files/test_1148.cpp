#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/types.cpp"



namespace Exiv2 {

    struct URational {

        uint32_t first;

        uint32_t second;

    };



    enum ByteOrder { bigEndian, littleEndian };

}



using namespace Exiv2;



TEST(ur2DataTest_1148, NormalOperation_BigEndian_1148) {

    byte buf[8] = {0};

    URational l = {0x12345678, 0x9ABCDEF0};

    size_t result = ur2Data(buf, l, bigEndian);

    EXPECT_EQ(result, 8);

    EXPECT_EQ(buf[0], 0x12);

    EXPECT_EQ(buf[1], 0x34);

    EXPECT_EQ(buf[2], 0x56);

    EXPECT_EQ(buf[3], 0x78);

    EXPECT_EQ(buf[4], 0x9A);

    EXPECT_EQ(buf[5], 0xBC);

    EXPECT_EQ(buf[6], 0xDE);

    EXPECT_EQ(buf[7], 0xF0);

}



TEST(ur2DataTest_1148, NormalOperation_LittleEndian_1148) {

    byte buf[8] = {0};

    URational l = {0x12345678, 0x9ABCDEF0};

    size_t result = ur2Data(buf, l, littleEndian);

    EXPECT_EQ(result, 8);

    EXPECT_EQ(buf[0], 0x78);

    EXPECT_EQ(buf[1], 0x56);

    EXPECT_EQ(buf[2], 0x34);

    EXPECT_EQ(buf[3], 0x12);

    EXPECT_EQ(buf[4], 0xF0);

    EXPECT_EQ(buf[5], 0xDE);

    EXPECT_EQ(buf[6], 0xBC);

    EXPECT_EQ(buf[7], 0x9A);

}



TEST(ur2DataTest_1148, BoundaryCondition_ZeroValues_1148) {

    byte buf[8] = {0xFF};

    URational l = {0, 0};

    size_t result = ur2Data(buf, l, bigEndian);

    EXPECT_EQ(result, 8);

    for (size_t i = 0; i < 8; ++i) {

        EXPECT_EQ(buf[i], 0x00);

    }

}



TEST(ur2DataTest_1148, BoundaryCondition_MaxValues_1148) {

    byte buf[8] = {0};

    URational l = {0xFFFFFFFF, 0xFFFFFFFF};

    size_t result = ur2Data(buf, l, bigEndian);

    EXPECT_EQ(result, 8);

    for (size_t i = 0; i < 4; ++i) {

        EXPECT_EQ(buf[i], 0xFF);

    }

    for (size_t i = 4; i < 8; ++i) {

        EXPECT_EQ(buf[i], 0xFF);

    }

}



TEST(ur2DataTest_1148, ExceptionalCase_BufferTooSmall_1148) {

    byte buf[7] = {0};

    URational l = {0x12345678, 0x9ABCDEF0};

    EXPECT_DEATH(ur2Data(buf, l, bigEndian), "");

}
