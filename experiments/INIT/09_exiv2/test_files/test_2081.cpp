// =================================================================================================
// TEST_ID: 2081
// Unit tests for UTF8_to_UTF32Swp (static in UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Include the .cpp directly so this test TU can call the file-static function.
// This is intentional: UTF8_to_UTF32Swp has internal linkage (static).
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

static inline UTF32Unit Swap32Expected(UTF32Unit v) {
  // Expected byte-swap of a 32-bit code point into "swapped" UTF-32 units.
  // (This helper does NOT re-implement UTF-8 decoding; it only swaps bytes.)
  uint32_t x = static_cast<uint32_t>(v);
  return static_cast<UTF32Unit>(((x & 0x000000FFu) << 24) | ((x & 0x0000FF00u) << 8) |
                               ((x & 0x00FF0000u) >> 8) | ((x & 0xFF000000u) >> 24));
}

class UTF8_to_UTF32SwpTest_2081 : public ::testing::Test {};

TEST_F(UTF8_to_UTF32SwpTest_2081, ConvertsAsciiFastPathAndReportsLengths_2081) {
  const UTF8Unit in[] = {
      static_cast<UTF8Unit>('A'),
      static_cast<UTF8Unit>('b'),
      static_cast<UTF8Unit>('0'),
  };

  UTF32Unit out[8] = {};
  size_t utf8Read = 0;
  size_t utf32Written = 0;

  UTF8_to_UTF32Swp(in, /*utf8Len=*/3, out, /*utf32Len=*/8, &utf8Read, &utf32Written);

  EXPECT_EQ(utf8Read, 3u);
  EXPECT_EQ(utf32Written, 3u);

  // For ASCII, the implementation explicitly does: UTF32Unit(inUnit) << 24.
  EXPECT_EQ(static_cast<uint32_t>(out[0]), 0x41000000u);  // 'A'
  EXPECT_EQ(static_cast<uint32_t>(out[1]), 0x62000000u);  // 'b'
  EXPECT_EQ(static_cast<uint32_t>(out[2]), 0x30000000u);  // '0'
}

TEST_F(UTF8_to_UTF32SwpTest_2081, StopsWhenUtf32OutputBufferIsFull_2081) {
  const UTF8Unit in[] = {
      static_cast<UTF8Unit>('A'),
      static_cast<UTF8Unit>('B'),
      static_cast<UTF8Unit>('C'),
      static_cast<UTF8Unit>('D'),
  };

  UTF32Unit out[2] = {};
  size_t utf8Read = 0;
  size_t utf32Written = 0;

  UTF8_to_UTF32Swp(in, /*utf8Len=*/4, out, /*utf32Len=*/2, &utf8Read, &utf32Written);

  // Should write only up to utf32Len units and report matching consumption.
  EXPECT_EQ(utf32Written, 2u);
  EXPECT_EQ(utf8Read, 2u);

  EXPECT_EQ(static_cast<uint32_t>(out[0]), 0x41000000u);  // 'A'
  EXPECT_EQ(static_cast<uint32_t>(out[1]), 0x42000000u);  // 'B'
}

TEST_F(UTF8_to_UTF32SwpTest_2081, ConvertsMixedAsciiAndMultiByteAndReportsLengths_2081) {
  // "A¢B" : 'A' (0x41), '¢' U+00A2 encoded as UTF-8 C2 A2, 'B' (0x42)
  const UTF8Unit in[] = {
      static_cast<UTF8Unit>(0x41),
      static_cast<UTF8Unit>(0xC2),
      static_cast<UTF8Unit>(0xA2),
      static_cast<UTF8Unit>(0x42),
  };

  UTF32Unit out[8] = {};
  size_t utf8Read = 0;
  size_t utf32Written = 0;

  UTF8_to_UTF32Swp(in, /*utf8Len=*/4, out, /*utf32Len=*/8, &utf8Read, &utf32Written);

  EXPECT_EQ(utf8Read, 4u);
  EXPECT_EQ(utf32Written, 3u);

  EXPECT_EQ(static_cast<uint32_t>(out[0]), 0x41000000u);                // 'A'
  EXPECT_EQ(static_cast<uint32_t>(out[1]), static_cast<uint32_t>(Swap32Expected(0x000000A2u)));  // '¢'
  EXPECT_EQ(static_cast<uint32_t>(out[2]), 0x42000000u);                // 'B'
}

TEST_F(UTF8_to_UTF32SwpTest_2081, TruncatedMultiByteSequenceConsumesNothingAndWritesNothing_2081) {
  // Start of a 2-byte sequence (C2) but missing the continuation byte.
  const UTF8Unit in[] = {static_cast<UTF8Unit>(0xC2)};

  UTF32Unit out[4] = {};
  size_t utf8Read = 999;       // sentinel
  size_t utf32Written = 999;   // sentinel

  UTF8_to_UTF32Swp(in, /*utf8Len=*/1, out, /*utf32Len=*/4, &utf8Read, &utf32Written);

  // Per observable contract in this implementation: if CodePoint_from_UTF8_Multi reports len == 0,
  // it exits without consuming input or producing output.
  EXPECT_EQ(utf8Read, 0u);
  EXPECT_EQ(utf32Written, 0u);
}

}  // namespace