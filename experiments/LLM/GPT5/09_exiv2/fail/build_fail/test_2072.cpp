// =================================================================================================
// TEST_ID: 2072
// Unit tests for UTF16Nat_to_UTF8 (black-box via observable outputs)
// File: UnicodeConversionsTest_2072.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// NOTE:
// UTF16Nat_to_UTF8 is declared `static` in UnicodeConversions.cpp.
// To test it via its interface (without touching private state), we include the .cpp directly
// so the function is visible within this translation unit.
#include "./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

static std::vector<UTF8Unit> Call_UTF16Nat_to_UTF8(
    const std::vector<UTF16Unit>& in,
    size_t outCap,
    size_t* utf16Read,
    size_t* utf8Written)
{
  std::vector<UTF8Unit> out(outCap);
  *utf16Read = 0;
  *utf8Written = 0;

  UTF16Nat_to_UTF8(in.data(),
                   in.size(),
                   out.data(),
                   out.size(),
                   utf16Read,
                   utf8Written);

  out.resize(*utf8Written);
  return out;
}

static std::vector<UTF8Unit> Bytes(std::initializer_list<uint8_t> b) {
  std::vector<UTF8Unit> v;
  v.reserve(b.size());
  for (auto x : b) v.push_back(static_cast<UTF8Unit>(x));
  return v;
}

}  // namespace

class UnicodeConversionsTest_2072 : public ::testing::Test {};

// ------------------------------------------------------------
// Normal operation
// ------------------------------------------------------------

TEST_F(UnicodeConversionsTest_2072, ConvertsPureASCII_2072) {
  const std::vector<UTF16Unit> in = {
      static_cast<UTF16Unit>('H'),
      static_cast<UTF16Unit>('e'),
      static_cast<UTF16Unit>('l'),
      static_cast<UTF16Unit>('l'),
      static_cast<UTF16Unit>('o'),
  };

  size_t read = 0, written = 0;
  const auto out = Call_UTF16Nat_to_UTF8(in, /*outCap*/ 32, &read, &written);

  ASSERT_EQ(read, in.size());
  ASSERT_EQ(written, in.size());
  ASSERT_EQ(out.size(), in.size());
  EXPECT_EQ(out, Bytes({'H', 'e', 'l', 'l', 'o'}));
}

TEST_F(UnicodeConversionsTest_2072, ConvertsBMPNonASCII_NoSurrogates_2072) {
  // U+00A9 COPYRIGHT SIGN -> C2 A9 in UTF-8
  // U+20AC EURO SIGN     -> E2 82 AC in UTF-8
  const std::vector<UTF16Unit> in = {
      static_cast<UTF16Unit>(0x0041),  // 'A'
      static_cast<UTF16Unit>(0x00A9),  // ©
      static_cast<UTF16Unit>(0x20AC),  // €
      static_cast<UTF16Unit>(0x0042),  // 'B'
  };

  size_t read = 0, written = 0;
  const auto out = Call_UTF16Nat_to_UTF8(in, /*outCap*/ 64, &read, &written);

  EXPECT_EQ(read, in.size());
  EXPECT_EQ(out, Bytes({
                    0x41,             // 'A'
                    0xC2, 0xA9,       // ©
                    0xE2, 0x82, 0xAC, // €
                    0x42,             // 'B'
                }));
  EXPECT_EQ(written, out.size());
}

TEST_F(UnicodeConversionsTest_2072, ConvertsSurrogatePairToUTF8_2072) {
  // U+1F600 GRINNING FACE 😀
  // UTF-16: D83D DE00
  // UTF-8:  F0 9F 98 80
  const std::vector<UTF16Unit> in = {
      static_cast<UTF16Unit>(0xD83D),
      static_cast<UTF16Unit>(0xDE00),
  };

  size_t read = 0, written = 0;
  const auto out = Call_UTF16Nat_to_UTF8(in, /*outCap*/ 16, &read, &written);

  EXPECT_EQ(read, in.size());
  EXPECT_EQ(out, Bytes({0xF0, 0x9F, 0x98, 0x80}));
  EXPECT_EQ(written, out.size());
}

// ------------------------------------------------------------
// Boundary conditions
// ------------------------------------------------------------

TEST_F(UnicodeConversionsTest_2072, EmptyInputWritesNothing_2072) {
  const std::vector<UTF16Unit> in;  // empty

  size_t read = 123, written = 456;
  const auto out = Call_UTF16Nat_to_UTF8(in, /*outCap*/ 8, &read, &written);

  EXPECT_EQ(read, 0u);
  EXPECT_EQ(written, 0u);
  EXPECT_TRUE(out.empty());
}

TEST_F(UnicodeConversionsTest_2072, ZeroOutputCapacityWritesNothingAndReadsNothing_2072) {
  const std::vector<UTF16Unit> in = {
      static_cast<UTF16Unit>('A'),
      static_cast<UTF16Unit>('B'),
  };

  size_t read = 0, written = 0;
  const auto out = Call_UTF16Nat_to_UTF8(in, /*outCap*/ 0, &read, &written);

  EXPECT_EQ(read, 0u);
  EXPECT_EQ(written, 0u);
  EXPECT_TRUE(out.empty());
}

TEST_F(UnicodeConversionsTest_2072, OutputBufferTooSmallStopsBeforeMultiByteUnit_2072) {
  // 'A' then U+00A9 requires 2 bytes in UTF-8.
  const std::vector<UTF16Unit> in = {
      static_cast<UTF16Unit>(0x0041),  // 'A'
      static_cast<UTF16Unit>(0x00A9),  // ©
      static_cast<UTF16Unit>(0x0042),  // 'B' (should not be reached if it stops at ©)
  };

  // Only room for 1 byte -> can write 'A' but not ©.
  size_t read = 0, written = 0;
  const auto out = Call_UTF16Nat_to_UTF8(in, /*outCap*/ 1, &read, &written);

  EXPECT_EQ(out, Bytes({0x41}));
  EXPECT_EQ(read, 1u);       // should not consume © when there's no room
  EXPECT_EQ(written, 1u);
}

// ------------------------------------------------------------
// Exceptional / error-like observable cases
// ------------------------------------------------------------

TEST_F(UnicodeConversionsTest_2072, InputEndsWithLoneHighSurrogateStopsBeforeIt_2072) {
  // 'A' then a lone high surrogate (invalid / incomplete pair)
  const std::vector<UTF16Unit> in = {
      static_cast<UTF16Unit>(0x0041),  // 'A'
      static_cast<UTF16Unit>(0xD800),  // high surrogate without a following low surrogate
  };

  size_t read = 0, written = 0;
  const auto out = Call_UTF16Nat_to_UTF8(in, /*outCap*/ 16, &read, &written);

  // Should convert what it can ('A') and stop when it encounters an incomplete surrogate pair.
  EXPECT_EQ(out, Bytes({0x41}));
  EXPECT_EQ(read, 1u);
  EXPECT_EQ(written, 1u);
}

TEST_F(UnicodeConversionsTest_2072, OutputBufferTooSmallForSurrogateUTF8SequenceStopsBeforePair_2072) {
  // 😀 needs 4 bytes in UTF-8.
  const std::vector<UTF16Unit> in = {
      static_cast<UTF16Unit>(0xD83D),
      static_cast<UTF16Unit>(0xDE00),
  };

  size_t read = 0, written = 0;
  const auto out = Call_UTF16Nat_to_UTF8(in, /*outCap*/ 3, &read, &written);

  // Not enough room to write the UTF-8 sequence; should write nothing and not consume input.
  EXPECT_TRUE(out.empty());
  EXPECT_EQ(read, 0u);
  EXPECT_EQ(written, 0u);
}