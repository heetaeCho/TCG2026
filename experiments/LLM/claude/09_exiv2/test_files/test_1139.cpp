#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

class GetURationalTest_1139 : public ::testing::Test {
protected:
    byte buf[8];

    void setBuf(uint32_t nominator, uint32_t denominator, ByteOrder byteOrder) {
        if (byteOrder == littleEndian) {
            buf[0] = static_cast<byte>(nominator & 0xFF);
            buf[1] = static_cast<byte>((nominator >> 8) & 0xFF);
            buf[2] = static_cast<byte>((nominator >> 16) & 0xFF);
            buf[3] = static_cast<byte>((nominator >> 24) & 0xFF);
            buf[4] = static_cast<byte>(denominator & 0xFF);
            buf[5] = static_cast<byte>((denominator >> 8) & 0xFF);
            buf[6] = static_cast<byte>((denominator >> 16) & 0xFF);
            buf[7] = static_cast<byte>((denominator >> 24) & 0xFF);
        } else {
            buf[0] = static_cast<byte>((nominator >> 24) & 0xFF);
            buf[1] = static_cast<byte>((nominator >> 16) & 0xFF);
            buf[2] = static_cast<byte>((nominator >> 8) & 0xFF);
            buf[3] = static_cast<byte>(nominator & 0xFF);
            buf[4] = static_cast<byte>((denominator >> 24) & 0xFF);
            buf[5] = static_cast<byte>((denominator >> 16) & 0xFF);
            buf[6] = static_cast<byte>((denominator >> 8) & 0xFF);
            buf[7] = static_cast<byte>(denominator & 0xFF);
        }
    }
};

TEST_F(GetURationalTest_1139, BasicLittleEndian_1139) {
    setBuf(1, 2, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 2u);
}

TEST_F(GetURationalTest_1139, BasicBigEndian_1139) {
    setBuf(1, 2, bigEndian);
    URational result = getURational(buf, bigEndian);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 2u);
}

TEST_F(GetURationalTest_1139, ZeroNominatorLittleEndian_1139) {
    setBuf(0, 5, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 0u);
    EXPECT_EQ(result.second, 5u);
}

TEST_F(GetURationalTest_1139, ZeroDenominatorLittleEndian_1139) {
    setBuf(5, 0, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 5u);
    EXPECT_EQ(result.second, 0u);
}

TEST_F(GetURationalTest_1139, BothZeroLittleEndian_1139) {
    setBuf(0, 0, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 0u);
    EXPECT_EQ(result.second, 0u);
}

TEST_F(GetURationalTest_1139, BothZeroBigEndian_1139) {
    setBuf(0, 0, bigEndian);
    URational result = getURational(buf, bigEndian);
    EXPECT_EQ(result.first, 0u);
    EXPECT_EQ(result.second, 0u);
}

TEST_F(GetURationalTest_1139, MaxValuesLittleEndian_1139) {
    setBuf(0xFFFFFFFF, 0xFFFFFFFF, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 0xFFFFFFFFu);
    EXPECT_EQ(result.second, 0xFFFFFFFFu);
}

TEST_F(GetURationalTest_1139, MaxValuesBigEndian_1139) {
    setBuf(0xFFFFFFFF, 0xFFFFFFFF, bigEndian);
    URational result = getURational(buf, bigEndian);
    EXPECT_EQ(result.first, 0xFFFFFFFFu);
    EXPECT_EQ(result.second, 0xFFFFFFFFu);
}

TEST_F(GetURationalTest_1139, LargeNominatorSmallDenominatorLE_1139) {
    setBuf(1000000, 1, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 1000000u);
    EXPECT_EQ(result.second, 1u);
}

TEST_F(GetURationalTest_1139, LargeNominatorSmallDenominatorBE_1139) {
    setBuf(1000000, 1, bigEndian);
    URational result = getURational(buf, bigEndian);
    EXPECT_EQ(result.first, 1000000u);
    EXPECT_EQ(result.second, 1u);
}

TEST_F(GetURationalTest_1139, SmallNominatorLargeDenominatorLE_1139) {
    setBuf(1, 1000000, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 1000000u);
}

TEST_F(GetURationalTest_1139, SmallNominatorLargeDenominatorBE_1139) {
    setBuf(1, 1000000, bigEndian);
    URational result = getURational(buf, bigEndian);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 1000000u);
}

TEST_F(GetURationalTest_1139, TypicalExifFocalLength_1139) {
    // e.g., focal length 50/1
    setBuf(50, 1, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 50u);
    EXPECT_EQ(result.second, 1u);
}

TEST_F(GetURationalTest_1139, TypicalExifExposureTime_1139) {
    // e.g., exposure time 1/250
    setBuf(1, 250, bigEndian);
    URational result = getURational(buf, bigEndian);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 250u);
}

TEST_F(GetURationalTest_1139, EqualNominatorDenominator_1139) {
    setBuf(100, 100, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 100u);
    EXPECT_EQ(result.second, 100u);
}

TEST_F(GetURationalTest_1139, SpecificBytePatternLE_1139) {
    // Manually set bytes to verify endianness interpretation
    // nominator = 0x01020304 in little endian: 04 03 02 01
    // denominator = 0x05060708 in little endian: 08 07 06 05
    buf[0] = 0x04; buf[1] = 0x03; buf[2] = 0x02; buf[3] = 0x01;
    buf[4] = 0x08; buf[5] = 0x07; buf[6] = 0x06; buf[7] = 0x05;
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 0x01020304u);
    EXPECT_EQ(result.second, 0x05060708u);
}

TEST_F(GetURationalTest_1139, SpecificBytePatternBE_1139) {
    // nominator = 0x01020304 in big endian: 01 02 03 04
    // denominator = 0x05060708 in big endian: 05 06 07 08
    buf[0] = 0x01; buf[1] = 0x02; buf[2] = 0x03; buf[3] = 0x04;
    buf[4] = 0x05; buf[5] = 0x06; buf[6] = 0x07; buf[7] = 0x08;
    URational result = getURational(buf, bigEndian);
    EXPECT_EQ(result.first, 0x01020304u);
    EXPECT_EQ(result.second, 0x05060708u);
}

TEST_F(GetURationalTest_1139, OnlyHighBitSetNominatorLE_1139) {
    setBuf(0x80000000, 1, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 0x80000000u);
    EXPECT_EQ(result.second, 1u);
}

TEST_F(GetURationalTest_1139, OnlyHighBitSetDenominatorBE_1139) {
    setBuf(1, 0x80000000, bigEndian);
    URational result = getURational(buf, bigEndian);
    EXPECT_EQ(result.first, 1u);
    EXPECT_EQ(result.second, 0x80000000u);
}

TEST_F(GetURationalTest_1139, PowerOfTwoValues_1139) {
    setBuf(256, 65536, littleEndian);
    URational result = getURational(buf, littleEndian);
    EXPECT_EQ(result.first, 256u);
    EXPECT_EQ(result.second, 65536u);
}
