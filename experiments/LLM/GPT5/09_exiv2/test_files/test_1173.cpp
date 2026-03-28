// ============================================================================
// Test file for Exiv2::Internal::TiffHeaderBase::setByteOrder
// File: ./TestProjects/exiv2/src/tiffimage_int.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <sstream>

// Exiv2 headers
#include "tiffimage_int.hpp"
#include "types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::littleEndian;
using Exiv2::Internal::TiffHeaderBase;

class TiffHeaderBaseTest_1173 : public ::testing::Test {
 protected:
  static TiffHeaderBase MakeHeader(ByteOrder bo) {
    // Use arbitrary but stable values for other constructor params.
    return TiffHeaderBase(/*tag*/ static_cast<uint16_t>(0x1234),
                          /*size*/ static_cast<uint32_t>(64),
                          /*byteOrder*/ bo,
                          /*offset*/ static_cast<uint32_t>(0x10));
  }
};

TEST_F(TiffHeaderBaseTest_1173, ConstructorSetsInitialByteOrder_1173) {
  TiffHeaderBase hdr = MakeHeader(littleEndian);
  EXPECT_EQ(hdr.byteOrder(), littleEndian);

  TiffHeaderBase hdr2 = MakeHeader(bigEndian);
  EXPECT_EQ(hdr2.byteOrder(), bigEndian);
}

TEST_F(TiffHeaderBaseTest_1173, SetByteOrderUpdatesByteOrder_1173) {
  TiffHeaderBase hdr = MakeHeader(littleEndian);
  ASSERT_EQ(hdr.byteOrder(), littleEndian);

  hdr.setByteOrder(bigEndian);
  EXPECT_EQ(hdr.byteOrder(), bigEndian);

  hdr.setByteOrder(littleEndian);
  EXPECT_EQ(hdr.byteOrder(), littleEndian);
}

TEST_F(TiffHeaderBaseTest_1173, SetByteOrderToSameValueIsAllowed_1173) {
  TiffHeaderBase hdr = MakeHeader(bigEndian);
  ASSERT_EQ(hdr.byteOrder(), bigEndian);

  hdr.setByteOrder(bigEndian);
  EXPECT_EQ(hdr.byteOrder(), bigEndian);
}

TEST_F(TiffHeaderBaseTest_1173, SetByteOrderDoesNotChangeOtherObservableFields_1173) {
  TiffHeaderBase hdr = MakeHeader(littleEndian);

  const uint16_t tag_before = hdr.tag();
  const uint32_t size_before = hdr.size();
  const uint32_t offset_before = hdr.offset();

  hdr.setByteOrder(bigEndian);

  EXPECT_EQ(hdr.byteOrder(), bigEndian);
  EXPECT_EQ(hdr.tag(), tag_before);
  EXPECT_EQ(hdr.size(), size_before);
  EXPECT_EQ(hdr.offset(), offset_before);
}

TEST_F(TiffHeaderBaseTest_1173, SetByteOrderMultipleTransitions_1173) {
  TiffHeaderBase hdr = MakeHeader(littleEndian);

  for (int i = 0; i < 5; ++i) {
    hdr.setByteOrder(bigEndian);
    EXPECT_EQ(hdr.byteOrder(), bigEndian);

    hdr.setByteOrder(littleEndian);
    EXPECT_EQ(hdr.byteOrder(), littleEndian);
  }
}

}  // namespace