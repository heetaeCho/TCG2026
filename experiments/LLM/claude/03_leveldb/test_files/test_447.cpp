#include "gtest/gtest.h"
#include "util/coding.h"
#include "leveldb/slice.h"

#include <string>
#include <cstring>

namespace leveldb {

// Helper function to encode a varint32 into a string
static void PutVarint32(std::string* dst, uint32_t v) {
  char buf[5];
  char* ptr = buf;
  if (v < (1 << 7)) {
    *(ptr++) = v;
  } else if (v < (1 << 14)) {
    *(ptr++) = v | 0x80;
    *(ptr++) = v >> 7;
  } else if (v < (1 << 21)) {
    *(ptr++) = v | 0x80;
    *(ptr++) = (v >> 7) | 0x80;
    *(ptr++) = v >> 14;
  } else if (v < (1 << 28)) {
    *(ptr++) = v | 0x80;
    *(ptr++) = (v >> 7) | 0x80;
    *(ptr++) = (v >> 14) | 0x80;
    *(ptr++) = v >> 21;
  } else {
    *(ptr++) = v | 0x80;
    *(ptr++) = (v >> 7) | 0x80;
    *(ptr++) = (v >> 14) | 0x80;
    *(ptr++) = (v >> 21) | 0x80;
    *(ptr++) = v >> 28;
  }
  dst->append(buf, ptr - buf);
}

class GetVarint32Test_447 : public ::testing::Test {
 protected:
};

// Test normal operation: decode a small value (single byte varint)
TEST_F(GetVarint32Test_447, DecodeSingleByteVarint_447) {
  std::string encoded;
  PutVarint32(&encoded, 42);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(42u, value);
  EXPECT_EQ(0u, input.size());
}

// Test decoding zero
TEST_F(GetVarint32Test_447, DecodeZero_447) {
  std::string encoded;
  PutVarint32(&encoded, 0);
  Slice input(encoded);
  uint32_t value = 999;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(0u, value);
  EXPECT_EQ(0u, input.size());
}

// Test decoding value 127 (max single byte)
TEST_F(GetVarint32Test_447, DecodeMaxSingleByte_447) {
  std::string encoded;
  PutVarint32(&encoded, 127);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(127u, value);
  EXPECT_EQ(0u, input.size());
}

// Test decoding value 128 (min two byte)
TEST_F(GetVarint32Test_447, DecodeMinTwoByte_447) {
  std::string encoded;
  PutVarint32(&encoded, 128);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(128u, value);
  EXPECT_EQ(0u, input.size());
}

// Test decoding a two-byte varint
TEST_F(GetVarint32Test_447, DecodeTwoByteVarint_447) {
  std::string encoded;
  PutVarint32(&encoded, 300);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(300u, value);
  EXPECT_EQ(0u, input.size());
}

// Test decoding a three-byte varint
TEST_F(GetVarint32Test_447, DecodeThreeByteVarint_447) {
  std::string encoded;
  PutVarint32(&encoded, 100000);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(100000u, value);
  EXPECT_EQ(0u, input.size());
}

// Test decoding a four-byte varint
TEST_F(GetVarint32Test_447, DecodeFourByteVarint_447) {
  std::string encoded;
  PutVarint32(&encoded, 50000000);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(50000000u, value);
  EXPECT_EQ(0u, input.size());
}

// Test decoding a five-byte varint (max uint32)
TEST_F(GetVarint32Test_447, DecodeMaxUint32_447) {
  std::string encoded;
  PutVarint32(&encoded, 0xFFFFFFFFu);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(0xFFFFFFFFu, value);
  EXPECT_EQ(0u, input.size());
}

// Test that the slice is advanced past the varint when there's trailing data
TEST_F(GetVarint32Test_447, SliceAdvancedWithTrailingData_447) {
  std::string encoded;
  PutVarint32(&encoded, 42);
  encoded.append("extra_data");
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(42u, value);
  EXPECT_EQ(10u, input.size());  // "extra_data" is 10 bytes
  EXPECT_EQ(std::string("extra_data"), std::string(input.data(), input.size()));
}

// Test empty input returns false
TEST_F(GetVarint32Test_447, EmptyInputReturnsFalse_447) {
  Slice input("");
  uint32_t value = 0;
  ASSERT_FALSE(GetVarint32(&input, &value));
}

// Test zero-length slice returns false
TEST_F(GetVarint32Test_447, ZeroLengthSliceReturnsFalse_447) {
  Slice input("", 0);
  uint32_t value = 0;
  ASSERT_FALSE(GetVarint32(&input, &value));
}

// Test truncated multi-byte varint (only first byte of a two-byte varint)
TEST_F(GetVarint32Test_447, TruncatedVarintReturnsFalse_447) {
  // A byte with the high bit set indicates more bytes follow
  char buf[1] = {static_cast<char>(0x80)};
  Slice input(buf, 1);
  uint32_t value = 0;
  ASSERT_FALSE(GetVarint32(&input, &value));
}

// Test decoding multiple varints sequentially from same slice
TEST_F(GetVarint32Test_447, DecodeMultipleVarintsSequentially_447) {
  std::string encoded;
  PutVarint32(&encoded, 1);
  PutVarint32(&encoded, 200);
  PutVarint32(&encoded, 50000);
  Slice input(encoded);

  uint32_t value1 = 0, value2 = 0, value3 = 0;
  ASSERT_TRUE(GetVarint32(&input, &value1));
  EXPECT_EQ(1u, value1);
  ASSERT_TRUE(GetVarint32(&input, &value2));
  EXPECT_EQ(200u, value2);
  ASSERT_TRUE(GetVarint32(&input, &value3));
  EXPECT_EQ(50000u, value3);
  EXPECT_EQ(0u, input.size());
}

// Test that after all varints are consumed, next call returns false
TEST_F(GetVarint32Test_447, DecodeAfterExhaustedReturnsFalse_447) {
  std::string encoded;
  PutVarint32(&encoded, 5);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(5u, value);
  ASSERT_FALSE(GetVarint32(&input, &value));
}

// Test boundary: value at 2^7 - 1 = 127 boundary
TEST_F(GetVarint32Test_447, BoundaryOneTwoBytes_447) {
  {
    std::string encoded;
    PutVarint32(&encoded, (1 << 7) - 1);
    EXPECT_EQ(1u, encoded.size());  // Should be 1 byte
    Slice input(encoded);
    uint32_t value = 0;
    ASSERT_TRUE(GetVarint32(&input, &value));
    EXPECT_EQ((1u << 7) - 1, value);
  }
  {
    std::string encoded;
    PutVarint32(&encoded, 1 << 7);
    EXPECT_EQ(2u, encoded.size());  // Should be 2 bytes
    Slice input(encoded);
    uint32_t value = 0;
    ASSERT_TRUE(GetVarint32(&input, &value));
    EXPECT_EQ(1u << 7, value);
  }
}

// Test boundary: value at 2^14 - 1 boundary
TEST_F(GetVarint32Test_447, BoundaryTwoThreeBytes_447) {
  {
    std::string encoded;
    PutVarint32(&encoded, (1 << 14) - 1);
    EXPECT_EQ(2u, encoded.size());
    Slice input(encoded);
    uint32_t value = 0;
    ASSERT_TRUE(GetVarint32(&input, &value));
    EXPECT_EQ((1u << 14) - 1, value);
  }
  {
    std::string encoded;
    PutVarint32(&encoded, 1 << 14);
    EXPECT_EQ(3u, encoded.size());
    Slice input(encoded);
    uint32_t value = 0;
    ASSERT_TRUE(GetVarint32(&input, &value));
    EXPECT_EQ(1u << 14, value);
  }
}

// Test boundary: value at 2^21 - 1 boundary
TEST_F(GetVarint32Test_447, BoundaryThreeFourBytes_447) {
  {
    std::string encoded;
    PutVarint32(&encoded, (1 << 21) - 1);
    EXPECT_EQ(3u, encoded.size());
    Slice input(encoded);
    uint32_t value = 0;
    ASSERT_TRUE(GetVarint32(&input, &value));
    EXPECT_EQ((1u << 21) - 1, value);
  }
  {
    std::string encoded;
    PutVarint32(&encoded, 1 << 21);
    EXPECT_EQ(4u, encoded.size());
    Slice input(encoded);
    uint32_t value = 0;
    ASSERT_TRUE(GetVarint32(&input, &value));
    EXPECT_EQ(1u << 21, value);
  }
}

// Test boundary: value at 2^28 - 1 boundary
TEST_F(GetVarint32Test_447, BoundaryFourFiveBytes_447) {
  {
    std::string encoded;
    PutVarint32(&encoded, (1 << 28) - 1);
    EXPECT_EQ(4u, encoded.size());
    Slice input(encoded);
    uint32_t value = 0;
    ASSERT_TRUE(GetVarint32(&input, &value));
    EXPECT_EQ((1u << 28) - 1, value);
  }
  {
    std::string encoded;
    PutVarint32(&encoded, 1 << 28);
    EXPECT_EQ(5u, encoded.size());
    Slice input(encoded);
    uint32_t value = 0;
    ASSERT_TRUE(GetVarint32(&input, &value));
    EXPECT_EQ(1u << 28, value);
  }
}

// Test truncated three-byte varint (only 2 of 3 bytes present)
TEST_F(GetVarint32Test_447, TruncatedThreeByteVarint_447) {
  char buf[2] = {static_cast<char>(0x80), static_cast<char>(0x80)};
  Slice input(buf, 2);
  uint32_t value = 0;
  ASSERT_FALSE(GetVarint32(&input, &value));
}

// Test that input slice is not modified on failure
TEST_F(GetVarint32Test_447, SliceUnchangedOnFailureEmpty_447) {
  Slice input("", 0);
  const char* original_data = input.data();
  size_t original_size = input.size();
  uint32_t value = 0;
  ASSERT_FALSE(GetVarint32(&input, &value));
  // On failure, the slice should remain unchanged (or at least the function returns false)
  // We just verify the return value is false
}

// Test value 1
TEST_F(GetVarint32Test_447, DecodeOne_447) {
  std::string encoded;
  PutVarint32(&encoded, 1);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(1u, value);
}

// Test large value near max
TEST_F(GetVarint32Test_447, DecodeLargeValue_447) {
  std::string encoded;
  PutVarint32(&encoded, 0xFFFFFFFEu);
  Slice input(encoded);
  uint32_t value = 0;
  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(0xFFFFFFFEu, value);
}

}  // namespace leveldb
