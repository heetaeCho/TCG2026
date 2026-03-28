// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::Value;
using Exiv2::TypeId;

void AddUShort(ExifData& ed, const char* key, uint16_t v) {
  ExifKey exifKey(key);
  Value::UniquePtr value = Value::create(Exiv2::unsignedShort);
  ASSERT_NE(value.get(), nullptr);
  value->read(std::to_string(v));
  ed.add(exifKey, value.get());  // ExifData clones the value internally.
}

}  // namespace

class ContrastTest_522 : public ::testing::Test {};

TEST_F(ContrastTest_522, ReturnsEndForEmptyExifData_522) {
  ExifData ed;
  const auto it = Exiv2::contrast(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(ContrastTest_522, ReturnsEndWhenNoKnownContrastKeysExist_522) {
  ExifData ed;
  // Add an unrelated key to ensure "non-empty but no match" behaves like no match.
  AddUShort(ed, "Exif.Photo.ISOSpeedRatings", 100);

  const auto it = Exiv2::contrast(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(ContrastTest_522, FindsPrimaryKeyExifPhotoContrast_522) {
  ExifData ed;
  AddUShort(ed, "Exif.Photo.Contrast", 2);

  const auto it = Exiv2::contrast(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.Contrast"));
}

TEST_F(ContrastTest_522, FindsAlternateKeyWhenPrimaryMissing_522) {
  ExifData ed;
  // Primary "Exif.Photo.Contrast" is not present.
  AddUShort(ed, "Exif.CanonCs.Contrast", 1);

  const auto it = Exiv2::contrast(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.CanonCs.Contrast"));
}

TEST_F(ContrastTest_522, PrefersEarlierKeyWhenMultipleKnownKeysExist_522) {
  ExifData ed;
  // Both are known keys; function should return the first match according to its key list.
  AddUShort(ed, "Exif.CanonCs.Contrast", 1);
  AddUShort(ed, "Exif.Photo.Contrast", 2);

  const auto it = Exiv2::contrast(ed);
  ASSERT_NE(it, ed.end());
  // "Exif.Photo.Contrast" appears earlier than "Exif.CanonCs.Contrast" in the function's key list.
  EXPECT_EQ(it->key(), std::string("Exif.Photo.Contrast"));
}

TEST_F(ContrastTest_522, CanFindLastListedKey_522) {
  ExifData ed;
  // Last key in the easyaccess.cpp contrast() key list.
  AddUShort(ed, "Exif.Casio2.Contrast2", 7);

  const auto it = Exiv2::contrast(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Casio2.Contrast2"));
}