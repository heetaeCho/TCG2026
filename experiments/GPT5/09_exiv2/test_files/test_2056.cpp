// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_UnicodeConversions_ToUTF32_2056.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// The function under test and UTF* unit typedefs live here in Exiv2's xmpsdk.
#include "UnicodeConversions.hpp"

namespace {

class UnicodeConversionsTest_2056 : public ::testing::Test {
 protected:
  static std::vector<uint8_t> Bytes(const std::string& s) {
    return std::vector<uint8_t>(s.begin(), s.end());
  }

  static void ExpectBytesEq(const std::string& actual, const std::vector<uint8_t>& expected) {
    const auto a = Bytes(actual);
    ASSERT_EQ(a.size(), expected.size());
    EXPECT_TRUE(std::memcmp(a.data(), expected.data(), expected.size()) == 0);
  }

  static std::string CallToUTF32(const std::string& utf8, bool bigEndian) {
    std::string out;
    const UTF8Unit* p = reinterpret_cast<const UTF8Unit*>(utf8.data());
    ToUTF32(p, utf8.size(), &out, bigEndian);
    return out;
  }
};

TEST_F(UnicodeConversionsTest_2056, EmptyInputProducesEmptyOutput_2056) {
  std::string out = CallToUTF32(std::string(), /*bigEndian=*/false);
  EXPECT_TRUE(out.empty());

  out = CallToUTF32(std::string(), /*bigEndian=*/true);
  EXPECT_TRUE(out.empty());
}

TEST_F(UnicodeConversionsTest_2056, AsciiAProducesExpectedUTF32LEBytes_2056) {
  const std::string out = CallToUTF32("A", /*bigEndian=*/false);

  // U+0041 as UTF-32LE: 41 00 00 00
  const std::vector<uint8_t> expected = {0x41, 0x00, 0x00, 0x00};
  ExpectBytesEq(out, expected);
}

TEST_F(UnicodeConversionsTest_2056, AsciiAProducesExpectedUTF32BEBytes_2056) {
  const std::string out = CallToUTF32("A", /*bigEndian=*/true);

  // U+0041 as UTF-32BE: 00 00 00 41
  const std::vector<uint8_t> expected = {0x00, 0x00, 0x00, 0x41};
  ExpectBytesEq(out, expected);
}

TEST_F(UnicodeConversionsTest_2056, MultipleAsciiCharsHaveCorrectLengthAndContent_2056) {
  const std::string outLE = CallToUTF32("ABC", /*bigEndian=*/false);
  ASSERT_EQ(outLE.size(), 3u * 4u);

  const std::vector<uint8_t> expectedLE = {
      0x41, 0x00, 0x00, 0x00,  // A
      0x42, 0x00, 0x00, 0x00,  // B
      0x43, 0x00, 0x00, 0x00   // C
  };
  ExpectBytesEq(outLE, expectedLE);

  const std::string outBE = CallToUTF32("ABC", /*bigEndian=*/true);
  ASSERT_EQ(outBE.size(), 3u * 4u);

  const std::vector<uint8_t> expectedBE = {
      0x00, 0x00, 0x00, 0x41,  // A
      0x00, 0x00, 0x00, 0x42,  // B
      0x00, 0x00, 0x00, 0x43   // C
  };
  ExpectBytesEq(outBE, expectedBE);
}

TEST_F(UnicodeConversionsTest_2056, TwoByteUtf8SequenceConvertsToExpectedUTF32_2056) {
  // "¢" U+00A2 in UTF-8 is: C2 A2
  const std::string utf8 = std::string("\xC2\xA2", 2);

  const std::string outLE = CallToUTF32(utf8, /*bigEndian=*/false);
  const std::vector<uint8_t> expectedLE = {0xA2, 0x00, 0x00, 0x00};
  ExpectBytesEq(outLE, expectedLE);

  const std::string outBE = CallToUTF32(utf8, /*bigEndian=*/true);
  const std::vector<uint8_t> expectedBE = {0x00, 0x00, 0x00, 0xA2};
  ExpectBytesEq(outBE, expectedBE);
}

TEST_F(UnicodeConversionsTest_2056, FourByteUtf8SequenceConvertsToExpectedUTF32_2056) {
  // "😀" U+1F600 in UTF-8 is: F0 9F 98 80
  const std::string utf8 = std::string("\xF0\x9F\x98\x80", 4);

  const std::string outLE = CallToUTF32(utf8, /*bigEndian=*/false);
  // 0x0001F600 in little-endian bytes: 00 F6 01 00
  const std::vector<uint8_t> expectedLE = {0x00, 0xF6, 0x01, 0x00};
  ExpectBytesEq(outLE, expectedLE);

  const std::string outBE = CallToUTF32(utf8, /*bigEndian=*/true);
  // 0x0001F600 in big-endian bytes: 00 01 F6 00
  const std::vector<uint8_t> expectedBE = {0x00, 0x01, 0xF6, 0x00};
  ExpectBytesEq(outBE, expectedBE);
}

TEST_F(UnicodeConversionsTest_2056, LongAsciiStringCrossesInternalChunkingAndKeepsFirstLast_2056) {
  // Large enough to plausibly require multiple internal converter calls.
  const size_t n = 5000;
  const std::string utf8(n, 'a');

  const std::string outLE = CallToUTF32(utf8, /*bigEndian=*/false);
  ASSERT_EQ(outLE.size(), n * 4u);

  // Check first and last UTF-32 code units are 'a' (0x61) in LE form.
  const auto bytes = Bytes(outLE);
  ASSERT_GE(bytes.size(), 8u);
  EXPECT_EQ(bytes[0], 0x61);
  EXPECT_EQ(bytes[1], 0x00);
  EXPECT_EQ(bytes[2], 0x00);
  EXPECT_EQ(bytes[3], 0x00);

  const size_t last = bytes.size() - 4;
  EXPECT_EQ(bytes[last + 0], 0x61);
  EXPECT_EQ(bytes[last + 1], 0x00);
  EXPECT_EQ(bytes[last + 2], 0x00);
  EXPECT_EQ(bytes[last + 3], 0x00);
}

TEST_F(UnicodeConversionsTest_2056, IncompleteUtf8AtEndThrows_2056) {
  // Truncated 3-byte sequence for '€' (would be E2 82 AC). Provide only E2 82.
  const std::string badUtf8 = std::string("\xE2\x82", 2);

  std::string out("preexisting");
  const UTF8Unit* p = reinterpret_cast<const UTF8Unit*>(badUtf8.data());

  EXPECT_ANY_THROW(ToUTF32(p, badUtf8.size(), &out, /*bigEndian=*/false));
  EXPECT_ANY_THROW(ToUTF32(p, badUtf8.size(), &out, /*bigEndian=*/true));
}

}  // namespace