// =================================================================================================
// Copyright
// Unit tests for UnicodeConversions.cpp : ToUTF16
// TEST_ID: 2054
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "UnicodeConversions.hpp" // Declares ToUTF16, UTF8Unit, UTF16Unit, etc.

// Helper: convert a UTF-16 code unit sequence to a byte string in LE/BE order.
static std::string MakeUTF16Bytes(const std::u16string& u16, bool bigEndian) {
  std::string out;
  out.reserve(u16.size() * 2);
  for (char16_t cu : u16) {
    uint16_t v = static_cast<uint16_t>(cu);
    unsigned char hi = static_cast<unsigned char>((v >> 8) & 0xFF);
    unsigned char lo = static_cast<unsigned char>(v & 0xFF);
    if (bigEndian) {
      out.push_back(static_cast<char>(hi));
      out.push_back(static_cast<char>(lo));
    } else {
      out.push_back(static_cast<char>(lo));
      out.push_back(static_cast<char>(hi));
    }
  }
  return out;
}

static void CallToUTF16(const std::string& utf8, std::string* outUtf16Bytes, bool bigEndian) {
  ASSERT_NE(outUtf16Bytes, nullptr);
  const UTF8Unit* in = reinterpret_cast<const UTF8Unit*>(utf8.data());
  ToUTF16(in, utf8.size(), outUtf16Bytes, bigEndian);
}

class UnicodeConversionsTest_2054 : public ::testing::Test {};

TEST_F(UnicodeConversionsTest_2054, EmptyInputProducesEmptyOutput_2054) {
  std::string out("non-empty");
  CallToUTF16(std::string(), &out, /*bigEndian*/ false);
  EXPECT_TRUE(out.empty());

  out.assign("non-empty-again");
  CallToUTF16(std::string(), &out, /*bigEndian*/ true);
  EXPECT_TRUE(out.empty());
}

TEST_F(UnicodeConversionsTest_2054, AsciiConvertsToUTF16LEBytes_2054) {
  const std::string utf8 = "ABCxyz012";
  std::string out;
  CallToUTF16(utf8, &out, /*bigEndian*/ false);

  const std::u16string expectedU16 = u"ABCxyz012";
  const std::string expectedBytes = MakeUTF16Bytes(expectedU16, /*bigEndian*/ false);

  EXPECT_EQ(out.size(), expectedBytes.size());
  EXPECT_EQ(out, expectedBytes);
}

TEST_F(UnicodeConversionsTest_2054, AsciiConvertsToUTF16BEBytes_2054) {
  const std::string utf8 = "Hello!";
  std::string out;
  CallToUTF16(utf8, &out, /*bigEndian*/ true);

  const std::u16string expectedU16 = u"Hello!";
  const std::string expectedBytes = MakeUTF16Bytes(expectedU16, /*bigEndian*/ true);

  EXPECT_EQ(out.size(), expectedBytes.size());
  EXPECT_EQ(out, expectedBytes);
}

TEST_F(UnicodeConversionsTest_2054, MultibyteBMPCharactersConvertCorrectlyLEAndBE_2054) {
  // "© €" => U+00A9, U+0020, U+20AC
  const std::string utf8 = u8"© €";

  std::string outLE;
  CallToUTF16(utf8, &outLE, /*bigEndian*/ false);
  const std::u16string expectedU16 = u"\u00A9 \u20AC";
  EXPECT_EQ(outLE, MakeUTF16Bytes(expectedU16, /*bigEndian*/ false));

  std::string outBE;
  CallToUTF16(utf8, &outBE, /*bigEndian*/ true);
  EXPECT_EQ(outBE, MakeUTF16Bytes(expectedU16, /*bigEndian*/ true));
}

TEST_F(UnicodeConversionsTest_2054, NonBMPEmojiProducesSurrogatePairBytes_2054) {
  // 😀 U+1F600 (requires surrogate pair in UTF-16).
  const std::string utf8 = u8"😀";
  const std::u16string expectedU16 = u"\U0001F600";

  std::string outLE;
  CallToUTF16(utf8, &outLE, /*bigEndian*/ false);
  EXPECT_EQ(outLE, MakeUTF16Bytes(expectedU16, /*bigEndian*/ false));
  EXPECT_EQ(outLE.size(), 4u); // surrogate pair => 2 code units => 4 bytes

  std::string outBE;
  CallToUTF16(utf8, &outBE, /*bigEndian*/ true);
  EXPECT_EQ(outBE, MakeUTF16Bytes(expectedU16, /*bigEndian*/ true));
  EXPECT_EQ(outBE.size(), 4u);
}

TEST_F(UnicodeConversionsTest_2054, LargeAsciiInputProcessesAllData_2054) {
  // Large enough to require multiple internal conversions/iterations.
  // We only validate observable output size/content pattern, not internal buffering.
  const size_t kLen = 20000;
  const std::string utf8(kLen, 'a');

  std::string out;
  CallToUTF16(utf8, &out, /*bigEndian*/ false);

  // For ASCII 'a' (U+0061), UTF-16 output should be 2 bytes per input byte.
  ASSERT_EQ(out.size(), kLen * 2);

  // Spot-check first and last code units are 'a' in UTF-16LE: 0x61 0x00.
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(static_cast<unsigned char>(out[0]), 0x61);
  EXPECT_EQ(static_cast<unsigned char>(out[1]), 0x00);
  EXPECT_EQ(static_cast<unsigned char>(out[out.size() - 2]), 0x61);
  EXPECT_EQ(static_cast<unsigned char>(out[out.size() - 1]), 0x00);
}

TEST_F(UnicodeConversionsTest_2054, InvalidUTF8AtEndThrows_2054) {
  // A truncated multibyte sequence: 0xE2 0x82 is an incomplete prefix for U+20AC (needs 3 bytes).
  const std::string badUtf8 = std::string("\xE2\x82", 2);

  std::string out;
  EXPECT_ANY_THROW({
    CallToUTF16(badUtf8, &out, /*bigEndian*/ false);
  });

  EXPECT_ANY_THROW({
    CallToUTF16(badUtf8, &out, /*bigEndian*/ true);
  });
}