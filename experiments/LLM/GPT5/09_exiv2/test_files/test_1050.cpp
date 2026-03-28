// =================================================================================================
// TEST_ID: 1050
// Unit tests for Exiv2::Image::isLongLongType(uint16_t)
// File: ./TestProjects/exiv2/src/image.cpp (black-box behavior via public interface)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

// Exiv2 public headers
#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

namespace {

// A minimal concrete Image so we can call the (non-static) member function isLongLongType()
// without touching private/protected internals. We never invoke any virtual metadata I/O here.
class TestImageForLongLongType_1050 final : public Exiv2::Image {
public:
  TestImageForLongLongType_1050()
      : Exiv2::Image(/*type*/ static_cast<Exiv2::ImageType>(0),
                     /*supportedMetadata*/ 0,
                     /*io*/ Exiv2::BasicIo::UniquePtr{}) {}
  ~TestImageForLongLongType_1050() override = default;
};

class ImageIsLongLongTypeTest_1050 : public ::testing::Test {
protected:
  TestImageForLongLongType_1050 img_;
};

}  // namespace

// Normal operation: recognized long long types
TEST_F(ImageIsLongLongTypeTest_1050, ReturnsTrueForUnsignedLongLong_1050) {
  EXPECT_TRUE(img_.isLongLongType(static_cast<uint16_t>(Exiv2::unsignedLongLong)));
}

TEST_F(ImageIsLongLongTypeTest_1050, ReturnsTrueForSignedLongLong_1050) {
  EXPECT_TRUE(img_.isLongLongType(static_cast<uint16_t>(Exiv2::signedLongLong)));
}

// Normal operation: other known types should not be classified as "long long"
TEST_F(ImageIsLongLongTypeTest_1050, ReturnsFalseForUnsignedLong_1050) {
  EXPECT_FALSE(img_.isLongLongType(static_cast<uint16_t>(Exiv2::unsignedLong)));
}

TEST_F(ImageIsLongLongTypeTest_1050, ReturnsFalseForSignedLong_1050) {
  EXPECT_FALSE(img_.isLongLongType(static_cast<uint16_t>(Exiv2::signedLong)));
}

TEST_F(ImageIsLongLongTypeTest_1050, ReturnsFalseForTiffIfd8_1050) {
  EXPECT_FALSE(img_.isLongLongType(static_cast<uint16_t>(Exiv2::tiffIfd8)));
}

TEST_F(ImageIsLongLongTypeTest_1050, ReturnsFalseForAsciiString_1050) {
  EXPECT_FALSE(img_.isLongLongType(static_cast<uint16_t>(Exiv2::asciiString)));
}

// Boundary conditions: low/high and "invalid" values should be handled safely (no exceptions),
// and should not be reported as long long unless they match the expected ids.
TEST_F(ImageIsLongLongTypeTest_1050, ReturnsFalseForZeroType_1050) {
  EXPECT_FALSE(img_.isLongLongType(static_cast<uint16_t>(0)));
}

TEST_F(ImageIsLongLongTypeTest_1050, ReturnsFalseForMaxUint16_1050) {
  EXPECT_FALSE(img_.isLongLongType(static_cast<uint16_t>(0xFFFF)));
}

TEST_F(ImageIsLongLongTypeTest_1050, ReturnsFalseForInvalidTypeIdTruncatedToUint16_1050) {
  // invalidTypeId is 131070; the function takes uint16_t so it will be truncated.
  // We only assert observable behavior through the interface: should not be treated as long long.
  const uint16_t truncated = static_cast<uint16_t>(Exiv2::invalidTypeId);
  EXPECT_FALSE(img_.isLongLongType(truncated));
}

// Exceptional / error cases: none observable (pure predicate). Still verify it doesn't throw.
TEST_F(ImageIsLongLongTypeTest_1050, DoesNotThrowForArbitraryValue_1050) {
  EXPECT_NO_THROW({
    volatile bool r = img_.isLongLongType(static_cast<uint16_t>(12345));
    (void)r;
  });
}