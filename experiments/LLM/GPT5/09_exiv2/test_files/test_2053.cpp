// =================================================================================================
// File:        test_UnicodeConversions_SwapUTF32_2053.cpp
// Description: Unit tests for SwapUTF32 (UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>
#include <limits>

// Prefer including the public header that declares SwapUTF32 / UTF32Unit.
// Adjust include if your tree uses a different path/name.
#include "UnicodeConversions.hpp"

namespace {

static inline std::uint32_t ByteSwap32(std::uint32_t v) {
  return ((v & 0x000000FFu) << 24) |
         ((v & 0x0000FF00u) << 8) |
         ((v & 0x00FF0000u) >> 8) |
         ((v & 0xFF000000u) >> 24);
}

static inline UTF32Unit SwapOne(UTF32Unit v) {
  // Avoid assuming UTF32Unit signedness; operate via uint32_t.
  const std::uint32_t u = static_cast<std::uint32_t>(v);
  return static_cast<UTF32Unit>(ByteSwap32(u));
}

class UnicodeConversionsSwapUTF32Test_2053 : public ::testing::Test {};

}  // namespace

TEST_F(UnicodeConversionsSwapUTF32Test_2053, SwapsEachElement_NormalOperation_2053) {
  const std::vector<UTF32Unit> input = {
      static_cast<UTF32Unit>(0x00000000u),
      static_cast<UTF32Unit>(0x11223344u),
      static_cast<UTF32Unit>(0xAABBCCDDu),
      static_cast<UTF32Unit>(0x0000FEFFu),
      static_cast<UTF32Unit>(0xFFFE0000u),
      static_cast<UTF32Unit>(0x7FFFFFFFu),
      static_cast<UTF32Unit>(0x80000000u),
      static_cast<UTF32Unit>(0xFFFFFFFFu),
  };

  std::vector<UTF32Unit> output(input.size(), static_cast<UTF32Unit>(0));

  SwapUTF32(input.data(), output.data(), input.size());

  ASSERT_EQ(output.size(), input.size());
  for (size_t i = 0; i < input.size(); ++i) {
    EXPECT_EQ(output[i], SwapOne(input[i])) << "index=" << i;
  }
}

TEST_F(UnicodeConversionsSwapUTF32Test_2053, InPlaceSwap_WritesCorrectly_2053) {
  std::vector<UTF32Unit> buffer = {
      static_cast<UTF32Unit>(0x01020304u),
      static_cast<UTF32Unit>(0x0A0B0C0Du),
      static_cast<UTF32Unit>(0xDEADBEEFu),
  };

  const std::vector<UTF32Unit> expected = {
      SwapOne(buffer[0]),
      SwapOne(buffer[1]),
      SwapOne(buffer[2]),
  };

  // In-place: input and output are the same buffer.
  SwapUTF32(buffer.data(), buffer.data(), buffer.size());

  ASSERT_EQ(buffer.size(), expected.size());
  for (size_t i = 0; i < buffer.size(); ++i) {
    EXPECT_EQ(buffer[i], expected[i]) << "index=" << i;
  }
}

TEST_F(UnicodeConversionsSwapUTF32Test_2053, DoubleSwap_RestoresOriginal_2053) {
  const std::vector<UTF32Unit> original = {
      static_cast<UTF32Unit>(0x12345678u),
      static_cast<UTF32Unit>(0x00010203u),
      static_cast<UTF32Unit>(0xABCDEF01u),
      static_cast<UTF32Unit>(0x01000000u),
  };

  std::vector<UTF32Unit> once(original.size(), static_cast<UTF32Unit>(0));
  std::vector<UTF32Unit> twice(original.size(), static_cast<UTF32Unit>(0));

  SwapUTF32(original.data(), once.data(), original.size());
  SwapUTF32(once.data(), twice.data(), once.size());

  ASSERT_EQ(twice.size(), original.size());
  for (size_t i = 0; i < original.size(); ++i) {
    EXPECT_EQ(twice[i], original[i]) << "index=" << i;
  }
}

TEST_F(UnicodeConversionsSwapUTF32Test_2053, ZeroLength_DoesNotModifyOutput_2053) {
  const UTF32Unit in = static_cast<UTF32Unit>(0x11223344u);

  UTF32Unit out0 = static_cast<UTF32Unit>(0xAAAAAAAAu);
  UTF32Unit out1 = static_cast<UTF32Unit>(0xBBBBBBBBu);

  // Passing a valid pointer with length 0 should result in no writes.
  SwapUTF32(&in, &out0, 0);
  EXPECT_EQ(static_cast<std::uint32_t>(out0), 0xAAAAAAAAu);

  // Also check it does not touch other memory.
  SwapUTF32(&in, &out1, 0);
  EXPECT_EQ(static_cast<std::uint32_t>(out1), 0xBBBBBBBBu);
}

TEST_F(UnicodeConversionsSwapUTF32Test_2053, ZeroLength_AllowsNullPointers_2053) {
  // With length 0, the loop body should not execute; this should not crash.
  SwapUTF32(nullptr, nullptr, 0);
  SUCCEED();
}