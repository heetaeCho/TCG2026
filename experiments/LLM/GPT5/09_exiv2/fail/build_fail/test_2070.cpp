// =================================================================================================
// TEST_ID: 2070
// Unit tests for UTF8_to_UTF16Nat (UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <array>

// Include the implementation file to access the internal-linkage (static) function under test.
// This is a common/unit-test technique when the function is not exposed via a header.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class UTF8_to_UTF16NatTest_2070 : public ::testing::Test {
protected:
  static std::vector<UTF16Unit> RunConvert(const std::vector<UTF8Unit>& in,
                                          size_t outUnits,
                                          size_t* utf8Read,
                                          size_t* utf16Written) {
    std::vector<UTF16Unit> out(outUnits, UTF16Unit(0xDEAD));  // sentinel
    *utf8Read = 0;
    *utf16Written = 0;

    UTF8_to_UTF16Nat(in.data(), in.size(), out.data(), out.size(), utf8Read, utf16Written);
    return out;
  }

  static void ExpectSentinelUnchangedBeyond(const std::vector<UTF16Unit>& out, size_t written) {
    for (size_t i = written; i < out.size(); ++i) {
      EXPECT_EQ(out[i], UTF16Unit(0xDEAD)) << "Index " << i << " should remain sentinel";
    }
  }
};

TEST_F(UTF8_to_UTF16NatTest_2070, ConvertsAsciiOnlyAndReportsCounts_2070) {
  const std::vector<UTF8Unit> in = {
      UTF8Unit('A'), UTF8Unit('B'), UTF8Unit('C'),
      UTF8Unit('x'), UTF8Unit('y'), UTF8Unit('z'),
  };

  size_t utf8Read = 0, utf16Written = 0;
  auto out = RunConvert(in, /*outUnits*/ 16, &utf8Read, &utf16Written);

  ASSERT_EQ(utf8Read, in.size());
  ASSERT_EQ(utf16Written, in.size());

  EXPECT_EQ(out[0], UTF16Unit('A'));
  EXPECT_EQ(out[1], UTF16Unit('B'));
  EXPECT_EQ(out[2], UTF16Unit('C'));
  EXPECT_EQ(out[3], UTF16Unit('x'));
  EXPECT_EQ(out[4], UTF16Unit('y'));
  EXPECT_EQ(out[5], UTF16Unit('z'));
  ExpectSentinelUnchangedBeyond(out, utf16Written);
}

TEST_F(UTF8_to_UTF16NatTest_2070, ConvertsMixedAsciiAndMultiByteAndSurrogate_2070) {
  // "A" + U+00A9 (©) + U+20AC (€) + U+1F600 (😀) + "Z"
  const std::vector<UTF8Unit> in = {
      UTF8Unit('A'),
      UTF8Unit(0xC2), UTF8Unit(0xA9),                   // ©
      UTF8Unit(0xE2), UTF8Unit(0x82), UTF8Unit(0xAC),   // €
      UTF8Unit(0xF0), UTF8Unit(0x9F), UTF8Unit(0x98), UTF8Unit(0x80),  // 😀
      UTF8Unit('Z'),
  };

  size_t utf8Read = 0, utf16Written = 0;
  auto out = RunConvert(in, /*outUnits*/ 16, &utf8Read, &utf16Written);

  ASSERT_EQ(utf8Read, in.size());

  // Expected UTF-16 code units:
  // 'A' -> 0x0041
  // ©   -> 0x00A9
  // €   -> 0x20AC
  // 😀  -> surrogate pair 0xD83D 0xDE00
  // 'Z' -> 0x005A
  ASSERT_EQ(utf16Written, size_t(1 + 1 + 1 + 2 + 1));

  EXPECT_EQ(out[0], UTF16Unit(0x0041));
  EXPECT_EQ(out[1], UTF16Unit(0x00A9));
  EXPECT_EQ(out[2], UTF16Unit(0x20AC));
  EXPECT_EQ(out[3], UTF16Unit(0xD83D));
  EXPECT_EQ(out[4], UTF16Unit(0xDE00));
  EXPECT_EQ(out[5], UTF16Unit(0x005A));
  ExpectSentinelUnchangedBeyond(out, utf16Written);
}

TEST_F(UTF8_to_UTF16NatTest_2070, StopsWhenOutputBufferTooSmallForAllAscii_2070) {
  const std::vector<UTF8Unit> in = {
      UTF8Unit('1'), UTF8Unit('2'), UTF8Unit('3'),
      UTF8Unit('4'), UTF8Unit('5'),
  };

  size_t utf8Read = 0, utf16Written = 0;
  auto out = RunConvert(in, /*outUnits*/ 3, &utf8Read, &utf16Written);

  ASSERT_EQ(utf16Written, size_t(3));
  ASSERT_EQ(utf8Read, size_t(3));  // should consume only what fits in output

  EXPECT_EQ(out[0], UTF16Unit('1'));
  EXPECT_EQ(out[1], UTF16Unit('2'));
  EXPECT_EQ(out[2], UTF16Unit('3'));
}

TEST_F(UTF8_to_UTF16NatTest_2070, DoesNotConsumePartialTrailingUtf8Sequence_2070) {
  // 'A' followed by an incomplete 2-byte sequence (0xC2 needs a continuation byte).
  const std::vector<UTF8Unit> in = {
      UTF8Unit('A'),
      UTF8Unit(0xC2),  // incomplete
  };

  size_t utf8Read = 0, utf16Written = 0;
  auto out = RunConvert(in, /*outUnits*/ 8, &utf8Read, &utf16Written);

  // Expect it to convert 'A' then stop before consuming the incomplete sequence.
  ASSERT_EQ(utf16Written, size_t(1));
  ASSERT_EQ(utf8Read, size_t(1));

  EXPECT_EQ(out[0], UTF16Unit('A'));
  ExpectSentinelUnchangedBeyond(out, utf16Written);
}

TEST_F(UTF8_to_UTF16NatTest_2070, SurrogateNeedsTwoUtf16UnitsIfOnlyOneAvailableConsumesNothing_2070) {
  // Single emoji 😀 (U+1F600) requires 2 UTF-16 units.
  const std::vector<UTF8Unit> in = {
      UTF8Unit(0xF0), UTF8Unit(0x9F), UTF8Unit(0x98), UTF8Unit(0x80),
  };

  size_t utf8Read = 0, utf16Written = 0;
  auto out = RunConvert(in, /*outUnits*/ 1, &utf8Read, &utf16Written);

  // When there isn't enough UTF-16 space for the surrogate pair, conversion should stop
  // without consuming the UTF-8 sequence (observable via counts).
  EXPECT_EQ(utf16Written, size_t(0));
  EXPECT_EQ(utf8Read, size_t(0));
  ExpectSentinelUnchangedBeyond(out, utf16Written);
}

}  // namespace