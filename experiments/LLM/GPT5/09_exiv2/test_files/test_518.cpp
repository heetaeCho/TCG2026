// SPDX-License-Identifier: MIT
// File: test_easyaccess_whiteBalance_518.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

namespace {

void addAsciiValue(Exiv2::ExifData& ed, const std::string& key, const std::string& value) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NO_THROW(v->read(value));
  ASSERT_NO_THROW(ed.add(Exiv2::ExifKey(key), v.get()));
}

}  // namespace

TEST(WhiteBalanceTest_518, ReturnsEndWhenExifDataEmpty_518) {
  Exiv2::ExifData ed;
  const Exiv2::ExifData& ced = ed;

  auto it = Exiv2::whiteBalance(ced);
  EXPECT_EQ(it, ced.end());
}

TEST(WhiteBalanceTest_518, ReturnsEndWhenNoKnownKeysPresent_518) {
  Exiv2::ExifData ed;
  // Add an unrelated key
  addAsciiValue(ed, "Exif.Image.Make", "AnyMake");
  const Exiv2::ExifData& ced = ed;

  auto it = Exiv2::whiteBalance(ced);
  EXPECT_EQ(it, ced.end());
}

TEST(WhiteBalanceTest_518, ReturnsIteratorToPhotoWhiteBalanceWhenPresent_518) {
  Exiv2::ExifData ed;
  addAsciiValue(ed, "Exif.Photo.WhiteBalance", "1");
  const Exiv2::ExifData& ced = ed;

  auto expected = ced.findKey(Exiv2::ExifKey("Exif.Photo.WhiteBalance"));
  ASSERT_NE(expected, ced.end());

  auto it = Exiv2::whiteBalance(ced);
  EXPECT_EQ(it, expected);
}

TEST(WhiteBalanceTest_518, PrefersEarlierKeyWhenMultipleKnownKeysExist_518) {
  Exiv2::ExifData ed;

  // Two known keys from the provided priority list:
  // "Exif.CanonSi.WhiteBalance" appears before "Exif.Photo.WhiteBalance".
  addAsciiValue(ed, "Exif.Photo.WhiteBalance", "9");
  addAsciiValue(ed, "Exif.CanonSi.WhiteBalance", "2");
  const Exiv2::ExifData& ced = ed;

  auto expected = ced.findKey(Exiv2::ExifKey("Exif.CanonSi.WhiteBalance"));
  ASSERT_NE(expected, ced.end());

  auto it = Exiv2::whiteBalance(ced);
  EXPECT_EQ(it, expected);
}

TEST(WhiteBalanceTest_518, PicksFirstAmongSeveralAcrossVendorsInPriorityOrder_518) {
  Exiv2::ExifData ed;

  // From the provided list ordering:
  // CanonSi (1st) < Fujifilm < ... < Nikon3 < ... < Photo (last)
  addAsciiValue(ed, "Exif.Nikon3.WhiteBalance", "3");
  addAsciiValue(ed, "Exif.Fujifilm.WhiteBalance", "4");
  addAsciiValue(ed, "Exif.Photo.WhiteBalance", "5");
  const Exiv2::ExifData& ced = ed;

  auto expected = ced.findKey(Exiv2::ExifKey("Exif.Fujifilm.WhiteBalance"));
  ASSERT_NE(expected, ced.end());

  auto it = Exiv2::whiteBalance(ced);
  EXPECT_EQ(it, expected);
}

TEST(WhiteBalanceTest_518, Boundary_SingleKeyAtEndOfPriorityListOnly_518) {
  Exiv2::ExifData ed;

  // Explicitly test the last key in the priority list is found when it's the only match.
  addAsciiValue(ed, "Exif.Photo.WhiteBalance", "0");
  // Add other unrelated keys to ensure it doesn't affect selection.
  addAsciiValue(ed, "Exif.Image.Model", "X");
  addAsciiValue(ed, "Exif.Image.Software", "Y");

  const Exiv2::ExifData& ced = ed;
  auto expected = ced.findKey(Exiv2::ExifKey("Exif.Photo.WhiteBalance"));
  ASSERT_NE(expected, ced.end());

  auto it = Exiv2::whiteBalance(ced);
  EXPECT_EQ(it, expected);
}