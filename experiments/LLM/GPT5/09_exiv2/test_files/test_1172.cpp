// TEST_ID 1172
// File: tiffheaderbase_byteorder_test.cpp

#include <gtest/gtest.h>

#include <exiv2/types.hpp>

#include "tiffimage_int.hpp"

namespace {

// Simple helper to create a header with arbitrary constructor args.
static Exiv2::Internal::TiffHeaderBase MakeHeader(Exiv2::ByteOrder bo) {
  // tag/size/offset values are not under test here; choose stable non-zero values.
  return Exiv2::Internal::TiffHeaderBase(/*tag=*/0x1234, /*size=*/8u, bo, /*offset=*/0u);
}

}  // namespace

TEST(TiffHeaderBaseTest_1172, ByteOrderReturnsCtorValueLittleEndian_1172) {
  auto header = MakeHeader(Exiv2::littleEndian);
  EXPECT_EQ(header.byteOrder(), Exiv2::littleEndian);
}

TEST(TiffHeaderBaseTest_1172, ByteOrderReturnsCtorValueBigEndian_1172) {
  auto header = MakeHeader(Exiv2::bigEndian);
  EXPECT_EQ(header.byteOrder(), Exiv2::bigEndian);
}

TEST(TiffHeaderBaseTest_1172, SetByteOrderUpdatesReportedValue_1172) {
  auto header = MakeHeader(Exiv2::littleEndian);
  ASSERT_EQ(header.byteOrder(), Exiv2::littleEndian);

  header.setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(header.byteOrder(), Exiv2::bigEndian);
}

TEST(TiffHeaderBaseTest_1172, SetByteOrderToSameValueKeepsReportedValue_1172) {
  auto header = MakeHeader(Exiv2::bigEndian);
  ASSERT_EQ(header.byteOrder(), Exiv2::bigEndian);

  header.setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(header.byteOrder(), Exiv2::bigEndian);
}

TEST(TiffHeaderBaseTest_1172, ByteOrderCanBeInvalidIfSupportedByEnum_1172) {
  // Boundary-ish case: if Exiv2 exposes an "invalidByteOrder" enumerator, ensure it round-trips.
  // This is observable via the public getter/setter.
  auto header = MakeHeader(Exiv2::invalidByteOrder);
  EXPECT_EQ(header.byteOrder(), Exiv2::invalidByteOrder);

  header.setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(header.byteOrder(), Exiv2::littleEndian);

  header.setByteOrder(Exiv2::invalidByteOrder);
  EXPECT_EQ(header.byteOrder(), Exiv2::invalidByteOrder);
}