#include "gtest/gtest.h"
#include "util/coding.h"
#include "leveldb/slice.h"
#include <string>
#include <cstring>

namespace leveldb {

// Helper function to decode varint32 from a string for verification
// This reads a varint32 from the beginning of the input and advances the pointer
static bool GetVarint32(const char** p, const char* limit, uint32_t* value) {
  *value = 0;
  for (uint32_t shift = 0; shift <= 28 && *p < limit; shift += 7) {
    uint32_t byte = static_cast<unsigned char>(**p);
    (*p)++;
    if (byte & 128) {
      *value |= ((byte & 0x7f) << shift);
    } else {
      *value |= (byte << shift);
      return true;
    }
  }
  return false;
}

// Test normal operation with a non-empty string slice
TEST(PutLengthPrefixedSliceTest_444, NormalStringSlice_444) {
  std::string dst;
  Slice value("hello");
  PutLengthPrefixedSlice(&dst, value);

  // Decode the varint32 length prefix
  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 5u);

  // Verify the remaining data matches "hello"
  std::string extracted(p, length);
  EXPECT_EQ(extracted, "hello");

  // Verify total size consumed
  EXPECT_EQ(p + length, limit);
}

// Test with an empty slice
TEST(PutLengthPrefixedSliceTest_444, EmptySlice_444) {
  std::string dst;
  Slice value("");
  PutLengthPrefixedSlice(&dst, value);

  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 0u);
  EXPECT_EQ(p, limit);
}

// Test with a single character slice
TEST(PutLengthPrefixedSliceTest_444, SingleCharSlice_444) {
  std::string dst;
  Slice value("x");
  PutLengthPrefixedSlice(&dst, value);

  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 1u);
  EXPECT_EQ(*p, 'x');
}

// Test appending to non-empty destination string
TEST(PutLengthPrefixedSliceTest_444, AppendToExistingString_444) {
  std::string dst = "prefix";
  size_t original_size = dst.size();
  Slice value("data");
  PutLengthPrefixedSlice(&dst, value);

  // Verify the prefix is preserved
  EXPECT_EQ(dst.substr(0, original_size), "prefix");

  // Decode from the appended portion
  const char* p = dst.data() + original_size;
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 4u);
  std::string extracted(p, length);
  EXPECT_EQ(extracted, "data");
}

// Test with binary data containing null bytes
TEST(PutLengthPrefixedSliceTest_444, BinaryDataWithNulls_444) {
  std::string dst;
  std::string binary_data("he\0lo", 5);
  Slice value(binary_data);
  PutLengthPrefixedSlice(&dst, value);

  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 5u);
  std::string extracted(p, length);
  EXPECT_EQ(extracted, binary_data);
}

// Test with a longer string (to test varint encoding for larger sizes)
TEST(PutLengthPrefixedSliceTest_444, LongerString_444) {
  std::string dst;
  std::string long_str(200, 'a');  // 200 bytes, which requires 2 bytes for varint
  Slice value(long_str);
  PutLengthPrefixedSlice(&dst, value);

  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 200u);
  std::string extracted(p, length);
  EXPECT_EQ(extracted, long_str);
  EXPECT_EQ(p + length, limit);
}

// Test multiple successive calls to PutLengthPrefixedSlice
TEST(PutLengthPrefixedSliceTest_444, MultipleAppends_444) {
  std::string dst;
  Slice value1("first");
  Slice value2("second");
  Slice value3("third");

  PutLengthPrefixedSlice(&dst, value1);
  PutLengthPrefixedSlice(&dst, value2);
  PutLengthPrefixedSlice(&dst, value3);

  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();

  // Decode first
  uint32_t length1;
  ASSERT_TRUE(GetVarint32(&p, limit, &length1));
  EXPECT_EQ(length1, 5u);
  EXPECT_EQ(std::string(p, length1), "first");
  p += length1;

  // Decode second
  uint32_t length2;
  ASSERT_TRUE(GetVarint32(&p, limit, &length2));
  EXPECT_EQ(length2, 6u);
  EXPECT_EQ(std::string(p, length2), "second");
  p += length2;

  // Decode third
  uint32_t length3;
  ASSERT_TRUE(GetVarint32(&p, limit, &length3));
  EXPECT_EQ(length3, 5u);
  EXPECT_EQ(std::string(p, length3), "third");
  p += length3;

  EXPECT_EQ(p, limit);
}

// Test with Slice constructed from data pointer and explicit size
TEST(PutLengthPrefixedSliceTest_444, SliceWithExplicitSize_444) {
  std::string dst;
  const char* data = "abcdefgh";
  Slice value(data, 3);  // Only "abc"
  PutLengthPrefixedSlice(&dst, value);

  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 3u);
  EXPECT_EQ(std::string(p, length), "abc");
}

// Test with a string that requires multi-byte varint encoding (>= 128 bytes)
TEST(PutLengthPrefixedSliceTest_444, VarintMultiByte_444) {
  std::string dst;
  std::string str_128(128, 'b');
  Slice value(str_128);
  PutLengthPrefixedSlice(&dst, value);

  // For 128, varint32 requires 2 bytes
  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 128u);
  EXPECT_EQ(std::string(p, length), str_128);
  // Total should be 2 (varint bytes for 128) + 128 = 130
  EXPECT_EQ(dst.size(), 130u);
}

// Test with a slice of size exactly 127 (single byte varint)
TEST(PutLengthPrefixedSliceTest_444, VarintSingleByteBoundary_444) {
  std::string dst;
  std::string str_127(127, 'c');
  Slice value(str_127);
  PutLengthPrefixedSlice(&dst, value);

  // For 127, varint32 requires 1 byte
  EXPECT_EQ(dst.size(), 128u);  // 1 + 127

  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 127u);
}

// Test with a large string (e.g., 16384 bytes, requiring 3-byte varint)
TEST(PutLengthPrefixedSliceTest_444, LargeString_444) {
  std::string dst;
  std::string large_str(16384, 'd');
  Slice value(large_str);
  PutLengthPrefixedSlice(&dst, value);

  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, 16384u);
  std::string extracted(p, length);
  EXPECT_EQ(extracted, large_str);
}

// Test that Slice constructed from std::string works correctly
TEST(PutLengthPrefixedSliceTest_444, SliceFromStdString_444) {
  std::string dst;
  std::string src = "test_string";
  Slice value(src);
  PutLengthPrefixedSlice(&dst, value);

  const char* p = dst.data();
  const char* limit = dst.data() + dst.size();
  uint32_t length;
  ASSERT_TRUE(GetVarint32(&p, limit, &length));
  EXPECT_EQ(length, src.size());
  EXPECT_EQ(std::string(p, length), src);
}

}  // namespace leveldb
