#include <gtest/gtest.h>
#include <exiv2/types.hpp>

using namespace Exiv2;

class GetUShortTest_1136 : public ::testing::Test {
 protected:
  byte buf[4];
};

// Test normal operation with little-endian byte order
TEST_F(GetUShortTest_1136, LittleEndianNormalValue_1136) {
  // 0x0201 in little-endian: low byte first
  buf[0] = 0x01;
  buf[1] = 0x02;
  uint16_t result = getUShort(buf, littleEndian);
  EXPECT_EQ(result, 0x0201);
}

// Test normal operation with big-endian byte order
TEST_F(GetUShortTest_1136, BigEndianNormalValue_1136) {
  // 0x0102 in big-endian: high byte first
  buf[0] = 0x01;
  buf[1] = 0x02;
  uint16_t result = getUShort(buf, bigEndian);
  EXPECT_EQ(result, 0x0102);
}

// Test with zero value
TEST_F(GetUShortTest_1136, ZeroValue_1136) {
  buf[0] = 0x00;
  buf[1] = 0x00;
  EXPECT_EQ(getUShort(buf, littleEndian), 0x0000);
  EXPECT_EQ(getUShort(buf, bigEndian), 0x0000);
}

// Test with maximum uint16_t value (0xFFFF)
TEST_F(GetUShortTest_1136, MaxValue_1136) {
  buf[0] = 0xFF;
  buf[1] = 0xFF;
  EXPECT_EQ(getUShort(buf, littleEndian), 0xFFFF);
  EXPECT_EQ(getUShort(buf, bigEndian), 0xFFFF);
}

// Test boundary: only high byte set in big-endian
TEST_F(GetUShortTest_1136, BigEndianHighByteOnly_1136) {
  buf[0] = 0xFF;
  buf[1] = 0x00;
  uint16_t result = getUShort(buf, bigEndian);
  EXPECT_EQ(result, 0xFF00);
}

// Test boundary: only low byte set in big-endian
TEST_F(GetUShortTest_1136, BigEndianLowByteOnly_1136) {
  buf[0] = 0x00;
  buf[1] = 0xFF;
  uint16_t result = getUShort(buf, bigEndian);
  EXPECT_EQ(result, 0x00FF);
}

// Test boundary: only high byte set in little-endian
TEST_F(GetUShortTest_1136, LittleEndianHighByteOnly_1136) {
  buf[0] = 0x00;
  buf[1] = 0xFF;
  uint16_t result = getUShort(buf, littleEndian);
  EXPECT_EQ(result, 0xFF00);
}

// Test boundary: only low byte set in little-endian
TEST_F(GetUShortTest_1136, LittleEndianLowByteOnly_1136) {
  buf[0] = 0xFF;
  buf[1] = 0x00;
  uint16_t result = getUShort(buf, littleEndian);
  EXPECT_EQ(result, 0x00FF);
}

// Test that big-endian and little-endian produce swapped results for asymmetric values
TEST_F(GetUShortTest_1136, EndianDifference_1136) {
  buf[0] = 0xAB;
  buf[1] = 0xCD;
  uint16_t bigResult = getUShort(buf, bigEndian);
  uint16_t littleResult = getUShort(buf, littleEndian);
  EXPECT_EQ(bigResult, 0xABCD);
  EXPECT_EQ(littleResult, 0xCDAB);
}

// Test with value 1 in little-endian
TEST_F(GetUShortTest_1136, ValueOneLittleEndian_1136) {
  buf[0] = 0x01;
  buf[1] = 0x00;
  uint16_t result = getUShort(buf, littleEndian);
  EXPECT_EQ(result, 1);
}

// Test with value 1 in big-endian
TEST_F(GetUShortTest_1136, ValueOneBigEndian_1136) {
  buf[0] = 0x00;
  buf[1] = 0x01;
  uint16_t result = getUShort(buf, bigEndian);
  EXPECT_EQ(result, 1);
}

// Test with value 256 (0x0100)
TEST_F(GetUShortTest_1136, Value256BigEndian_1136) {
  buf[0] = 0x01;
  buf[1] = 0x00;
  uint16_t result = getUShort(buf, bigEndian);
  EXPECT_EQ(result, 256);
}

TEST_F(GetUShortTest_1136, Value256LittleEndian_1136) {
  buf[0] = 0x00;
  buf[1] = 0x01;
  uint16_t result = getUShort(buf, littleEndian);
  EXPECT_EQ(result, 256);
}

// Test symmetric value where endianness doesn't matter
TEST_F(GetUShortTest_1136, SymmetricValue_1136) {
  buf[0] = 0xAA;
  buf[1] = 0xAA;
  EXPECT_EQ(getUShort(buf, bigEndian), getUShort(buf, littleEndian));
  EXPECT_EQ(getUShort(buf, bigEndian), 0xAAAA);
}

// Test that only first 2 bytes are used (buffer has more data)
TEST_F(GetUShortTest_1136, OnlyFirstTwoBytesUsed_1136) {
  buf[0] = 0x12;
  buf[1] = 0x34;
  buf[2] = 0x56;
  buf[3] = 0x78;
  uint16_t result = getUShort(buf, bigEndian);
  EXPECT_EQ(result, 0x1234);
}
