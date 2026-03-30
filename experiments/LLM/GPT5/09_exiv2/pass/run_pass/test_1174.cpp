// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstdint>

#include "tiffimage_int.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::Internal::TiffHeaderBase;

class TiffHeaderBaseTest_1174 : public ::testing::Test {
 protected:
  static TiffHeaderBase makeHeader(uint32_t offset) {
    // Use arbitrary but valid-looking values for the other ctor params.
    const uint16_t tag = 0x1234;
    const uint32_t size = 8;
    const ByteOrder bo = Exiv2::littleEndian;
    return TiffHeaderBase(tag, size, bo, offset);
  }
};

TEST_F(TiffHeaderBaseTest_1174, OffsetReturnsConstructorValue_1174) {
  const uint32_t kOffset = 0x11223344u;
  const auto hdr = makeHeader(kOffset);

  EXPECT_EQ(hdr.offset(), kOffset);
}

TEST_F(TiffHeaderBaseTest_1174, OffsetCallableOnConstObject_1174) {
  const uint32_t kOffset = 0xA5A5A5A5u;
  const auto hdr0 = makeHeader(kOffset);
  const TiffHeaderBase& hdr = hdr0;

  EXPECT_EQ(hdr.offset(), kOffset);
}

TEST_F(TiffHeaderBaseTest_1174, SetOffsetUpdatesOffset_1174) {
  auto hdr = makeHeader(1u);

  hdr.setOffset(0x55667788u);
  EXPECT_EQ(hdr.offset(), 0x55667788u);

  hdr.setOffset(0u);
  EXPECT_EQ(hdr.offset(), 0u);
}

TEST_F(TiffHeaderBaseTest_1174, OffsetBoundaryZero_1174) {
  const auto hdr = makeHeader(0u);
  EXPECT_EQ(hdr.offset(), 0u);
}

TEST_F(TiffHeaderBaseTest_1174, OffsetBoundaryMaxUint32_1174) {
  const uint32_t kMax = 0xFFFFFFFFu;
  const auto hdr = makeHeader(kMax);
  EXPECT_EQ(hdr.offset(), kMax);
}

}  // namespace