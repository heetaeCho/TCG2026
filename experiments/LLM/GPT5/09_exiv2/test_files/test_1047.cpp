// =================================================================================================
// TestProjects/exiv2/src/image_test_isStringType_1047.cpp
// Unit tests for Exiv2::Image::isStringType(uint16_t)
// TEST_ID: 1047
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>

#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

namespace {

class ImageIsStringTypeTest_1047 : public ::testing::Test {};

}  // namespace

// Normal operation: known "string-like" TypeId values should return true.
TEST_F(ImageIsStringTypeTest_1047, ReturnsTrueForAsciiString_1047) {
  EXPECT_TRUE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::asciiString)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsTrueForUnsignedByte_1047) {
  EXPECT_TRUE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::unsignedByte)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsTrueForSignedByte_1047) {
  EXPECT_TRUE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::signedByte)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsTrueForUndefined_1047) {
  EXPECT_TRUE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::undefined)));
}

// Normal operation: common non-string scalar types should return false.
TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForUnsignedShort_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::unsignedShort)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForUnsignedLong_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::unsignedLong)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForUnsignedRational_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::unsignedRational)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForSignedShort_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::signedShort)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForSignedLong_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::signedLong)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForSignedRational_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::signedRational)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForTiffFloat_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::tiffFloat)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForTiffDouble_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::tiffDouble)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForTiffIfd_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::tiffIfd)));
}

// Boundary conditions: values around known true/false regions and extremes.
TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForZero_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(0)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForMaxUint16_1047) {
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(0xFFFF)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForJustBelowUnsignedByte_1047) {
  // unsignedByte == 1, so 0 is a boundary neighbor.
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::unsignedByte - 1)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsTrueForUnsignedByteItself_1047) {
  EXPECT_TRUE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::unsignedByte)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForJustAboveUndefined_1047) {
  // undefined == 7, so 8 (signedShort) is a boundary neighbor.
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::undefined + 1)));
}

// "Exceptional/error" cases (observable): values that are not valid TIFF TypeId
// in the 1..18 range should be handled and simply return false (no throw).
TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForHighNonTiffTypeIdLikeString65536_1047) {
  // Exiv2::string is 65536, which truncates to 0 when cast to uint16_t.
  // We only assert observable behavior via the interface: no crash, returns false.
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::string)));
}

TEST_F(ImageIsStringTypeTest_1047, ReturnsFalseForInvalidTypeId131070Truncated_1047) {
  // invalidTypeId is 131070; truncation yields 65534. Should be treated as non-string.
  EXPECT_FALSE(Exiv2::Image::isStringType(static_cast<uint16_t>(Exiv2::invalidTypeId)));
}