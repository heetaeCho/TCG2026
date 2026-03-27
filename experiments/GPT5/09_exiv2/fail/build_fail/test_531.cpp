// =================================================================================================
// TEST_ID: 531
// File: test_easyaccess_brightnessvalue_531.cpp
// Unit tests for Exiv2::brightnessValue(const Exiv2::ExifData&)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

class BrightnessValueTest_531 : public ::testing::Test {
 protected:
  static void AddDummyExif(Exiv2::ExifData& ed, const std::string& key, const std::string& value = "0") {
    Exiv2::ExifKey exifKey(key);

    // Create a generic value (ASCII) and populate it. We only need the tag to exist for lookup.
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
    ASSERT_TRUE(v.get() != nullptr);
    ASSERT_NO_THROW(v->read(value));

    // ExifData::add clones/copies the Value internally in Exiv2.
    ASSERT_NO_THROW(ed.add(exifKey, v.get()));
  }
};

TEST_F(BrightnessValueTest_531, ReturnsEndForEmptyExifData_531) {
  Exiv2::ExifData ed;
  const Exiv2::ExifData& ced = ed;

  auto it = Exiv2::brightnessValue(ced);
  EXPECT_EQ(it, ced.end());
}

TEST_F(BrightnessValueTest_531, FindsExifPhotoBrightnessValueWhenPresent_531) {
  Exiv2::ExifData ed;
  AddDummyExif(ed, "Exif.Photo.BrightnessValue", "1");

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::brightnessValue(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it, ced.findKey(Exiv2::ExifKey("Exif.Photo.BrightnessValue")));
}

TEST_F(BrightnessValueTest_531, FindsExifImageBrightnessValueWhenPhotoKeyAbsent_531) {
  Exiv2::ExifData ed;
  AddDummyExif(ed, "Exif.Image.BrightnessValue", "2");

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::brightnessValue(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it, ced.findKey(Exiv2::ExifKey("Exif.Image.BrightnessValue")));
}

TEST_F(BrightnessValueTest_531, FindsSony1BrightnessWhenOnlySony1KeyPresent_531) {
  Exiv2::ExifData ed;
  AddDummyExif(ed, "Exif.Sony1.Brightness", "3");

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::brightnessValue(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it, ced.findKey(Exiv2::ExifKey("Exif.Sony1.Brightness")));
}

TEST_F(BrightnessValueTest_531, FindsSony2BrightnessWhenOnlySony2KeyPresent_531) {
  Exiv2::ExifData ed;
  AddDummyExif(ed, "Exif.Sony2.Brightness", "4");

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::brightnessValue(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it, ced.findKey(Exiv2::ExifKey("Exif.Sony2.Brightness")));
}

TEST_F(BrightnessValueTest_531, PrefersPhotoBrightnessOverOtherCandidates_531) {
  Exiv2::ExifData ed;
  AddDummyExif(ed, "Exif.Image.BrightnessValue", "2");
  AddDummyExif(ed, "Exif.Sony1.Brightness", "3");
  AddDummyExif(ed, "Exif.Sony2.Brightness", "4");
  AddDummyExif(ed, "Exif.Photo.BrightnessValue", "1");  // highest priority per key list in interface

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::brightnessValue(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it, ced.findKey(Exiv2::ExifKey("Exif.Photo.BrightnessValue")));
}

TEST_F(BrightnessValueTest_531, PrefersImageBrightnessOverSonyCandidatesWhenPhotoAbsent_531) {
  Exiv2::ExifData ed;
  AddDummyExif(ed, "Exif.Sony1.Brightness", "3");
  AddDummyExif(ed, "Exif.Sony2.Brightness", "4");
  AddDummyExif(ed, "Exif.Image.BrightnessValue", "2");  // higher priority than Sony keys

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::brightnessValue(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it, ced.findKey(Exiv2::ExifKey("Exif.Image.BrightnessValue")));
}

TEST_F(BrightnessValueTest_531, ReturnsEndWhenNoCandidateKeysExist_531) {
  Exiv2::ExifData ed;
  AddDummyExif(ed, "Exif.Image.Make", "Sony");  // unrelated key

  const Exiv2::ExifData& ced = ed;
  auto it = Exiv2::brightnessValue(ced);

  EXPECT_EQ(it, ced.end());
}

}  // namespace