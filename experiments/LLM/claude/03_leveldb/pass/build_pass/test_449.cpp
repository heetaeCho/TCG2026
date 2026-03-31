#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include "util/coding.h"

namespace leveldb {

// Helper function to encode a varint64 into a string
static std::string EncodeVarint64(uint64_t value) {
  char buf[10];
  char* p = buf;
  while (value >= 128) {
    *p++ = static_cast<char>(value | 0x80);
    value >>= 7;
  }
  *p++ = static_cast<char>(value);
  return std::string(buf, p - buf);
}

class GetVarint64Test_449 : public ::testing::Test {};

TEST_F(GetVarint64Test_449, DecodesZero_449) {
  std::string encoded = EncodeVarint64(0);
  Slice input(encoded);
  uint64_t value = 999;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(0u, value);
  EXPECT_EQ(0u, input.size());
}

TEST_F(GetVarint64Test_449, DecodesOne_449) {
  std::string encoded = EncodeVarint64(1);
  Slice input(encoded);
  uint64_t value = 0;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(1u, value);
  EXPECT_EQ(0u, input.size());
}

TEST_F(GetVarint64Test_449, DecodesSmallValue_449) {
  std::string encoded = EncodeVarint64(127);
  Slice input(encoded);
  uint64_t value = 0;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(127u, value);
  EXPECT_EQ(0u, input.size());
}

TEST_F(GetVarint64Test_449, DecodesTwoByteValue_449) {
  std::string encoded = EncodeVarint64(128);
  Slice input(encoded);
  uint64_t value = 0;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(128u, value);
  EXPECT_EQ(0u, input.size());
}

TEST_F(GetVarint64Test_449, DecodesMediumValue_449) {
  std::string encoded = EncodeVarint64(16383);
  Slice input(encoded);
  uint64_t value = 0;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(16383u, value);
  EXPECT_EQ(0u, input.size());
}

TEST_F(GetVarint64Test_449, DecodesLargeValue_449) {
  uint64_t expected = 1ull << 32;
  std::string encoded = EncodeVarint64(expected);
  Slice input(encoded);
  uint64_t value = 0;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(expected, value);
  EXPECT_EQ(0u, input.size());
}

TEST_F(GetVarint64Test_449, DecodesMaxUint64_449) {
  uint64_t expected = UINT64_MAX;
  std::string encoded = EncodeVarint64(expected);
  Slice input(encoded);
  uint64_t value = 0;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(expected, value);
  EXPECT_EQ(0u, input.size());
}

TEST_F(GetVarint64Test_449, EmptyInputReturnsFalse_449) {
  Slice input("", 0);
  uint64_t value = 42;
  ASSERT_FALSE(GetVarint64(&input, &value));
}

TEST_F(GetVarint64Test_449, SliceAdvancesPastVarint_449) {
  // Encode a varint followed by extra data
  std::string encoded = EncodeVarint64(300);
  encoded += "extra";
  Slice input(encoded);
  uint64_t value = 0;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(300u, value);
  EXPECT_EQ(5u, input.size());
  EXPECT_EQ('e', input[0]);
}

TEST_F(GetVarint64Test_449, TruncatedVarintReturnsFalse_449) {
  // Encode a multi-byte varint and then truncate it
  std::string encoded = EncodeVarint64(1ull << 35);  // requires multiple bytes
  ASSERT_GT(encoded.size(), 1u);
  // Truncate: only keep the first byte (which has continuation bit set)
  std::string truncated = encoded.substr(0, 1);
  Slice input(truncated);
  uint64_t value = 0;
  ASSERT_FALSE(GetVarint64(&input, &value));
}

TEST_F(GetVarint64Test_449, MultipleVarintsInSequence_449) {
  std::string encoded;
  encoded += EncodeVarint64(100);
  encoded += EncodeVarint64(200);
  encoded += EncodeVarint64(300);
  
  Slice input(encoded);
  uint64_t value = 0;

  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(100u, value);

  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(200u, value);

  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(300u, value);

  EXPECT_EQ(0u, input.size());
}

TEST_F(GetVarint64Test_449, PowersOfTwo_449) {
  for (int i = 0; i < 64; i++) {
    uint64_t expected = 1ull << i;
    std::string encoded = EncodeVarint64(expected);
    Slice input(encoded);
    uint64_t value = 0;
    ASSERT_TRUE(GetVarint64(&input, &value));
    EXPECT_EQ(expected, value) << "Failed for power 2^" << i;
    EXPECT_EQ(0u, input.size());
  }
}

TEST_F(GetVarint64Test_449, PowersOfTwoMinusOne_449) {
  for (int i = 1; i < 64; i++) {
    uint64_t expected = (1ull << i) - 1;
    std::string encoded = EncodeVarint64(expected);
    Slice input(encoded);
    uint64_t value = 0;
    ASSERT_TRUE(GetVarint64(&input, &value));
    EXPECT_EQ(expected, value) << "Failed for (2^" << i << ")-1";
    EXPECT_EQ(0u, input.size());
  }
}

TEST_F(GetVarint64Test_449, SingleByteValues_449) {
  for (uint64_t i = 0; i < 128; i++) {
    std::string encoded = EncodeVarint64(i);
    EXPECT_EQ(1u, encoded.size());
    Slice input(encoded);
    uint64_t value = 999;
    ASSERT_TRUE(GetVarint64(&input, &value));
    EXPECT_EQ(i, value);
    EXPECT_EQ(0u, input.size());
  }
}

TEST_F(GetVarint64Test_449, Value128RequiresTwoBytes_449) {
  std::string encoded = EncodeVarint64(128);
  EXPECT_EQ(2u, encoded.size());
  Slice input(encoded);
  uint64_t value = 0;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(128u, value);
}

TEST_F(GetVarint64Test_449, TruncatedMaxVarintReturnsFalse_449) {
  // UINT64_MAX encodes as 10 bytes. Truncate at various points.
  std::string full = EncodeVarint64(UINT64_MAX);
  for (size_t len = 1; len < full.size(); len++) {
    std::string truncated = full.substr(0, len);
    Slice input(truncated);
    uint64_t value = 0;
    EXPECT_FALSE(GetVarint64(&input, &value))
        << "Should fail with " << len << " bytes of " << full.size();
  }
}

TEST_F(GetVarint64Test_449, SliceDataAfterDecode_449) {
  std::string encoded = EncodeVarint64(42);
  std::string trailing = "hello";
  std::string combined = encoded + trailing;
  
  Slice input(combined);
  uint64_t value = 0;
  ASSERT_TRUE(GetVarint64(&input, &value));
  EXPECT_EQ(42u, value);
  EXPECT_EQ(trailing.size(), input.size());
  EXPECT_EQ(std::string(input.data(), input.size()), trailing);
}

}  // namespace leveldb
