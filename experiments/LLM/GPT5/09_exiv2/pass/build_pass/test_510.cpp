// File: test_easyaccess_orientation_510.cpp
#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

#include <cstdint>
#include <string>

namespace {

class OrientationTest_510 : public ::testing::Test {
 protected:
  static void SetUShort(Exiv2::ExifData& ed, const std::string& key, uint16_t v) {
    // Exiv2::Exifdatum supports assignment from integer types in the public API.
    ed[key] = v;
  }
};

TEST_F(OrientationTest_510, ReturnsEndWhenExifDataEmpty_510) {
  Exiv2::ExifData ed;

  const auto it = Exiv2::orientation(ed);

  EXPECT_EQ(it, ed.end());
}

TEST_F(OrientationTest_510, ReturnsEndWhenNoKnownOrientationKeysPresent_510) {
  Exiv2::ExifData ed;
  SetUShort(ed, "Exif.Image.Make", 1);
  SetUShort(ed, "Exif.Photo.Flash", 0);

  const auto it = Exiv2::orientation(ed);

  EXPECT_EQ(it, ed.end());
}

TEST_F(OrientationTest_510, FindsPrimaryExifImageOrientationWhenPresent_510) {
  Exiv2::ExifData ed;
  SetUShort(ed, "Exif.Image.Orientation", 6);

  const auto it = Exiv2::orientation(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Image.Orientation");
}

TEST_F(OrientationTest_510, FindsLaterKeyWhenPrimaryKeyMissing_510) {
  Exiv2::ExifData ed;
  SetUShort(ed, "Exif.Panasonic.Rotation", 90);

  const auto it = Exiv2::orientation(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Panasonic.Rotation");
}

TEST_F(OrientationTest_510, RespectsKeyPriorityOrderWhenMultiplePresent_510) {
  Exiv2::ExifData ed;

  // Add a "later" key first, then the earlier/primary key afterwards.
  SetUShort(ed, "Exif.Panasonic.Rotation", 90);
  SetUShort(ed, "Exif.Image.Orientation", 3);

  const auto it = Exiv2::orientation(ed);

  ASSERT_NE(it, ed.end());
  // Observable behavior: the iterator should refer to the highest-priority key.
  EXPECT_EQ(it->key(), "Exif.Image.Orientation");
}

TEST_F(OrientationTest_510, ReturnsFirstMatchAmongSeveralNonPrimaryKeys_510) {
  Exiv2::ExifData ed;

  // Both are in the known list; Panasonic.Rotation appears before PanasonicRaw.Orientation.
  SetUShort(ed, "Exif.PanasonicRaw.Orientation", 2);
  SetUShort(ed, "Exif.Panasonic.Rotation", 90);

  const auto it = Exiv2::orientation(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Panasonic.Rotation");
}

TEST_F(OrientationTest_510, HandlesDuplicateKeyInSearchListByReturningThatKeyIfPresent_510) {
  Exiv2::ExifData ed;

  // This key appears more than once in the compiled-in key list in easyaccess.cpp.
  SetUShort(ed, "Exif.Sony1MltCsA100.Rotation", 1);

  const auto it = Exiv2::orientation(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Sony1MltCsA100.Rotation");
}

}  // namespace