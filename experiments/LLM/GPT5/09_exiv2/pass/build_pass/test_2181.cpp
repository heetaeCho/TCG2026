// File: test_exifkey_ctor_tag_groupname_2181.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "exiv2/error.hpp"
#include "exiv2/tags.hpp"

namespace {

class ExifKeyCtorTagGroupNameTest_2181 : public ::testing::Test {};

// Normal operation: construct with a widely-known Exif.Image tag (IFD0 "Make" = 0x010F).
TEST_F(ExifKeyCtorTagGroupNameTest_2181, ConstructWithValidExifImageTagDoesNotThrow_2181) {
  ASSERT_NO_THROW({
    Exiv2::ExifKey key(/*tag=*/0x010F, /*groupName=*/"Exif.Image");
    EXPECT_EQ(key.groupName(), "Exif.Image");
    EXPECT_EQ(key.tag(), static_cast<uint16_t>(0x010F));

    // Observable, non-prescriptive sanity checks (do not assume specific internal formatting).
    EXPECT_FALSE(key.key().empty());
    EXPECT_FALSE(key.tagName().empty());
  });
}

// Normal operation: construct with a widely-known Exif.Photo tag ("ExposureTime" = 0x829A).
TEST_F(ExifKeyCtorTagGroupNameTest_2181, ConstructWithValidExifPhotoTagDoesNotThrow_2181) {
  ASSERT_NO_THROW({
    Exiv2::ExifKey key(/*tag=*/0x829A, /*groupName=*/"Exif.Photo");
    EXPECT_EQ(key.groupName(), "Exif.Photo");
    EXPECT_EQ(key.tag(), static_cast<uint16_t>(0x829A));

    EXPECT_FALSE(key.key().empty());
    EXPECT_FALSE(key.tagName().empty());
  });
}

// Boundary-ish / API robustness: passing an unknown/invalid group name should throw.
TEST_F(ExifKeyCtorTagGroupNameTest_2181, ConstructWithInvalidGroupNameThrows_2181) {
  EXPECT_THROW(
      {
        Exiv2::ExifKey key(/*tag=*/0x010F, /*groupName=*/"NotARealGroup");
        (void)key;
      },
      Exiv2::Error);
}

// Exceptional case: valid-looking group, but an unlikely/unknown tag should throw (observable via exception).
TEST_F(ExifKeyCtorTagGroupNameTest_2181, ConstructWithUnknownTagInValidGroupThrows_2181) {
  EXPECT_THROW(
      {
        Exiv2::ExifKey key(/*tag=*/0xFFFF, /*groupName=*/"Exif.Image");
        (void)key;
      },
      Exiv2::Error);
}

// Boundary condition: tag zero may or may not exist; we only assert that behavior is consistent/observable.
// This test checks that the constructor either succeeds and returns matching tag/group, or throws Exiv2::Error.
TEST_F(ExifKeyCtorTagGroupNameTest_2181, ConstructWithZeroTagIsEitherValidOrThrowsError_2181) {
  try {
    Exiv2::ExifKey key(/*tag=*/0x0000, /*groupName=*/"Exif.Image");
    EXPECT_EQ(key.groupName(), "Exif.Image");
    EXPECT_EQ(key.tag(), static_cast<uint16_t>(0x0000));
  } catch (const Exiv2::Error&) {
    SUCCEED();  // Acceptable observable behavior: implementation rejects unknown tag.
  }
}

}  // namespace