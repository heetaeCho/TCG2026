// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for Exiv2::shutterSpeedValue (easyaccess.cpp)
//
// The TEST_ID is 529

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

namespace {

class ShutterSpeedValueTest_529 : public ::testing::Test {};

TEST_F(ShutterSpeedValueTest_529, ReturnsEndWhenExifDataEmpty_529) {
  Exiv2::ExifData ed;

  const auto it = Exiv2::shutterSpeedValue(ed);

  EXPECT_TRUE(ed.empty());
  EXPECT_EQ(it, ed.end());
}

TEST_F(ShutterSpeedValueTest_529, ReturnsEndWhenNeitherKeyExists_529) {
  Exiv2::ExifData ed;

  // Add an unrelated key to ensure "non-empty but missing target keys".
  ed["Exif.Image.Make"] = "NIKON";

  const auto it = Exiv2::shutterSpeedValue(ed);

  EXPECT_FALSE(ed.empty());
  EXPECT_EQ(it, ed.end());
}

TEST_F(ShutterSpeedValueTest_529, FindsExifPhotoShutterSpeedValueWhenPresent_529) {
  Exiv2::ExifData ed;

  ed["Exif.Photo.ShutterSpeedValue"] = "7";  // value content not important for lookup

  const auto it = Exiv2::shutterSpeedValue(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.ShutterSpeedValue");
}

TEST_F(ShutterSpeedValueTest_529, FindsExifImageShutterSpeedValueWhenPhotoMissing_529) {
  Exiv2::ExifData ed;

  ed["Exif.Image.ShutterSpeedValue"] = "8";

  const auto it = Exiv2::shutterSpeedValue(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Image.ShutterSpeedValue");
}

TEST_F(ShutterSpeedValueTest_529, PrefersExifPhotoOverExifImageWhenBothPresent_529) {
  Exiv2::ExifData ed;

  ed["Exif.Image.ShutterSpeedValue"] = "8";
  ed["Exif.Photo.ShutterSpeedValue"] = "7";

  const auto it = Exiv2::shutterSpeedValue(ed);

  ASSERT_NE(it, ed.end());
  // Observable behavior: the returned iterator corresponds to one of the known keys.
  // Since the function searches keys in a fixed order, it should return the first match.
  EXPECT_EQ(it->key(), "Exif.Photo.ShutterSpeedValue");
}

TEST_F(ShutterSpeedValueTest_529, StillFindsKeyWithManyEntriesPresent_529) {
  Exiv2::ExifData ed;

  // Populate with many unrelated keys (boundary-ish: larger metadata set).
  ed["Exif.Image.Make"] = "NIKON";
  ed["Exif.Image.Model"] = "D850";
  ed["Exif.Photo.FNumber"] = "5/1";
  ed["Exif.Photo.ISOSpeedRatings"] = "100";
  ed["Exif.Photo.FocalLength"] = "850/10";

  // Target key
  ed["Exif.Image.ShutterSpeedValue"] = "8";

  const auto it = Exiv2::shutterSpeedValue(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Image.ShutterSpeedValue");
}

}  // namespace