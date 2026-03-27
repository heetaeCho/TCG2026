// =================================================================================================
// TEST_ID: 2087
// Unit tests for UTF16Swp_to_UTF32Nat (UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// NOTE:
// The function under test is declared `static` in the .cpp file, so it is not link-visible.
// We include the implementation file to test it as a black box via its interface.
// This is a common approach for unit-testing internal-file-scope helpers.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

static UTF16Unit Swap16(UTF16Unit v) {
  // Pure byte swap helper for test data preparation (not re-implementing the CUT logic).
  return static_cast<UTF16Unit>((v >> 8) | (v << 8));
}

TEST(UTF16Swp_to_UTF32NatTest_2087, ConvertsNonSurrogates_WhenBytesAreSelfSwapped_2087) {
  // Use values with identical high/low bytes so swapping has no effect (0x1212 -> 0x1212).
  const std::vector<UTF16Unit> utf16In = {static_cast<UTF16Unit>(0x1212),
                                         static_cast<UTF16Unit>(0x3434),
                                         static_cast<UTF16Unit>(0x5656)};

  std::vector<UTF32Unit> utf32Out(utf16In.size(), 0);

  size_t utf16Read = 999;
  size_t utf32Written = 999;

  UTF16Swp_to_UTF32Nat(utf16In.data(), utf16In.size(), utf32Out.data(), utf32Out.size(), &utf16Read,
                       &utf32Written);

  EXPECT_EQ(utf16Read, utf16In.size());
  EXPECT_EQ(utf32Written, utf16In.size());

  for (size_t i = 0; i < utf16In.size(); ++i) {
    EXPECT_EQ(utf32Out[i], static_cast<UTF32Unit>(utf16In[i]));
  }
}

TEST(UTF16Swp_to_UTF32NatTest_2087, RespectsUtf32OutputCapacity_OnNonSurrogates_2087) {
  const std::vector<UTF16Unit> utf16In = {static_cast<UTF16Unit>(0x1212),
                                         static_cast<UTF16Unit>(0x3434),
                                         static_cast<UTF16Unit>(0x5656)};

  std::vector<UTF32Unit> utf32Out(2, 0);

  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Swp_to_UTF32Nat(utf16In.data(), utf16In.size(), utf32Out.data(), utf32Out.size(), &utf16Read,
                       &utf32Written);

  EXPECT_EQ(utf32Written, 2u);
  EXPECT_EQ(utf16Read, 2u);

  EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(utf16In[0]));
  EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>(utf16In[1]));
}

TEST(UTF16Swp_to_UTF32NatTest_2087, HandlesEmptyInput_2087) {
  std::vector<UTF32Unit> utf32Out(4, 0xFFFFFFFFu);

  size_t utf16Read = 123;
  size_t utf32Written = 456;

  UTF16Swp_to_UTF32Nat(/*utf16In*/ reinterpret_cast<const UTF16Unit*>(""), /*utf16Len*/ 0,
                       utf32Out.data(), utf32Out.size(), &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 0u);
  EXPECT_EQ(utf32Written, 0u);
}

TEST(UTF16Swp_to_UTF32NatTest_2087, ConvertsSingleSurrogatePair_ToSingleUTF32CodePoint_2087) {
  // 😀 U+1F600 represented in UTF-16 as surrogate pair: D83D DE00 (native order).
  // Provide swapped input so UTF16InSwap() yields the native surrogate units.
  const UTF16Unit high_native = static_cast<UTF16Unit>(0xD83D);
  const UTF16Unit low_native = static_cast<UTF16Unit>(0xDE00);

  const std::vector<UTF16Unit> utf16InSwapped = {Swap16(high_native), Swap16(low_native)};

  std::vector<UTF32Unit> utf32Out(1, 0);

  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Swp_to_UTF32Nat(utf16InSwapped.data(), utf16InSwapped.size(), utf32Out.data(), utf32Out.size(),
                       &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 2u);
  EXPECT_EQ(utf32Written, 1u);
  EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x0001F600u));
}

TEST(UTF16Swp_to_UTF32NatTest_2087, StopsWhenInputEndsMidSurrogatePair_2087) {
  // Provide only the first half of a surrogate pair (swapped).
  const UTF16Unit high_native = static_cast<UTF16Unit>(0xD83D);
  const std::vector<UTF16Unit> utf16InSwapped = {Swap16(high_native)};

  std::vector<UTF32Unit> utf32Out(4, 0);

  size_t utf16Read = 777;
  size_t utf32Written = 888;

  UTF16Swp_to_UTF32Nat(utf16InSwapped.data(), utf16InSwapped.size(), utf32Out.data(), utf32Out.size(),
                       &utf16Read, &utf32Written);

  // Observable behavior: should not consume partial surrogate pair and should not write output.
  EXPECT_EQ(utf16Read, 0u);
  EXPECT_EQ(utf32Written, 0u);
}

TEST(UTF16Swp_to_UTF32NatTest_2087, StopsAtOutputCapacity_WhenSurrogatePairWouldOverflow_2087) {
  // Input begins with a surrogate pair, but output buffer has capacity 0.
  const UTF16Unit high_native = static_cast<UTF16Unit>(0xD83D);
  const UTF16Unit low_native = static_cast<UTF16Unit>(0xDE00);
  const std::vector<UTF16Unit> utf16InSwapped = {Swap16(high_native), Swap16(low_native)};

  std::vector<UTF32Unit> utf32Out;  // size 0

  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Swp_to_UTF32Nat(utf16InSwapped.data(), utf16InSwapped.size(), utf32Out.data(),
                       utf32Out.size(), &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 0u);
  EXPECT_EQ(utf32Written, 0u);
}

#if GTEST_HAS_DEATH_TEST
TEST(UTF16Swp_to_UTF32NatDeathTest_2087, DiesOnNullPointers_2087) {
  const UTF16Unit in = static_cast<UTF16Unit>(0x1212);
  UTF32Unit out = 0;
  size_t r = 0;
  size_t w = 0;

  EXPECT_DEATH(UTF16Swp_to_UTF32Nat(nullptr, 1, &out, 1, &r, &w), ".*");
  EXPECT_DEATH(UTF16Swp_to_UTF32Nat(&in, 1, nullptr, 1, &r, &w), ".*");
  EXPECT_DEATH(UTF16Swp_to_UTF32Nat(&in, 1, &out, 1, nullptr, &w), ".*");
  EXPECT_DEATH(UTF16Swp_to_UTF32Nat(&in, 1, &out, 1, &r, nullptr), ".*");
}
#endif

}  // namespace