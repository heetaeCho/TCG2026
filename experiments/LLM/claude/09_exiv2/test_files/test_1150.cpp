#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace Exiv2 {
size_t l2Data(byte* buf, int32_t l, ByteOrder byteOrder);
}

using namespace Exiv2;

class L2DataTest_1150 : public ::testing::Test {
protected:
    byte buf[4];

    void SetUp() override {
        memset(buf, 0, sizeof(buf));
    }
};

// Test that the function returns 4 for little endian
TEST_F(L2DataTest_1150, ReturnsFourLittleEndian_1150) {
    size_t result = l2Data(buf, 0, littleEndian);
    EXPECT_EQ(result, 4u);
}

// Test that the function returns 4 for big endian
TEST_F(L2DataTest_1150, ReturnsFourBigEndian_1150) {
    size_t result = l2Data(buf, 0, bigEndian);
    EXPECT_EQ(result, 4u);
}

// Test zero value in little endian
TEST_F(L2DataTest_1150, ZeroValueLittleEndian_1150) {
    l2Data(buf, 0, littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test zero value in big endian
TEST_F(L2DataTest_1150, ZeroValueBigEndian_1150) {
    l2Data(buf, 0, bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test positive value in little endian
TEST_F(L2DataTest_1150, PositiveValueLittleEndian_1150) {
    l2Data(buf, 0x01020304, littleEndian);
    EXPECT_EQ(buf[0], 0x04);
    EXPECT_EQ(buf[1], 0x03);
    EXPECT_EQ(buf[2], 0x02);
    EXPECT_EQ(buf[3], 0x01);
}

// Test positive value in big endian
TEST_F(L2DataTest_1150, PositiveValueBigEndian_1150) {
    l2Data(buf, 0x01020304, bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
}

// Test negative value (-1 = 0xFFFFFFFF) in little endian
TEST_F(L2DataTest_1150, NegativeValueLittleEndian_1150) {
    l2Data(buf, -1, littleEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test negative value (-1 = 0xFFFFFFFF) in big endian
TEST_F(L2DataTest_1150, NegativeValueBigEndian_1150) {
    l2Data(buf, -1, bigEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test INT32_MAX in little endian
TEST_F(L2DataTest_1150, MaxInt32LittleEndian_1150) {
    l2Data(buf, INT32_MAX, littleEndian);
    // INT32_MAX = 0x7FFFFFFF
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0x7F);
}

// Test INT32_MAX in big endian
TEST_F(L2DataTest_1150, MaxInt32BigEndian_1150) {
    l2Data(buf, INT32_MAX, bigEndian);
    // INT32_MAX = 0x7FFFFFFF
    EXPECT_EQ(buf[0], 0x7F);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test INT32_MIN in little endian
TEST_F(L2DataTest_1150, MinInt32LittleEndian_1150) {
    l2Data(buf, INT32_MIN, littleEndian);
    // INT32_MIN = 0x80000000
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x80);
}

// Test INT32_MIN in big endian
TEST_F(L2DataTest_1150, MinInt32BigEndian_1150) {
    l2Data(buf, INT32_MIN, bigEndian);
    // INT32_MIN = 0x80000000
    EXPECT_EQ(buf[0], 0x80);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test value with single byte set (0x000000AB) little endian
TEST_F(L2DataTest_1150, SingleByteLittleEndian_1150) {
    l2Data(buf, 0xAB, littleEndian);
    EXPECT_EQ(buf[0], 0xAB);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test value with single byte set (0x000000AB) big endian
TEST_F(L2DataTest_1150, SingleByteBigEndian_1150) {
    l2Data(buf, 0xAB, bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0xAB);
}

// Test value 1 little endian
TEST_F(L2DataTest_1150, ValueOneLittleEndian_1150) {
    l2Data(buf, 1, littleEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test value 1 big endian
TEST_F(L2DataTest_1150, ValueOneBigEndian_1150) {
    l2Data(buf, 1, bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x01);
}

// Test value 256 (0x100) little endian
TEST_F(L2DataTest_1150, Value256LittleEndian_1150) {
    l2Data(buf, 256, littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test value 256 (0x100) big endian
TEST_F(L2DataTest_1150, Value256BigEndian_1150) {
    l2Data(buf, 256, bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x01);
    EXPECT_EQ(buf[3], 0x00);
}

// Test distinct bytes to verify ordering (0xAABBCCDD) little endian
TEST_F(L2DataTest_1150, DistinctBytesLittleEndian_1150) {
    l2Data(buf, static_cast<int32_t>(0xAABBCCDD), littleEndian);
    EXPECT_EQ(buf[0], 0xDD);
    EXPECT_EQ(buf[1], 0xCC);
    EXPECT_EQ(buf[2], 0xBB);
    EXPECT_EQ(buf[3], 0xAA);
}

// Test distinct bytes to verify ordering (0xAABBCCDD) big endian
TEST_F(L2DataTest_1150, DistinctBytesBigEndian_1150) {
    l2Data(buf, static_cast<int32_t>(0xAABBCCDD), bigEndian);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
    EXPECT_EQ(buf[3], 0xDD);
}

// Test negative value -256 (0xFFFFFF00) little endian
TEST_F(L2DataTest_1150, NegativeValue256LittleEndian_1150) {
    l2Data(buf, -256, littleEndian);
    // -256 = 0xFFFFFF00
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test negative value -256 (0xFFFFFF00) big endian
TEST_F(L2DataTest_1150, NegativeValue256BigEndian_1150) {
    l2Data(buf, -256, bigEndian);
    // -256 = 0xFFFFFF00
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0x00);
}
