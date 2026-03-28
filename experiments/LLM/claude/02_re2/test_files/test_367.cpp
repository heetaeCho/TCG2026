#include "gtest/gtest.h"
#include <string>
#include "re2/regexp.h"
#include "util/utf.h"

namespace re2 {

// Declaration of the function under test
void ConvertRunesToBytes(bool latin1, Rune* runes, int nrunes, std::string* bytes);

// Test with latin1 mode, empty input
TEST(ConvertRunesToBytesTest_367, Latin1EmptyInput_367) {
  std::string bytes;
  ConvertRunesToBytes(true, nullptr, 0, &bytes);
  EXPECT_EQ(bytes.size(), 0u);
  EXPECT_EQ(bytes, "");
}

// Test with UTF mode, empty input
TEST(ConvertRunesToBytesTest_367, UTFEmptyInput_367) {
  std::string bytes;
  ConvertRunesToBytes(false, nullptr, 0, &bytes);
  EXPECT_EQ(bytes.size(), 0u);
  EXPECT_EQ(bytes, "");
}

// Test latin1 mode with simple ASCII characters
TEST(ConvertRunesToBytesTest_367, Latin1SimpleAscii_367) {
  Rune runes[] = {'H', 'e', 'l', 'l', 'o'};
  std::string bytes;
  ConvertRunesToBytes(true, runes, 5, &bytes);
  EXPECT_EQ(bytes.size(), 5u);
  EXPECT_EQ(bytes, "Hello");
}

// Test UTF mode with simple ASCII characters
TEST(ConvertRunesToBytesTest_367, UTFSimpleAscii_367) {
  Rune runes[] = {'H', 'e', 'l', 'l', 'o'};
  std::string bytes;
  ConvertRunesToBytes(false, runes, 5, &bytes);
  EXPECT_EQ(bytes.size(), 5u);
  EXPECT_EQ(bytes, "Hello");
}

// Test latin1 mode with single character
TEST(ConvertRunesToBytesTest_367, Latin1SingleChar_367) {
  Rune runes[] = {'A'};
  std::string bytes;
  ConvertRunesToBytes(true, runes, 1, &bytes);
  EXPECT_EQ(bytes.size(), 1u);
  EXPECT_EQ(bytes[0], 'A');
}

// Test UTF mode with single character
TEST(ConvertRunesToBytesTest_367, UTFSingleChar_367) {
  Rune runes[] = {'A'};
  std::string bytes;
  ConvertRunesToBytes(false, runes, 1, &bytes);
  EXPECT_EQ(bytes.size(), 1u);
  EXPECT_EQ(bytes[0], 'A');
}

// Test latin1 mode with values in 0-255 range (latin1 range)
TEST(ConvertRunesToBytesTest_367, Latin1HighByteValues_367) {
  Rune runes[] = {0, 127, 128, 255};
  std::string bytes;
  ConvertRunesToBytes(true, runes, 4, &bytes);
  EXPECT_EQ(bytes.size(), 4u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[0]), 0u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[1]), 127u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[2]), 128u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[3]), 255u);
}

// Test UTF mode with multi-byte UTF-8 characters (2-byte)
TEST(ConvertRunesToBytesTest_367, UTFTwoByteChars_367) {
  // U+00E9 (é) is a 2-byte UTF-8 character: 0xC3 0xA9
  Rune runes[] = {0x00E9};
  std::string bytes;
  ConvertRunesToBytes(false, runes, 1, &bytes);
  EXPECT_EQ(bytes.size(), 2u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[0]), 0xC3u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[1]), 0xA9u);
}

// Test UTF mode with 3-byte UTF-8 characters
TEST(ConvertRunesToBytesTest_367, UTFThreeByteChars_367) {
  // U+4E16 (世) is a 3-byte UTF-8 character: 0xE4 0xB8 0x96
  Rune runes[] = {0x4E16};
  std::string bytes;
  ConvertRunesToBytes(false, runes, 1, &bytes);
  EXPECT_EQ(bytes.size(), 3u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[0]), 0xE4u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[1]), 0xB8u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[2]), 0x96u);
}

// Test UTF mode with 4-byte UTF-8 characters
TEST(ConvertRunesToBytesTest_367, UTFFourByteChars_367) {
  // U+1F600 (😀) is a 4-byte UTF-8 character: 0xF0 0x9F 0x98 0x80
  Rune runes[] = {0x1F600};
  std::string bytes;
  ConvertRunesToBytes(false, runes, 1, &bytes);
  EXPECT_EQ(bytes.size(), 4u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[0]), 0xF0u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[1]), 0x9Fu);
  EXPECT_EQ(static_cast<unsigned char>(bytes[2]), 0x98u);
  EXPECT_EQ(static_cast<unsigned char>(bytes[3]), 0x80u);
}

// Test UTF mode with mixed single-byte and multi-byte characters
TEST(ConvertRunesToBytesTest_367, UTFMixedByteWidths_367) {
  Rune runes[] = {'A', 0x00E9, 0x4E16, 0x1F600};
  std::string bytes;
  ConvertRunesToBytes(false, runes, 4, &bytes);
  // A = 1 byte, é = 2 bytes, 世 = 3 bytes, 😀 = 4 bytes => total 10 bytes
  EXPECT_EQ(bytes.size(), 10u);
}

// Test latin1 mode with null character (rune value 0)
TEST(ConvertRunesToBytesTest_367, Latin1NullCharacter_367) {
  Rune runes[] = {0};
  std::string bytes;
  ConvertRunesToBytes(true, runes, 1, &bytes);
  EXPECT_EQ(bytes.size(), 1u);
  EXPECT_EQ(bytes[0], '\0');
}

// Test UTF mode with null character (rune value 0)
TEST(ConvertRunesToBytesTest_367, UTFNullCharacter_367) {
  Rune runes[] = {0};
  std::string bytes;
  ConvertRunesToBytes(false, runes, 1, &bytes);
  // runetochar for rune 0 should produce a single byte
  EXPECT_GE(bytes.size(), 1u);
}

// Test UTF mode with Runemax boundary
TEST(ConvertRunesToBytesTest_367, UTFRunemax_367) {
  Rune runes[] = {Runemax};  // 0x10FFFF
  std::string bytes;
  ConvertRunesToBytes(false, runes, 1, &bytes);
  // Runemax (U+10FFFF) should encode as 4 bytes in UTF-8
  EXPECT_EQ(bytes.size(), 4u);
}

// Test latin1 mode with multiple identical characters
TEST(ConvertRunesToBytesTest_367, Latin1RepeatedChars_367) {
  Rune runes[] = {'x', 'x', 'x', 'x', 'x'};
  std::string bytes;
  ConvertRunesToBytes(true, runes, 5, &bytes);
  EXPECT_EQ(bytes.size(), 5u);
  EXPECT_EQ(bytes, "xxxxx");
}

// Test that existing content in bytes string is overwritten
TEST(ConvertRunesToBytesTest_367, OverwritesExistingString_367) {
  Rune runes[] = {'A', 'B'};
  std::string bytes = "old content that should be replaced";
  ConvertRunesToBytes(true, runes, 2, &bytes);
  EXPECT_EQ(bytes.size(), 2u);
  EXPECT_EQ(bytes, "AB");
}

// Test UTF mode overwrites existing string content
TEST(ConvertRunesToBytesTest_367, UTFOverwritesExistingString_367) {
  Rune runes[] = {'A', 'B'};
  std::string bytes = "old content that should be replaced";
  ConvertRunesToBytes(false, runes, 2, &bytes);
  EXPECT_EQ(bytes.size(), 2u);
  EXPECT_EQ(bytes, "AB");
}

// Test UTF mode with Runeself boundary (128)
TEST(ConvertRunesToBytesTest_367, UTFRuneselfBoundary_367) {
  // 127 should be 1 byte, 128 should be 2 bytes
  Rune runes_below[] = {127};
  std::string bytes_below;
  ConvertRunesToBytes(false, runes_below, 1, &bytes_below);
  EXPECT_EQ(bytes_below.size(), 1u);

  Rune runes_at[] = {128};
  std::string bytes_at;
  ConvertRunesToBytes(false, runes_at, 1, &bytes_at);
  EXPECT_EQ(bytes_at.size(), 2u);
}

// Test UTF mode with boundary between 2-byte and 3-byte encoding
TEST(ConvertRunesToBytesTest_367, UTFTwoToThreeByteBoundary_367) {
  // U+07FF is the last 2-byte character
  Rune runes_2byte[] = {0x07FF};
  std::string bytes_2byte;
  ConvertRunesToBytes(false, runes_2byte, 1, &bytes_2byte);
  EXPECT_EQ(bytes_2byte.size(), 2u);

  // U+0800 is the first 3-byte character
  Rune runes_3byte[] = {0x0800};
  std::string bytes_3byte;
  ConvertRunesToBytes(false, runes_3byte, 1, &bytes_3byte);
  EXPECT_EQ(bytes_3byte.size(), 3u);
}

// Test UTF mode with boundary between 3-byte and 4-byte encoding
TEST(ConvertRunesToBytesTest_367, UTFThreeToFourByteBoundary_367) {
  // U+FFFF is the last 3-byte character
  Rune runes_3byte[] = {0xFFFF};
  std::string bytes_3byte;
  ConvertRunesToBytes(false, runes_3byte, 1, &bytes_3byte);
  EXPECT_EQ(bytes_3byte.size(), 3u);

  // U+10000 is the first 4-byte character
  Rune runes_4byte[] = {0x10000};
  std::string bytes_4byte;
  ConvertRunesToBytes(false, runes_4byte, 1, &bytes_4byte);
  EXPECT_EQ(bytes_4byte.size(), 4u);
}

// Test latin1 with large number of characters
TEST(ConvertRunesToBytesTest_367, Latin1LargeInput_367) {
  const int n = 1000;
  Rune runes[n];
  for (int i = 0; i < n; i++) {
    runes[i] = 'a' + (i % 26);
  }
  std::string bytes;
  ConvertRunesToBytes(true, runes, n, &bytes);
  EXPECT_EQ(bytes.size(), static_cast<size_t>(n));
  for (int i = 0; i < n; i++) {
    EXPECT_EQ(bytes[i], static_cast<char>('a' + (i % 26)));
  }
}

// Test UTF mode with large number of multi-byte characters
TEST(ConvertRunesToBytesTest_367, UTFLargeMultiByteInput_367) {
  const int n = 500;
  Rune runes[n];
  for (int i = 0; i < n; i++) {
    runes[i] = 0x4E16;  // 世 - 3 bytes each
  }
  std::string bytes;
  ConvertRunesToBytes(false, runes, n, &bytes);
  EXPECT_EQ(bytes.size(), static_cast<size_t>(n * 3));
}

}  // namespace re2
