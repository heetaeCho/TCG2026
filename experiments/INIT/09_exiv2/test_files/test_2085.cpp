// =================================================================================================
// TEST_ID: 2085
// Unit tests for UTF32Swp_to_UTF16Swp (black-box via interface/observable outputs)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

// Include the implementation file to access the internal (static) function under test.
//
// NOTE: These tests assume the test target does NOT also compile/link another copy of
// UnicodeConversions.cpp (to avoid ODR/linker issues with non-static symbols). This is a
// common pattern when unit-testing internal static helpers.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

static inline bool IsLittleEndianHost() {
  const uint16_t one = 1;
  return (*reinterpret_cast<const uint8_t*>(&one) == 1);
}

static inline uint16_t BSwap16(uint16_t v) {
  return static_cast<uint16_t>((v >> 8) | (v << 8));
}

static inline uint32_t BSwap32(uint32_t v) {
  return ((v & 0x000000FFu) << 24) | ((v & 0x0000FF00u) << 8) | ((v & 0x00FF0000u) >> 8) |
         ((v & 0xFF000000u) >> 24);
}

// "Swp" in this file denotes "opposite byte order". For unit tests, we can construct Swp values
// by byte-swapping native integers.
static inline UTF32Unit ToUTF32Swp(uint32_t cp) {
  return static_cast<UTF32Unit>(BSwap32(static_cast<uint32_t>(cp)));
}
static inline uint16_t FromUTF16Swp(UTF16Unit u16swp) {
  return BSwap16(static_cast<uint16_t>(u16swp));
}

static inline void ExpectSurrogatePair(uint32_t codePoint, uint16_t lead, uint16_t trail) {
  ASSERT_GE(codePoint, 0x10000u);
  ASSERT_LE(codePoint, 0x10FFFFu);

  const uint32_t v = codePoint - 0x10000u;
  const uint16_t expLead = static_cast<uint16_t>(0xD800u + ((v >> 10) & 0x3FFu));
  const uint16_t expTrail = static_cast<uint16_t>(0xDC00u + (v & 0x3FFu));

  EXPECT_EQ(expLead, lead);
  EXPECT_EQ(expTrail, trail);
}

class UTF32Swp_to_UTF16SwpTest_2085 : public ::testing::Test {
 protected:
  void SetUp() override {
    // This static helper uses ::swap32to16Offset for its fast BMP path (<= 0xFFFF).
    // On little-endian hosts, the desired 16-bit halfword is at offset 1; on big-endian, offset 0.
    savedOffset_ = ::swap32to16Offset;
    ::swap32to16Offset = IsLittleEndianHost() ? 1u : 0u;
  }

  void TearDown() override { ::swap32to16Offset = savedOffset_; }

 private:
  size_t savedOffset_{0};
};

}  // namespace

TEST_F(UTF32Swp_to_UTF16SwpTest_2085, ConvertsBmpCodePointsAndReportsLengths_2085) {
  const std::vector<uint32_t> cps = {0x0041u, 0x00E9u, 0x20ACu};  // 'A', 'é', '€'
  std::vector<UTF32Unit> in;
  in.reserve(cps.size());
  for (uint32_t cp : cps) in.push_back(ToUTF32Swp(cp));

  std::vector<UTF16Unit> out(cps.size(), static_cast<UTF16Unit>(0xFFFFu));
  size_t utf32Read = 999, utf16Written = 999;

  UTF32Swp_to_UTF16Swp(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(in.size(), utf32Read);
  EXPECT_EQ(out.size(), utf16Written);

  for (size_t i = 0; i < cps.size(); ++i) {
    EXPECT_EQ(static_cast<uint16_t>(cps[i]), FromUTF16Swp(out[i]));
  }
}

TEST_F(UTF32Swp_to_UTF16SwpTest_2085, ConvertsNonBmpToSurrogatePairs_2085) {
  const std::vector<uint32_t> cps = {0x1F600u, 0x10437u};  // 😀, 𐐷
  std::vector<UTF32Unit> in;
  in.reserve(cps.size());
  for (uint32_t cp : cps) in.push_back(ToUTF32Swp(cp));

  std::vector<UTF16Unit> out(/*utf16Len*/ 4, static_cast<UTF16Unit>(0));
  size_t utf32Read = 0, utf16Written = 0;

  UTF32Swp_to_UTF16Swp(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(2u, utf32Read);
  EXPECT_EQ(4u, utf16Written);

  const uint16_t lead0 = FromUTF16Swp(out[0]);
  const uint16_t trail0 = FromUTF16Swp(out[1]);
  const uint16_t lead1 = FromUTF16Swp(out[2]);
  const uint16_t trail1 = FromUTF16Swp(out[3]);

  ExpectSurrogatePair(cps[0], lead0, trail0);
  ExpectSurrogatePair(cps[1], lead1, trail1);
}

TEST_F(UTF32Swp_to_UTF16SwpTest_2085, StopsWhenUtf16BufferTooSmallForSurrogatePair_2085) {
  // One non-BMP code point requires a surrogate pair (2 UTF16 units), but output has room for 1.
  const std::vector<uint32_t> cps = {0x1F600u};
  const UTF32Unit in[1] = {ToUTF32Swp(cps[0])};

  UTF16Unit out[1];
  out[0] = static_cast<UTF16Unit>(0xA5A5u);  // sentinel
  size_t utf32Read = 777, utf16Written = 777;

  UTF32Swp_to_UTF16Swp(in, 1, out, 1, &utf32Read, &utf16Written);

  // Observable behavior: nothing should be fully written if it can't fit.
  EXPECT_EQ(0u, utf32Read);
  EXPECT_EQ(0u, utf16Written);
  EXPECT_EQ(static_cast<UTF16Unit>(0xA5A5u), out[0]);  // should remain unchanged
}

TEST_F(UTF32Swp_to_UTF16SwpTest_2085, ConvertsOnlyWhatFitsWhenOutputShorterThanInputBmpOnly_2085) {
  const std::vector<uint32_t> cps = {0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u};  // A B C D E
  std::vector<UTF32Unit> in;
  in.reserve(cps.size());
  for (uint32_t cp : cps) in.push_back(ToUTF32Swp(cp));

  std::vector<UTF16Unit> out(/*utf16Len*/ 3, static_cast<UTF16Unit>(0));
  size_t utf32Read = 0, utf16Written = 0;

  UTF32Swp_to_UTF16Swp(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(3u, utf32Read);
  EXPECT_EQ(3u, utf16Written);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(static_cast<uint16_t>(cps[i]), FromUTF16Swp(out[i]));
  }
}

TEST_F(UTF32Swp_to_UTF16SwpTest_2085, MixedBmpAndNonBmpDoesNotPartiallyWriteSurrogatePair_2085) {
  // With utf16Len=3, we can fit two BMP (2 units) but not the following non-BMP (needs 2 units).
  const std::vector<uint32_t> cps = {0x0061u, 0x0062u, 0x1F600u, 0x0063u};  // a b 😀 c
  std::vector<UTF32Unit> in;
  in.reserve(cps.size());
  for (uint32_t cp : cps) in.push_back(ToUTF32Swp(cp));

  std::vector<UTF16Unit> out(/*utf16Len*/ 3, static_cast<UTF16Unit>(0xBEEFu));
  size_t utf32Read = 0, utf16Written = 0;

  UTF32Swp_to_UTF16Swp(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf16Written);

  // Should stop before writing the surrogate pair.
  EXPECT_EQ(2u, utf32Read);
  EXPECT_EQ(2u, utf16Written);

  EXPECT_EQ(static_cast<uint16_t>(0x0061u), FromUTF16Swp(out[0]));
  EXPECT_EQ(static_cast<uint16_t>(0x0062u), FromUTF16Swp(out[1]));
  EXPECT_EQ(static_cast<UTF16Unit>(0xBEEFu), out[2]);  // untouched sentinel
}