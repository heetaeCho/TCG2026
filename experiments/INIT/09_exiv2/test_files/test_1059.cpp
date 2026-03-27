// =================================================================================================
// File:        test_image_byteswap_uint16_1059.cpp
// Description: Unit tests for Exiv2::Image::byteSwap(uint16_t, bool)
// Test ID:     1059
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "exiv2/image.hpp"

namespace {

// Local helper to compute the expected 16-bit byte swap (black-box expectation from signature/intent).
constexpr uint16_t ExpectedSwap16(uint16_t v) {
  return static_cast<uint16_t>(((v & 0x00FFu) << 8) | ((v & 0xFF00u) >> 8));
}

// Call wrapper: supports both static and non-static forms at compile time (whichever exists).
template <typename T>
uint16_t CallByteSwap16(uint16_t value, bool bSwap) {
  // If byteSwap is static, &T::byteSwap is a plain function pointer (not a member function pointer).
  if constexpr (!std::is_member_function_pointer_v<decltype(&T::byteSwap)>) {
    return T::byteSwap(value, bSwap);
  } else {
    // If it is a non-static member function, we would need a valid instance. The public interface in
    // exiv2/image.hpp declares byteSwap as static; this branch is here only as a build-time hedge.
    // If your build hits this branch, replace this with a real Image instance factory appropriate
    // to your test environment.
    (void)bSwap;
    (void)value;
    ADD_FAILURE() << "Exiv2::Image::byteSwap(uint16_t,bool) is non-static in this build; "
                     "tests expect the static interface from exiv2/image.hpp.";
    return 0;
  }
}

class ImageByteSwapUint16Test_1059 : public ::testing::Test {};

}  // namespace

TEST_F(ImageByteSwapUint16Test_1059, NoSwap_ReturnsOriginal_ForCommonValues_1059) {
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(static_cast<uint16_t>(0x0000u), false),
            static_cast<uint16_t>(0x0000u));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(static_cast<uint16_t>(0x00FFu), false),
            static_cast<uint16_t>(0x00FFu));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(static_cast<uint16_t>(0xFF00u), false),
            static_cast<uint16_t>(0xFF00u));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(static_cast<uint16_t>(0x1234u), false),
            static_cast<uint16_t>(0x1234u));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(static_cast<uint16_t>(0xFFFFu), false),
            static_cast<uint16_t>(0xFFFFu));
}

TEST_F(ImageByteSwapUint16Test_1059, Swap_ProducesExpectedByteReversal_ForCommonValues_1059) {
  const uint16_t v1 = static_cast<uint16_t>(0x0000u);
  const uint16_t v2 = static_cast<uint16_t>(0x00FFu);
  const uint16_t v3 = static_cast<uint16_t>(0xFF00u);
  const uint16_t v4 = static_cast<uint16_t>(0x1234u);
  const uint16_t v5 = static_cast<uint16_t>(0xABCDu);
  const uint16_t v6 = static_cast<uint16_t>(0xFFFFu);

  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(v1, true), ExpectedSwap16(v1));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(v2, true), ExpectedSwap16(v2));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(v3, true), ExpectedSwap16(v3));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(v4, true), ExpectedSwap16(v4));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(v5, true), ExpectedSwap16(v5));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(v6, true), ExpectedSwap16(v6));
}

TEST_F(ImageByteSwapUint16Test_1059, Swap_IsInvolution_SwappingTwiceReturnsOriginal_1059) {
  const uint16_t values[] = {
      static_cast<uint16_t>(0x0000u),
      static_cast<uint16_t>(0x0001u),
      static_cast<uint16_t>(0x00FFu),
      static_cast<uint16_t>(0x0100u),
      static_cast<uint16_t>(0x1234u),
      static_cast<uint16_t>(0x8001u),
      static_cast<uint16_t>(0xFFFEu),
      static_cast<uint16_t>(0xFFFFu),
  };

  for (uint16_t v : values) {
    const uint16_t once = CallByteSwap16<Exiv2::Image>(v, true);
    const uint16_t twice = CallByteSwap16<Exiv2::Image>(once, true);
    EXPECT_EQ(twice, v) << "value=0x" << std::hex << v;
  }
}

TEST_F(ImageByteSwapUint16Test_1059, BoundaryValues_MinMax_AreHandled_1059) {
  const uint16_t minv = static_cast<uint16_t>(0x0000u);
  const uint16_t maxv = static_cast<uint16_t>(0xFFFFu);

  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(minv, false), minv);
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(maxv, false), maxv);

  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(minv, true), ExpectedSwap16(minv));
  EXPECT_EQ(CallByteSwap16<Exiv2::Image>(maxv, true), ExpectedSwap16(maxv));
}

TEST_F(ImageByteSwapUint16Test_1059, Swap_FlagControlsBehavior_ForSameInput_1059) {
  const uint16_t v = static_cast<uint16_t>(0xB00Bu);

  const uint16_t noSwap = CallByteSwap16<Exiv2::Image>(v, false);
  const uint16_t swapped = CallByteSwap16<Exiv2::Image>(v, true);

  EXPECT_EQ(noSwap, v);
  EXPECT_EQ(swapped, ExpectedSwap16(v));
  EXPECT_NE(noSwap, swapped);  // For this chosen value, swapped should differ.
}