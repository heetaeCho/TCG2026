// TEST_ID 1177
// File: tiffheaderbase_tag_test_1177.cpp

#include <gtest/gtest.h>

#include <cstdint>

// Include the class under test.
#include "tiffimage_int.hpp"

namespace {

using Exiv2::Internal::TiffHeaderBase;

// Helper to create a ByteOrder value without depending on specific enum constants.
static Exiv2::ByteOrder AnyByteOrder(int v = 0) {
  return static_cast<Exiv2::ByteOrder>(v);
}

class TiffHeaderBaseTest_1177 : public ::testing::Test {};

TEST_F(TiffHeaderBaseTest_1177, TagReturnsConstructorTag_1177) {
  const uint16_t tag = 0x1234;
  TiffHeaderBase hdr(tag, /*size=*/8u, AnyByteOrder(0), /*offset=*/0u);

  EXPECT_EQ(hdr.tag(), tag);
}

TEST_F(TiffHeaderBaseTest_1177, TagWorksOnConstObject_1177) {
  const uint16_t tag = 0x00A5;
  const TiffHeaderBase hdr(tag, /*size=*/1u, AnyByteOrder(1), /*offset=*/42u);

  EXPECT_EQ(hdr.tag(), tag);
}

TEST_F(TiffHeaderBaseTest_1177, TagBoundaryZero_1177) {
  const uint16_t tag = 0u;
  TiffHeaderBase hdr(tag, /*size=*/0u, AnyByteOrder(0), /*offset=*/0u);

  EXPECT_EQ(hdr.tag(), tag);
}

TEST_F(TiffHeaderBaseTest_1177, TagBoundaryMaxUint16_1177) {
  const uint16_t tag = static_cast<uint16_t>(0xFFFFu);
  TiffHeaderBase hdr(tag, /*size=*/0u, AnyByteOrder(0), /*offset=*/0u);

  EXPECT_EQ(hdr.tag(), tag);
}

TEST_F(TiffHeaderBaseTest_1177, MultipleInstancesPreserveIndependentTags_1177) {
  TiffHeaderBase a(/*tag=*/1u, /*size=*/10u, AnyByteOrder(0), /*offset=*/100u);
  TiffHeaderBase b(/*tag=*/2u, /*size=*/20u, AnyByteOrder(1), /*offset=*/200u);

  EXPECT_EQ(a.tag(), 1u);
  EXPECT_EQ(b.tag(), 2u);
}

TEST_F(TiffHeaderBaseTest_1177, TagUnaffectedByOtherConstructorParameters_1177) {
  const uint16_t tag = 0xBEEFu;

  TiffHeaderBase hdr1(tag, /*size=*/0u, AnyByteOrder(0), /*offset=*/0u);
  TiffHeaderBase hdr2(tag, /*size=*/0xFFFFFFFFu, AnyByteOrder(123), /*offset=*/0xFFFFFFFFu);

  EXPECT_EQ(hdr1.tag(), tag);
  EXPECT_EQ(hdr2.tag(), tag);
}

}  // namespace