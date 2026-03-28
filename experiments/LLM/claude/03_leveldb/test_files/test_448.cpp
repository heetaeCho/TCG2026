#include "gtest/gtest.h"
#include <cstdint>
#include <cstring>
#include <vector>

namespace leveldb {
const char* GetVarint64Ptr(const char* p, const char* limit, uint64_t* value);
}

class GetVarint64PtrTest_448 : public ::testing::Test {
 protected:
  // Helper to encode a uint64_t as a varint into a buffer.
  // Returns the number of bytes written.
  static int EncodeVarint64(char* buf, uint64_t value) {
    int i = 0;
    while (value >= 128) {
      buf[i++] = static_cast<char>(value | 128);
      value >>= 7;
    }
    buf[i++] = static_cast<char>(value);
    return i;
  }
};

// Test decoding zero
TEST_F(GetVarint64PtrTest_448, DecodesZero_448) {
  char buf[10];
  int len = EncodeVarint64(buf, 0);
  uint64_t result = 0xDEAD;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, 0u);
  EXPECT_EQ(p, buf + len);
}

// Test decoding value 1
TEST_F(GetVarint64PtrTest_448, DecodesOne_448) {
  char buf[10];
  int len = EncodeVarint64(buf, 1);
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, 1u);
  EXPECT_EQ(p, buf + len);
}

// Test decoding 127 (max single-byte varint)
TEST_F(GetVarint64PtrTest_448, DecodesSingleByteMax_448) {
  char buf[10];
  int len = EncodeVarint64(buf, 127);
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, 127u);
  EXPECT_EQ(p, buf + 1);
}

// Test decoding 128 (requires two bytes)
TEST_F(GetVarint64PtrTest_448, DecodesTwoByteMin_448) {
  char buf[10];
  int len = EncodeVarint64(buf, 128);
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, 128u);
  EXPECT_EQ(p, buf + len);
}

// Test decoding a medium value
TEST_F(GetVarint64PtrTest_448, DecodesMediumValue_448) {
  char buf[10];
  uint64_t expected = 300;
  int len = EncodeVarint64(buf, expected);
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, expected);
}

// Test decoding UINT32_MAX
TEST_F(GetVarint64PtrTest_448, DecodesUint32Max_448) {
  char buf[10];
  uint64_t expected = UINT32_MAX;
  int len = EncodeVarint64(buf, expected);
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, expected);
}

// Test decoding a large 64-bit value
TEST_F(GetVarint64PtrTest_448, DecodesLargeValue_448) {
  char buf[10];
  uint64_t expected = (1ULL << 56) - 1;
  int len = EncodeVarint64(buf, expected);
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, expected);
}

// Test decoding UINT64_MAX
TEST_F(GetVarint64PtrTest_448, DecodesUint64Max_448) {
  char buf[10];
  uint64_t expected = UINT64_MAX;
  int len = EncodeVarint64(buf, expected);
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, expected);
}

// Test with empty range (p == limit) returns nullptr
TEST_F(GetVarint64PtrTest_448, EmptyRangeReturnsNull_448) {
  char buf[1] = {0};
  uint64_t result = 0xDEAD;
  const char* p = leveldb::GetVarint64Ptr(buf, buf, &result);
  EXPECT_EQ(p, nullptr);
}

// Test with truncated multi-byte varint returns nullptr
TEST_F(GetVarint64PtrTest_448, TruncatedVarintReturnsNull_448) {
  char buf[10];
  // Encode a value that needs 2 bytes, but only provide 1 byte to decode
  int len = EncodeVarint64(buf, 128);
  ASSERT_GE(len, 2);
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + 1, &result);
  EXPECT_EQ(p, nullptr);
}

// Test with all continuation bytes (no termination) returns nullptr
TEST_F(GetVarint64PtrTest_448, AllContinuationBytesReturnsNull_448) {
  // 10 bytes all with the high bit set (continuation), no terminator
  char buf[10];
  for (int i = 0; i < 10; i++) {
    buf[i] = static_cast<char>(0x80);
  }
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + 10, &result);
  EXPECT_EQ(p, nullptr);
}

// Test that only the varint bytes are consumed, not extra trailing bytes
TEST_F(GetVarint64PtrTest_448, DoesNotConsumeExtraBytes_448) {
  char buf[20];
  uint64_t expected = 12345;
  int len = EncodeVarint64(buf, expected);
  // Fill rest with garbage
  for (int i = len; i < 20; i++) {
    buf[i] = static_cast<char>(0xFF);
  }
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + 20, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, expected);
  EXPECT_EQ(p, buf + len);
}

// Test decoding multiple varints sequentially
TEST_F(GetVarint64PtrTest_448, DecodeMultipleSequential_448) {
  char buf[30];
  uint64_t values[] = {0, 1, 127, 128, 16383, 16384, UINT64_MAX};
  int offset = 0;
  for (auto v : values) {
    offset += EncodeVarint64(buf + offset, v);
  }

  const char* p = buf;
  const char* limit = buf + offset;
  for (auto expected : values) {
    uint64_t result = 0;
    p = leveldb::GetVarint64Ptr(p, limit, &result);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(result, expected);
  }
  EXPECT_EQ(p, limit);
}

// Test with single byte buffer containing value
TEST_F(GetVarint64PtrTest_448, SingleByteBuffer_448) {
  char buf[1] = {42};  // 42 < 128, so single byte varint
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + 1, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, 42u);
  EXPECT_EQ(p, buf + 1);
}

// Test power-of-two boundary values
TEST_F(GetVarint64PtrTest_448, PowerOfTwoBoundaries_448) {
  uint64_t test_values[] = {
    (1ULL << 7) - 1,   // 127
    (1ULL << 7),        // 128
    (1ULL << 14) - 1,   // 16383
    (1ULL << 14),       // 16384
    (1ULL << 21) - 1,
    (1ULL << 21),
    (1ULL << 28) - 1,
    (1ULL << 28),
    (1ULL << 35) - 1,
    (1ULL << 35),
    (1ULL << 42) - 1,
    (1ULL << 42),
    (1ULL << 49) - 1,
    (1ULL << 49),
    (1ULL << 56) - 1,
    (1ULL << 56),
    (1ULL << 63) - 1,
    (1ULL << 63),
  };

  for (uint64_t expected : test_values) {
    char buf[10];
    int len = EncodeVarint64(buf, expected);
    uint64_t result = 0;
    const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
    ASSERT_NE(p, nullptr) << "Failed for value: " << expected;
    EXPECT_EQ(result, expected) << "Failed for value: " << expected;
    EXPECT_EQ(p, buf + len) << "Failed for value: " << expected;
  }
}

// Test: exactly enough bytes for the varint, limit is tight
TEST_F(GetVarint64PtrTest_448, ExactLimitForMultiByteVarint_448) {
  char buf[10];
  uint64_t expected = 123456789ULL;
  int len = EncodeVarint64(buf, expected);
  uint64_t result = 0;
  // Limit is exactly at end of varint encoding
  const char* p = leveldb::GetVarint64Ptr(buf, buf + len, &result);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(result, expected);
}

// Test: severely truncated 10-byte varint (only provide 5 bytes)
TEST_F(GetVarint64PtrTest_448, SeverelyTruncatedVarint_448) {
  char buf[10];
  uint64_t val = UINT64_MAX;
  int len = EncodeVarint64(buf, val);
  ASSERT_EQ(len, 10);  // UINT64_MAX should take 10 bytes
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + 5, &result);
  EXPECT_EQ(p, nullptr);
}

// Test: overflow scenario - more than 10 continuation bytes
TEST_F(GetVarint64PtrTest_448, TooManyContinuationBytes_448) {
  // 11 continuation bytes followed by a terminator - shift would exceed 63
  char buf[12];
  for (int i = 0; i < 11; i++) {
    buf[i] = static_cast<char>(0x80 | (i + 1));
  }
  buf[11] = 0x01;  // terminator
  uint64_t result = 0;
  const char* p = leveldb::GetVarint64Ptr(buf, buf + 12, &result);
  // After shift > 63, the loop condition fails, returns nullptr
  EXPECT_EQ(p, nullptr);
}
