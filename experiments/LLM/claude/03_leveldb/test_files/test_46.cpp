#include "gtest/gtest.h"
#include "util/coding.h"

#include <cstring>
#include <string>
#include <vector>

namespace leveldb {

// Helper functions from coding.h that we also need to test
// We'll use the public API: PutVarint32, PutVarint64, PutFixed32, PutFixed64,
// GetVarint32, GetVarint64, GetFixed32, GetFixed64, etc.

// ============================================================
// Tests for GetVarint32Ptr (the inline function shown)
// ============================================================

TEST(GetVarint32PtrTest_46, SingleByteValue_46) {
  // Value < 128 should be encoded in a single byte
  char buf[5];
  buf[0] = 0x05;  // value = 5, no high bit set
  uint32_t value = 0;
  const char* result = GetVarint32Ptr(buf, buf + 5, &value);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value, 5u);
  EXPECT_EQ(result, buf + 1);
}

TEST(GetVarint32PtrTest_46, SingleByteZero_46) {
  char buf[1];
  buf[0] = 0x00;
  uint32_t value = 999;
  const char* result = GetVarint32Ptr(buf, buf + 1, &value);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value, 0u);
  EXPECT_EQ(result, buf + 1);
}

TEST(GetVarint32PtrTest_46, SingleByteMaxNoFallback_46) {
  // 127 is the max single-byte varint value (0x7F, no high bit)
  char buf[1];
  buf[0] = 0x7F;
  uint32_t value = 0;
  const char* result = GetVarint32Ptr(buf, buf + 1, &value);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value, 127u);
  EXPECT_EQ(result, buf + 1);
}

TEST(GetVarint32PtrTest_46, EmptyBuffer_46) {
  // p == limit, should go to fallback which returns nullptr
  char buf[1];
  uint32_t value = 0;
  const char* result = GetVarint32Ptr(buf, buf, &value);
  EXPECT_EQ(result, nullptr);
}

TEST(GetVarint32PtrTest_46, HighBitSetGoesToFallback_46) {
  // If the first byte has the high bit set (>=128), it falls through to fallback
  // Encode 128 as varint: 0x80 0x01
  char buf[2];
  buf[0] = static_cast<char>(0x80);
  buf[1] = static_cast<char>(0x01);
  uint32_t value = 0;
  const char* result = GetVarint32Ptr(buf, buf + 2, &value);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value, 128u);
}

TEST(GetVarint32PtrTest_46, MultiByteFallback_300_46) {
  // 300 = 0x012C -> varint: 0xAC 0x02
  char buf[2];
  buf[0] = static_cast<char>(0xAC);
  buf[1] = static_cast<char>(0x02);
  uint32_t value = 0;
  const char* result = GetVarint32Ptr(buf, buf + 2, &value);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value, 300u);
}

// ============================================================
// Tests using PutVarint32 / GetVarint32 roundtrip
// ============================================================

TEST(VarintRoundtripTest_46, PutGetVarint32Small_46) {
  std::string s;
  PutVarint32(&s, 0);
  PutVarint32(&s, 1);
  PutVarint32(&s, 127);
  PutVarint32(&s, 128);
  PutVarint32(&s, 255);

  Slice input(s);
  uint32_t v;

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 0u);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 1u);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 127u);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 128u);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 255u);
}

TEST(VarintRoundtripTest_46, PutGetVarint32Large_46) {
  std::string s;
  PutVarint32(&s, 16384);
  PutVarint32(&s, (1u << 21) - 1);
  PutVarint32(&s, (1u << 28) - 1);
  PutVarint32(&s, 0xFFFFFFFFu);

  Slice input(s);
  uint32_t v;

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 16384u);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, (1u << 21) - 1);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, (1u << 28) - 1);

  ASSERT_TRUE(GetVarint32(&input, &v));
  EXPECT_EQ(v, 0xFFFFFFFFu);
}

TEST(VarintRoundtripTest_46, PutGetVarint64_46) {
  std::string s;
  PutVarint64(&s, 0);
  PutVarint64(&s, 1);
  PutVarint64(&s, 127);
  PutVarint64(&s, 128);
  PutVarint64(&s, 0xFFFFFFFFull);
  PutVarint64(&s, 0xFFFFFFFFFFFFFFFFull);

  Slice input(s);
  uint64_t v;

  ASSERT_TRUE(GetVarint64(&input, &v));
  EXPECT_EQ(v, 0u);

  ASSERT_TRUE(GetVarint64(&input, &v));
  EXPECT_EQ(v, 1u);

  ASSERT_TRUE(GetVarint64(&input, &v));
  EXPECT_EQ(v, 127u);

  ASSERT_TRUE(GetVarint64(&input, &v));
  EXPECT_EQ(v, 128u);

  ASSERT_TRUE(GetVarint64(&input, &v));
  EXPECT_EQ(v, 0xFFFFFFFFull);

  ASSERT_TRUE(GetVarint64(&input, &v));
  EXPECT_EQ(v, 0xFFFFFFFFFFFFFFFFull);
}

// ============================================================
// Tests for Fixed32 encoding
// ============================================================

TEST(Fixed32Test_46, PutGetFixed32_46) {
  std::string s;
  PutFixed32(&s, 0);
  PutFixed32(&s, 1);
  PutFixed32(&s, 0xFFFFFFFFu);
  PutFixed32(&s, 0x12345678u);

  const char* p = s.data();

  EXPECT_EQ(DecodeFixed32(p), 0u);
  p += 4;
  EXPECT_EQ(DecodeFixed32(p), 1u);
  p += 4;
  EXPECT_EQ(DecodeFixed32(p), 0xFFFFFFFFu);
  p += 4;
  EXPECT_EQ(DecodeFixed32(p), 0x12345678u);
}

TEST(Fixed32Test_46, EncodeDecodeFixed32_46) {
  char buf[4];
  EncodeFixed32(buf, 42);
  EXPECT_EQ(DecodeFixed32(buf), 42u);

  EncodeFixed32(buf, 0);
  EXPECT_EQ(DecodeFixed32(buf), 0u);

  EncodeFixed32(buf, 0xFFFFFFFFu);
  EXPECT_EQ(DecodeFixed32(buf), 0xFFFFFFFFu);
}

// ============================================================
// Tests for Fixed64 encoding
// ============================================================

TEST(Fixed64Test_46, PutGetFixed64_46) {
  std::string s;
  PutFixed64(&s, 0);
  PutFixed64(&s, 1);
  PutFixed64(&s, 0xFFFFFFFFFFFFFFFFull);
  PutFixed64(&s, 0x123456789ABCDEF0ull);

  const char* p = s.data();

  EXPECT_EQ(DecodeFixed64(p), 0u);
  p += 8;
  EXPECT_EQ(DecodeFixed64(p), 1u);
  p += 8;
  EXPECT_EQ(DecodeFixed64(p), 0xFFFFFFFFFFFFFFFFull);
  p += 8;
  EXPECT_EQ(DecodeFixed64(p), 0x123456789ABCDEF0ull);
}

TEST(Fixed64Test_46, EncodeDecodeFixed64_46) {
  char buf[8];
  EncodeFixed64(buf, 42);
  EXPECT_EQ(DecodeFixed64(buf), 42u);

  EncodeFixed64(buf, 0);
  EXPECT_EQ(DecodeFixed64(buf), 0u);

  EncodeFixed64(buf, 0xFFFFFFFFFFFFFFFFull);
  EXPECT_EQ(DecodeFixed64(buf), 0xFFFFFFFFFFFFFFFFull);
}

// ============================================================
// Tests for Varint encoding sizes
// ============================================================

TEST(VarintLengthTest_46, VarintLength_46) {
  EXPECT_EQ(VarintLength(0), 1);
  EXPECT_EQ(VarintLength(1), 1);
  EXPECT_EQ(VarintLength(127), 1);
  EXPECT_EQ(VarintLength(128), 2);
  EXPECT_EQ(VarintLength(16383), 2);
  EXPECT_EQ(VarintLength(16384), 3);
  EXPECT_EQ(VarintLength((1ull << 21) - 1), 3);
  EXPECT_EQ(VarintLength(1ull << 21), 4);
  EXPECT_EQ(VarintLength((1ull << 28) - 1), 4);
  EXPECT_EQ(VarintLength(1ull << 28), 5);
  EXPECT_EQ(VarintLength((1ull << 35) - 1), 5);
  EXPECT_EQ(VarintLength(1ull << 35), 6);
  EXPECT_EQ(VarintLength((1ull << 63)), 9);
  EXPECT_EQ(VarintLength(0xFFFFFFFFFFFFFFFFull), 10);
}

// ============================================================
// Tests for PutLengthPrefixedSlice / GetLengthPrefixedSlice
// ============================================================

TEST(LengthPrefixedSliceTest_46, RoundTrip_46) {
  std::string s;
  PutLengthPrefixedSlice(&s, Slice("hello"));
  PutLengthPrefixedSlice(&s, Slice(""));
  PutLengthPrefixedSlice(&s, Slice("world"));

  Slice input(s);
  Slice result;

  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "hello");

  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "");

  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "world");
}

// ============================================================
// Error / boundary tests
// ============================================================

TEST(VarintErrorTest_46, GetVarint32FromEmptySlice_46) {
  Slice input("");
  uint32_t v;
  EXPECT_FALSE(GetVarint32(&input, &v));
}

TEST(VarintErrorTest_46, GetVarint64FromEmptySlice_46) {
  Slice input("");
  uint64_t v;
  EXPECT_FALSE(GetVarint64(&input, &v));
}

TEST(VarintErrorTest_46, GetLengthPrefixedSliceFromEmpty_46) {
  Slice input("");
  Slice result;
  EXPECT_FALSE(GetLengthPrefixedSlice(&input, &result));
}

TEST(VarintErrorTest_46, TruncatedVarint32_46) {
  // A varint32 that needs more bytes but buffer is truncated
  // 0x80 means "more bytes follow" but there are none
  std::string s;
  s.push_back(static_cast<char>(0x80));
  Slice input(s);
  uint32_t v;
  EXPECT_FALSE(GetVarint32(&input, &v));
}

TEST(VarintErrorTest_46, TruncatedVarint64_46) {
  std::string s;
  s.push_back(static_cast<char>(0x80));
  Slice input(s);
  uint64_t v;
  EXPECT_FALSE(GetVarint64(&input, &v));
}

TEST(GetVarint32PtrTest_46, NullptrInputs_46) {
  uint32_t value = 0;
  // Both p and limit are nullptr (p < limit is false for equal pointers)
  const char* result = GetVarint32Ptr(nullptr, nullptr, &value);
  EXPECT_EQ(result, nullptr);
}

// ============================================================
// Stress-like: many values roundtrip
// ============================================================

TEST(VarintRoundtripTest_46, ManyVarint32Values_46) {
  std::string s;
  std::vector<uint32_t> values;
  for (uint32_t power = 0; power < 32; power++) {
    uint32_t v = (1u << power) - 1;
    values.push_back(v);
    PutVarint32(&s, v);
    v = 1u << power;
    values.push_back(v);
    PutVarint32(&s, v);
  }

  Slice input(s);
  for (size_t i = 0; i < values.size(); i++) {
    uint32_t v;
    ASSERT_TRUE(GetVarint32(&input, &v)) << "Failed at index " << i;
    EXPECT_EQ(v, values[i]) << "Mismatch at index " << i;
  }
  EXPECT_TRUE(input.empty());
}

TEST(VarintRoundtripTest_46, ManyVarint64Values_46) {
  std::string s;
  std::vector<uint64_t> values;
  for (uint32_t power = 0; power < 64; power++) {
    uint64_t v = (1ull << power) - 1;
    values.push_back(v);
    PutVarint64(&s, v);
    v = 1ull << power;
    values.push_back(v);
    PutVarint64(&s, v);
  }

  Slice input(s);
  for (size_t i = 0; i < values.size(); i++) {
    uint64_t v;
    ASSERT_TRUE(GetVarint64(&input, &v)) << "Failed at index " << i;
    EXPECT_EQ(v, values[i]) << "Mismatch at index " << i;
  }
  EXPECT_TRUE(input.empty());
}

TEST(GetVarint32PtrTest_46, ExactlyOneByte_46) {
  // Buffer of exactly one byte with value < 128
  char buf[1] = {42};
  uint32_t value = 0;
  const char* result = GetVarint32Ptr(buf, buf + 1, &value);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(value, 42u);
  EXPECT_EQ(result, buf + 1);
}

TEST(GetVarint32PtrTest_46, ExactlyOneByteHighBitSet_46) {
  // Buffer of exactly one byte with high bit set => fallback, which should fail
  // because there's no second byte
  char buf[1];
  buf[0] = static_cast<char>(0x80);
  uint32_t value = 0;
  const char* result = GetVarint32Ptr(buf, buf + 1, &value);
  EXPECT_EQ(result, nullptr);
}

}  // namespace leveldb
