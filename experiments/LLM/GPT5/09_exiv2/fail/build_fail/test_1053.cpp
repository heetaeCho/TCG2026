// =================================================================================================
//  Exiv2 Image::is4ByteType(uint16_t) unit tests
//  File: ./TestProjects/exiv2/src/image.cpp
//  TEST_ID: 1053
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

// Exiv2 public headers
#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

namespace {

// A minimal concrete Image to allow instantiation for tests that need an object.
// We never touch private/protected internals; only use public API.
class TestImageForIs4ByteType_1053 final : public Exiv2::Image {
public:
  TestImageForIs4ByteType_1053()
      : Exiv2::Image(/*type*/ Exiv2::ImageType::none, /*supportedMetadata*/ 0, /*io*/ nullptr) {}

  ~TestImageForIs4ByteType_1053() override = default;
};

class ImageIs4ByteTypeTest_1053 : public ::testing::Test {
protected:
  TestImageForIs4ByteType_1053 img_;
};

// NOTE:
// is4ByteType is static in the header. The partial implementation shown uses:
//   return isLongType(type) || type == Exiv2::tiffFloat || type == Exiv2::tiffIfd;
// These tests validate observable behavior for known TypeIds and some boundary-ish values,
// without relying on any private state or re-implementing helper logic.

}  // namespace

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsTrueForUnsignedLong_1053) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(Exiv2::unsignedLong)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsTrueForSignedLong_1053) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(Exiv2::signedLong)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsTrueForTiffFloat_1053) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(Exiv2::tiffFloat)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsTrueForTiffIfd_1053) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(Exiv2::tiffIfd)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsFalseForUnsignedShort_1053) {
  EXPECT_FALSE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(Exiv2::unsignedShort)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsFalseForUnsignedRational_1053) {
  // Rational types are typically 8 bytes (two 4-byte integers), so is4ByteType should be false.
  EXPECT_FALSE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(Exiv2::unsignedRational)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsFalseForTiffDouble_1053) {
  EXPECT_FALSE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(Exiv2::tiffDouble)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsFalseForUndefined_1053) {
  EXPECT_FALSE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(Exiv2::undefined)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsFalseForZeroTypeIdBoundary_1053) {
  // Boundary / unusual value not listed in TypeId enumeration.
  EXPECT_FALSE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(0)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsFalseForMaxUint16Boundary_1053) {
  // Boundary value; should not crash and should return a deterministic boolean.
  EXPECT_FALSE(Exiv2::Image::is4ByteType(static_cast<uint16_t>(0xFFFF)));
}

TEST_F(ImageIs4ByteTypeTest_1053, ReturnsFalseForTypeIdBeyondUint16Truncation_1053) {
  // Some TypeIds (e.g., Exiv2::string = 65536) exceed uint16_t.
  // is4ByteType takes uint16_t, so the caller may accidentally truncate.
  // We validate it behaves safely and predictably for the truncated value.
  const uint16_t truncated = static_cast<uint16_t>(Exiv2::string);  // 65536 -> 0
  EXPECT_EQ(truncated, static_cast<uint16_t>(0));
  EXPECT_FALSE(Exiv2::Image::is4ByteType(truncated));
}

TEST_F(ImageIs4ByteTypeTest_1053, CallableViaInstanceAsWellAsClass_1053) {
  // Even though the API is static, calling through an instance is allowed in C++.
  // This checks the call path is available and consistent.
  EXPECT_EQ(img_.is4ByteType(static_cast<uint16_t>(Exiv2::tiffIfd)),
            Exiv2::Image::is4ByteType(static_cast<uint16_t>(Exiv2::tiffIfd)));
}