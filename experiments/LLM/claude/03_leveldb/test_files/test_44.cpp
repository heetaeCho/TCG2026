#include "util/coding.h"

#include <cstring>
#include <string>

#include "gtest/gtest.h"

namespace leveldb {

TEST(DecodeFixed32Test_44, DecodesZero_44) {
  char buf[4] = {0, 0, 0, 0};
  EXPECT_EQ(0u, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesOne_44) {
  char buf[4] = {1, 0, 0, 0};
  EXPECT_EQ(1u, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesMaxUint32_44) {
  char buf[4];
  buf[0] = static_cast<char>(0xFF);
  buf[1] = static_cast<char>(0xFF);
  buf[2] = static_cast<char>(0xFF);
  buf[3] = static_cast<char>(0xFF);
  EXPECT_EQ(0xFFFFFFFFu, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesLittleEndianOrder_44) {
  // Encode 0x04030201 in little-endian: bytes are 0x01, 0x02, 0x03, 0x04
  char buf[4];
  buf[0] = 0x01;
  buf[1] = 0x02;
  buf[2] = 0x03;
  buf[3] = 0x04;
  EXPECT_EQ(0x04030201u, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesKnownValue_44) {
  // Value: 256 = 0x00000100 -> little-endian: 0x00, 0x01, 0x00, 0x00
  char buf[4] = {0x00, 0x01, 0x00, 0x00};
  EXPECT_EQ(256u, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesHighBitSet_44) {
  // Value: 0x80000000 -> little-endian: 0x00, 0x00, 0x00, 0x80
  char buf[4];
  buf[0] = 0x00;
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = static_cast<char>(0x80);
  EXPECT_EQ(0x80000000u, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesOnlyFirstByte_44) {
  // Value: 0x000000AB -> little-endian: 0xAB, 0x00, 0x00, 0x00
  char buf[4];
  buf[0] = static_cast<char>(0xAB);
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = 0x00;
  EXPECT_EQ(0xABu, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesOnlySecondByte_44) {
  // Value: 0x0000CD00 -> little-endian: 0x00, 0xCD, 0x00, 0x00
  char buf[4];
  buf[0] = 0x00;
  buf[1] = static_cast<char>(0xCD);
  buf[2] = 0x00;
  buf[3] = 0x00;
  EXPECT_EQ(0x0000CD00u, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesOnlyThirdByte_44) {
  // Value: 0x00EF0000 -> little-endian: 0x00, 0x00, 0xEF, 0x00
  char buf[4];
  buf[0] = 0x00;
  buf[1] = 0x00;
  buf[2] = static_cast<char>(0xEF);
  buf[3] = 0x00;
  EXPECT_EQ(0x00EF0000u, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesOnlyFourthByte_44) {
  // Value: 0x12000000 -> little-endian: 0x00, 0x00, 0x00, 0x12
  char buf[4];
  buf[0] = 0x00;
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = 0x12;
  EXPECT_EQ(0x12000000u, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesFromMiddleOfBuffer_44) {
  // Make sure it works when pointer is not at the start of an array
  char buf[8] = {0x00, 0x00, 0x78, 0x56, 0x34, 0x12, 0x00, 0x00};
  // Decode from offset 2: bytes 0x78, 0x56, 0x34, 0x12 -> 0x12345678
  EXPECT_EQ(0x12345678u, DecodeFixed32(buf + 2));
}

TEST(DecodeFixed32Test_44, DecodesArbitraryValue_44) {
  // Value: 0xDEADBEEF -> little-endian: 0xEF, 0xBE, 0xAD, 0xDE
  char buf[4];
  buf[0] = static_cast<char>(0xEF);
  buf[1] = static_cast<char>(0xBE);
  buf[2] = static_cast<char>(0xAD);
  buf[3] = static_cast<char>(0xDE);
  EXPECT_EQ(0xDEADBEEFu, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, DecodesPowerOfTwo_44) {
  // Value: 65536 = 0x00010000 -> little-endian: 0x00, 0x00, 0x01, 0x00
  char buf[4] = {0x00, 0x00, 0x01, 0x00};
  EXPECT_EQ(65536u, DecodeFixed32(buf));
}

TEST(DecodeFixed32Test_44, ConsistencyRoundTrip_44) {
  // Manually encode a value in little-endian and verify decode
  uint32_t value = 0x1A2B3C4D;
  char buf[4];
  buf[0] = static_cast<char>(value & 0xFF);
  buf[1] = static_cast<char>((value >> 8) & 0xFF);
  buf[2] = static_cast<char>((value >> 16) & 0xFF);
  buf[3] = static_cast<char>((value >> 24) & 0xFF);
  EXPECT_EQ(value, DecodeFixed32(buf));
}

}  // namespace leveldb
