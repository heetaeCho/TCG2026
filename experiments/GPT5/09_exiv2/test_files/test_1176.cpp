// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1176
//
// Unit tests for Exiv2::Internal::TiffHeaderBase::size() const
//
// Constraints respected:
// - Treat implementation as black box (tests only use public interface/observable behavior).
// - No access to private state.
// - No re-implementation of logic.

#include <gtest/gtest.h>

#include <cstdint>

#include "tiffimage_int.hpp"  // Exiv2::Internal::TiffHeaderBase

namespace {

// Some builds expose ByteOrder in different headers/namespaces; prefer using Exiv2::ByteOrder.
static Exiv2::ByteOrder AnyByteOrder() {
  // Prefer littleEndian if available; otherwise fall back to whatever compiles.
  return Exiv2::littleEndian;
}

class TiffHeaderBaseTest_1176 : public ::testing::Test {};

TEST_F(TiffHeaderBaseTest_1176, SizeReflectsConstructorArgument_1176) {
  const uint16_t tag = 0x1234;
  const uint32_t size = 42u;
  const uint32_t offset = 7u;

  Exiv2::Internal::TiffHeaderBase hdr(tag, size, AnyByteOrder(), offset);

  const auto& chdr = static_cast<const Exiv2::Internal::TiffHeaderBase&>(hdr);
  EXPECT_EQ(chdr.size(), size);
}

TEST_F(TiffHeaderBaseTest_1176, SizeIsZeroWhenConstructedWithZero_1176) {
  const uint16_t tag = 0x0001;
  const uint32_t size = 0u;
  const uint32_t offset = 0u;

  Exiv2::Internal::TiffHeaderBase hdr(tag, size, AnyByteOrder(), offset);

  const auto& chdr = static_cast<const Exiv2::Internal::TiffHeaderBase&>(hdr);
  EXPECT_EQ(chdr.size(), 0u);
}

TEST_F(TiffHeaderBaseTest_1176, SizeHandlesMaxUint32Boundary_1176) {
  const uint16_t tag = 0xFFFF;
  const uint32_t size = 0xFFFFFFFFu;
  const uint32_t offset = 0u;

  Exiv2::Internal::TiffHeaderBase hdr(tag, size, AnyByteOrder(), offset);

  const auto& chdr = static_cast<const Exiv2::Internal::TiffHeaderBase&>(hdr);
  EXPECT_EQ(chdr.size(), 0xFFFFFFFFu);
}

TEST_F(TiffHeaderBaseTest_1176, SizeCallableOnConstObject_1176) {
  const uint16_t tag = 0x00AB;
  const uint32_t size = 123u;
  const uint32_t offset = 99u;

  const Exiv2::Internal::TiffHeaderBase hdr(tag, size, AnyByteOrder(), offset);

  // Ensures the const overload is usable and returns an observable value.
  EXPECT_EQ(hdr.size(), size);
}

}  // namespace