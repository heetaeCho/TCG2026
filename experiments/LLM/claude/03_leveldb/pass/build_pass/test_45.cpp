#include "util/coding.h"

#include <cstring>
#include <string>

#include "gtest/gtest.h"

namespace leveldb {

class DecodeFixed64Test_45 : public ::testing::Test {};

TEST_F(DecodeFixed64Test_45, DecodesZero_45) {
  char buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  EXPECT_EQ(0ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesOne_45) {
  char buf[8] = {1, 0, 0, 0, 0, 0, 0, 0};
  EXPECT_EQ(1ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesMaxUint64_45) {
  char buf[8];
  std::memset(buf, 0xFF, 8);
  EXPECT_EQ(0xFFFFFFFFFFFFFFFFULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesLittleEndianOrder_45) {
  // Encode 0x0807060504030201 in little-endian
  char buf[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  EXPECT_EQ(0x0807060504030201ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesHighBitSet_45) {
  // 0x80 in the most significant byte (byte index 7)
  char buf[8] = {0, 0, 0, 0, 0, 0, 0, static_cast<char>(0x80)};
  EXPECT_EQ(0x8000000000000000ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesSingleByteValues_45) {
  // Only byte 0 set to 0xFF
  char buf[8] = {static_cast<char>(0xFF), 0, 0, 0, 0, 0, 0, 0};
  EXPECT_EQ(0xFFULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesSecondByte_45) {
  char buf[8] = {0, static_cast<char>(0xFF), 0, 0, 0, 0, 0, 0};
  EXPECT_EQ(0xFF00ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesThirdByte_45) {
  char buf[8] = {0, 0, static_cast<char>(0xFF), 0, 0, 0, 0, 0};
  EXPECT_EQ(0xFF0000ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesFourthByte_45) {
  char buf[8] = {0, 0, 0, static_cast<char>(0xFF), 0, 0, 0, 0};
  EXPECT_EQ(0xFF000000ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesFifthByte_45) {
  char buf[8] = {0, 0, 0, 0, static_cast<char>(0xFF), 0, 0, 0};
  EXPECT_EQ(0xFF00000000ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesSixthByte_45) {
  char buf[8] = {0, 0, 0, 0, 0, static_cast<char>(0xFF), 0, 0};
  EXPECT_EQ(0xFF0000000000ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesSeventhByte_45) {
  char buf[8] = {0, 0, 0, 0, 0, 0, static_cast<char>(0xFF), 0};
  EXPECT_EQ(0xFF000000000000ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesEighthByte_45) {
  char buf[8] = {0, 0, 0, 0, 0, 0, 0, static_cast<char>(0xFF)};
  EXPECT_EQ(0xFF00000000000000ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesKnownValue_45) {
  // Encode value 0x0000000100000000 (2^32) in little endian
  // That's byte 4 = 1, rest 0
  char buf[8] = {0, 0, 0, 0, 1, 0, 0, 0};
  EXPECT_EQ(0x100000000ULL, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesArbitraryValue_45) {
  // Value: 0xDEADBEEFCAFEBABE in little endian
  uint64_t expected = 0xDEADBEEFCAFEBABEULL;
  char buf[8];
  buf[0] = static_cast<char>(expected & 0xFF);
  buf[1] = static_cast<char>((expected >> 8) & 0xFF);
  buf[2] = static_cast<char>((expected >> 16) & 0xFF);
  buf[3] = static_cast<char>((expected >> 24) & 0xFF);
  buf[4] = static_cast<char>((expected >> 32) & 0xFF);
  buf[5] = static_cast<char>((expected >> 40) & 0xFF);
  buf[6] = static_cast<char>((expected >> 48) & 0xFF);
  buf[7] = static_cast<char>((expected >> 56) & 0xFF);
  EXPECT_EQ(expected, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesFromMiddleOfBuffer_45) {
  char buf[16] = {};
  // Place a known value at offset 4
  uint64_t expected = 0x123456789ABCDEF0ULL;
  buf[4] = static_cast<char>(expected & 0xFF);
  buf[5] = static_cast<char>((expected >> 8) & 0xFF);
  buf[6] = static_cast<char>((expected >> 16) & 0xFF);
  buf[7] = static_cast<char>((expected >> 24) & 0xFF);
  buf[8] = static_cast<char>((expected >> 32) & 0xFF);
  buf[9] = static_cast<char>((expected >> 40) & 0xFF);
  buf[10] = static_cast<char>((expected >> 48) & 0xFF);
  buf[11] = static_cast<char>((expected >> 56) & 0xFF);
  EXPECT_EQ(expected, DecodeFixed64(buf + 4));
}

TEST_F(DecodeFixed64Test_45, DecodesAlternatingBits_45) {
  // 0xAAAAAAAAAAAAAAAA in little endian
  uint64_t expected = 0xAAAAAAAAAAAAAAAAULL;
  char buf[8];
  for (int i = 0; i < 8; i++) {
    buf[i] = static_cast<char>(0xAA);
  }
  EXPECT_EQ(expected, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, DecodesAlternatingBits2_45) {
  // 0x5555555555555555 in little endian
  uint64_t expected = 0x5555555555555555ULL;
  char buf[8];
  for (int i = 0; i < 8; i++) {
    buf[i] = static_cast<char>(0x55);
  }
  EXPECT_EQ(expected, DecodeFixed64(buf));
}

TEST_F(DecodeFixed64Test_45, ConsistentMultipleCalls_45) {
  char buf[8] = {0x12, 0x34, 0x56, 0x78,
                 static_cast<char>(0x9A), static_cast<char>(0xBC),
                 static_cast<char>(0xDE), static_cast<char>(0xF0)};
  uint64_t first = DecodeFixed64(buf);
  uint64_t second = DecodeFixed64(buf);
  EXPECT_EQ(first, second);
}

}  // namespace leveldb
