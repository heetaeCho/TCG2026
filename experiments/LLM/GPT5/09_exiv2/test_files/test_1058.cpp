// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_image_byteswap_uint32_1058.cpp
//
// Unit tests for Exiv2::Image::byteSwap(uint32_t, bool)
//
// Constraints reminder:
// - Treat implementation as a black box.
// - Assert only observable behavior via the public interface.

#include <gtest/gtest.h>

#include <cstdint>

#include "exiv2/image.hpp"

namespace {

// A small, test-only reference for expected uint32 byte swap.
// This is not intended to mirror Exiv2 internals—just the mathematical
// definition of swapping the 4 bytes of a 32-bit word.
static uint32_t RefByteSwap32(uint32_t v) {
#ifdef __cpp_lib_byteswap
  return std::byteswap(v);
#else
  return ((v & 0x000000FFu) << 24) | ((v & 0x0000FF00u) << 8) | ((v & 0x00FF0000u) >> 8) |
         ((v & 0xFF000000u) >> 24);
#endif
}

class ImageByteSwapUint32Test_1058 : public ::testing::Test {};

}  // namespace

TEST_F(ImageByteSwapUint32Test_1058, NoSwapReturnsSameValue_1058) {
  const uint32_t values[] = {0u, 1u, 0xFFFFFFFFu, 0x01020304u, 0xAABBCCDDu, 0x80000000u};
  for (uint32_t v : values) {
    EXPECT_EQ(Exiv2::Image::byteSwap(v, /*bSwap=*/false), v) << std::hex << v;
  }
}

TEST_F(ImageByteSwapUint32Test_1058, SwapTrueSwapsKnownPatterns_1058) {
  struct Case {
    uint32_t in;
    uint32_t out;
  };
  const Case cases[] = {
      {0x01020304u, 0x04030201u},
      {0xAABBCCDDu, 0xDDCCBBAAu},
      {0x11223344u, 0x44332211u},
      {0x00000001u, 0x01000000u},
      {0x80000000u, 0x00000080u},
  };

  for (const auto& c : cases) {
    EXPECT_EQ(Exiv2::Image::byteSwap(c.in, /*bSwap=*/true), c.out) << std::hex << c.in;
  }
}

TEST_F(ImageByteSwapUint32Test_1058, SwapTrueHandlesBoundaryValues_1058) {
  // Boundary-ish values: all zeros and all ones should remain the same after swapping.
  EXPECT_EQ(Exiv2::Image::byteSwap(0u, /*bSwap=*/true), 0u);
  EXPECT_EQ(Exiv2::Image::byteSwap(0xFFFFFFFFu, /*bSwap=*/true), 0xFFFFFFFFu);

  // Alternating-bit style values to ensure all bytes move.
  const uint32_t v1 = 0x00FF00FFu;
  const uint32_t v2 = 0xFF00FF00u;
  EXPECT_EQ(Exiv2::Image::byteSwap(v1, /*bSwap=*/true), RefByteSwap32(v1));
  EXPECT_EQ(Exiv2::Image::byteSwap(v2, /*bSwap=*/true), RefByteSwap32(v2));
}

TEST_F(ImageByteSwapUint32Test_1058, SwapTrueMatchesReferenceDefinition_1058) {
  // A handful of diverse values (no need for randomness).
  const uint32_t values[] = {0x12345678u, 0xDEADBEEFu, 0xCAFEBABEu, 0x0F1E2D3Cu, 0x13579BDFu};

  for (uint32_t v : values) {
    EXPECT_EQ(Exiv2::Image::byteSwap(v, /*bSwap=*/true), RefByteSwap32(v)) << std::hex << v;
  }
}

TEST_F(ImageByteSwapUint32Test_1058, SwappingTwiceWithSwapTrueReturnsOriginal_1058) {
  const uint32_t values[] = {0u, 0x01020304u, 0x89ABCDEFu, 0xFFFFFFFFu, 0x10203040u};

  for (uint32_t v : values) {
    const uint32_t swapped = Exiv2::Image::byteSwap(v, /*bSwap=*/true);
    const uint32_t swapped_back = Exiv2::Image::byteSwap(swapped, /*bSwap=*/true);
    EXPECT_EQ(swapped_back, v) << std::hex << v;
  }
}

TEST_F(ImageByteSwapUint32Test_1058, SwapFlagControlsBehaviorIndependentlyPerCall_1058) {
  const uint32_t v = 0x0A0B0C0Du;

  const uint32_t no_swap = Exiv2::Image::byteSwap(v, /*bSwap=*/false);
  const uint32_t yes_swap = Exiv2::Image::byteSwap(v, /*bSwap=*/true);

  EXPECT_EQ(no_swap, v);
  EXPECT_EQ(yes_swap, RefByteSwap32(v));
  EXPECT_NE(no_swap, yes_swap);
}