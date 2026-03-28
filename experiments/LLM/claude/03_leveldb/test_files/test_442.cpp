#include "gtest/gtest.h"
#include <cstdint>
#include <cstring>

namespace leveldb {
char* EncodeVarint64(char* dst, uint64_t v);
}

class EncodeVarint64Test_442 : public ::testing::Test {
 protected:
  char buf_[16];  // Large enough for any varint64

  void SetUp() override {
    std::memset(buf_, 0, sizeof(buf_));
  }

  int EncodedLength(uint64_t v) {
    char* end = leveldb::EncodeVarint64(buf_, v);
    return static_cast<int>(end - buf_);
  }
};

// Test encoding zero — should produce a single byte with value 0
TEST_F(EncodeVarint64Test_442, EncodesZero_442) {
  char* end = leveldb::EncodeVarint64(buf_, 0);
  ASSERT_EQ(end - buf_, 1);
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x00);
}

// Test encoding value 1 — single byte
TEST_F(EncodeVarint64Test_442, EncodesOne_442) {
  char* end = leveldb::EncodeVarint64(buf_, 1);
  ASSERT_EQ(end - buf_, 1);
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x01);
}

// Test encoding 127 (max value that fits in one byte)
TEST_F(EncodeVarint64Test_442, Encodes127_442) {
  char* end = leveldb::EncodeVarint64(buf_, 127);
  ASSERT_EQ(end - buf_, 1);
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x7F);
}

// Test encoding 128 — requires two bytes
TEST_F(EncodeVarint64Test_442, Encodes128_442) {
  char* end = leveldb::EncodeVarint64(buf_, 128);
  ASSERT_EQ(end - buf_, 2);
  // 128 = 0b10000000 -> first byte: 0x80 | 0x00 = 0x80, second byte: 0x01
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x01);
}

// Test encoding 300 — requires two bytes
TEST_F(EncodeVarint64Test_442, Encodes300_442) {
  char* end = leveldb::EncodeVarint64(buf_, 300);
  ASSERT_EQ(end - buf_, 2);
  // 300 = 0b100101100 -> low 7 bits: 0b0101100 = 0x2C, with continuation: 0xAC
  // remaining: 0b10 = 0x02
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0xAC);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x02);
}

// Test encoding a value that requires exactly 3 bytes
TEST_F(EncodeVarint64Test_442, EncodesThreeBytes_442) {
  // 2^14 = 16384 requires 3 bytes
  uint64_t v = 16384;
  char* end = leveldb::EncodeVarint64(buf_, v);
  ASSERT_EQ(end - buf_, 3);
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0x80);
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0x01);
}

// Test encoding UINT32_MAX
TEST_F(EncodeVarint64Test_442, EncodesUint32Max_442) {
  uint64_t v = UINT32_MAX;
  char* end = leveldb::EncodeVarint64(buf_, v);
  // 2^32 - 1 = 4294967295, needs 5 bytes in varint encoding
  ASSERT_EQ(end - buf_, 5);
  EXPECT_EQ(static_cast<uint8_t>(buf_[0]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[1]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[2]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[3]), 0xFF);
  EXPECT_EQ(static_cast<uint8_t>(buf_[4]), 0x0F);
}

// Test encoding UINT64_MAX — should require 10 bytes
TEST_F(EncodeVarint64Test_442, EncodesUint64Max_442) {
  uint64_t v = UINT64_MAX;
  char* end = leveldb::EncodeVarint64(buf_, v);
  // UINT64_MAX needs 10 bytes in varint encoding
  ASSERT_EQ(end - buf_, 10);
  // First 9 bytes should all have continuation bit set (0xFF)
  for (int i = 0; i < 9; i++) {
    EXPECT_EQ(static_cast<uint8_t>(buf_[i]), 0xFF);
  }
  // Last byte: remaining bit is 1
  EXPECT_EQ(static_cast<uint8_t>(buf_[9]), 0x01);
}

// Test encoding powers of two to verify byte boundaries
TEST_F(EncodeVarint64Test_442, EncodesPowersOfTwo_442) {
  // 2^7 = 128: 2 bytes
  EXPECT_EQ(EncodedLength(1ULL << 7), 2);
  // 2^14 = 16384: 3 bytes
  EXPECT_EQ(EncodedLength(1ULL << 14), 3);
  // 2^21: 4 bytes
  EXPECT_EQ(EncodedLength(1ULL << 21), 4);
  // 2^28: 5 bytes
  EXPECT_EQ(EncodedLength(1ULL << 28), 5);
  // 2^35: 6 bytes
  EXPECT_EQ(EncodedLength(1ULL << 35), 6);
  // 2^42: 7 bytes
  EXPECT_EQ(EncodedLength(1ULL << 42), 7);
  // 2^49: 8 bytes
  EXPECT_EQ(EncodedLength(1ULL << 49), 8);
  // 2^56: 9 bytes
  EXPECT_EQ(EncodedLength(1ULL << 56), 9);
  // 2^63: 10 bytes
  EXPECT_EQ(EncodedLength(1ULL << 63), 10);
}

// Test boundary: max value fitting in 1 byte vs min value needing 2 bytes
TEST_F(EncodeVarint64Test_442, BoundaryOneToTwoBytes_442) {
  EXPECT_EQ(EncodedLength(127), 1);
  EXPECT_EQ(EncodedLength(128), 2);
}

// Test boundary: max value fitting in 2 bytes vs min value needing 3 bytes
TEST_F(EncodeVarint64Test_442, BoundaryTwoToThreeBytes_442) {
  EXPECT_EQ(EncodedLength((1ULL << 14) - 1), 2);
  EXPECT_EQ(EncodedLength(1ULL << 14), 3);
}

// Test encoding a specific large 64-bit value
TEST_F(EncodeVarint64Test_442, EncodesLarge64BitValue_442) {
  uint64_t v = 0x123456789ABCDEF0ULL;
  char* end = leveldb::EncodeVarint64(buf_, v);
  // This is a large value; verify it uses the expected number of bytes
  int len = static_cast<int>(end - buf_);
  EXPECT_GT(len, 0);
  EXPECT_LE(len, 10);

  // All bytes except the last should have the high bit set
  for (int i = 0; i < len - 1; i++) {
    EXPECT_NE(static_cast<uint8_t>(buf_[i]) & 0x80, 0)
        << "Byte " << i << " should have continuation bit set";
  }
  // Last byte should NOT have the high bit set
  EXPECT_EQ(static_cast<uint8_t>(buf_[len - 1]) & 0x80, 0)
      << "Last byte should not have continuation bit set";
}

// Verify the encoding can be decoded back (manual decode)
TEST_F(EncodeVarint64Test_442, RoundTripSmallValues_442) {
  for (uint64_t v = 0; v < 1024; v++) {
    std::memset(buf_, 0, sizeof(buf_));
    char* end = leveldb::EncodeVarint64(buf_, v);
    int len = static_cast<int>(end - buf_);

    // Manual decode
    uint64_t decoded = 0;
    int shift = 0;
    for (int i = 0; i < len; i++) {
      uint8_t byte = static_cast<uint8_t>(buf_[i]);
      decoded |= (static_cast<uint64_t>(byte & 0x7F)) << shift;
      shift += 7;
    }
    EXPECT_EQ(decoded, v) << "Round-trip failed for value " << v;
  }
}

// Verify round-trip for specific large values
TEST_F(EncodeVarint64Test_442, RoundTripLargeValues_442) {
  uint64_t test_values[] = {
    0, 1, 127, 128, 255, 256, 16383, 16384,
    UINT32_MAX, static_cast<uint64_t>(UINT32_MAX) + 1,
    UINT64_MAX, UINT64_MAX - 1,
    0x7FFFFFFFFFFFFFFFULL, 0x8000000000000000ULL,
    0x0102030405060708ULL
  };

  for (uint64_t v : test_values) {
    std::memset(buf_, 0, sizeof(buf_));
    char* end = leveldb::EncodeVarint64(buf_, v);
    int len = static_cast<int>(end - buf_);

    // Manual decode
    uint64_t decoded = 0;
    int shift = 0;
    for (int i = 0; i < len; i++) {
      uint8_t byte = static_cast<uint8_t>(buf_[i]);
      decoded |= (static_cast<uint64_t>(byte & 0x7F)) << shift;
      shift += 7;
    }
    EXPECT_EQ(decoded, v) << "Round-trip failed for value " << v;
  }
}

// Test that the returned pointer is valid (not null, and past the start)
TEST_F(EncodeVarint64Test_442, ReturnedPointerIsValid_442) {
  char* end = leveldb::EncodeVarint64(buf_, 42);
  EXPECT_NE(end, nullptr);
  EXPECT_GT(end, buf_);
  EXPECT_LE(end, buf_ + 10);
}
