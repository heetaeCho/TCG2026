// ============================================================================
// TEST_ID 2075
// Unit tests for UTF32Nat_to_UTF16Nat (static function in UnicodeConversions.cpp)
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <vector>

// NOTE:
// The function under test is `static` inside UnicodeConversions.cpp, so it is not
// link-visible from other translation units. To test it as a black box via its
// signature, we include the .cpp directly in this test TU.
#include "./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class UTF32NatToUTF16NatTest_2075 : public ::testing::Test {};

static std::vector<UTF16Unit> MakeUTF16Buffer(size_t n, UTF16Unit fill = UTF16Unit(0xFFFF)) {
  return std::vector<UTF16Unit>(n, fill);
}

TEST_F(UTF32NatToUTF16NatTest_2075, ConvertsBMPOnly_2075) {
  const UTF32Unit utf32In[] = {
      UTF32Unit(0x0000), UTF32Unit(0x0041), UTF32Unit(0x20AC), UTF32Unit(0xFFFF)};
  const size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

  auto utf16Out = MakeUTF16Buffer(16, UTF16Unit(0xEEEE));
  size_t utf32Read = 999;
  size_t utf16Written = 999;

  UTF32Nat_to_UTF16Nat(utf32In, utf32Len, utf16Out.data(), utf16Out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, utf32Len);
  EXPECT_EQ(utf16Written, utf32Len);

  EXPECT_EQ(utf16Out[0], UTF16Unit(0x0000));
  EXPECT_EQ(utf16Out[1], UTF16Unit(0x0041));
  EXPECT_EQ(utf16Out[2], UTF16Unit(0x20AC));
  EXPECT_EQ(utf16Out[3], UTF16Unit(0xFFFF));
}

TEST_F(UTF32NatToUTF16NatTest_2075, ConvertsSingleSupplementaryToSurrogatePair_2075) {
  // U+1F600 GRINNING FACE => UTF-16: D83D DE00
  const UTF32Unit utf32In[] = {UTF32Unit(0x1F600)};
  const size_t utf32Len = 1;

  auto utf16Out = MakeUTF16Buffer(2, UTF16Unit(0xEEEE));
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Nat_to_UTF16Nat(utf32In, utf32Len, utf16Out.data(), utf16Out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, size_t(1));
  EXPECT_EQ(utf16Written, size_t(2));
  EXPECT_EQ(utf16Out[0], UTF16Unit(0xD83D));
  EXPECT_EQ(utf16Out[1], UTF16Unit(0xDE00));
}

TEST_F(UTF32NatToUTF16NatTest_2075, ConvertsMixedBMPAndSupplementary_2075) {
  // 'A', U+1F600, '€'
  const UTF32Unit utf32In[] = {UTF32Unit(0x0041), UTF32Unit(0x1F600), UTF32Unit(0x20AC)};
  const size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

  auto utf16Out = MakeUTF16Buffer(8, UTF16Unit(0xEEEE));
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Nat_to_UTF16Nat(utf32In, utf32Len, utf16Out.data(), utf16Out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, utf32Len);
  EXPECT_EQ(utf16Written, size_t(4));  // 1 (A) + 2 (surrogates) + 1 (Euro)

  EXPECT_EQ(utf16Out[0], UTF16Unit(0x0041));
  EXPECT_EQ(utf16Out[1], UTF16Unit(0xD83D));
  EXPECT_EQ(utf16Out[2], UTF16Unit(0xDE00));
  EXPECT_EQ(utf16Out[3], UTF16Unit(0x20AC));
}

TEST_F(UTF32NatToUTF16NatTest_2075, StopsWhenUTF16BufferTooSmallForBMPRun_2075) {
  const UTF32Unit utf32In[] = {UTF32Unit(0x0041), UTF32Unit(0x0042), UTF32Unit(0x0043)};
  const size_t utf32Len = 3;

  // Only room for 2 UTF-16 code units.
  auto utf16Out = MakeUTF16Buffer(2, UTF16Unit(0xEEEE));
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Nat_to_UTF16Nat(utf32In, utf32Len, utf16Out.data(), utf16Out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, size_t(2));
  EXPECT_EQ(utf16Written, size_t(2));
  EXPECT_EQ(utf16Out[0], UTF16Unit(0x0041));
  EXPECT_EQ(utf16Out[1], UTF16Unit(0x0042));
}

TEST_F(UTF32NatToUTF16NatTest_2075, DoesNotConsumeSupplementaryIfOnlyOneUTF16UnitLeft_2075) {
  // First BMP 'A', then a supplementary char needing 2 UTF-16 units.
  const UTF32Unit utf32In[] = {UTF32Unit(0x0041), UTF32Unit(0x1F600)};
  const size_t utf32Len = 2;

  // Only room for 2 UTF-16 units total: should write 'A' (1 unit) and then be unable
  // to write the surrogate pair (needs 2, only 1 left). Expect it stops before consuming it.
  auto utf16Out = MakeUTF16Buffer(2, UTF16Unit(0xEEEE));
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Nat_to_UTF16Nat(utf32In, utf32Len, utf16Out.data(), utf16Out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, size_t(1));
  EXPECT_EQ(utf16Written, size_t(1));
  EXPECT_EQ(utf16Out[0], UTF16Unit(0x0041));
  // utf16Out[1] left unchanged or unspecified; we just ensure we didn't write the pair.
  EXPECT_NE(utf16Out[1], UTF16Unit(0xD83D));
}

TEST_F(UTF32NatToUTF16NatTest_2075, ZeroLengthsProduceZeroCounts_2075) {
  const UTF32Unit utf32In[] = {UTF32Unit(0x0041)};
  auto utf16Out = MakeUTF16Buffer(4, UTF16Unit(0xEEEE));

  {
    size_t utf32Read = 1;
    size_t utf16Written = 1;
    UTF32Nat_to_UTF16Nat(utf32In, 0, utf16Out.data(), utf16Out.size(), &utf32Read, &utf16Written);
    EXPECT_EQ(utf32Read, size_t(0));
    EXPECT_EQ(utf16Written, size_t(0));
  }

  {
    size_t utf32Read = 1;
    size_t utf16Written = 1;
    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out.data(), 0, &utf32Read, &utf16Written);
    EXPECT_EQ(utf32Read, size_t(0));
    EXPECT_EQ(utf16Written, size_t(0));
  }
}

TEST_F(UTF32NatToUTF16NatTest_2075, NullPointerArgumentsDeathIfSupported_2075) {
  // UC_Assert is expected to enforce non-null arguments (debug builds / assert-enabled).
  // We use a death test if supported by the platform/build.
#if GTEST_HAS_DEATH_TEST
  UTF32Unit inOne = UTF32Unit(0x0041);
  UTF16Unit outOne = UTF16Unit(0);

  size_t utf32Read = 0;
  size_t utf16Written = 0;

  ASSERT_DEATH_IF_SUPPORTED(
      UTF32Nat_to_UTF16Nat(nullptr, 1, &outOne, 1, &utf32Read, &utf16Written), "");

  ASSERT_DEATH_IF_SUPPORTED(
      UTF32Nat_to_UTF16Nat(&inOne, 1, nullptr, 1, &utf32Read, &utf16Written), "");

  ASSERT_DEATH_IF_SUPPORTED(
      UTF32Nat_to_UTF16Nat(&inOne, 1, &outOne, 1, nullptr, &utf16Written), "");

  ASSERT_DEATH_IF_SUPPORTED(
      UTF32Nat_to_UTF16Nat(&inOne, 1, &outOne, 1, &utf32Read, nullptr), "");
#else
  GTEST_SKIP() << "Death tests are not supported in this build configuration.";
#endif
}

}  // namespace