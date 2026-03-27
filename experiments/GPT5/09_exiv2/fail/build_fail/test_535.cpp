// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_easyaccess_lightSource_535.cpp

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

namespace {

// TEST_ID = 535
class EasyAccessLightSourceTest_535 : public ::testing::Test {
 protected:
  Exiv2::ExifData ed_;
};

TEST_F(EasyAccessLightSourceTest_535, ReturnsEndWhenExifDataEmpty_535) {
  const auto it = Exiv2::lightSource(ed_);
  EXPECT_EQ(it, ed_.end());
}

TEST_F(EasyAccessLightSourceTest_535, ReturnsEndWhenNoMatchingKeysPresent_535) {
  ed_["Exif.Image.Make"] = "TestMake";
  ed_["Exif.Photo.ExposureTime"] = "1/125";
  ed_["Exif.Photo.ISOSpeedRatings"] = "100";

  const auto it = Exiv2::lightSource(ed_);
  EXPECT_EQ(it, ed_.end());
}

TEST_F(EasyAccessLightSourceTest_535, FindsExifPhotoLightSourceWhenPresent_535) {
  ed_["Exif.Photo.LightSource"] = "1";

  const auto it = Exiv2::lightSource(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.Photo.LightSource");
}

TEST_F(EasyAccessLightSourceTest_535, FindsExifImageLightSourceWhenPhotoMissing_535) {
  ed_["Exif.Image.LightSource"] = "2";

  const auto it = Exiv2::lightSource(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.Image.LightSource");
}

TEST_F(EasyAccessLightSourceTest_535, PrefersExifPhotoLightSourceWhenBothPresent_535) {
  ed_["Exif.Image.LightSource"] = "2";
  ed_["Exif.Photo.LightSource"] = "1";

  const auto it = Exiv2::lightSource(ed_);
  ASSERT_NE(it, ed_.end());
  // Observable behavior from the public return value: which key was selected.
  EXPECT_EQ(it->key(), "Exif.Photo.LightSource");
}

TEST_F(EasyAccessLightSourceTest_535, StillFindsLightSourceAmongManyEntries_535) {
  // Add a bunch of unrelated metadata to exercise a "busy" ExifData scenario.
  ed_["Exif.Image.Make"] = "TestMake";
  ed_["Exif.Image.Model"] = "TestModel";
  ed_["Exif.Photo.FNumber"] = "5.6";
  ed_["Exif.Photo.FocalLength"] = "50/1";
  ed_["Exif.Photo.DateTimeOriginal"] = "2026:02:05 08:00:00";

  ed_["Exif.Image.LightSource"] = "3";

  const auto it = Exiv2::lightSource(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.Image.LightSource");
}

}  // namespace