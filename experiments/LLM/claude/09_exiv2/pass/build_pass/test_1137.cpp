#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

// Include the necessary headers
#include "exiv2/types.hpp"

namespace Exiv2 {
uint32_t getULong(const byte* buf, ByteOrder byteOrder);
}

using namespace Exiv2;

class GetULongTest_1137 : public ::testing::Test {
 protected:
  byte buf[4];
};

// Test little-endian byte order with a known value
TEST_F(GetULongTest_1137, LittleEndianKnownValue_1137) {
  // Value: 0x04030201
  // In little-endian memory: 01 02 03 04
  buf[0] = 0x01;
  buf[1] = 0x02;
  buf[2] = 0x03;
  buf[3] = 0x04;
  uint32_t result = getULong(buf, littleEndian);
  EXPECT_EQ(result, 0x04030201u);
}

// Test big-endian byte order with a known value
TEST_F(GetULongTest_1137, BigEndianKnownValue_1137) {
  // Value: 0x01020304
  // In big-endian memory: 01 02 03 04
  buf[0] = 0x01;
  buf[1] = 0x02;
  buf[2] = 0x03;
  buf[3] = 0x04;
  uint32_t result = getULong(buf, bigEndian);
  EXPECT_EQ(result, 0x01020304u);
}

// Test little-endian with all zeros
TEST_F(GetULongTest_1137, LittleEndianAllZeros_1137) {
  memset(buf, 0, 4);
  uint32_t result = getULong(buf, littleEndian);
  EXPECT_EQ(result, 0u);
}

// Test big-endian with all zeros
TEST_F(GetULongTest_1137, BigEndianAllZeros_1137) {
  memset(buf, 0, 4);
  uint32_t result = getULong(buf, bigEndian);
  EXPECT_EQ(result, 0u);
}

// Test little-endian with all 0xFF bytes (max value)
TEST_F(GetULongTest_1137, LittleEndianMaxValue_1137) {
  memset(buf, 0xFF, 4);
  uint32_t result = getULong(buf, littleEndian);
  EXPECT_EQ(result, 0xFFFFFFFFu);
}

// Test big-endian with all 0xFF bytes (max value)
TEST_F(GetULongTest_1137, BigEndianMaxValue_1137) {
  memset(buf, 0xFF, 4);
  uint32_t result = getULong(buf, bigEndian);
  EXPECT_EQ(result, 0xFFFFFFFFu);
}

// Test little-endian with value 1 (only LSB set)
TEST_F(GetULongTest_1137, LittleEndianValueOne_1137) {
  buf[0] = 0x01;
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = 0x00;
  uint32_t result = getULong(buf, littleEndian);
  EXPECT_EQ(result, 1u);
}

// Test big-endian with value 1 (only LSB set)
TEST_F(GetULongTest_1137, BigEndianValueOne_1137) {
  buf[0] = 0x00;
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = 0x01;
  uint32_t result = getULong(buf, bigEndian);
  EXPECT_EQ(result, 1u);
}

// Test little-endian with only MSB set (0x80000000)
TEST_F(GetULongTest_1137, LittleEndianMSBSet_1137) {
  buf[0] = 0x00;
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = 0x80;
  uint32_t result = getULong(buf, littleEndian);
  EXPECT_EQ(result, 0x80000000u);
}

// Test big-endian with only MSB set (0x80000000)
TEST_F(GetULongTest_1137, BigEndianMSBSet_1137) {
  buf[0] = 0x80;
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = 0x00;
  uint32_t result = getULong(buf, bigEndian);
  EXPECT_EQ(result, 0x80000000u);
}

// Test that little-endian and big-endian produce the same result for a palindromic buffer
TEST_F(GetULongTest_1137, PalindromicBufferSameResult_1137) {
  buf[0] = 0xAB;
  buf[1] = 0xCD;
  buf[2] = 0xCD;
  buf[3] = 0xAB;
  uint32_t le_result = getULong(buf, littleEndian);
  uint32_t be_result = getULong(buf, bigEndian);
  EXPECT_EQ(le_result, be_result);
}

// Test that little-endian and big-endian produce byte-swapped results
TEST_F(GetULongTest_1137, LittleAndBigEndianAreByteSwapped_1137) {
  buf[0] = 0x12;
  buf[1] = 0x34;
  buf[2] = 0x56;
  buf[3] = 0x78;
  uint32_t le_result = getULong(buf, littleEndian);
  uint32_t be_result = getULong(buf, bigEndian);
  EXPECT_EQ(le_result, 0x78563412u);
  EXPECT_EQ(be_result, 0x12345678u);
}

// Test little-endian with value 256 (second byte set)
TEST_F(GetULongTest_1137, LittleEndianValue256_1137) {
  buf[0] = 0x00;
  buf[1] = 0x01;
  buf[2] = 0x00;
  buf[3] = 0x00;
  uint32_t result = getULong(buf, littleEndian);
  EXPECT_EQ(result, 256u);
}

// Test big-endian with value 256 (second byte set)
TEST_F(GetULongTest_1137, BigEndianValue256_1137) {
  buf[0] = 0x00;
  buf[1] = 0x00;
  buf[2] = 0x01;
  buf[3] = 0x00;
  uint32_t result = getULong(buf, bigEndian);
  EXPECT_EQ(result, 256u);
}

// Test little-endian with value 0x00010000 (third byte set)
TEST_F(GetULongTest_1137, LittleEndianThirdByteSet_1137) {
  buf[0] = 0x00;
  buf[1] = 0x00;
  buf[2] = 0x01;
  buf[3] = 0x00;
  uint32_t result = getULong(buf, littleEndian);
  EXPECT_EQ(result, 0x00010000u);
}

// Test big-endian with value 0x00010000 (third byte set)
TEST_F(GetULongTest_1137, BigEndianThirdByteSet_1137) {
  buf[0] = 0x00;
  buf[1] = 0x01;
  buf[2] = 0x00;
  buf[3] = 0x00;
  uint32_t result = getULong(buf, bigEndian);
  EXPECT_EQ(result, 0x00010000u);
}

// Test with a specific real-world-like value
TEST_F(GetULongTest_1137, LittleEndianSpecificValue_1137) {
  // Encode 0xDEADBEEF in little-endian
  buf[0] = 0xEF;
  buf[1] = 0xBE;
  buf[2] = 0xAD;
  buf[3] = 0xDE;
  uint32_t result = getULong(buf, littleEndian);
  EXPECT_EQ(result, 0xDEADBEEFu);
}

// Test with a specific real-world-like value in big-endian
TEST_F(GetULongTest_1137, BigEndianSpecificValue_1137) {
  // Encode 0xDEADBEEF in big-endian
  buf[0] = 0xDE;
  buf[1] = 0xAD;
  buf[2] = 0xBE;
  buf[3] = 0xEF;
  uint32_t result = getULong(buf, bigEndian);
  EXPECT_EQ(result, 0xDEADBEEFu);
}

// Test each byte position independently in little-endian
TEST_F(GetULongTest_1137, LittleEndianEachBytePosition_1137) {
  // Byte 0 only
  buf[0] = 0xAA; buf[1] = 0x00; buf[2] = 0x00; buf[3] = 0x00;
  EXPECT_EQ(getULong(buf, littleEndian), 0x000000AAu);

  // Byte 1 only
  buf[0] = 0x00; buf[1] = 0xBB; buf[2] = 0x00; buf[3] = 0x00;
  EXPECT_EQ(getULong(buf, littleEndian), 0x0000BB00u);

  // Byte 2 only
  buf[0] = 0x00; buf[1] = 0x00; buf[2] = 0xCC; buf[3] = 0x00;
  EXPECT_EQ(getULong(buf, littleEndian), 0x00CC0000u);

  // Byte 3 only
  buf[0] = 0x00; buf[1] = 0x00; buf[2] = 0x00; buf[3] = 0xDD;
  EXPECT_EQ(getULong(buf, littleEndian), 0xDD000000u);
}

// Test each byte position independently in big-endian
TEST_F(GetULongTest_1137, BigEndianEachBytePosition_1137) {
  // Byte 0 only
  buf[0] = 0xAA; buf[1] = 0x00; buf[2] = 0x00; buf[3] = 0x00;
  EXPECT_EQ(getULong(buf, bigEndian), 0xAA000000u);

  // Byte 1 only
  buf[0] = 0x00; buf[1] = 0xBB; buf[2] = 0x00; buf[3] = 0x00;
  EXPECT_EQ(getULong(buf, bigEndian), 0x00BB0000u);

  // Byte 2 only
  buf[0] = 0x00; buf[1] = 0x00; buf[2] = 0xCC; buf[3] = 0x00;
  EXPECT_EQ(getULong(buf, bigEndian), 0x0000CC00u);

  // Byte 3 only
  buf[0] = 0x00; buf[1] = 0x00; buf[2] = 0x00; buf[3] = 0xDD;
  EXPECT_EQ(getULong(buf, bigEndian), 0x000000DDu);
}
