// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifthumbc_extension_769.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/exifdata.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/value.hpp>

namespace {

class ExifThumbCTest_769 : public ::testing::Test {
 protected:
  Exiv2::ExifData exif_;
};

TEST_F(ExifThumbCTest_769, Extension_EmptyExifDataReturnsEmptyString_769) {
  const Exiv2::ExifThumbC thumb(exif_);

  const char* ext = thumb.extension();

  // Observable behavior: for ExifData with no thumbnail, extension() should be empty.
  ASSERT_NE(ext, nullptr);
  EXPECT_STREQ(ext, "");
}

TEST_F(ExifThumbCTest_769, Extension_WithUnrelatedExifTagsStillReturnsEmptyString_769) {
  // Add some unrelated EXIF metadata (not a thumbnail).
  exif_["Exif.Image.Make"] = std::string("TestMaker");
  exif_["Exif.Image.Model"] = std::string("TestModel");

  const Exiv2::ExifThumbC thumb(exif_);
  const char* ext = thumb.extension();

  ASSERT_NE(ext, nullptr);
  EXPECT_STREQ(ext, "");
}

TEST_F(ExifThumbCTest_769, Extension_CalledMultipleTimesIsSafeAndConsistentForNoThumbnail_769) {
  const Exiv2::ExifThumbC thumb(exif_);

  const char* ext1 = thumb.extension();
  const char* ext2 = thumb.extension();

  ASSERT_NE(ext1, nullptr);
  ASSERT_NE(ext2, nullptr);

  // For "no thumbnail" case, both calls should report an empty extension.
  EXPECT_STREQ(ext1, "");
  EXPECT_STREQ(ext2, "");
}

}  // namespace