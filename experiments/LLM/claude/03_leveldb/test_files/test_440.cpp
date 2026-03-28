#include "gtest/gtest.h"
#include <cstdint>
#include <cstring>

namespace leveldb {
char* EncodeVarint32(char* dst, uint32_t v);
}

class EncodeVarint32Test_440 : public ::testing::Test {
 protected:
  char buf_[10];  // More than enough for varint32 (max 5 bytes)

  void SetUp() override {
    memset(buf_, 0, sizeof(buf_));
  }
};

// Test encoding zero
TEST_F(EncodeVarint32Test_440, EncodesZero_440) {
  char* end = leveldb::EncodeVarint32(buf_, 0);
  ASSERT_EQ(end - buf_, 1);
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0);
}

// Test encoding value 1
TEST_F(EncodeVarint32Test_440, EncodesOne_440) {
  char* end = leveldb::EncodeVarint32(buf_, 1);
  ASSERT_EQ(end - buf_, 1);
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 1);
}

// Test maximum single-byte value (127 = 2^7 - 1)
TEST_F(EncodeVarint32Test_440, EncodesMaxSingleByte_440) {
  char* end = leveldb::EncodeVarint32(buf_, 127);
  ASSERT_EQ(end - buf_, 1);
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 127);
}

// Test minimum two-byte value (128 = 2^7)
TEST_F(EncodeVarint32Test_440, EncodesMinTwoBytes_440) {
  char* end = leveldb::EncodeVarint32(buf_, 128);
  ASSERT_EQ(end - buf_, 2);
  // 128 = 0x80 => byte0 = 0x80 | 0x80 = 0x80 (low 7 bits = 0, continuation bit set)
  // Wait, let me re-derive: v=128
  // v | B = 128 | 128 = 128 (0x80), then v>>7 = 1
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x01);
}

// Test maximum two-byte value (16383 = 2^14 - 1)
TEST_F(EncodeVarint32Test_440, EncodesMaxTwoBytes_440) {
  char* end = leveldb::EncodeVarint32(buf_, 16383);
  ASSERT_EQ(end - buf_, 2);
  // v = 16383 = 0x3FFF
  // byte0 = (0x3FFF | 0x80) & 0xFF = 0xFF
  // byte1 = 0x3FFF >> 7 = 127 = 0x7F
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x7F);
}

// Test minimum three-byte value (16384 = 2^14)
TEST_F(EncodeVarint32Test_440, EncodesMinThreeBytes_440) {
  char* end = leveldb::EncodeVarint32(buf_, 16384);
  ASSERT_EQ(end - buf_, 3);
  // v = 16384 = 0x4000
  // byte0 = (0x4000 | 0x80) & 0xFF = 0x80
  // byte1 = ((0x4000 >> 7) | 0x80) & 0xFF = (0x80 | 0x80) & 0xFF = 0x80
  // byte2 = 0x4000 >> 14 = 1
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0x01);
}

// Test maximum three-byte value (2097151 = 2^21 - 1)
TEST_F(EncodeVarint32Test_440, EncodesMaxThreeBytes_440) {
  char* end = leveldb::EncodeVarint32(buf_, 2097151);
  ASSERT_EQ(end - buf_, 3);
  // v = 2097151 = 0x1FFFFF
  // byte0 = (0x1FFFFF | 0x80) & 0xFF = 0xFF
  // byte1 = ((0x1FFFFF >> 7) | 0x80) & 0xFF = (0x3FFF | 0x80) & 0xFF = 0xFF
  // byte2 = 0x1FFFFF >> 14 = 0x7F = 127
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0x7F);
}

// Test minimum four-byte value (2097152 = 2^21)
TEST_F(EncodeVarint32Test_440, EncodesMinFourBytes_440) {
  char* end = leveldb::EncodeVarint32(buf_, 2097152);
  ASSERT_EQ(end - buf_, 4);
  // v = 2097152 = 0x200000
  // byte0 = (0x200000 | 0x80) & 0xFF = 0x80
  // byte1 = ((0x200000 >> 7) | 0x80) & 0xFF = (0x4000 | 0x80) & 0xFF = 0x80
  // byte2 = ((0x200000 >> 14) | 0x80) & 0xFF = (0x80 | 0x80) & 0xFF = 0x80
  // byte3 = 0x200000 >> 21 = 1
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[3]), 0x01);
}

// Test maximum four-byte value (268435455 = 2^28 - 1)
TEST_F(EncodeVarint32Test_440, EncodesMaxFourBytes_440) {
  char* end = leveldb::EncodeVarint32(buf_, 268435455);
  ASSERT_EQ(end - buf_, 4);
  // v = 268435455 = 0xFFFFFFF
  // byte0 = 0xFF, byte1 = 0xFF, byte2 = 0xFF, byte3 = 0x7F
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[3]), 0x7F);
}

// Test minimum five-byte value (268435456 = 2^28)
TEST_F(EncodeVarint32Test_440, EncodesMinFiveBytes_440) {
  char* end = leveldb::EncodeVarint32(buf_, 268435456);
  ASSERT_EQ(end - buf_, 5);
  // v = 268435456 = 0x10000000
  // byte0 = 0x80, byte1 = 0x80, byte2 = 0x80, byte3 = 0x80, byte4 = 0x01
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[3]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[4]), 0x01);
}

// Test maximum uint32_t value (4294967295 = 2^32 - 1)
TEST_F(EncodeVarint32Test_440, EncodesMaxUint32_440) {
  char* end = leveldb::EncodeVarint32(buf_, 0xFFFFFFFF);
  ASSERT_EQ(end - buf_, 5);
  // v = 0xFFFFFFFF
  // byte0 = 0xFF, byte1 = 0xFF, byte2 = 0xFF, byte3 = 0xFF
  // byte4 = 0xFFFFFFFF >> 28 = 0xF = 15
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[3]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[4]), 0x0F);
}

// Test a typical small value
TEST_F(EncodeVarint32Test_440, EncodesTypicalSmallValue_440) {
  char* end = leveldb::EncodeVarint32(buf_, 42);
  ASSERT_EQ(end - buf_, 1);
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 42);
}

// Test a value in the middle of the two-byte range
TEST_F(EncodeVarint32Test_440, EncodesMidTwoByteValue_440) {
  // 300 = 0x12C
  char* end = leveldb::EncodeVarint32(buf_, 300);
  ASSERT_EQ(end - buf_, 2);
  // byte0 = (300 | 128) & 0xFF = (0x12C | 0x80) & 0xFF = 0xAC
  // byte1 = 300 >> 7 = 2
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0xAC);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x02);
}

// Test that the function returns a pointer past the written bytes
TEST_F(EncodeVarint32Test_440, ReturnsPtrPastWrittenBytes_440) {
  // For a 1-byte encoding
  char* end1 = leveldb::EncodeVarint32(buf_, 50);
  EXPECT_EQ(end1, buf_ + 1);

  // For a 5-byte encoding
  char* end5 = leveldb::EncodeVarint32(buf_, 0xFFFFFFFF);
  EXPECT_EQ(end5, buf_ + 5);
}

// Test boundary at exactly 2^7 - 1 and 2^7
TEST_F(EncodeVarint32Test_440, BoundaryOneToTwoBytes_440) {
  char* end1 = leveldb::EncodeVarint32(buf_, (1 << 7) - 1);
  EXPECT_EQ(end1 - buf_, 1);

  char* end2 = leveldb::EncodeVarint32(buf_, (1 << 7));
  EXPECT_EQ(end2 - buf_, 2);
}

// Test boundary at exactly 2^14 - 1 and 2^14
TEST_F(EncodeVarint32Test_440, BoundaryTwoToThreeBytes_440) {
  char* end2 = leveldb::EncodeVarint32(buf_, (1 << 14) - 1);
  EXPECT_EQ(end2 - buf_, 2);

  char* end3 = leveldb::EncodeVarint32(buf_, (1 << 14));
  EXPECT_EQ(end3 - buf_, 3);
}

// Test boundary at exactly 2^21 - 1 and 2^21
TEST_F(EncodeVarint32Test_440, BoundaryThreeToFourBytes_440) {
  char* end3 = leveldb::EncodeVarint32(buf_, (1 << 21) - 1);
  EXPECT_EQ(end3 - buf_, 3);

  char* end4 = leveldb::EncodeVarint32(buf_, (1 << 21));
  EXPECT_EQ(end4 - buf_, 4);
}

// Test boundary at exactly 2^28 - 1 and 2^28
TEST_F(EncodeVarint32Test_440, BoundaryFourToFiveBytes_440) {
  char* end4 = leveldb::EncodeVarint32(buf_, (1 << 28) - 1);
  EXPECT_EQ(end4 - buf_, 4);

  char* end5 = leveldb::EncodeVarint32(buf_, (1 << 28));
  EXPECT_EQ(end5 - buf_, 5);
}

// Test that encoding doesn't write beyond the expected number of bytes
TEST_F(EncodeVarint32Test_440, DoesNotOverwrite_440) {
  // Fill buffer with sentinel
  memset(buf_, 0xAA, sizeof(buf_));

  // Encode a 2-byte value
  leveldb::EncodeVarint32(buf_, 300);

  // Bytes beyond the 2nd should remain untouched
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0xAA);
  EXPECT_EQ(static_cast<uint8_t>(buf_[3]), 0xAA);
  EXPECT_EQ(static_cast<uint8_t>(buf_[4]), 0xAA);
}

// Test encoding a large 5-byte value (not max)
TEST_F(EncodeVarint32Test_440, EncodesLargeFiveByteValue_440) {
  uint32_t v = 0x80000000;  // 2^31
  char* end = leveldb::EncodeVarint32(buf_, v);
  ASSERT_EQ(end - buf_, 5);
  // byte0 = (v | 0x80) & 0xFF = 0x80
  // byte1 = ((v >> 7) | 0x80) & 0xFF = (0x1000000 | 0x80) & 0xFF = 0x80
  // byte2 = ((v >> 14) | 0x80) & 0xFF = (0x20000 | 0x80) & 0xFF = 0x80
  // byte3 = ((v >> 21) | 0x80) & 0xFF = (0x400 | 0x80) & 0xFF = 0x80
  // byte4 = v >> 28 = 0x8
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[3]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[4]), 0x08);
}
