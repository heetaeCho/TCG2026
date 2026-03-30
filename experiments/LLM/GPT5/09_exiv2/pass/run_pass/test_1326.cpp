// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 1326
//
// Unit tests for Exiv2::ExifTags::isExifGroup()
// File under test: ./TestProjects/exiv2/src/tags.cpp

#include <gtest/gtest.h>

#include <string>

#include "exiv2/tags.hpp"

namespace {

class ExifTagsTest_1326 : public ::testing::Test {
 protected:
  Exiv2::ExifTags tags;
};

TEST_F(ExifTagsTest_1326, ReturnsTrueForCommonExifGroups_1326) {
  // Common Exif group names used throughout Exiv2 (should map to Exif IFDs).
  EXPECT_NO_THROW(EXPECT_TRUE(tags.isExifGroup("Exif.Image")));
  EXPECT_NO_THROW(EXPECT_TRUE(tags.isExifGroup("Exif.Photo")));
  EXPECT_NO_THROW(EXPECT_TRUE(tags.isExifGroup("Exif.Thumbnail")));
  EXPECT_NO_THROW(EXPECT_TRUE(tags.isExifGroup("Exif.GPSInfo")));
}

TEST_F(ExifTagsTest_1326, ReturnsFalseForNonExifNamespaces_1326) {
  // Groups from other metadata namespaces should not be considered Exif groups.
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup("Iptc.Application2")));
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup("Xmp.dc")));
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup("Xmp.xmp")));
}

TEST_F(ExifTagsTest_1326, ReturnsFalseForUnknownGroupName_1326) {
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup("Not.A.Real.Group")));
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup("")));
}

TEST_F(ExifTagsTest_1326, BoundaryInputs_DoNotThrow_AndAreNotExif_1326) {
  // Boundary-style inputs: whitespace, unusual casing, very long strings.
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup(" ")));
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup("\t\n")));
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup("exif.photo")));  // likely case-sensitive

  const std::string longName(4096, 'A');
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup(longName)));
}

TEST_F(ExifTagsTest_1326, HandlesNonAsciiInput_DoNotThrow_1326) {
  // Non-ASCII group names are not expected to be valid Exif group identifiers.
  // We only assert the call is safe and the result is not Exif.
  const std::string nonAscii = "Exif.\xE2\x98\x83";  // "Exif.☃" (UTF-8 snowman)
  EXPECT_NO_THROW(EXPECT_FALSE(tags.isExifGroup(nonAscii)));
}

}  // namespace