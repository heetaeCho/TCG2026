#include "gtest/gtest.h"
#include "util/coding.h"
#include "leveldb/slice.h"

namespace leveldb {

// Helper function to encode a varint32 into a string
static std::string EncodeVarint32(uint32_t v) {
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
  return std::string(buf, ptr - buf);
}

// Helper to build a length-prefixed slice
static std::string EncodeLengthPrefixed(const std::string& value) {
  std::string result = EncodeVarint32(static_cast<uint32_t>(value.size()));
  result.append(value);
  return result;
}

class GetLengthPrefixedSliceTest_450 : public ::testing::Test {};

TEST_F(GetLengthPrefixedSliceTest_450, NormalString_450) {
  std::string encoded = EncodeLengthPrefixed("hello");
  Slice input(encoded);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "hello");
  EXPECT_EQ(input.size(), 0u);
}

TEST_F(GetLengthPrefixedSliceTest_450, EmptyString_450) {
  std::string encoded = EncodeLengthPrefixed("");
  Slice input(encoded);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "");
  EXPECT_EQ(input.size(), 0u);
}

TEST_F(GetLengthPrefixedSliceTest_450, EmptyInput_450) {
  Slice input;
  Slice result;
  ASSERT_FALSE(GetLengthPrefixedSlice(&input, &result));
}

TEST_F(GetLengthPrefixedSliceTest_450, TruncatedData_450) {
  // Encode length as 10, but only provide 5 bytes of data
  std::string encoded = EncodeVarint32(10);
  encoded.append("hello");  // only 5 bytes, not 10
  Slice input(encoded);
  Slice result;
  ASSERT_FALSE(GetLengthPrefixedSlice(&input, &result));
}

TEST_F(GetLengthPrefixedSliceTest_450, LengthOnlyNoData_450) {
  // Encode length as 5, but provide no data after it
  std::string encoded = EncodeVarint32(5);
  Slice input(encoded);
  Slice result;
  ASSERT_FALSE(GetLengthPrefixedSlice(&input, &result));
}

TEST_F(GetLengthPrefixedSliceTest_450, MultipleEncodedSlices_450) {
  std::string encoded;
  encoded.append(EncodeLengthPrefixed("foo"));
  encoded.append(EncodeLengthPrefixed("bar"));
  Slice input(encoded);
  Slice result;

  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "foo");

  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "bar");

  EXPECT_EQ(input.size(), 0u);
}

TEST_F(GetLengthPrefixedSliceTest_450, ExtraDataAfterSlice_450) {
  std::string encoded = EncodeLengthPrefixed("test");
  encoded.append("extra");
  Slice input(encoded);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "test");
  EXPECT_EQ(input.size(), 5u);  // "extra" remains
  EXPECT_EQ(input.ToString(), "extra");
}

TEST_F(GetLengthPrefixedSliceTest_450, SingleByteString_450) {
  std::string encoded = EncodeLengthPrefixed("x");
  Slice input(encoded);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), "x");
  EXPECT_EQ(input.size(), 0u);
}

TEST_F(GetLengthPrefixedSliceTest_450, IncompleteVarint_450) {
  // A byte with continuation bit set but no following byte
  std::string encoded;
  encoded.push_back(static_cast<char>(0x80));
  Slice input(encoded);
  Slice result;
  ASSERT_FALSE(GetLengthPrefixedSlice(&input, &result));
}

TEST_F(GetLengthPrefixedSliceTest_450, ZeroLengthWithExtraData_450) {
  std::string encoded = EncodeVarint32(0);
  encoded.append("remaining");
  Slice input(encoded);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.size(), 0u);
  EXPECT_EQ(input.ToString(), "remaining");
}

TEST_F(GetLengthPrefixedSliceTest_450, ExactLengthMatch_450) {
  // Length exactly matches remaining data
  std::string data(127, 'a');  // 127 bytes, fits in 1-byte varint
  std::string encoded = EncodeLengthPrefixed(data);
  Slice input(encoded);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), data);
  EXPECT_EQ(input.size(), 0u);
}

TEST_F(GetLengthPrefixedSliceTest_450, LargerLength2ByteVarint_450) {
  // Use a string that requires 2-byte varint for length (128 bytes)
  std::string data(128, 'b');
  std::string encoded = EncodeLengthPrefixed(data);
  Slice input(encoded);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.ToString(), data);
  EXPECT_EQ(input.size(), 0u);
}

TEST_F(GetLengthPrefixedSliceTest_450, DataWithNullBytes_450) {
  std::string data;
  data.push_back('\0');
  data.push_back('a');
  data.push_back('\0');
  std::string encoded = EncodeLengthPrefixed(data);
  Slice input(encoded);
  Slice result;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &result));
  EXPECT_EQ(result.size(), 3u);
  EXPECT_EQ(result.ToString(), data);
}

TEST_F(GetLengthPrefixedSliceTest_450, InputNotModifiedOnFailure_450) {
  // When GetLengthPrefixedSlice fails due to insufficient data,
  // the input may or may not be modified depending on implementation.
  // We just verify it returns false.
  std::string encoded = EncodeVarint32(100);
  encoded.append("short");  // only 5 bytes, not 100
  Slice input(encoded);
  Slice result;
  ASSERT_FALSE(GetLengthPrefixedSlice(&input, &result));
}

TEST_F(GetLengthPrefixedSliceTest_450, OneByteLessThanNeeded_450) {
  // Length says 6, but only 5 bytes of data
  std::string encoded = EncodeVarint32(6);
  encoded.append("hello");  // 5 bytes
  Slice input(encoded);
  Slice result;
  ASSERT_FALSE(GetLengthPrefixedSlice(&input, &result));
}

}  // namespace leveldb
