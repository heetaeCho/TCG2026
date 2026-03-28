// ============================================================================
// TEST_ID: 2074
// Unit tests for UTF16Nat_to_UTF32Nat (UnicodeConversions.cpp)
// ============================================================================

#include <gtest/gtest.h>
#include <cstddef>
#include <cstdint>
#include <algorithm>

// Include the implementation file directly to access the internal `static`
// function in this translation unit.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

// Sentinel to detect untouched output slots.
static const UTF32Unit kSentinel32 = static_cast<UTF32Unit>(0xDEADBEEFu);

class UTF16NatToUTF32NatTest_2074 : public ::testing::Test {
protected:
  void FillSentinel(UTF32Unit* buf, size_t len) {
    std::fill(buf, buf + len, kSentinel32);
  }
};

}  // namespace

TEST_F(UTF16NatToUTF32NatTest_2074, ConvertsBMPUnits_2074) {
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0x0041),  // 'A'
      static_cast<UTF16Unit>(0x0062),  // 'b'
      static_cast<UTF16Unit>(0x03A9),  // 'Ω'
      static_cast<UTF16Unit>(0x20AC),  // '€'
  };
  UTF32Unit out[4];
  FillSentinel(out, 4);

  size_t utf16Read = 999;
  size_t utf32Written = 999;

  UTF16Nat_to_UTF32Nat(in, 4, out, 4, &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 4u);
  EXPECT_EQ(utf32Written, 4u);

  EXPECT_EQ(out[0], static_cast<UTF32Unit>(0x0041));
  EXPECT_EQ(out[1], static_cast<UTF32Unit>(0x0062));
  EXPECT_EQ(out[2], static_cast<UTF32Unit>(0x03A9));
  EXPECT_EQ(out[3], static_cast<UTF32Unit>(0x20AC));
}

TEST_F(UTF16NatToUTF32NatTest_2074, StopsWhenOutputBufferIsFull_2074) {
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0x0041),
      static_cast<UTF16Unit>(0x0042),
      static_cast<UTF16Unit>(0x0043),
      static_cast<UTF16Unit>(0x0044),
      static_cast<UTF16Unit>(0x0045),
  };
  UTF32Unit out[3];
  FillSentinel(out, 3);

  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Nat_to_UTF32Nat(in, 5, out, 3, &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 3u);
  EXPECT_EQ(utf32Written, 3u);

  EXPECT_EQ(out[0], static_cast<UTF32Unit>(0x0041));
  EXPECT_EQ(out[1], static_cast<UTF32Unit>(0x0042));
  EXPECT_EQ(out[2], static_cast<UTF32Unit>(0x0043));
}

TEST_F(UTF16NatToUTF32NatTest_2074, ConvertsSingleValidSurrogatePair_2074) {
  // U+1F600 GRINNING FACE 😀 => UTF-16: D83D DE00
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0xD83D),
      static_cast<UTF16Unit>(0xDE00),
  };
  UTF32Unit out[1];
  FillSentinel(out, 1);

  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Nat_to_UTF32Nat(in, 2, out, 1, &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 2u);
  EXPECT_EQ(utf32Written, 1u);
  EXPECT_EQ(out[0], static_cast<UTF32Unit>(0x0001F600));
}

TEST_F(UTF16NatToUTF32NatTest_2074, ConvertsMixedBMPAndSurrogatePairs_2074) {
  // 'A', 😀 (D83D DE00), 'B'
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0x0041),
      static_cast<UTF16Unit>(0xD83D),
      static_cast<UTF16Unit>(0xDE00),
      static_cast<UTF16Unit>(0x0042),
  };
  UTF32Unit out[3];
  FillSentinel(out, 3);

  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Nat_to_UTF32Nat(in, 4, out, 3, &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 4u);
  EXPECT_EQ(utf32Written, 3u);

  EXPECT_EQ(out[0], static_cast<UTF32Unit>(0x0041));
  EXPECT_EQ(out[1], static_cast<UTF32Unit>(0x0001F600));
  EXPECT_EQ(out[2], static_cast<UTF32Unit>(0x0042));
}

TEST_F(UTF16NatToUTF32NatTest_2074, StopsBeforeIncompleteTrailingSurrogatePair_2074) {
  // The code comment explicitly indicates it stops if the input ends
  // in the middle of a surrogate pair.
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0x0041),  // 'A'
      static_cast<UTF16Unit>(0xD83D),  // high surrogate without a following low surrogate
  };
  UTF32Unit out[2];
  FillSentinel(out, 2);

  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Nat_to_UTF32Nat(in, 2, out, 2, &utf16Read, &utf32Written);

  // Should convert the leading BMP unit, then stop before consuming the
  // incomplete surrogate.
  EXPECT_EQ(utf16Read, 1u);
  EXPECT_EQ(utf32Written, 1u);

  EXPECT_EQ(out[0], static_cast<UTF32Unit>(0x0041));
  EXPECT_EQ(out[1], kSentinel32);  // remains untouched
}

TEST_F(UTF16NatToUTF32NatTest_2074, HandlesZeroLengths_2074) {
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0x0041)};
  UTF32Unit out[1];
  FillSentinel(out, 1);

  // Case 1: utf16Len == 0
  {
    size_t utf16Read = 123;
    size_t utf32Written = 456;
    UTF16Nat_to_UTF32Nat(in, 0, out, 1, &utf16Read, &utf32Written);
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
    EXPECT_EQ(out[0], kSentinel32);
  }

  // Case 2: utf32Len == 0
  {
    size_t utf16Read = 123;
    size_t utf32Written = 456;
    UTF16Nat_to_UTF32Nat(in, 1, out, 0, &utf16Read, &utf32Written);
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
    EXPECT_EQ(out[0], kSentinel32);
  }
}