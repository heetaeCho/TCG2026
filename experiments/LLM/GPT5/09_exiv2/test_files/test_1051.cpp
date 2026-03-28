// ============================================================================
// TestProjects/exiv2/tests/test_image_isRationalType_1051.cpp
// Unit tests for Exiv2::Image::isRationalType (TEST_ID: 1051)
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>

#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

namespace {

// NOTE: Tests treat implementation as a black box and only validate observable
// behavior via the public interface.

class ImageIsRationalTypeTest_1051 : public ::testing::Test {};

TEST_F(ImageIsRationalTypeTest_1051, UnsignedRationalReturnsTrue_1051) {
  const uint16_t type = static_cast<uint16_t>(Exiv2::unsignedRational);
  EXPECT_TRUE(Exiv2::Image::isRationalType(type));
}

TEST_F(ImageIsRationalTypeTest_1051, SignedRationalReturnsTrue_1051) {
  const uint16_t type = static_cast<uint16_t>(Exiv2::signedRational);
  EXPECT_TRUE(Exiv2::Image::isRationalType(type));
}

TEST_F(ImageIsRationalTypeTest_1051, NonRationalTypesReturnFalse_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::unsignedByte)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::asciiString)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::unsignedShort)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::unsignedLong)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::signedLong)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::undefined)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::tiffFloat)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::tiffDouble)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::tiffIfd)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::unsignedLongLong)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::signedLongLong)));
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(Exiv2::tiffIfd8)));
}

TEST_F(ImageIsRationalTypeTest_1051, BoundaryZeroTypeReturnsFalse_1051) {
  // Boundary value not defined in TypeId enum.
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(0)));
}

TEST_F(ImageIsRationalTypeTest_1051, BoundaryMaxUint16ReturnsFalse_1051) {
  // Boundary value at maximum uint16_t.
  EXPECT_FALSE(Exiv2::Image::isRationalType(static_cast<uint16_t>(0xFFFF)));
}

TEST_F(ImageIsRationalTypeTest_1051, InvalidTypeIdTruncatedToUint16Handled_1051) {
  // invalidTypeId is outside uint16_t range; only observable input is uint16_t,
  // so we pass the truncated value and assert it is not treated as rational.
  const uint16_t truncated = static_cast<uint16_t>(Exiv2::invalidTypeId);
  EXPECT_FALSE(Exiv2::Image::isRationalType(truncated));
}

}  // namespace