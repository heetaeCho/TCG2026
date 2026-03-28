// =================================================================================================
// TEST_ID: 2080
// Unit tests for UTF8_to_UTF16Swp (black-box via observable outputs)
// File: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

// NOTE:
// The function under test is `static` in the .cpp, so we include the implementation file
// to bring it into this translation unit.
//
// This style is commonly used for testing internal-linkage helpers while still treating
// behavior as a black box (only validating observable outputs).
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class UnicodeConversionsTest_2080 : public ::testing::Test {
protected:
  static std::vector<uint8_t> AsBytes(const UTF16Unit* p, size_t units) {
    const auto* b = reinterpret_cast<const uint8_t*>(p);
    return std::vector<uint8_t>(b, b + units * sizeof(UTF16Unit));
  }
};

TEST_F(UnicodeConversionsTest_2080, ConvertsASCIIToSwappedUTF16_2080) {
  // "ABC" -> UTF-16 (swapped) bytes: 00 41 00 42 00 43
  const UTF8Unit in[] = {'A', 'B', 'C'};
  UTF16Unit out[8];
  std::memset(out, 0xA5, sizeof(out));

  size_t utf8Read = 0, utf16Written = 0;
  UTF8_to_UTF16Swp(in, 3, out, 8, &utf8Read, &utf16Written);

  EXPECT_EQ(utf8Read, 3u);
  EXPECT_EQ(utf16Written, 3u);

  const auto bytes = AsBytes(out, utf16Written);
  const std::vector<uint8_t> expected = {0x00, 0x41, 0x00, 0x42, 0x00, 0x43};
  EXPECT_EQ(bytes, expected);
}

TEST_F(UnicodeConversionsTest_2080, StopsWhenOutputBufferTooSmallForASCII_2080) {
  // Input longer than output capacity: should convert only what fits.
  const UTF8Unit in[] = {'A', 'B', 'C', 'D', 'E'};
  UTF16Unit out[2];
  std::memset(out, 0xA5, sizeof(out));

  size_t utf8Read = 0, utf16Written = 0;
  UTF8_to_UTF16Swp(in, 5, out, 2, &utf8Read, &utf16Written);

  EXPECT_EQ(utf16Written, 2u);
  EXPECT_EQ(utf8Read, 2u);

  const auto bytes = AsBytes(out, utf16Written);
  const std::vector<uint8_t> expected = {0x00, 0x41, 0x00, 0x42};
  EXPECT_EQ(bytes, expected);
}

TEST_F(UnicodeConversionsTest_2080, ConvertsTwoByteUTF8CodePoint_2080) {
  // U+00A9 COPYRIGHT SIGN: UTF-8 C2 A9 -> UTF-16 swapped bytes: 00 A9
  const UTF8Unit in[] = {static_cast<UTF8Unit>(0xC2), static_cast<UTF8Unit>(0xA9)};
  UTF16Unit out[4];
  std::memset(out, 0xA5, sizeof(out));

  size_t utf8Read = 0, utf16Written = 0;
  UTF8_to_UTF16Swp(in, 2, out, 4, &utf8Read, &utf16Written);

  EXPECT_EQ(utf8Read, 2u);
  EXPECT_EQ(utf16Written, 1u);

  const auto bytes = AsBytes(out, utf16Written);
  const std::vector<uint8_t> expected = {0x00, 0xA9};
  EXPECT_EQ(bytes, expected);
}

TEST_F(UnicodeConversionsTest_2080, ConvertsSupplementaryPlaneToSurrogatePair_2080) {
  // U+1F600 GRINNING FACE: UTF-8 F0 9F 98 80
  // UTF-16 surrogate pair: D83D DE00 -> swapped bytes: D8 3D DE 00
  const UTF8Unit in[] = {static_cast<UTF8Unit>(0xF0), static_cast<UTF8Unit>(0x9F),
                         static_cast<UTF8Unit>(0x98), static_cast<UTF8Unit>(0x80)};
  UTF16Unit out[4];
  std::memset(out, 0xA5, sizeof(out));

  size_t utf8Read = 0, utf16Written = 0;
  UTF8_to_UTF16Swp(in, 4, out, 4, &utf8Read, &utf16Written);

  EXPECT_EQ(utf8Read, 4u);
  EXPECT_EQ(utf16Written, 2u);

  const auto bytes = AsBytes(out, utf16Written);
  const std::vector<uint8_t> expected = {0xD8, 0x3D, 0xDE, 0x00};
  EXPECT_EQ(bytes, expected);
}

TEST_F(UnicodeConversionsTest_2080, DoesNotWritePartialSurrogateWhenOutputHasOnlyOneUnit_2080) {
  // Same U+1F600, but output buffer has only 1 UTF16 unit -> should not write partial.
  const UTF8Unit in[] = {static_cast<UTF8Unit>(0xF0), static_cast<UTF8Unit>(0x9F),
                         static_cast<UTF8Unit>(0x98), static_cast<UTF8Unit>(0x80)};
  UTF16Unit out[1];
  std::memset(out, 0xA5, sizeof(out));

  size_t utf8Read = 0, utf16Written = 0;
  UTF8_to_UTF16Swp(in, 4, out, 1, &utf8Read, &utf16Written);

  // Observable contract from implementation: if not enough room, it goes to Done without consuming.
  EXPECT_EQ(utf8Read, 0u);
  EXPECT_EQ(utf16Written, 0u);

  // Ensure buffer remains untouched (still 0xA5 pattern).
  const auto bytes = AsBytes(out, 1);
  EXPECT_EQ(bytes.size(), sizeof(UTF16Unit));
  for (uint8_t b : bytes) {
    EXPECT_EQ(b, 0xA5);
  }
}

TEST_F(UnicodeConversionsTest_2080, StopsWhenInputEndsMidCharacter_2080) {
  // Truncated UTF-8 sequence: only leading byte of a 2-byte sequence (C2).
  const UTF8Unit in[] = {static_cast<UTF8Unit>(0xC2)};
  UTF16Unit out[4];
  std::memset(out, 0xA5, sizeof(out));

  size_t utf8Read = 0, utf16Written = 0;
  UTF8_to_UTF16Swp(in, 1, out, 4, &utf8Read, &utf16Written);

  // Implementation comment: "The input buffer ends in the middle of a character."
  EXPECT_EQ(utf8Read, 0u);
  EXPECT_EQ(utf16Written, 0u);

  // Ensure no output was produced.
  const auto bytes = AsBytes(out, 1);
  for (uint8_t b : bytes) {
    EXPECT_EQ(b, 0xA5);
  }
}

}  // namespace