// =================================================================================================
//  TEST_ID: 1063
//  File:    test_image_typeName_1063.cpp
//  Purpose: Unit tests for Exiv2::Image::typeName(uint16_t)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include <exiv2/image.hpp>
#include <exiv2/types.hpp>

namespace {

// Exiv2::Image::typeName is protected, so expose it via a tiny derived test class.
// We do NOT change behavior; we only provide access for testing observable output.
class TestImageTypeNameAccessor : public Exiv2::Image {
public:
  // Construct with minimal requirements; we don't use IO/metadata for these tests.
  TestImageTypeNameAccessor()
      : Exiv2::Image(Exiv2::ImageType::none, /*supportedMetadata*/ 0, Exiv2::BasicIo::UniquePtr()) {}

  const char* CallTypeName(uint16_t tag) { return this->typeName(tag); }
};

class ImageTypeNameTest_1063 : public ::testing::Test {
protected:
  TestImageTypeNameAccessor img_;
};

}  // namespace

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForUnsignedByte_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::unsignedByte));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "BYTE");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForAsciiString_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::asciiString));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "ASCII");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForUnsignedShort_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::unsignedShort));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "SHORT");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForUnsignedLong_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::unsignedLong));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "LONG");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForUnsignedRational_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::unsignedRational));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "RATIONAL");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForSignedByte_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::signedByte));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "SBYTE");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForUndefined_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::undefined));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "UNDEFINED");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForSignedShort_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::signedShort));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "SSHORT");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForSignedLong_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::signedLong));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "SLONG");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForSignedRational_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::signedRational));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "SRATIONAL");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForTiffFloat_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::tiffFloat));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "FLOAT");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForTiffDouble_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::tiffDouble));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "DOUBLE");
}

TEST_F(ImageTypeNameTest_1063, ReturnsExpectedNameForTiffIfd_1063) {
  const char* s = img_.CallTypeName(static_cast<uint16_t>(Exiv2::tiffIfd));
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "IFD");
}

TEST_F(ImageTypeNameTest_1063, ReturnsUnknownForUnrecognizedTypeId_1063) {
  const uint16_t unknownTag = static_cast<uint16_t>(0);
  const char* s = img_.CallTypeName(unknownTag);
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "unknown");
}

TEST_F(ImageTypeNameTest_1063, ReturnsUnknownForValidButUnmappedTypeIds_1063) {
  // These are valid TypeId values per types.hpp but not listed in the provided switch.
  const uint16_t t1 = static_cast<uint16_t>(Exiv2::unsignedLongLong);
  const uint16_t t2 = static_cast<uint16_t>(Exiv2::signedLongLong);
  const uint16_t t3 = static_cast<uint16_t>(Exiv2::tiffIfd8);

  const char* s1 = img_.CallTypeName(t1);
  const char* s2 = img_.CallTypeName(t2);
  const char* s3 = img_.CallTypeName(t3);

  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);
  ASSERT_NE(s3, nullptr);

  EXPECT_STREQ(s1, "unknown");
  EXPECT_STREQ(s2, "unknown");
  EXPECT_STREQ(s3, "unknown");
}

TEST_F(ImageTypeNameTest_1063, ReturnsUnknownForLargeOutOfRangeValues_1063) {
  // Boundary-ish: max uint16_t.
  const uint16_t maxTag = static_cast<uint16_t>(0xFFFFu);
  const char* s = img_.CallTypeName(maxTag);
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "unknown");
}

TEST_F(ImageTypeNameTest_1063, ReturnedPointerIsStableAcrossCallsForSameTag_1063) {
  // We only check that the returned pointer address stays the same across calls,
  // which is observable behavior and does not depend on private state.
  const uint16_t tag = static_cast<uint16_t>(Exiv2::unsignedShort);

  const char* a = img_.CallTypeName(tag);
  const char* b = img_.CallTypeName(tag);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_EQ(a, b);
  EXPECT_STREQ(a, "SHORT");
}