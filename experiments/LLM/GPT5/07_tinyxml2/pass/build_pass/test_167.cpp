// File: test_xmlutil_tostr_bool_167.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>

#include "tinyxml2.h"

namespace {

class XMLUtilToStrBoolTest_167 : public ::testing::Test {
protected:
  static void Fill(char* buf, size_t n, unsigned char value = 0xA5) {
    std::memset(buf, value, n);
  }

  static void ExpectCanaryUnchanged(const unsigned char* buf, size_t start, size_t n,
                                   unsigned char value = 0xA5) {
    for (size_t i = start; i < start + n; ++i) {
      EXPECT_EQ(buf[i], value) << "Canary changed at index " << i;
    }
  }
};

TEST_F(XMLUtilToStrBoolTest_167, TrueUsesCustomSerialization_167) {
  tinyxml2::XMLUtil::SetBoolSerialization("YES", "NO");

  char buffer[16];
  Fill(buffer, sizeof(buffer));

  tinyxml2::XMLUtil::ToStr(true, buffer, static_cast<int>(sizeof(buffer)));

  EXPECT_STREQ("YES", buffer);
}

TEST_F(XMLUtilToStrBoolTest_167, FalseUsesCustomSerialization_167) {
  tinyxml2::XMLUtil::SetBoolSerialization("on", "off");

  char buffer[16];
  Fill(buffer, sizeof(buffer));

  tinyxml2::XMLUtil::ToStr(false, buffer, static_cast<int>(sizeof(buffer)));

  EXPECT_STREQ("off", buffer);
}

TEST_F(XMLUtilToStrBoolTest_167, BufferSizeOneWritesOnlyNullTerminator_167) {
  tinyxml2::XMLUtil::SetBoolSerialization("TRUE", "FALSE");

  // 1 byte for output, plus a canary byte after it.
  unsigned char raw[2];
  raw[0] = 0xCC;
  raw[1] = 0xA5;

  char* buffer = reinterpret_cast<char*>(&raw[0]);

  tinyxml2::XMLUtil::ToStr(true, buffer, 1);

  EXPECT_EQ(buffer[0], '\0');                 // truncated to empty string
  EXPECT_EQ(raw[1], static_cast<unsigned char>(0xA5));  // no overflow
}

TEST_F(XMLUtilToStrBoolTest_167, BufferSizeTwoTruncatesAndNullTerminates_167) {
  tinyxml2::XMLUtil::SetBoolSerialization("TRUE", "FALSE");

  // 2 bytes for output, plus canary bytes after.
  unsigned char raw[2 + 4];
  Fill(reinterpret_cast<char*>(raw), sizeof(raw));

  char* buffer = reinterpret_cast<char*>(raw);
  const int bufferSize = 2;

  tinyxml2::XMLUtil::ToStr(true, buffer, bufferSize);

  // With 2 bytes total: one character + '\0' at most.
  EXPECT_EQ(buffer[0], 'T');
  EXPECT_EQ(buffer[1], '\0');

  // Ensure nothing wrote past bufferSize.
  ExpectCanaryUnchanged(raw, /*start=*/2, /*n=*/4);
}

TEST_F(XMLUtilToStrBoolTest_167, SmallBufferTruncatesLongCustomStringWithoutOverflow_167) {
  const char* kLongTrue = "THIS_IS_A_VERY_LONG_TRUE_STRING";
  const char* kLongFalse = "THIS_IS_A_VERY_LONG_FALSE_STRING";
  tinyxml2::XMLUtil::SetBoolSerialization(kLongTrue, kLongFalse);

  // Make a small buffer and canary region after it.
  constexpr int kBufSize = 8;  // 7 chars + '\0' max
  unsigned char raw[kBufSize + 8];
  Fill(reinterpret_cast<char*>(raw), sizeof(raw));

  char* buffer = reinterpret_cast<char*>(raw);

  tinyxml2::XMLUtil::ToStr(true, buffer, kBufSize);

  // Must be NUL-terminated within the buffer.
  EXPECT_EQ(buffer[kBufSize - 1], '\0');

  // The written content must match the prefix of the configured true string.
  // (We don't assume anything beyond standard snprintf-like truncation.)
  char expectedPrefix[kBufSize];
  std::memset(expectedPrefix, 0, sizeof(expectedPrefix));
  std::strncpy(expectedPrefix, kLongTrue, static_cast<size_t>(kBufSize - 1));
  expectedPrefix[kBufSize - 1] = '\0';

  EXPECT_STREQ(expectedPrefix, buffer);

  // Ensure nothing wrote past the provided buffer.
  ExpectCanaryUnchanged(raw, /*start=*/kBufSize, /*n=*/8);
}

TEST_F(XMLUtilToStrBoolTest_167, ZeroBufferSizeDoesNotOverflowProvidedMemory_167) {
  tinyxml2::XMLUtil::SetBoolSerialization("Y", "N");

  // Provide a buffer but report size 0; verify no bytes change.
  unsigned char raw[8];
  Fill(reinterpret_cast<char*>(raw), sizeof(raw), /*value=*/0x5A);

  char* buffer = reinterpret_cast<char*>(raw);

  tinyxml2::XMLUtil::ToStr(true, buffer, 0);

  // With bufferSize == 0, the safe observable requirement is: no overwrite.
  for (size_t i = 0; i < sizeof(raw); ++i) {
    EXPECT_EQ(raw[i], static_cast<unsigned char>(0x5A)) << "Byte changed at index " << i;
  }
}

}  // namespace
