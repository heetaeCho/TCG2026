// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_easyaccess_apertureValue_530.cpp

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

namespace {

class EasyAccessApertureValueTest_530 : public ::testing::Test {
protected:
  static void addStringValue(Exiv2::ExifData& ed, const std::string& key, const std::string& value) {
    // Exiv2::ExifData::operator[] returns Exiv2::Exifdatum&.
    // In Exiv2, Exifdatum supports assigning a string value.
    ed[key] = value;
  }
};

TEST_F(EasyAccessApertureValueTest_530, ReturnsEndWhenNoMatchingKeys_530) {
  Exiv2::ExifData ed;

  const auto it = Exiv2::apertureValue(ed);

  EXPECT_EQ(it, ed.end());
}

TEST_F(EasyAccessApertureValueTest_530, FindsExifPhotoApertureValueWhenPresent_530) {
  Exiv2::ExifData ed;
  addStringValue(ed, "Exif.Photo.ApertureValue", "5.6");

  const auto it = Exiv2::apertureValue(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.ApertureValue"));
}

TEST_F(EasyAccessApertureValueTest_530, FallsBackToExifImageApertureValueWhenPhotoMissing_530) {
  Exiv2::ExifData ed;
  addStringValue(ed, "Exif.Image.ApertureValue", "8");

  const auto it = Exiv2::apertureValue(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.ApertureValue"));
}

TEST_F(EasyAccessApertureValueTest_530, FallsBackToExifCanonSiApertureValueWhenOthersMissing_530) {
  Exiv2::ExifData ed;
  addStringValue(ed, "Exif.CanonSi.ApertureValue", "11");

  const auto it = Exiv2::apertureValue(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.CanonSi.ApertureValue"));
}

TEST_F(EasyAccessApertureValueTest_530, PrefersPhotoOverImageWhenBothPresent_530) {
  Exiv2::ExifData ed;
  addStringValue(ed, "Exif.Image.ApertureValue", "8");
  addStringValue(ed, "Exif.Photo.ApertureValue", "5.6");

  const auto it = Exiv2::apertureValue(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.ApertureValue"));
}

TEST_F(EasyAccessApertureValueTest_530, PrefersImageOverCanonSiWhenPhotoMissing_530) {
  Exiv2::ExifData ed;
  addStringValue(ed, "Exif.CanonSi.ApertureValue", "11");
  addStringValue(ed, "Exif.Image.ApertureValue", "8");

  const auto it = Exiv2::apertureValue(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.ApertureValue"));
}

TEST_F(EasyAccessApertureValueTest_530, ReturnsFirstMatchEvenIfValueIsEmptyString_530) {
  Exiv2::ExifData ed;
  addStringValue(ed, "Exif.Photo.ApertureValue", "");

  const auto it = Exiv2::apertureValue(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.ApertureValue"));
}

TEST_F(EasyAccessApertureValueTest_530, ReturnsEndAfterErasingTheOnlyMatchingEntry_530) {
  Exiv2::ExifData ed;
  addStringValue(ed, "Exif.Image.ApertureValue", "8");

  // Verify it is found first.
  ASSERT_NE(Exiv2::apertureValue(ed), ed.end());

  // Erase that entry via public iterator-based erase API.
  auto itNonConst = ed.begin();
  for (; itNonConst != ed.end(); ++itNonConst) {
    // Exifdatum supports key() in Exiv2.
    if (itNonConst->key() == std::string("Exif.Image.ApertureValue")) break;
  }
  ASSERT_NE(itNonConst, ed.end());
  ed.erase(itNonConst);

  const auto it = Exiv2::apertureValue(ed);
  EXPECT_EQ(it, ed.end());
}

}  // namespace