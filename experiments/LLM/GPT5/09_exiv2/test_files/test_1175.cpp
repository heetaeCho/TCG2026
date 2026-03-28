// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::Internal::TiffHeaderBase::setOffset
//
// The TEST_ID is 1175

#include <gtest/gtest.h>

#include <cstdint>

// Exiv2 internal header under test
#include "tiffimage_int.hpp"

namespace {

using Exiv2::Internal::TiffHeaderBase;

class TiffHeaderBaseTest_1175 : public ::testing::Test {
 protected:
  static constexpr uint16_t kTag = static_cast<uint16_t>(0x1234);
  static constexpr uint32_t kSize = static_cast<uint32_t>(0x100);
  static constexpr uint32_t kInitialOffset = static_cast<uint32_t>(0x10);

  // Avoid depending on specific enum enumerator names (littleEndian/bigEndian/etc.).
  static constexpr Exiv2::ByteOrder kByteOrder0 =
      static_cast<Exiv2::ByteOrder>(0);
  static constexpr Exiv2::ByteOrder kByteOrder1 =
      static_cast<Exiv2::ByteOrder>(1);
};

TEST_F(TiffHeaderBaseTest_1175, ConstructorExposesInitialOffset_1175) {
  TiffHeaderBase hdr(kTag, kSize, kByteOrder0, kInitialOffset);
  EXPECT_EQ(hdr.offset(), kInitialOffset);
}

TEST_F(TiffHeaderBaseTest_1175, SetOffsetUpdatesOffset_1175) {
  TiffHeaderBase hdr(kTag, kSize, kByteOrder0, kInitialOffset);

  const uint32_t newOffset = static_cast<uint32_t>(0xDEADBEEF);
  hdr.setOffset(newOffset);

  EXPECT_EQ(hdr.offset(), newOffset);
}

TEST_F(TiffHeaderBaseTest_1175, SetOffsetAllowsZero_1175) {
  TiffHeaderBase hdr(kTag, kSize, kByteOrder0, kInitialOffset);

  hdr.setOffset(0u);

  EXPECT_EQ(hdr.offset(), 0u);
}

TEST_F(TiffHeaderBaseTest_1175, SetOffsetAllowsMaxUint32_1175) {
  TiffHeaderBase hdr(kTag, kSize, kByteOrder0, kInitialOffset);

  const uint32_t maxVal = 0xFFFFFFFFu;
  hdr.setOffset(maxVal);

  EXPECT_EQ(hdr.offset(), maxVal);
}

TEST_F(TiffHeaderBaseTest_1175, SetOffsetIsIdempotentForSameValue_1175) {
  TiffHeaderBase hdr(kTag, kSize, kByteOrder0, kInitialOffset);

  hdr.setOffset(kInitialOffset);
  EXPECT_EQ(hdr.offset(), kInitialOffset);

  hdr.setOffset(kInitialOffset);
  EXPECT_EQ(hdr.offset(), kInitialOffset);
}

TEST_F(TiffHeaderBaseTest_1175, MultipleSetOffsetCallsUseLastValue_1175) {
  TiffHeaderBase hdr(kTag, kSize, kByteOrder0, kInitialOffset);

  hdr.setOffset(1u);
  EXPECT_EQ(hdr.offset(), 1u);

  hdr.setOffset(2u);
  EXPECT_EQ(hdr.offset(), 2u);

  hdr.setOffset(0xABCDEF01u);
  EXPECT_EQ(hdr.offset(), 0xABCDEF01u);
}

TEST_F(TiffHeaderBaseTest_1175, SetOffsetDoesNotChangeOtherObservableProperties_1175) {
  TiffHeaderBase hdr(kTag, kSize, kByteOrder1, kInitialOffset);

  // Capture observable state via public API (no private access).
  const uint16_t tagBefore = hdr.tag();
  const uint32_t sizeBefore = hdr.size();
  const Exiv2::ByteOrder boBefore = hdr.byteOrder();

  hdr.setOffset(0x22222222u);

  EXPECT_EQ(hdr.offset(), 0x22222222u);
  EXPECT_EQ(hdr.tag(), tagBefore);
  EXPECT_EQ(hdr.size(), sizeBefore);
  EXPECT_EQ(hdr.byteOrder(), boBefore);
}

}  // namespace