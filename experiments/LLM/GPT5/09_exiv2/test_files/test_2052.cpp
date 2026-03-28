// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_2052_UnicodeConversions_SwapUTF16.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#if __has_include("UnicodeConversions.hpp")
  #include "UnicodeConversions.hpp"
#elif __has_include("UnicodeConversions.h")
  #include "UnicodeConversions.h"
#elif __has_include("UnicodeConversions.hpp")
  #include "UnicodeConversions.hpp"
#else
  // If the include path differs in your build, adjust it to wherever SwapUTF16 is declared.
  #include "xmpsdk/src/UnicodeConversions.hpp"
#endif

namespace {

// Keep the fixture even if not strictly necessary for consistency across the suite.
class UnicodeConversionsTest_2052 : public ::testing::Test {};

TEST_F(UnicodeConversionsTest_2052, SwapUTF16_ZeroLength_DoesNotModifyOutput_2052) {
  const std::array<UTF16Unit, 3> in = {UTF16Unit(0x1234), UTF16Unit(0xABCD), UTF16Unit(0x0001)};
  std::array<UTF16Unit, 3> out = {UTF16Unit(0xDEAD), UTF16Unit(0xBEEF), UTF16Unit(0xCAFE)};

  SwapUTF16(in.data(), out.data(), 0);

  EXPECT_EQ(out[0], UTF16Unit(0xDEAD));
  EXPECT_EQ(out[1], UTF16Unit(0xBEEF));
  EXPECT_EQ(out[2], UTF16Unit(0xCAFE));
}

TEST_F(UnicodeConversionsTest_2052, SwapUTF16_SingleElement_MatchesUTF16InSwap_2052) {
  const std::array<UTF16Unit, 1> in = {UTF16Unit(0x1234)};
  std::array<UTF16Unit, 1> out = {UTF16Unit(0x0000)};

  SwapUTF16(in.data(), out.data(), in.size());

  // Observable behavior: each output element is the swapped form of the corresponding input element.
  EXPECT_EQ(out[0], UTF16InSwap(&in[0]));
}

TEST_F(UnicodeConversionsTest_2052, SwapUTF16_MultipleElements_MatchesUTF16InSwapPerUnit_2052) {
  const std::array<UTF16Unit, 6> in = {
      UTF16Unit(0x0000), UTF16Unit(0x00FF), UTF16Unit(0xFF00),
      UTF16Unit(0x1234), UTF16Unit(0xABCD), UTF16Unit(0xFFFF)};
  std::array<UTF16Unit, 6> out = {UTF16Unit(0), UTF16Unit(0), UTF16Unit(0), UTF16Unit(0), UTF16Unit(0), UTF16Unit(0)};

  SwapUTF16(in.data(), out.data(), in.size());

  for (size_t i = 0; i < in.size(); ++i) {
    EXPECT_EQ(out[i], UTF16InSwap(&in[i])) << "Index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2052, SwapUTF16_InPlaceSwap_MatchesUTF16InSwapOfOriginalValues_2052) {
  std::array<UTF16Unit, 5> buffer = {
      UTF16Unit(0x1111), UTF16Unit(0x2222), UTF16Unit(0x3333), UTF16Unit(0x4444), UTF16Unit(0x5555)};
  const auto original = buffer;  // Preserve original inputs for expectations.

  // In-place: input and output buffers are the same.
  SwapUTF16(buffer.data(), buffer.data(), buffer.size());

  for (size_t i = 0; i < buffer.size(); ++i) {
    EXPECT_EQ(buffer[i], UTF16InSwap(&original[i])) << "Index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2052, SwapUTF16_DoesNotWritePastSpecifiedLength_2052) {
  const std::array<UTF16Unit, 4> in = {UTF16Unit(0x1357), UTF16Unit(0x2468), UTF16Unit(0xAAAA), UTF16Unit(0x5555)};
  std::array<UTF16Unit, 6> out = {
      UTF16Unit(0x0000), UTF16Unit(0x0000), UTF16Unit(0x0000), UTF16Unit(0x0000),
      UTF16Unit(0xDEAD), UTF16Unit(0xBEEF)};

  const size_t len = in.size();  // swap first 4, last 2 are sentinels
  SwapUTF16(in.data(), out.data(), len);

  for (size_t i = 0; i < len; ++i) {
    EXPECT_EQ(out[i], UTF16InSwap(&in[i])) << "Index " << i;
  }
  EXPECT_EQ(out[4], UTF16Unit(0xDEAD));
  EXPECT_EQ(out[5], UTF16Unit(0xBEEF));
}

TEST_F(UnicodeConversionsTest_2052, SwapUTF16_LargerInput_AllElementsProcessed_2052) {
  const size_t kLen = 1024;
  std::vector<UTF16Unit> in(kLen);
  std::vector<UTF16Unit> out(kLen, UTF16Unit(0));

  for (size_t i = 0; i < kLen; ++i) {
    // Deterministic pattern; avoids relying on any internal swapping logic.
    in[i] = static_cast<UTF16Unit>((i * 37u) & 0xFFFFu);
  }

  SwapUTF16(in.data(), out.data(), kLen);

  for (size_t i = 0; i < kLen; ++i) {
    EXPECT_EQ(out[i], UTF16InSwap(&in[i])) << "Index " << i;
  }
}

}  // namespace