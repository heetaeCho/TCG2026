// InternalKeyEncodingLength_test_47.cc
#include <gtest/gtest.h>
#include <string>
#include "db/dbformat.h"   // Provides ParsedInternalKey and InternalKeyEncodingLength
#include "leveldb/slice.h" // Provides Slice

using namespace leveldb;

class InternalKeyEncodingLengthTest_47 : public ::testing::Test {};

// [Normal] Empty user key -> length should be 8 (overhead only)
TEST_F(InternalKeyEncodingLengthTest_47, EmptyUserKeyReturns8_47) {
  ParsedInternalKey pik(Slice(), /*seq*/0, /*type*/static_cast<ValueType>(0));
  EXPECT_EQ(8u, InternalKeyEncodingLength(pik));
}

// [Normal] Small ASCII key -> size(bytes) + 8
TEST_F(InternalKeyEncodingLengthTest_47, CountsBytesPlusEight_Ascii_47) {
  ParsedInternalKey pik(Slice("abc"), /*seq*/123, /*type*/static_cast<ValueType>(1));
  EXPECT_EQ(3u + 8u, InternalKeyEncodingLength(pik));
}

// [Boundary] UTF-8 multibyte characters are counted by bytes, not glyphs
TEST_F(InternalKeyEncodingLengthTest_47, CountsBytesPlusEight_UTF8_47) {
  // "안녕" is 2 UTF-8 characters, typically 6 bytes.
  const std::string utf8 = u8"안녕";
  ParsedInternalKey pik(Slice(utf8), /*seq*/999, /*type*/static_cast<ValueType>(1));
  EXPECT_EQ(utf8.size() + 8u, InternalKeyEncodingLength(pik));
}

// [Boundary] Binary data (including embedded NUL) counted via explicit length
TEST_F(InternalKeyEncodingLengthTest_47, CountsBytesPlusEight_BinaryData_47) {
  const char raw[5] = {'a', '\0', 'b', 'c', 'd'};
  ParsedInternalKey pik(Slice(raw, sizeof(raw)), /*seq*/42, /*type*/static_cast<ValueType>(1));
  EXPECT_EQ(sizeof(raw) + 8u, InternalKeyEncodingLength(pik));
}

// [Boundary] Large key (e.g., 1 MiB) -> ensure no overflow in common cases
TEST_F(InternalKeyEncodingLengthTest_47, LargeKey_OneMiB_47) {
  const size_t kLen = 1 << 20; // 1 MiB
  std::string big(kLen, 'x');
  ParsedInternalKey pik(Slice(big), /*seq*/7, /*type*/static_cast<ValueType>(1));
  EXPECT_EQ(kLen + 8u, InternalKeyEncodingLength(pik));
}

// [Behavior] Sequence number and type should not affect the encoded length
TEST_F(InternalKeyEncodingLengthTest_47, IgnoresSequenceAndType_47) {
  const std::string key = "same-key";
  ParsedInternalKey a(Slice(key), /*seq*/0,   /*type*/static_cast<ValueType>(0));
  ParsedInternalKey b(Slice(key), /*seq*/999, /*type*/static_cast<ValueType>(1));
  EXPECT_EQ(InternalKeyEncodingLength(a), InternalKeyEncodingLength(b));
  EXPECT_EQ(key.size() + 8u, InternalKeyEncodingLength(a));
}
