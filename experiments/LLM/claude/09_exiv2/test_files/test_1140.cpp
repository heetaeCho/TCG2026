#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace Exiv2 {
int16_t getShort(const byte* buf, ByteOrder byteOrder);
}

using namespace Exiv2;

class GetShortTest_1140 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(GetShortTest_1140, LittleEndianBasicValue_1140) {
    // 0x0102 in little endian: low byte first
    byte buf[] = {0x02, 0x01};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, 0x0102);
}

TEST_F(GetShortTest_1140, BigEndianBasicValue_1140) {
    // 0x0102 in big endian: high byte first
    byte buf[] = {0x01, 0x02};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, 0x0102);
}

TEST_F(GetShortTest_1140, LittleEndianZero_1140) {
    byte buf[] = {0x00, 0x00};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, 0);
}

TEST_F(GetShortTest_1140, BigEndianZero_1140) {
    byte buf[] = {0x00, 0x00};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, 0);
}

TEST_F(GetShortTest_1140, LittleEndianOne_1140) {
    byte buf[] = {0x01, 0x00};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, 1);
}

TEST_F(GetShortTest_1140, BigEndianOne_1140) {
    byte buf[] = {0x00, 0x01};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, 1);
}

// Boundary condition tests

TEST_F(GetShortTest_1140, LittleEndianMaxPositive_1140) {
    // 0x7FFF = 32767 in little endian
    byte buf[] = {0xFF, 0x7F};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, 32767);
}

TEST_F(GetShortTest_1140, BigEndianMaxPositive_1140) {
    // 0x7FFF = 32767 in big endian
    byte buf[] = {0x7F, 0xFF};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, 32767);
}

TEST_F(GetShortTest_1140, LittleEndianMinNegative_1140) {
    // 0x8000 = -32768 in little endian
    byte buf[] = {0x00, 0x80};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, -32768);
}

TEST_F(GetShortTest_1140, BigEndianMinNegative_1140) {
    // 0x8000 = -32768 in big endian
    byte buf[] = {0x80, 0x00};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, -32768);
}

TEST_F(GetShortTest_1140, LittleEndianAllOnes_1140) {
    // 0xFFFF = -1 in little endian
    byte buf[] = {0xFF, 0xFF};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, -1);
}

TEST_F(GetShortTest_1140, BigEndianAllOnes_1140) {
    // 0xFFFF = -1 in big endian
    byte buf[] = {0xFF, 0xFF};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, -1);
}

TEST_F(GetShortTest_1140, LittleEndianMinusOne_1140) {
    byte buf[] = {0xFF, 0xFF};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, static_cast<int16_t>(0xFFFF));
}

TEST_F(GetShortTest_1140, BigEndianMinusOne_1140) {
    byte buf[] = {0xFF, 0xFF};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, static_cast<int16_t>(0xFFFF));
}

// Verify byte order actually matters

TEST_F(GetShortTest_1140, ByteOrderMatters_1140) {
    byte buf[] = {0x01, 0x02};
    int16_t le_result = getShort(buf, littleEndian);
    int16_t be_result = getShort(buf, bigEndian);
    // Little endian: 0x0201, Big endian: 0x0102
    EXPECT_EQ(le_result, 0x0201);
    EXPECT_EQ(be_result, 0x0102);
    EXPECT_NE(le_result, be_result);
}

TEST_F(GetShortTest_1140, LittleEndianHighByteOnly_1140) {
    // buf[0]=0x00, buf[1]=0x01 => little endian: 0x0100 = 256
    byte buf[] = {0x00, 0x01};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, 256);
}

TEST_F(GetShortTest_1140, BigEndianHighByteOnly_1140) {
    // buf[0]=0x01, buf[1]=0x00 => big endian: 0x0100 = 256
    byte buf[] = {0x01, 0x00};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, 256);
}

TEST_F(GetShortTest_1140, LittleEndianLowByteOnly_1140) {
    // buf[0]=0xAB, buf[1]=0x00 => little endian: 0x00AB = 171
    byte buf[] = {0xAB, 0x00};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, 0x00AB);
}

TEST_F(GetShortTest_1140, BigEndianLowByteOnly_1140) {
    // buf[0]=0x00, buf[1]=0xAB => big endian: 0x00AB = 171
    byte buf[] = {0x00, 0xAB};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, 0x00AB);
}

// Symmetric values should be the same in both byte orders
TEST_F(GetShortTest_1140, SymmetricBytesGiveSameResult_1140) {
    byte buf[] = {0xAB, 0xAB};
    int16_t le_result = getShort(buf, littleEndian);
    int16_t be_result = getShort(buf, bigEndian);
    EXPECT_EQ(le_result, be_result);
}

TEST_F(GetShortTest_1140, LittleEndianNegativeValue_1140) {
    // -256 = 0xFF00 in little endian: buf[0]=0x00, buf[1]=0xFF
    byte buf[] = {0x00, 0xFF};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, -256);
}

TEST_F(GetShortTest_1140, BigEndianNegativeValue_1140) {
    // -256 = 0xFF00 in big endian: buf[0]=0xFF, buf[1]=0x00
    byte buf[] = {0xFF, 0x00};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, -256);
}

TEST_F(GetShortTest_1140, LittleEndianSpecificPattern_1140) {
    // 0xCAFE in little endian: buf[0]=0xFE, buf[1]=0xCA
    byte buf[] = {0xFE, 0xCA};
    int16_t result = getShort(buf, littleEndian);
    EXPECT_EQ(result, static_cast<int16_t>(0xCAFE));
}

TEST_F(GetShortTest_1140, BigEndianSpecificPattern_1140) {
    // 0xCAFE in big endian: buf[0]=0xCA, buf[1]=0xFE
    byte buf[] = {0xCA, 0xFE};
    int16_t result = getShort(buf, bigEndian);
    EXPECT_EQ(result, static_cast<int16_t>(0xCAFE));
}
