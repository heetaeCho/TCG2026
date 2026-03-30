// ============================================================================
//  TEST_ID: 2073
//  Unit tests for UTF32Nat_to_UTF8 (black-box tests via observable outputs)
//  File under test: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// NOTE:
// UTF32Nat_to_UTF8 is declared `static` in the production .cpp file. These tests
// assume the test build compiles this source file into the test binary (common in
// some projects), so we can include it to get access to the internal-linkage symbol.
//
// If your build links UnicodeConversions.cpp separately into a library/object that is
// ALSO linked into this test, including the .cpp here may cause duplicate symbol errors.
// In that case, compile this test by adding UnicodeConversions.cpp ONLY ONCE (either
// as part of the test target sources, or via the library, but not both).
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class UTF32NatToUTF8Test_2073 : public ::testing::Test {};

static std::vector<UTF8Unit> RunUTF32NatToUTF8(
    const std::vector<UTF32Unit>& in,
    size_t outCapacity,
    size_t* utf32Read,
    size_t* utf8Written) {
  std::vector<UTF8Unit> out(outCapacity);
  *utf32Read = 0;
  *utf8Written = 0;

  UTF32Nat_to_UTF8(in.data(), in.size(), out.data(), out.size(), utf32Read, utf8Written);
  out.resize(*utf8Written);
  return out;
}

}  // namespace

TEST_F(UTF32NatToUTF8Test_2073, AsciiOnly_ExactFit_WritesAll_2073) {
  const std::vector<UTF32Unit> in = {UTF32Unit('A'), UTF32Unit('B'), UTF32Unit('C')};

  size_t utf32Read = 0, utf8Written = 0;
  const auto out = RunUTF32NatToUTF8(in, /*outCapacity=*/3, &utf32Read, &utf8Written);

  ASSERT_EQ(utf32Read, 3u);
  ASSERT_EQ(utf8Written, 3u);
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], UTF8Unit('A'));
  EXPECT_EQ(out[1], UTF8Unit('B'));
  EXPECT_EQ(out[2], UTF8Unit('C'));
}

TEST_F(UTF32NatToUTF8Test_2073, AsciiOnly_OutputShorter_StopsAtCapacity_2073) {
  const std::vector<UTF32Unit> in = {
      UTF32Unit('A'), UTF32Unit('B'), UTF32Unit('C'), UTF32Unit('D')};

  size_t utf32Read = 0, utf8Written = 0;
  const auto out = RunUTF32NatToUTF8(in, /*outCapacity=*/2, &utf32Read, &utf8Written);

  ASSERT_EQ(utf32Read, 2u);
  ASSERT_EQ(utf8Written, 2u);
  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(out[0], UTF8Unit('A'));
  EXPECT_EQ(out[1], UTF8Unit('B'));
}

TEST_F(UTF32NatToUTF8Test_2073, MixedAsciiAndTwoByteCodePoint_EncodesBoth_2073) {
  // U+00A9 COPYRIGHT SIGN => UTF-8: C2 A9
  const std::vector<UTF32Unit> in = {UTF32Unit('A'), UTF32Unit(0x00A9)};

  size_t utf32Read = 0, utf8Written = 0;
  const auto out = RunUTF32NatToUTF8(in, /*outCapacity=*/8, &utf32Read, &utf8Written);

  ASSERT_EQ(utf32Read, 2u);
  ASSERT_EQ(out.size(), utf8Written);
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], UTF8Unit('A'));
  EXPECT_EQ(out[1], UTF8Unit(0xC2));
  EXPECT_EQ(out[2], UTF8Unit(0xA9));
}

TEST_F(UTF32NatToUTF8Test_2073, TwoByteCodePoint_OutputTooSmall_WritesNothing_ReadsNothing_2073) {
  // U+00A9 needs 2 bytes; output capacity is 1 => should not consume input.
  const std::vector<UTF32Unit> in = {UTF32Unit(0x00A9)};

  size_t utf32Read = 0, utf8Written = 0;
  const auto out = RunUTF32NatToUTF8(in, /*outCapacity=*/1, &utf32Read, &utf8Written);

  EXPECT_EQ(utf32Read, 0u);
  EXPECT_EQ(utf8Written, 0u);
  EXPECT_TRUE(out.empty());
}

TEST_F(UTF32NatToUTF8Test_2073, AsciiThenTwoByte_NoRoomForSecond_ConsumesAsciiOnly_2073) {
  // Output capacity allows only the leading ASCII byte; should stop before U+00A9.
  const std::vector<UTF32Unit> in = {UTF32Unit('Z'), UTF32Unit(0x00A9)};

  size_t utf32Read = 0, utf8Written = 0;
  const auto out = RunUTF32NatToUTF8(in, /*outCapacity=*/1, &utf32Read, &utf8Written);

  ASSERT_EQ(utf32Read, 1u);
  ASSERT_EQ(utf8Written, 1u);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], UTF8Unit('Z'));
}

TEST_F(UTF32NatToUTF8Test_2073, FourByteCodePoint_EncodesEmoji_2073) {
  // U+1F600 GRINNING FACE => UTF-8: F0 9F 98 80
  const std::vector<UTF32Unit> in = {UTF32Unit(0x1F600)};

  size_t utf32Read = 0, utf8Written = 0;
  const auto out = RunUTF32NatToUTF8(in, /*outCapacity=*/8, &utf32Read, &utf8Written);

  ASSERT_EQ(utf32Read, 1u);
  ASSERT_EQ(out.size(), utf8Written);
  ASSERT_EQ(out.size(), 4u);
  EXPECT_EQ(out[0], UTF8Unit(0xF0));
  EXPECT_EQ(out[1], UTF8Unit(0x9F));
  EXPECT_EQ(out[2], UTF8Unit(0x98));
  EXPECT_EQ(out[3], UTF8Unit(0x80));
}

TEST_F(UTF32NatToUTF8Test_2073, EmptyInput_WritesNothing_2073) {
  const std::vector<UTF32Unit> in;

  size_t utf32Read = 123, utf8Written = 456;
  std::vector<UTF8Unit> out(4, UTF8Unit(0xEE));

  UTF32Nat_to_UTF8(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf8Written);

  EXPECT_EQ(utf32Read, 0u);
  EXPECT_EQ(utf8Written, 0u);
}

TEST_F(UTF32NatToUTF8Test_2073, ZeroOutputCapacity_WritesNothing_ReadsNothing_2073) {
  const std::vector<UTF32Unit> in = {UTF32Unit('A')};

  size_t utf32Read = 0, utf8Written = 0;
  std::vector<UTF8Unit> out;  // size = 0

  UTF32Nat_to_UTF8(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf8Written);

  EXPECT_EQ(utf32Read, 0u);
  EXPECT_EQ(utf8Written, 0u);
}

#if GTEST_HAS_DEATH_TEST
// UC_Assert behavior may vary by build (enabled/disabled). We only run death
// checks in debug-like builds where asserts are expected to terminate.
#if !defined(NDEBUG)
TEST_F(UTF32NatToUTF8Test_2073, NullPointers_TriggerAssert_2073) {
  size_t utf32Read = 0, utf8Written = 0;
  const UTF32Unit inOne[1] = {UTF32Unit('A')};
  UTF8Unit outOne[1] = {0};

  EXPECT_DEATH(
      UTF32Nat_to_UTF8(nullptr, 1, outOne, 1, &utf32Read, &utf8Written),
      "");
  EXPECT_DEATH(
      UTF32Nat_to_UTF8(inOne, 1, nullptr, 1, &utf32Read, &utf8Written),
      "");
  EXPECT_DEATH(
      UTF32Nat_to_UTF8(inOne, 1, outOne, 1, nullptr, &utf8Written),
      "");
  EXPECT_DEATH(
      UTF32Nat_to_UTF8(inOne, 1, outOne, 1, &utf32Read, nullptr),
      "");
}
#endif  // !defined(NDEBUG)
#endif  // GTEST_HAS_DEATH_TEST