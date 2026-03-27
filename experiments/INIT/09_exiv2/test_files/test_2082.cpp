// ============================================================================
// TEST_ID: 2082
// Unit tests for UTF16Swp_to_UTF8 (black-box via including implementation TU)
// File: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// Include the public declarations/types first (UTF16Unit/UTF8Unit/UTF32Unit, etc).
// Then include the .cpp so the TU-local static function UTF16Swp_to_UTF8 is visible here.
//
// NOTE: This pattern is intentional for testing TU-local static helpers without
//       changing production code.
#include "UnicodeConversions.hpp"
#include "UnicodeConversions.cpp"

namespace {

// Helper: create "swapped" UTF-16 units for input by using the existing swap helper,
// rather than re-implementing byte swapping logic in the test.
static UTF16Unit MakeSwappedUnit(UTF16Unit desiredUnit) {
  UTF16Unit tmp = desiredUnit;
  // UTF16InSwap takes a pointer to UTF16Unit (as seen in production code usage).
  // It returns the swapped interpretation of the memory at tmp.
  return UTF16InSwap(&tmp);
}

static std::vector<UTF16Unit> MakeSwappedUnits(std::initializer_list<UTF16Unit> desiredUnits) {
  std::vector<UTF16Unit> out;
  out.reserve(desiredUnits.size());
  for (UTF16Unit u : desiredUnits) out.push_back(MakeSwappedUnit(u));
  return out;
}

static std::vector<UTF8Unit> ToUTF8Units(const std::string& s) {
  return std::vector<UTF8Unit>(reinterpret_cast<const UTF8Unit*>(s.data()),
                               reinterpret_cast<const UTF8Unit*>(s.data()) + s.size());
}

class UTF16Swp_to_UTF8Test_2082 : public ::testing::Test {};

}  // namespace

TEST_F(UTF16Swp_to_UTF8Test_2082, ConvertsAllAsciiAndReportsLengths_2082) {
  const std::string expected = "Hello, ASCII!";
  auto utf16Swp = MakeSwappedUnits({0x0048, 0x0065, 0x006C, 0x006C, 0x006F, 0x002C, 0x0020,
                                   0x0041, 0x0053, 0x0043, 0x0049, 0x0049, 0x0021});

  std::vector<UTF8Unit> out(expected.size() + 8, UTF8Unit(0xEE));  // fill with sentinel
  size_t utf16Read = 999, utf8Written = 999;

  UTF16Swp_to_UTF8(utf16Swp.data(), utf16Swp.size(), out.data(), out.size(), &utf16Read, &utf8Written);

  ASSERT_EQ(utf16Read, utf16Swp.size());
  ASSERT_EQ(utf8Written, expected.size());
  ASSERT_EQ(std::memcmp(out.data(), expected.data(), expected.size()), 0);

  // Ensure we didn't clobber beyond what was reported written.
  for (size_t i = utf8Written; i < out.size(); ++i) {
    ASSERT_EQ(out[i], UTF8Unit(0xEE));
  }
}

TEST_F(UTF16Swp_to_UTF8Test_2082, ConvertsBmpNonAsciiToMultibyteUtf8_2082) {
  // "A©€" => 0x41, 0xA9, 0x20AC
  const std::string expected = u8"A©€";
  auto utf16Swp = MakeSwappedUnits({0x0041, 0x00A9, 0x20AC});

  std::vector<UTF8Unit> out(expected.size() + 4, UTF8Unit(0xEE));
  size_t utf16Read = 0, utf8Written = 0;

  UTF16Swp_to_UTF8(utf16Swp.data(), utf16Swp.size(), out.data(), out.size(), &utf16Read, &utf8Written);

  EXPECT_EQ(utf16Read, utf16Swp.size());
  EXPECT_EQ(utf8Written, expected.size());
  EXPECT_EQ(std::memcmp(out.data(), expected.data(), expected.size()), 0);
}

TEST_F(UTF16Swp_to_UTF8Test_2082, ConvertsSurrogatePairToUtf8_2082) {
  // U+1F600 GRINNING FACE 😀 => UTF-16: D83D DE00
  const std::string expected = u8"😀";
  auto utf16Swp = MakeSwappedUnits({0xD83D, 0xDE00});

  std::vector<UTF8Unit> out(expected.size() + 4, UTF8Unit(0xEE));
  size_t utf16Read = 0, utf8Written = 0;

  UTF16Swp_to_UTF8(utf16Swp.data(), utf16Swp.size(), out.data(), out.size(), &utf16Read, &utf8Written);

  EXPECT_EQ(utf16Read, utf16Swp.size());
  EXPECT_EQ(utf8Written, expected.size());
  EXPECT_EQ(std::memcmp(out.data(), expected.data(), expected.size()), 0);
}

TEST_F(UTF16Swp_to_UTF8Test_2082, StopsBeforeWritingWhenOutputTooSmallForNextUnit_2082) {
  // Single BMP non-ASCII that requires multi-byte UTF-8 output ("©" => 2 bytes).
  auto utf16Swp = MakeSwappedUnits({0x00A9});

  // Only 1 byte of space: should not write partial encoding.
  std::vector<UTF8Unit> out(1, UTF8Unit(0xEE));
  size_t utf16Read = 123, utf8Written = 456;

  UTF16Swp_to_UTF8(utf16Swp.data(), utf16Swp.size(), out.data(), out.size(), &utf16Read, &utf8Written);

  EXPECT_EQ(utf16Read, size_t(0));
  EXPECT_EQ(utf8Written, size_t(0));
  EXPECT_EQ(out[0], UTF8Unit(0xEE));  // unchanged
}

TEST_F(UTF16Swp_to_UTF8Test_2082, StopsWhenInputEndsMidSurrogatePair_2082) {
  // High surrogate only, no low surrogate following.
  auto utf16Swp = MakeSwappedUnits({0xD83D});

  std::vector<UTF8Unit> out(8, UTF8Unit(0xEE));
  size_t utf16Read = 0, utf8Written = 0;

  UTF16Swp_to_UTF8(utf16Swp.data(), utf16Swp.size(), out.data(), out.size(), &utf16Read, &utf8Written);

  // Observable behavior: no complete code point => no progress should be reported.
  EXPECT_EQ(utf16Read, size_t(0));
  EXPECT_EQ(utf8Written, size_t(0));
  for (auto b : out) EXPECT_EQ(b, UTF8Unit(0xEE));
}

TEST_F(UTF16Swp_to_UTF8Test_2082, ConvertsPrefixThenStopsAtInsufficientOutputSpace_2082) {
  // "Hi " + "€" (Euro is 3 bytes) + "!"
  const std::string prefixExpected = "Hi ";
  auto utf16Swp = MakeSwappedUnits({0x0048, 0x0069, 0x0020, 0x20AC, 0x0021});

  // Provide space only for "Hi " (3 bytes) and *not enough* for "€" (needs 3 more).
  std::vector<UTF8Unit> out(3, UTF8Unit(0xEE));
  size_t utf16Read = 0, utf8Written = 0;

  UTF16Swp_to_UTF8(utf16Swp.data(), utf16Swp.size(), out.data(), out.size(), &utf16Read, &utf8Written);

  EXPECT_EQ(utf8Written, prefixExpected.size());
  EXPECT_EQ(std::memcmp(out.data(), prefixExpected.data(), prefixExpected.size()), 0);

  // It should have consumed exactly the UTF-16 units for 'H','i',' ' and stop before '€'.
  EXPECT_EQ(utf16Read, size_t(3));
}