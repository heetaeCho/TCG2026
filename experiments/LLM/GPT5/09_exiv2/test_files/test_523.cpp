// File: test_sceneCaptureType_523.cpp
// Unit tests for Exiv2::sceneCaptureType (./TestProjects/exiv2/src/easyaccess.cpp)

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

// Helper: add a minimal Value for a given Exif key into ExifData.
// We deliberately avoid assuming anything about sceneCaptureType internals beyond the public API.
static void AddUShortValue(Exiv2::ExifData& ed, const std::string& keyStr, uint16_t v) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
  // Exiv2::Value::read parses a string representation.
  value->read(std::to_string(v));
  ed.add(Exiv2::ExifKey(keyStr), value.get());
}

class SceneCaptureTypeTest_523 : public ::testing::Test {};

}  // namespace

TEST_F(SceneCaptureTypeTest_523, ReturnsEndForEmptyExifData_523) {
  Exiv2::ExifData ed;
  const auto it = Exiv2::sceneCaptureType(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(SceneCaptureTypeTest_523, ReturnsEndWhenNoMatchingKeysPresent_523) {
  Exiv2::ExifData ed;
  AddUShortValue(ed, "Exif.Photo.FNumber", 8);
  AddUShortValue(ed, "Exif.Photo.ISOSpeedRatings", 100);

  const auto it = Exiv2::sceneCaptureType(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(SceneCaptureTypeTest_523, FindsPrimaryKeyExifPhotoSceneCaptureType_523) {
  Exiv2::ExifData ed;
  AddUShortValue(ed, "Exif.Photo.SceneCaptureType", 1);

  const auto it = Exiv2::sceneCaptureType(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.SceneCaptureType");
}

TEST_F(SceneCaptureTypeTest_523, FallsBackToExifOlympusSpecialModeWhenPrimaryMissing_523) {
  Exiv2::ExifData ed;
  AddUShortValue(ed, "Exif.Olympus.SpecialMode", 7);

  const auto it = Exiv2::sceneCaptureType(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Olympus.SpecialMode");
}

TEST_F(SceneCaptureTypeTest_523, PrefersPrimaryKeyWhenBothKeysPresent_523) {
  Exiv2::ExifData ed;
  // Insert both keys; the observable requirement is that the returned iterator points to the
  // preferred key (as determined by the function's interface-level behavior).
  AddUShortValue(ed, "Exif.Olympus.SpecialMode", 7);
  AddUShortValue(ed, "Exif.Photo.SceneCaptureType", 1);

  const auto it = Exiv2::sceneCaptureType(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.SceneCaptureType");
}

TEST_F(SceneCaptureTypeTest_523, UnchangedByUnrelatedEntriesEvenWhenManyPresent_523) {
  Exiv2::ExifData ed;
  AddUShortValue(ed, "Exif.Photo.FNumber", 8);
  AddUShortValue(ed, "Exif.Photo.ExposureTime", 1);
  AddUShortValue(ed, "Exif.Photo.ISOSpeedRatings", 200);
  AddUShortValue(ed, "Exif.Olympus.SpecialMode", 5);
  AddUShortValue(ed, "Exif.Photo.FocalLength", 50);

  const auto it = Exiv2::sceneCaptureType(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Olympus.SpecialMode");
}