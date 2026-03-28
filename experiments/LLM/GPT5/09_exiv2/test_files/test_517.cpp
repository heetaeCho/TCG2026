// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: test_easyaccess_imageQuality_517.cpp
//
// Unit tests for: Exiv2::imageQuality(const Exiv2::ExifData&)
// Covered file: ./TestProjects/exiv2/src/easyaccess.cpp

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

class ImageQualityTest_517 : public ::testing::Test {
 protected:
  static void AddAscii(Exiv2::ExifData& ed, const std::string& key, const std::string& valueStr) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
    ASSERT_NE(v.get(), nullptr);
    ASSERT_NO_THROW(v->read(valueStr));
    ASSERT_NO_THROW(ed.add(Exiv2::ExifKey(key), v.get()));
  }
};

TEST_F(ImageQualityTest_517, EmptyExifDataReturnsEnd_517) {
  Exiv2::ExifData ed;
  ASSERT_TRUE(ed.empty());

  Exiv2::ExifData::const_iterator it = Exiv2::imageQuality(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(ImageQualityTest_517, UnrelatedTagsReturnEnd_517) {
  Exiv2::ExifData ed;
  AddAscii(ed, "Exif.Image.Make", "DummyCameraBrand");
  AddAscii(ed, "Exif.Photo.UserComment", "hello");

  Exiv2::ExifData::const_iterator it = Exiv2::imageQuality(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(ImageQualityTest_517, FindsCanonCsQualityWhenPresent_517) {
  Exiv2::ExifData ed;
  AddAscii(ed, "Exif.CanonCs.Quality", "Fine");

  Exiv2::ExifData::const_iterator it = Exiv2::imageQuality(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.CanonCs.Quality"));
}

TEST_F(ImageQualityTest_517, FindsKeyNearEndOfKnownList_Casio2Quality_517) {
  Exiv2::ExifData ed;
  AddAscii(ed, "Exif.Casio2.Quality", "Normal");

  Exiv2::ExifData::const_iterator it = Exiv2::imageQuality(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Casio2.Quality"));
}

TEST_F(ImageQualityTest_517, PrefersEarlierKeyWhenMultipleQualityTagsExist_517) {
  Exiv2::ExifData ed;

  // Add multiple known "quality" keys. Observable expectation: the iterator corresponds
  // to the first matching key according to the function's configured key list order.
  AddAscii(ed, "Exif.Sony2.Quality", "ExtraFine");
  AddAscii(ed, "Exif.CanonCs.Quality", "Fine");   // earlier in the list than Sony2.Quality
  AddAscii(ed, "Exif.Fujifilm.Quality", "Normal"); // also early, but after CanonCs.Quality

  Exiv2::ExifData::const_iterator it = Exiv2::imageQuality(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.CanonCs.Quality"));
}

TEST_F(ImageQualityTest_517, WorksWithConstExifDataReference_517) {
  Exiv2::ExifData ed;
  AddAscii(ed, "Exif.Nikon3.Quality", "High");

  const Exiv2::ExifData& ced = ed;
  Exiv2::ExifData::const_iterator it = Exiv2::imageQuality(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Nikon3.Quality"));
}

TEST_F(ImageQualityTest_517, DoesNotThrowOnCall_517) {
  Exiv2::ExifData ed;
  AddAscii(ed, "Exif.Olympus.Quality", "1");

  EXPECT_NO_THROW({
    Exiv2::ExifData::const_iterator it = Exiv2::imageQuality(ed);
    (void)it;
  });
}

}  // namespace