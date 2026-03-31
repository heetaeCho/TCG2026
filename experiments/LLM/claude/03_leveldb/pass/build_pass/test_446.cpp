#include "gtest/gtest.h"
#include "util/coding.h"

#include <string>
#include <cstring>

namespace leveldb {

// Tests for GetVarint32PtrFallback
class GetVarint32PtrFallbackTest_446 : public ::testing::Test {
 protected:
  uint32_t value_;

  void SetUp() override { value_ = 0; }
};

// Test: Single-byte varint (value 0)
TEST_F(GetVarint32PtrFallbackTest_446, SingleByteZero_446) {
  const char data[] = {0x00};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 0u);
  EXPECT_EQ(result, data + 1);
}

// Test: Single-byte varint (value 1)
TEST_F(GetVarint32PtrFallbackTest_446, SingleByteOne_446) {
  const char data[] = {0x01};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 1u);
  EXPECT_EQ(result, data + 1);
}

// Test: Single-byte varint (max single byte = 127)
TEST_F(GetVarint32PtrFallbackTest_446, SingleByteMax_446) {
  const char data[] = {0x7F};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 127u);
  EXPECT_EQ(result, data + 1);
}

// Test: Two-byte varint (value 128)
TEST_F(GetVarint32PtrFallbackTest_446, TwoByte128_446) {
  // 128 = 0x80 -> varint encoding: 0x80, 0x01
  const char data[] = {static_cast<char>(0x80), 0x01};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 128u);
  EXPECT_EQ(result, data + 2);
}

// Test: Two-byte varint (value 300)
TEST_F(GetVarint32PtrFallbackTest_446, TwoByte300_446) {
  // 300 = 0x12C -> varint: 0xAC, 0x02
  const char data[] = {static_cast<char>(0xAC), 0x02};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 300u);
  EXPECT_EQ(result, data + 2);
}

// Test: Three-byte varint (value 16384)
TEST_F(GetVarint32PtrFallbackTest_446, ThreeByte16384_446) {
  // 16384 = 0x4000 -> varint: 0x80, 0x80, 0x01
  const char data[] = {static_cast<char>(0x80), static_cast<char>(0x80), 0x01};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 16384u);
  EXPECT_EQ(result, data + 3);
}

// Test: Four-byte varint (value 2097152)
TEST_F(GetVarint32PtrFallbackTest_446, FourByte2097152_446) {
  // 2097152 = 0x200000 -> varint: 0x80, 0x80, 0x80, 0x01
  const char data[] = {static_cast<char>(0x80), static_cast<char>(0x80),
                       static_cast<char>(0x80), 0x01};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 2097152u);
  EXPECT_EQ(result, data + 4);
}

// Test: Five-byte varint (value 268435456)
TEST_F(GetVarint32PtrFallbackTest_446, FiveByte268435456_446) {
  // 268435456 = 0x10000000 -> varint: 0x80, 0x80, 0x80, 0x80, 0x01
  const char data[] = {static_cast<char>(0x80), static_cast<char>(0x80),
                       static_cast<char>(0x80), static_cast<char>(0x80), 0x01};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 268435456u);
  EXPECT_EQ(result, data + 5);
}

// Test: Max uint32 value (4294967295)
TEST_F(GetVarint32PtrFallbackTest_446, FiveByteMaxUint32_446) {
  // 4294967295 = 0xFFFFFFFF -> varint: 0xFF, 0xFF, 0xFF, 0xFF, 0x0F
  const char data[] = {static_cast<char>(0xFF), static_cast<char>(0xFF),
                       static_cast<char>(0xFF), static_cast<char>(0xFF), 0x0F};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 4294967295u);
  EXPECT_EQ(result, data + 5);
}

// Test: Empty input (p == limit) returns nullptr
TEST_F(GetVarint32PtrFallbackTest_446, EmptyInput_446) {
  const char data[] = {0x00};
  const char* result = GetVarint32PtrFallback(data, data, &value_);
  EXPECT_EQ(result, nullptr);
}

// Test: Truncated varint (continuation bit set but no more bytes)
TEST_F(GetVarint32PtrFallbackTest_446, TruncatedVarintOneByte_446) {
  const char data[] = {static_cast<char>(0x80)};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  EXPECT_EQ(result, nullptr);
}

// Test: Truncated varint (two bytes with continuation, missing third)
TEST_F(GetVarint32PtrFallbackTest_446, TruncatedVarintTwoBytes_446) {
  const char data[] = {static_cast<char>(0x80), static_cast<char>(0x80)};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  EXPECT_EQ(result, nullptr);
}

// Test: Truncated varint (three continuation bytes, missing fourth)
TEST_F(GetVarint32PtrFallbackTest_446, TruncatedVarintThreeBytes_446) {
  const char data[] = {static_cast<char>(0x80), static_cast<char>(0x80),
                       static_cast<char>(0x80)};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  EXPECT_EQ(result, nullptr);
}

// Test: Truncated varint (four continuation bytes, missing fifth)
TEST_F(GetVarint32PtrFallbackTest_446, TruncatedVarintFourBytes_446) {
  const char data[] = {static_cast<char>(0x80), static_cast<char>(0x80),
                       static_cast<char>(0x80), static_cast<char>(0x80)};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  EXPECT_EQ(result, nullptr);
}

// Test: Too many continuation bytes (more than 5 bytes all with continuation bit)
TEST_F(GetVarint32PtrFallbackTest_446, TooManyContinuationBytes_446) {
  // All 6 bytes have continuation bits set. The loop only goes up to shift=28
  // (5 iterations), so the 6th byte is never read, and the function should
  // return nullptr since all 5 processed bytes had continuation bits.
  const char data[] = {static_cast<char>(0x80), static_cast<char>(0x80),
                       static_cast<char>(0x80), static_cast<char>(0x80),
                       static_cast<char>(0x80), static_cast<char>(0x80)};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  EXPECT_EQ(result, nullptr);
}

// Test: Varint with extra data after it (pointer advances correctly)
TEST_F(GetVarint32PtrFallbackTest_446, ExtraDataAfterVarint_446) {
  // Value 42 (single byte: 0x2A), followed by extra bytes
  const char data[] = {0x2A, 0x55, 0x66};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 42u);
  EXPECT_EQ(result, data + 1);
}

// Test: Two-byte varint with extra data
TEST_F(GetVarint32PtrFallbackTest_446, TwoByteWithExtraData_446) {
  // Value 150: varint 0x96, 0x01
  const char data[] = {static_cast<char>(0x96), 0x01, 0x42, 0x43};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 150u);
  EXPECT_EQ(result, data + 2);
}

// Test: Limit is exactly at the terminating byte
TEST_F(GetVarint32PtrFallbackTest_446, LimitExactlyAtEnd_446) {
  // Two-byte varint: 0x80, 0x01 = 128
  const char data[] = {static_cast<char>(0x80), 0x01};
  const char* result =
      GetVarint32PtrFallback(data, data + 2, &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 128u);
}

// Test: Limit cuts off before terminating byte
TEST_F(GetVarint32PtrFallbackTest_446, LimitCutsOffBeforeEnd_446) {
  // Two-byte varint: 0x80, 0x01 = 128, but limit at 1
  const char data[] = {static_cast<char>(0x80), 0x01};
  const char* result =
      GetVarint32PtrFallback(data, data + 1, &value_);
  EXPECT_EQ(result, nullptr);
}

// Test: Encoding of value 16383 (max two-byte varint)
TEST_F(GetVarint32PtrFallbackTest_446, TwoByteMax16383_446) {
  // 16383 = 0x3FFF -> varint: 0xFF, 0x7F
  const char data[] = {static_cast<char>(0xFF), 0x7F};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 16383u);
  EXPECT_EQ(result, data + 2);
}

// Test: Encoding of value 2097151 (max three-byte varint)
TEST_F(GetVarint32PtrFallbackTest_446, ThreeByteMax2097151_446) {
  // 2097151 = 0x1FFFFF -> varint: 0xFF, 0xFF, 0x7F
  const char data[] = {static_cast<char>(0xFF), static_cast<char>(0xFF), 0x7F};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 2097151u);
  EXPECT_EQ(result, data + 3);
}

// Test: Encoding of value 268435455 (max four-byte varint)
TEST_F(GetVarint32PtrFallbackTest_446, FourByteMax268435455_446) {
  // 268435455 = 0xFFFFFFF -> varint: 0xFF, 0xFF, 0xFF, 0x7F
  const char data[] = {static_cast<char>(0xFF), static_cast<char>(0xFF),
                       static_cast<char>(0xFF), 0x7F};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 268435455u);
  EXPECT_EQ(result, data + 4);
}

// Test using PutVarint32 and GetVarint32Ptr together (integration)
TEST_F(GetVarint32PtrFallbackTest_446, RoundTripWithPutVarint32_446) {
  std::string dst;
  PutVarint32(&dst, 12345u);
  const char* p = dst.data();
  const char* limit = p + dst.size();
  // The first byte should have continuation bit set (12345 > 127)
  // so GetVarint32PtrFallback should be called.
  const char* result = GetVarint32PtrFallback(p, limit, &value_);
  // For values >= 128, GetVarint32Ptr calls GetVarint32PtrFallback.
  // Let's just use GetVarint32Ptr directly to verify the encoding.
  uint32_t value2 = 0;
  const char* result2 = GetVarint32Ptr(p, limit, &value2);
  ASSERT_NE(result2, nullptr);
  EXPECT_EQ(value2, 12345u);
}

// Test: Various known values through encoding/decoding
TEST_F(GetVarint32PtrFallbackTest_446, KnownValueVariousSmall_446) {
  // Value 127 is single byte, not actually passed through Fallback in normal
  // use, but let's test the function directly
  const char data[] = {0x7F};
  const char* result =
      GetVarint32PtrFallback(data, data + sizeof(data), &value_);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value_, 127u);
}

// Tests using the higher-level Varint32 encode/decode functions
class CodingVarint32Test_446 : public ::testing::Test {};

TEST_F(CodingVarint32Test_446, EncodeDecodeSmallValues_446) {
  for (uint32_t v = 0; v < 256; v++) {
    std::string dst;
    PutVarint32(&dst, v);
    Slice input(dst);
    uint32_t decoded = 0;
    ASSERT_TRUE(GetVarint32(&input, &decoded));
    EXPECT_EQ(decoded, v);
  }
}

TEST_F(CodingVarint32Test_446, EncodeDecodeLargeValues_446) {
  std::vector<uint32_t> values = {0, 1, 127, 128, 255, 256, 16383, 16384,
                                   2097151, 2097152, 268435455, 268435456,
                                   UINT32_MAX};
  for (uint32_t v : values) {
    std::string dst;
    PutVarint32(&dst, v);
    Slice input(dst);
    uint32_t decoded = 0;
    ASSERT_TRUE(GetVarint32(&input, &decoded)) << "Failed for value " << v;
    EXPECT_EQ(decoded, v) << "Mismatch for value " << v;
  }
}

// Tests for Varint64
class CodingVarint64Test_446 : public ::testing::Test {};

TEST_F(CodingVarint64Test_446, EncodeDecodeVarint64_446) {
  std::vector<uint64_t> values = {0, 1, 127, 128, 255, 256,
                                   (1ull << 14) - 1, (1ull << 14),
                                   (1ull << 21) - 1, (1ull << 21),
                                   (1ull << 28) - 1, (1ull << 28),
                                   (1ull << 35) - 1, (1ull << 35),
                                   (1ull << 63), UINT64_MAX};
  for (uint64_t v : values) {
    std::string dst;
    PutVarint64(&dst, v);
    Slice input(dst);
    uint64_t decoded = 0;
    ASSERT_TRUE(GetVarint64(&input, &decoded)) << "Failed for value " << v;
    EXPECT_EQ(decoded, v) << "Mismatch for value " << v;
  }
}

// Tests for Fixed32
class CodingFixed32Test_446 : public ::testing::Test {};

TEST_F(CodingFixed32Test_446, EncodeDecodeFixed32_446) {
  std::string dst;
  PutFixed32(&dst, 0);
  PutFixed32(&dst, 1);
  PutFixed32(&dst, 0xFFFFFFFF);
  PutFixed32(&dst, 0x12345678);

  const char* p = dst.data();
  EXPECT_EQ(DecodeFixed32(p), 0u);
  p += 4;
  EXPECT_EQ(DecodeFixed32(p), 1u);
  p += 4;
  EXPECT_EQ(DecodeFixed32(p), 0xFFFFFFFFu);
  p += 4;
  EXPECT_EQ(DecodeFixed32(p), 0x12345678u);
}

// Tests for Fixed64
class CodingFixed64Test_446 : public ::testing::Test {};

TEST_F(CodingFixed64Test_446, EncodeDecodeFixed64_446) {
  std::string dst;
  PutFixed64(&dst, 0);
  PutFixed64(&dst, 1);
  PutFixed64(&dst, 0xFFFFFFFFFFFFFFFFull);
  PutFixed64(&dst, 0x123456789ABCDEFull);

  const char* p = dst.data();
  EXPECT_EQ(DecodeFixed64(p), 0ull);
  p += 8;
  EXPECT_EQ(DecodeFixed64(p), 1ull);
  p += 8;
  EXPECT_EQ(DecodeFixed64(p), 0xFFFFFFFFFFFFFFFFull);
  p += 8;
  EXPECT_EQ(DecodeFixed64(p), 0x123456789ABCDEFull);
}

// Tests for PutLengthPrefixedSlice / GetLengthPrefixedSlice
class CodingLengthPrefixedSliceTest_446 : public ::testing::Test {};

TEST_F(CodingLengthPrefixedSliceTest_446, EncodeDecodeEmpty_446) {
  std::string dst;
  PutLengthPrefixedSlice(&dst, Slice(""));
  Slice input(dst);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.size(), 0u);
  EXPECT_EQ(result.ToString(), "");
}

TEST_F(CodingLengthPrefixedSliceTest_446, EncodeDecodeNonEmpty_446) {
  std::string dst;
  PutLengthPrefixedSlice(&dst, Slice("hello"));
  Slice input(dst);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "hello");
}

TEST_F(CodingLengthPrefixedSliceTest_446, EncodeDecodeMultiple_446) {
  std::string dst;
  PutLengthPrefixedSlice(&dst, Slice("foo"));
  PutLengthPrefixedSlice(&dst, Slice("bar"));
  PutLengthPrefixedSlice(&dst, Slice(""));

  Slice input(dst);
  Slice result;

  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "foo");

  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "bar");

  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "");
}

// Test: GetLengthPrefixedSlice on truncated data
TEST_F(CodingLengthPrefixedSliceTest_446, TruncatedData_446) {
  std::string dst;
  PutLengthPrefixedSlice(&dst, Slice("hello"));
  // Truncate the data portion
  dst.resize(dst.size() - 2);
  Slice input(dst);
  Slice result;
  EXPECT_FALSE(GetLengthPrefixedSlice(&input, &result));
}

// Test: Multiple varint32 values concatenated
class CodingMultipleVarint32Test_446 : public ::testing::Test {};

TEST_F(CodingMultipleVarint32Test_446, MultipleValues_446) {
  std::string dst;
  PutVarint32(&dst, 0);
  PutVarint32(&dst, 100);
  PutVarint32(&dst, 128);
  PutVarint32(&dst, 999999);
  PutVarint32(&dst, UINT32_MAX);

  Slice input(dst);
  uint32_t v;

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 0u);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 100u);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 128u);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 999999u);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, UINT32_MAX);

  // No more data
  EXPECT_FALSE(GetVarint32(&input, &v));
}

// Test: EncodeFixed32 little-endian format
TEST_F(CodingFixed32Test_446, LittleEndianEncoding_446) {
  char buf[4];
  EncodeFixed32(buf, 0x04030201);
  EXPECT_EQ(static_cast<unsigned char>(buf[0]), 0x01);
  EXPECT_EQ(static_cast<unsigned char>(buf[1]), 0x02);
  EXPECT_EQ(static_cast<unsigned char>(buf[2]), 0x03);
  EXPECT_EQ(static_cast<unsigned char>(buf[3]), 0x04);
}

// Test: EncodeFixed64 little-endian format
TEST_F(CodingFixed64Test_446, LittleEndianEncoding_446) {
  char buf[8];
  EncodeFixed64(buf, 0x0807060504030201ull);
  EXPECT_EQ(static_cast<unsigned char>(buf[0]), 0x01);
  EXPECT_EQ(static_cast<unsigned char>(buf[1]), 0x02);
  EXPECT_EQ(static_cast<unsigned char>(buf[2]), 0x03);
  EXPECT_EQ(static_cast<unsigned char>(buf[3]), 0x04);
  EXPECT_EQ(static_cast<unsigned char>(buf[4]), 0x05);
  EXPECT_EQ(static_cast<unsigned char>(buf[5]), 0x06);
  EXPECT_EQ(static_cast<unsigned char>(buf[6]), 0x07);
  EXPECT_EQ(static_cast<unsigned char>(buf[7]), 0x08);
}

// Test: Varint32 encoding length
TEST_F(CodingVarint32Test_446, VarintLength_446) {
  EXPECT_EQ(VarintLength(0), 1);
  EXPECT_EQ(VarintLength(127), 1);
  EXPECT_EQ(VarintLength(128), 2);
  EXPECT_EQ(VarintLength(16383), 2);
  EXPECT_EQ(VarintLength(16384), 3);
  EXPECT_EQ(VarintLength(2097151), 3);
  EXPECT_EQ(VarintLength(2097152), 4);
  EXPECT_EQ(VarintLength(268435455), 4);
  EXPECT_EQ(VarintLength(268435456), 5);
  EXPECT_EQ(VarintLength(UINT32_MAX), 5);
}

// Test: Varint64 encoding length for large values
TEST_F(CodingVarint64Test_446, VarintLengthLarge_446) {
  EXPECT_EQ(VarintLength(1ull << 35), 6);
  EXPECT_EQ(VarintLength(1ull << 42), 7);
  EXPECT_EQ(VarintLength(1ull << 49), 8);
  EXPECT_EQ(VarintLength(1ull << 56), 9);
  EXPECT_EQ(VarintLength(1ull << 63), 10);
  EXPECT_EQ(VarintLength(UINT64_MAX), 10);
}

}  // namespace leveldb
