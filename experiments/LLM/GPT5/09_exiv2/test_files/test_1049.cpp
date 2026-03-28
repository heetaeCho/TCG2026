// File: test_image_isLongType_1049.cpp

#include <gtest/gtest.h>

#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

namespace {

class ImageIsLongTypeTest_1049 : public ::testing::Test {};

TEST_F(ImageIsLongTypeTest_1049, ReturnsTrueForUnsignedLong_1049) {
  EXPECT_TRUE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::unsignedLong)));
}

TEST_F(ImageIsLongTypeTest_1049, ReturnsTrueForSignedLong_1049) {
  EXPECT_TRUE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::signedLong)));
}

TEST_F(ImageIsLongTypeTest_1049, ReturnsFalseForOtherWellKnownTypeIds_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::unsignedByte)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::asciiString)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::unsignedShort)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::unsignedRational)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::signedShort)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::signedRational)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::tiffIfd)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::unsignedLongLong)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::signedLongLong)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::tiffIfd8)));
}

TEST_F(ImageIsLongTypeTest_1049, BoundaryValuesAroundLongTypeIds_1049) {
  // Values adjacent to unsignedLong (4) and signedLong (9) should not be treated as long types.
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::unsignedLong - 1)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::unsignedLong + 1)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::signedLong - 1)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(Exiv2::signedLong + 1)));
}

TEST_F(ImageIsLongTypeTest_1049, ReturnsFalseForZeroAndMaxUint16_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(0)));
  EXPECT_FALSE(Exiv2::Image::isLongType(static_cast<uint16_t>(0xFFFF)));
}

TEST_F(ImageIsLongTypeTest_1049, ReturnsFalseForTruncatedOutOfRangeTypeIdValues_1049) {
  // TypeId contains values larger than uint16_t (e.g., invalidTypeId = 131070).
  // The interface takes uint16_t; ensure such truncated values are handled consistently.
  const uint16_t truncatedInvalid =
      static_cast<uint16_t>(static_cast<uint32_t>(Exiv2::invalidTypeId));
  EXPECT_FALSE(Exiv2::Image::isLongType(truncatedInvalid));

  const uint16_t truncatedLast =
      static_cast<uint16_t>(static_cast<uint32_t>(Exiv2::lastTypeId));
  EXPECT_FALSE(Exiv2::Image::isLongType(truncatedLast));
}

}  // namespace