// ============================================================================
// TEST_ID: 1048
// Unit tests for Exiv2::Image::isShortType(uint16_t)
// File under test: ./TestProjects/exiv2/src/image.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

// Exiv2 headers (adjust include paths as needed in your build)
#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

namespace {

// A minimal concrete Image so we can construct an Exiv2::Image instance.
// We do NOT test any behavior except calling isShortType through the public API.
class TestImage_1048 final : public Exiv2::Image {
public:
  TestImage_1048()
      : Exiv2::Image(
            /*type*/ static_cast<Exiv2::ImageType>(0),
            /*supportedMetadata*/ 0,
            /*io*/ std::unique_ptr<Exiv2::BasicIo>()) {}
  ~TestImage_1048() override = default;
};

class ImageIsShortTypeTest_1048 : public ::testing::Test {
protected:
  TestImage_1048 image_;
};

}  // namespace

TEST_F(ImageIsShortTypeTest_1048, ReturnsTrueForUnsignedShort_1048) {
  EXPECT_TRUE(image_.isShortType(static_cast<uint16_t>(Exiv2::unsignedShort)));
}

TEST_F(ImageIsShortTypeTest_1048, ReturnsTrueForSignedShort_1048) {
  EXPECT_TRUE(image_.isShortType(static_cast<uint16_t>(Exiv2::signedShort)));
}

TEST_F(ImageIsShortTypeTest_1048, ReturnsFalseForOtherKnownTypeIds_1048) {
  // Spot-check several non-short TypeIds; these should not be treated as "short".
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::unsignedByte)));
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::asciiString)));
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::unsignedLong)));
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::signedLong)));
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::unsignedRational)));
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::signedRational)));
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::tiffIfd)));
}

TEST_F(ImageIsShortTypeTest_1048, BoundaryValuesReturnFalse_1048) {
  // Boundary conditions for uint16_t input.
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(0)));
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(1)));        // unsignedByte
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(65535u)));   // max uint16_t
}

TEST_F(ImageIsShortTypeTest_1048, NearShortTypeValuesBehavior_1048) {
  // Values adjacent to unsignedShort(3) and signedShort(8) should not match unless exact.
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::unsignedShort - 1)));  // 2
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::unsignedShort + 1)));  // 4
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::signedShort - 1)));    // 7
  EXPECT_FALSE(image_.isShortType(static_cast<uint16_t>(Exiv2::signedShort + 1)));    // 9
}