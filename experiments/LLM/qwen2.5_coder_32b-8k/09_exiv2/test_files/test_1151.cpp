#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "types.cpp"



namespace Exiv2 {

    struct Rational {

        long first;

        long second;

    };



    enum ByteOrder { littleEndian, bigEndian };

}



using namespace Exiv2;



class R2DataTest_1151 : public ::testing::Test {

protected:

    byte buffer[16];  // Sufficiently large to hold two 4-byte integers

};



TEST_F(R2DataTest_1151, NormalOperation_LittleEndian_1151) {

    Rational r = {0x12345678, 0x9ABCDEF0};

    size_t result = r2Data(buffer, r, littleEndian);

    EXPECT_EQ(result, 8u);

    EXPECT_EQ(buffer[0], 0x78);

    EXPECT_EQ(buffer[1], 0x56);

    EXPECT_EQ(buffer[2], 0x34);

    EXPECT_EQ(buffer[3], 0x12);

    EXPECT_EQ(buffer[4], 0xF0);

    EXPECT_EQ(buffer[5], 0xDE);

    EXPECT_EQ(buffer[6], 0xBC);

    EXPECT_EQ(buffer[7], 0x9A);

}



TEST_F(R2DataTest_1151, NormalOperation_BigEndian_1151) {

    Rational r = {0x12345678, 0x9ABCDEF0};

    size_t result = r2Data(buffer, r, bigEndian);

    EXPECT_EQ(result, 8u);

    EXPECT_EQ(buffer[0], 0x12);

    EXPECT_EQ(buffer[1], 0x34);

    EXPECT_EQ(buffer[2], 0x56);

    EXPECT_EQ(buffer[3], 0x78);

    EXPECT_EQ(buffer[4], 0x9A);

    EXPECT_EQ(buffer[5], 0xBC);

    EXPECT_EQ(buffer[6], 0xDE);

    EXPECT_EQ(buffer[7], 0xF0);

}



TEST_F(R2DataTest_1151, ZeroValues_1151) {

    Rational r = {0, 0};

    size_t result = r2Data(buffer, r, littleEndian);

    EXPECT_EQ(result, 8u);

    EXPECT_EQ(buffer[0], 0x00);

    EXPECT_EQ(buffer[1], 0x00);

    EXPECT_EQ(buffer[2], 0x00);

    EXPECT_EQ(buffer[3], 0x00);

    EXPECT_EQ(buffer[4], 0x00);

    EXPECT_EQ(buffer[5], 0x00);

    EXPECT_EQ(buffer[6], 0x00);

    EXPECT_EQ(buffer[7], 0x00);

}



TEST_F(R2DataTest_1151, MaxValues_1151) {

    Rational r = {0xFFFFFFFF, 0xFFFFFFFF};

    size_t result = r2Data(buffer, r, littleEndian);

    EXPECT_EQ(result, 8u);

    EXPECT_EQ(buffer[0], 0xFF);

    EXPECT_EQ(buffer[1], 0xFF);

    EXPECT_EQ(buffer[2], 0xFF);

    EXPECT_EQ(buffer[3], 0xFF);

    EXPECT_EQ(buffer[4], 0xFF);

    EXPECT_EQ(buffer[5], 0xFF);

    EXPECT_EQ(buffer[6], 0xFF);

    EXPECT_EQ(buffer[7], 0xFF);

}



TEST_F(R2DataTest_1151, MixedValues_BigEndian_1151) {

    Rational r = {0x1234, 0xABCD};

    size_t result = r2Data(buffer, r, bigEndian);

    EXPECT_EQ(result, 8u);

    EXPECT_EQ(buffer[0], 0x00);

    EXPECT_EQ(buffer[1], 0x00);

    EXPECT_EQ(buffer[2], 0x12);

    EXPECT_EQ(buffer[3], 0x34);

    EXPECT_EQ(buffer[4], 0x00);

    EXPECT_EQ(buffer[5], 0x00);

    EXPECT_EQ(buffer[6], 0xAB);

    EXPECT_EQ(buffer[7], 0xCD);

}
