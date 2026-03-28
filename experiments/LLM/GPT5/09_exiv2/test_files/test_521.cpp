// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_easyaccess_sharpness_521.cpp

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

class EasyAccessSharpnessTest_521 : public ::testing::Test {
 protected:
  static void AddUShort(Exiv2::ExifData& ed, const std::string& keyStr, uint16_t v) {
    Exiv2::ExifKey key(keyStr);
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    ASSERT_NE(value.get(), nullptr);
    value->read(std::to_string(v));
    ed.add(key, value.get());
  }
};

TEST_F(EasyAccessSharpnessTest_521, ReturnsEndWhenExifDataEmpty_521) {
  Exiv2::ExifData ed;
  const auto it = Exiv2::sharpness(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(EasyAccessSharpnessTest_521, ReturnsIteratorToFirstKeyWhenPresent_521) {
  Exiv2::ExifData ed;
  AddUShort(ed, "Exif.Photo.Sharpness", 1);

  const auto expected = ed.findKey(Exiv2::ExifKey("Exif.Photo.Sharpness"));
  ASSERT_NE(expected, ed.end());

  const auto it = Exiv2::sharpness(ed);
  EXPECT_EQ(it, expected);
}

TEST_F(EasyAccessSharpnessTest_521, PrefersEarlierKeyOverLaterKeyWhenBothPresent_521) {
  Exiv2::ExifData ed;

  // Put a later key in the list first, then an earlier one.
  AddUShort(ed, "Exif.Casio2.Sharpness2", 22);
  AddUShort(ed, "Exif.Photo.Sharpness", 11);

  const auto expectedEarlier = ed.findKey(Exiv2::ExifKey("Exif.Photo.Sharpness"));
  ASSERT_NE(expectedEarlier, ed.end());

  const auto it = Exiv2::sharpness(ed);
  EXPECT_EQ(it, expectedEarlier);
}

TEST_F(EasyAccessSharpnessTest_521, ReturnsIteratorToLastKeyWhenOnlyLastKeyPresent_521) {
  Exiv2::ExifData ed;
  AddUShort(ed, "Exif.Casio2.Sharpness2", 7);

  const auto expected = ed.findKey(Exiv2::ExifKey("Exif.Casio2.Sharpness2"));
  ASSERT_NE(expected, ed.end());

  const auto it = Exiv2::sharpness(ed);
  EXPECT_EQ(it, expected);
}

TEST_F(EasyAccessSharpnessTest_521, IgnoresUnknownKeysAndReturnsEndWhenNoMatch_521) {
  Exiv2::ExifData ed;
  AddUShort(ed, "Exif.Photo.ISOSpeedRatings", 100);  // Not in the sharpness key list.

  const auto it = Exiv2::sharpness(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(EasyAccessSharpnessTest_521, DoesNotModifyExifDataObservableCount_521) {
  Exiv2::ExifData ed;
  AddUShort(ed, "Exif.Fujifilm.Sharpness", 3);
  AddUShort(ed, "Exif.Photo.ISOSpeedRatings", 200);

  const auto beforeCount = ed.count();
  (void)Exiv2::sharpness(ed);
  const auto afterCount = ed.count();

  EXPECT_EQ(afterCount, beforeCount);
}

}  // namespace