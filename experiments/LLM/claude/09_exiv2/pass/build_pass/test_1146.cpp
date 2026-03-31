#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace Exiv2 {
size_t ul2Data(byte* buf, uint32_t l, ByteOrder byteOrder);
}

using namespace Exiv2;

class Ul2DataTest_1146 : public ::testing::Test {
 protected:
  byte buf[4];
};

// Test that the function returns 4 for little endian
TEST_F(Ul2DataTest_1146, ReturnsFourForLittleEndian_1146) {
  size_t result = ul2Data(buf, 0x12345678, littleEndian);
  EXPECT_EQ(4u, result);
}

// Test that the function returns 4 for big endian
TEST_F(Ul2DataTest_1146, ReturnsFourForBigEndian_1146) {
  size_t result = ul2Data(buf, 0x12345678, bigEndian);
  EXPECT_EQ(4u, result);
}

// Test little endian byte order with a known value
TEST_F(Ul2DataTest_1146, LittleEndianCorrectByteOrder_1146) {
  ul2Data(buf, 0x12345678, littleEndian);
  EXPECT_EQ(0x78, buf[0]);
  EXPECT_EQ(0x56, buf[1]);
  EXPECT_EQ(0x34, buf[2]);
  EXPECT_EQ(0x12, buf[3]);
}

// Test big endian byte order with a known value
TEST_F(Ul2DataTest_1146, BigEndianCorrectByteOrder_1146) {
  ul2Data(buf, 0x12345678, bigEndian);
  EXPECT_EQ(0x12, buf[0]);
  EXPECT_EQ(0x34, buf[1]);
  EXPECT_EQ(0x56, buf[2]);
  EXPECT_EQ(0x78, buf[3]);
}

// Test with zero value in little endian
TEST_F(Ul2DataTest_1146, ZeroValueLittleEndian_1146) {
  ul2Data(buf, 0x00000000, littleEndian);
  EXPECT_EQ(0x00, buf[0]);
  EXPECT_EQ(0x00, buf[1]);
  EXPECT_EQ(0x00, buf[2]);
  EXPECT_EQ(0x00, buf[3]);
}

// Test with zero value in big endian
TEST_F(Ul2DataTest_1146, ZeroValueBigEndian_1146) {
  ul2Data(buf, 0x00000000, bigEndian);
  EXPECT_EQ(0x00, buf[0]);
  EXPECT_EQ(0x00, buf[1]);
  EXPECT_EQ(0x00, buf[2]);
  EXPECT_EQ(0x00, buf[3]);
}

// Test with maximum uint32_t value in little endian
TEST_F(Ul2DataTest_1146, MaxValueLittleEndian_1146) {
  ul2Data(buf, 0xFFFFFFFF, littleEndian);
  EXPECT_EQ(0xFF, buf[0]);
  EXPECT_EQ(0xFF, buf[1]);
  EXPECT_EQ(0xFF, buf[2]);
  EXPECT_EQ(0xFF, buf[3]);
}

// Test with maximum uint32_t value in big endian
TEST_F(Ul2DataTest_1146, MaxValueBigEndian_1146) {
  ul2Data(buf, 0xFFFFFFFF, bigEndian);
  EXPECT_EQ(0xFF, buf[0]);
  EXPECT_EQ(0xFF, buf[1]);
  EXPECT_EQ(0xFF, buf[2]);
  EXPECT_EQ(0xFF, buf[3]);
}

// Test with value 1 in little endian
TEST_F(Ul2DataTest_1146, ValueOneLittleEndian_1146) {
  ul2Data(buf, 1, littleEndian);
  EXPECT_EQ(0x01, buf[0]);
  EXPECT_EQ(0x00, buf[1]);
  EXPECT_EQ(0x00, buf[2]);
  EXPECT_EQ(0x00, buf[3]);
}

// Test with value 1 in big endian
TEST_F(Ul2DataTest_1146, ValueOneBigEndian_1146) {
  ul2Data(buf, 1, bigEndian);
  EXPECT_EQ(0x00, buf[0]);
  EXPECT_EQ(0x00, buf[1]);
  EXPECT_EQ(0x00, buf[2]);
  EXPECT_EQ(0x01, buf[3]);
}

// Test with value that has only the high byte set in little endian
TEST_F(Ul2DataTest_1146, HighByteOnlyLittleEndian_1146) {
  ul2Data(buf, 0xFF000000, littleEndian);
  EXPECT_EQ(0x00, buf[0]);
  EXPECT_EQ(0x00, buf[1]);
  EXPECT_EQ(0x00, buf[2]);
  EXPECT_EQ(0xFF, buf[3]);
}

// Test with value that has only the high byte set in big endian
TEST_F(Ul2DataTest_1146, HighByteOnlyBigEndian_1146) {
  ul2Data(buf, 0xFF000000, bigEndian);
  EXPECT_EQ(0xFF, buf[0]);
  EXPECT_EQ(0x00, buf[1]);
  EXPECT_EQ(0x00, buf[2]);
  EXPECT_EQ(0x00, buf[3]);
}

// Test with value 256 (0x100) in little endian
TEST_F(Ul2DataTest_1146, Value256LittleEndian_1146) {
  ul2Data(buf, 0x00000100, littleEndian);
  EXPECT_EQ(0x00, buf[0]);
  EXPECT_EQ(0x01, buf[1]);
  EXPECT_EQ(0x00, buf[2]);
  EXPECT_EQ(0x00, buf[3]);
}

// Test with value 256 (0x100) in big endian
TEST_F(Ul2DataTest_1146, Value256BigEndian_1146) {
  ul2Data(buf, 0x00000100, bigEndian);
  EXPECT_EQ(0x00, buf[0]);
  EXPECT_EQ(0x00, buf[1]);
  EXPECT_EQ(0x01, buf[2]);
  EXPECT_EQ(0x00, buf[3]);
}

// Test with alternating byte pattern in little endian
TEST_F(Ul2DataTest_1146, AlternatingPatternLittleEndian_1146) {
  ul2Data(buf, 0xAABBCCDD, littleEndian);
  EXPECT_EQ(0xDD, buf[0]);
  EXPECT_EQ(0xCC, buf[1]);
  EXPECT_EQ(0xBB, buf[2]);
  EXPECT_EQ(0xAA, buf[3]);
}

// Test with alternating byte pattern in big endian
TEST_F(Ul2DataTest_1146, AlternatingPatternBigEndian_1146) {
  ul2Data(buf, 0xAABBCCDD, bigEndian);
  EXPECT_EQ(0xAA, buf[0]);
  EXPECT_EQ(0xBB, buf[1]);
  EXPECT_EQ(0xCC, buf[2]);
  EXPECT_EQ(0xDD, buf[3]);
}

// Test with only the second byte set in little endian
TEST_F(Ul2DataTest_1146, SecondByteOnlyLittleEndian_1146) {
  ul2Data(buf, 0x0000FF00, littleEndian);
  EXPECT_EQ(0x00, buf[0]);
  EXPECT_EQ(0xFF, buf[1]);
  EXPECT_EQ(0x00, buf[2]);
  EXPECT_EQ(0x00, buf[3]);
}

// Test with only the third byte set in big endian
TEST_F(Ul2DataTest_1146, ThirdByteOnlyBigEndian_1146) {
  ul2Data(buf, 0x00FF0000, bigEndian);
  EXPECT_EQ(0x00, buf[0]);
  EXPECT_EQ(0xFF, buf[1]);
  EXPECT_EQ(0x00, buf[2]);
  EXPECT_EQ(0x00, buf[3]);
}

// Test that big endian and little endian produce reversed results
TEST_F(Ul2DataTest_1146, LittleAndBigEndianAreReversed_1146) {
  byte buf_le[4];
  byte buf_be[4];
  ul2Data(buf_le, 0x01020304, littleEndian);
  ul2Data(buf_be, 0x01020304, bigEndian);
  EXPECT_EQ(buf_le[0], buf_be[3]);
  EXPECT_EQ(buf_le[1], buf_be[2]);
  EXPECT_EQ(buf_le[2], buf_be[1]);
  EXPECT_EQ(buf_le[3], buf_be[0]);
}
