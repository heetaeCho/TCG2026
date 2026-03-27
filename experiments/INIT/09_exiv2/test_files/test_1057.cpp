// ============================================================================
// TEST_ID: 1057
// File: test_image_byteswap_1057.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "exiv2/image.hpp"

namespace {

// Hardcoded reference values avoid re-implementing the production algorithm.
// These are well-known byte-order reversals for fixed constants.
constexpr uint64_t kV1 = 0x0102030405060708ULL;
constexpr uint64_t kV1Swapped = 0x0807060504030201ULL;

constexpr uint64_t kV2 = 0xA1B2C3D4E5F60718ULL;
constexpr uint64_t kV2Swapped = 0x1807F6E5D4C3B2A1ULL;

// Byte-palindrome across 8 bytes: swapping yields the same value.
constexpr uint64_t kPalindrome = 0x0100000000000001ULL;

class ImageByteSwapTest_1057 : public ::testing::Test {};

}  // namespace

TEST_F(ImageByteSwapTest_1057, NoSwapReturnsOriginalValue_1057) {
  const uint64_t input = kV1;
  const uint64_t out = Exiv2::Image::byteSwap(input, /*bSwap=*/false);
  EXPECT_EQ(out, input);
}

TEST_F(ImageByteSwapTest_1057, SwapReversesBytesForKnownPattern_1057) {
  const uint64_t out = Exiv2::Image::byteSwap(kV1, /*bSwap=*/true);
  EXPECT_EQ(out, kV1Swapped);
}

TEST_F(ImageByteSwapTest_1057, SwapReversesBytesForAnotherKnownPattern_1057) {
  const uint64_t out = Exiv2::Image::byteSwap(kV2, /*bSwap=*/true);
  EXPECT_EQ(out, kV2Swapped);
}

TEST_F(ImageByteSwapTest_1057, SwapOfZeroStaysZero_1057) {
  const uint64_t out = Exiv2::Image::byteSwap(0ULL, /*bSwap=*/true);
  EXPECT_EQ(out, 0ULL);

  const uint64_t outNoSwap = Exiv2::Image::byteSwap(0ULL, /*bSwap=*/false);
  EXPECT_EQ(outNoSwap, 0ULL);
}

TEST_F(ImageByteSwapTest_1057, SwapOfAllOnesStaysAllOnes_1057) {
  const uint64_t allOnes = std::numeric_limits<uint64_t>::max();
  const uint64_t out = Exiv2::Image::byteSwap(allOnes, /*bSwap=*/true);
  EXPECT_EQ(out, allOnes);

  const uint64_t outNoSwap = Exiv2::Image::byteSwap(allOnes, /*bSwap=*/false);
  EXPECT_EQ(outNoSwap, allOnes);
}

TEST_F(ImageByteSwapTest_1057, SwapOfPalindromeValueUnchanged_1057) {
  const uint64_t out = Exiv2::Image::byteSwap(kPalindrome, /*bSwap=*/true);
  EXPECT_EQ(out, kPalindrome);

  const uint64_t outNoSwap = Exiv2::Image::byteSwap(kPalindrome, /*bSwap=*/false);
  EXPECT_EQ(outNoSwap, kPalindrome);
}

TEST_F(ImageByteSwapTest_1057, DoubleSwapWithSwapEnabledReturnsOriginal_1057) {
  const uint64_t input = kV2;
  const uint64_t once = Exiv2::Image::byteSwap(input, /*bSwap=*/true);
  const uint64_t twice = Exiv2::Image::byteSwap(once, /*bSwap=*/true);
  EXPECT_EQ(twice, input);
}

TEST_F(ImageByteSwapTest_1057, MixedSwapFlagsBehaveAsExpected_1057) {
  const uint64_t input = kV1;

  // Swap then "no swap" keeps swapped value.
  const uint64_t swapped = Exiv2::Image::byteSwap(input, /*bSwap=*/true);
  const uint64_t stillSwapped = Exiv2::Image::byteSwap(swapped, /*bSwap=*/false);
  EXPECT_EQ(stillSwapped, kV1Swapped);

  // No swap then swap equals swap.
  const uint64_t noSwap = Exiv2::Image::byteSwap(input, /*bSwap=*/false);
  const uint64_t swappedAfter = Exiv2::Image::byteSwap(noSwap, /*bSwap=*/true);
  EXPECT_EQ(swappedAfter, kV1Swapped);
}