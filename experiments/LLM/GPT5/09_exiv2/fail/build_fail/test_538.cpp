// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::focalLength (easyaccess.cpp)
// The TEST_ID is 538

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

class FocalLengthEasyAccessTest_538 : public ::testing::Test {
 protected:
  static void addURational(Exiv2::ExifData& ed, const std::string& keyStr, const std::string& urationalText) {
    Exiv2::ExifKey key(keyStr);
    auto v = Exiv2::Value::create(Exiv2::unsignedRational);
    ASSERT_NE(v.get(), nullptr);
    ASSERT_NO_THROW(v->read(urationalText));
    ASSERT_NO_THROW(ed.add(key, v.get()));
  }

  static Exiv2::ExifData::const_iterator findKey(const Exiv2::ExifData& ed, const std::string& keyStr) {
    return ed.findKey(Exiv2::ExifKey(keyStr));
  }
};

TEST_F(FocalLengthEasyAccessTest_538, EmptyExifDataReturnsEnd_538) {
  Exiv2::ExifData ed;
  const auto it = Exiv2::focalLength(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(FocalLengthEasyAccessTest_538, NoMatchingKeysReturnsEnd_538) {
  Exiv2::ExifData ed;
  addURational(ed, "Exif.Photo.ExposureTime", "1/60");
  addURational(ed, "Exif.Photo.FNumber", "28/10");

  const auto it = Exiv2::focalLength(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(FocalLengthEasyAccessTest_538, ReturnsIteratorForSinglePresentKey_538) {
  Exiv2::ExifData ed;
  addURational(ed, "Exif.Photo.FocalLength", "50/1");

  const auto it = Exiv2::focalLength(ed);
  ASSERT_NE(it, ed.end());

  const auto expected = findKey(ed, "Exif.Photo.FocalLength");
  ASSERT_NE(expected, ed.end());
  EXPECT_EQ(it, expected);
}

TEST_F(FocalLengthEasyAccessTest_538, PrefersEarlierKeyWhenMultipleKeysPresent_538) {
  Exiv2::ExifData ed;

  // Add multiple candidates; the function should pick a deterministic one.
  addURational(ed, "Exif.Image.FocalLength", "35/1");
  addURational(ed, "Exif.Photo.FocalLength", "85/1");  // Listed before Exif.Image.FocalLength in keys[]
  addURational(ed, "Exif.Canon.FocalLength", "100/1");

  const auto it = Exiv2::focalLength(ed);
  ASSERT_NE(it, ed.end());

  const auto expected = findKey(ed, "Exif.Photo.FocalLength");
  ASSERT_NE(expected, ed.end());
  EXPECT_EQ(it, expected);
}

TEST_F(FocalLengthEasyAccessTest_538, NikonLd4ZeroCanBeSkippedInFavorOfOtherCandidate_538) {
  Exiv2::ExifData ed;

  // This function delegates to findMetadatumSkip0inNikonLd4(...).
  // Observable expectation: if NikonLd4 focal length is effectively "0",
  // another available candidate key may be returned instead.
  addURational(ed, "Exif.NikonLd4.FocalLength2", "0/1");
  addURational(ed, "Exif.Casio2.FocalLength", "24/1");

  const auto it = Exiv2::focalLength(ed);
  ASSERT_NE(it, ed.end());

  const auto casio = findKey(ed, "Exif.Casio2.FocalLength");
  ASSERT_NE(casio, ed.end());
  EXPECT_EQ(it, casio);
}

TEST_F(FocalLengthEasyAccessTest_538, NikonLd4NonZeroIsReturnedWhenItIsOnlyCandidate_538) {
  Exiv2::ExifData ed;
  addURational(ed, "Exif.NikonLd4.FocalLength2", "70/1");

  const auto it = Exiv2::focalLength(ed);
  ASSERT_NE(it, ed.end());

  const auto expected = findKey(ed, "Exif.NikonLd4.FocalLength2");
  ASSERT_NE(expected, ed.end());
  EXPECT_EQ(it, expected);
}

}  // namespace