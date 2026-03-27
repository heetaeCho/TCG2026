// File: test_easyaccess_make_525.cpp
#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

namespace {

class EasyAccessMakeTest_525 : public ::testing::Test {};

TEST_F(EasyAccessMakeTest_525, ReturnsEndWhenExifDataEmpty_525) {
  const Exiv2::ExifData ed;
  const auto it = Exiv2::make(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(EasyAccessMakeTest_525, ReturnsEndWhenNoMatchingKeysPresent_525) {
  Exiv2::ExifData ed;
  ed["Exif.Image.Model"] = "X100V";
  ed["Exif.Photo.DateTimeOriginal"] = "2020:01:01 00:00:00";

  const auto& ced = ed;
  const auto it = Exiv2::make(ced);
  EXPECT_EQ(it, ced.end());
}

TEST_F(EasyAccessMakeTest_525, FindsExifImageMakeWhenPresent_525) {
  Exiv2::ExifData ed;
  ed["Exif.Image.Make"] = "Nikon";

  const auto& ced = ed;
  const auto it = Exiv2::make(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.Make"));

  const auto expected = ced.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  EXPECT_EQ(it, expected);
}

TEST_F(EasyAccessMakeTest_525, FindsPanasonicRawMakeWhenPresent_525) {
  Exiv2::ExifData ed;
  ed["Exif.PanasonicRaw.Make"] = "Panasonic";

  const auto& ced = ed;
  const auto it = Exiv2::make(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.PanasonicRaw.Make"));

  const auto expected = ced.findKey(Exiv2::ExifKey("Exif.PanasonicRaw.Make"));
  EXPECT_EQ(it, expected);
}

TEST_F(EasyAccessMakeTest_525, PrefersExifImageMakeOverPanasonicRawMakeWhenBothPresent_525) {
  Exiv2::ExifData ed;
  ed["Exif.PanasonicRaw.Make"] = "Panasonic";
  ed["Exif.Image.Make"] = "Nikon";

  const auto& ced = ed;
  const auto it = Exiv2::make(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.Make"));

  const auto expectedPreferred = ced.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  EXPECT_EQ(it, expectedPreferred);
}

}  // namespace